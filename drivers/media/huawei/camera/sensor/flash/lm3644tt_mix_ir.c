/* Copyright (c) 2011-2019, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "hw_flash.h"
#include <linux/device.h>
#include <linux/pm_wakeup.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>

/* lm3644tt Registers define */
#define LM3644TT_SLAVE_ADDRESS              (0x63)
#define REG_CHIP_ID                         (0x0c)

#define REG_MODE                            0x01
/* LED1 : back flash / torch ; LED2 : front IR flash */
#define REG_L1_FLASH                        0x03
#define REG_L2_FLASH                        0x04
#define REG_L1_TORCH                        0x05
#define REG_L2_TORCH                        0x06
#define REG_FLAGS1                          0x0A
#define REG_FLAGS2                          0x0B
#define REG_FLASH_TIMEOUT                   0x08
#define MODE_TEMP                           0x09
#define MODE_TEMP_VALUE                     0x08

#define LM3644TT_CHIP_ID                    0x04
#define KTD2687_CHIP_ID                     0x02

#define LED2_EN                             (0x1 << 1)
#define LED1_EN                             0x1
#define LED2_DIS                            0xFD
#define LED1_DIS                            0xFF

/* Enable register 0x01 (REG_MODE) */
#define MODE_STANDBY                        (0x00 << 2)
#define MODE_TORCH                          (0x02 << 2)
#define MODE_FLASH                          (0x03 << 2)
#define MODE_IR_DRIVER                      (0x01 << 2)
#define MODE_STANDBY_DISABLE                0xF3

#define STROBE_ENABLE                       (0x01 << 5)
#define STROBE_DISABLE                      0x00

#define INDUCTOR_CURRENT_LIMMIT             0x80
#define FLASH_TIMEOUT_TIME                  0x09 /* 400ms */
#define KTD2687_FLASH_TIMEOUT_TIME          0x0F /* 400ms KTD2687 MAX time-out*/

#define LM3644TT_TORCH_MAX_CUR              360  /* mA */
#define LM3644TT_FLASH_MAX_CUR              1500 /* mA */
#define LM3644TT_TORCH_FRONT_CUR            350 /* mA */

#define LM3644TT_FLASH_DEFAULT_CUR_LEV      63 /* 729mA */
#define LM3644TT_TORCH_DEFAULT_CUR_LEV      63 /* 178.6mA */

#define FLASH_LED_MAX                       128
#define TORCH_LED_MAX                       128
#define FLASH_LED_LEVEL_INVALID             0xff

#define LM3644TT_OVER_VOLTAGE_PROTECT       0x02
#define LM3644TT_LED_OPEN_SHORT             0x70
#define LM3644TT_OVER_TEMP_PROTECT          0x04
#define LM3644TT_OVER_CURRENT_PROTECT       0x10

#define FLASH_CURRENT_TO_LEVEL_TI(x)        (((x) * 1000 - 10900) / 11725)
#define TORCH_CURRENT_TO_LEVEL_TI(x)        (((x) * 1000 - 1954) / 2800)
#define FLASH_CURRENT_TO_LEVEL_KTD2687(x)   (((32 * (x)) / 375) - 1)
#define TORCH_CURRENT_TO_LEVEL_KTD2687(x)   (((256 * (x)) / 375) - 1)
#define FLASH_CURRENT_TO_LEVEL_AW3644(x)    (((x) * 100 - 1135) / 1172)
#define TORCH_CURRENT_TO_LEVEL_AW3644(x)    (((x) * 100 - 255) / 291)

/* lm3644tt_mix_ir define */
#define TOTAL_STEPS_OF_TORCH                8
#define TOTAL_STEPS_OF_FLASH                16
#define INVALID_GPIO                        999
#define LM3644TT_STANDBY_MODE_CUR           (0)
#define WAKE_LOCK_ENABLE                    1
#define WAKE_LOCK_DISABLE                   0
#define UNDER_VOLTAGE_LOCKOUT               0x04
#define COUNT_BASE                          (100)
#define LM3644TT_LED1_BASE_CUR_OF_FLASH     (2304) /* 100ma */
#define LM3644TT_LED1_STEP_CUR_OF_FLASH     (1172) /* 100ma */
#define LM3644TT_LED1_BASE_CUR_OF_TORCH     (253)  /* 100ma */
#define LM3644TT_LED1_STEP_CUR_OF_TORCH     (146)  /* 100ma */
#define LM3644TT_STANDBY_MODE_CUR           (0)
#define REG_MASK_0XFF                       (0xFF)

/* 1 means I2C control, 0 means GPIO control. */
#define LM3644TT_CTRL_TYPE_STROBE           (0)
#define LM3644TT_CTRL_TYPE_I2C              (1)
#define TX_ENABLE                           0x08
#define ENABLE_SHORT_PROTECT                0x80
#define LM3644TT_FLASH_LED_VAL_MASK         (0)
#define LM3644TT_TORCH_LED_VAL_MASK         (0)
#define BACK_FLASH_USE_LED2                 (1)
#define LM3644TT_TORCH_MAX_VAL_SHIFT        (4)
#define MAX_LIGHTNESS_PARAM_NUM_RT          3
#define LIGHTNESS_PARAM_FD_INDEX_RT         0
#define LIGHTNESS_PARAM_MODE_INDEX_RT       1
#define LIGHTNESS_PARAM_CURRENT_INDEX_RT    2
#define MAX_FLASH_ID                        0xFF /* used to check flash_lightness_sotre */
#define MAX_BRIGHTNESS_FORMMI               0x09

#define RETURN_ERROR_IF(x) \
	if ((x)) { \
		cam_err("%s error %s", __func__, #x); \
		return -EINVAL; \
	}

#define RETURN_ERROR_ON_NULL(x) \
	if ((x)==NULL) { \
		cam_err("%s invalid params %s", __func__, #x); \
		return -EINVAL; \
	}

#define LIMITE_VAL_CELLING(x, celling) \
	if ((x) > (celling)) { \
	(x) = (celling); \
	}

#define RETURN_ERROR_OUT_OF_BOUNDS(x, min, max) \
	if (((x) < (min)) || ((x) > (max))) { \
		cam_err("%s out of bounds: %s", __func__, #x); \
		return -EINVAL; \
	}

typedef enum {
	STROBE = 0,
	FLASH_EN,
	TORCH,
	MAX_PIN,
}lm3644tt_mix_ir_pin_type_t;

typedef enum {
	FREED = 0,
	REQUESTED,
}lm3644tt_mix_ir_pin_status_t;

typedef struct {
	unsigned int pin_id;
	lm3644tt_mix_ir_pin_status_t pin_status;
}lm3644tt_mix_ir_pin_t;

typedef enum {
	CURRENT_TORCH_LEVEL_MMI_BACK = 0,
	CURRENT_TORCH_LEVEL_MMI_FRONT = 1,
	CURRENT_TORCH_LEVEL_RT_BACK = 2,
	CURRENT_TORCH_LEVEL_RT_FRONT = 3,
	CURRENT_MIX_MAX = 4,
}lm3644tt_mix_ir_current_conf;

/* flash mode for single front or back */
typedef enum {
	SINGLE_STANDBY_MODE = 0x00,
	SINGLE_FLASH_MODE   = 0x01,
	SINGLE_TORCH_MODE   = 0x02,
	SINGLE_IR_MODE      = 0x03,
}lm3644tt_mix_ir_single_mode_t;

/* flash mode for entire IC which depends on current flash mode of single front and back */
typedef enum {
	ENTIRE_IC_STANDBY_MODE = 0,
	ENTIRE_IC_FLASH_MODE   = 1,
	ENTIRE_IC_TORCH_MODE   = 2,
	ENTIRE_IC_IR_MODE      = 2,
}lm3644tt_mix_ir_entire_ic_mode_t;

/* ir flash RT self test param */
typedef enum {
	IR_SELFTEST_ON_TIME_INDEX  = 0,
	IR_SELFTEST_OFF_TIME_INDEX = 1,
	IR_SELFTEST_CURRENT_INDEX  = 2,
	IR_SELFTEST_TIMES_INDEX    = 3,
	IR_SELFTEST_MAX_INDEX      = 4,
}lm3644tt_mix_ir_selftest_param;

typedef enum {
	TYPE_MIX,
	LM3644TT, /* LM3644TT is 1 */
	AW3644,
	KTD2687,
	TYPE_MAX
}lm3644tt_mix_ir_chip_type_t;

/* Internal data struct define */
struct hw_lm3644tt_mix_ir_private_data_t {
	struct wakeup_source  lm3644tt_mix_ir_wakelock;
	unsigned int need_wakelock;
	/* flash control pin */
	lm3644tt_mix_ir_pin_t pin[MAX_PIN];
	/* flash electric current config */
	unsigned int ecurrent[CURRENT_MIX_MAX];
	unsigned int selftest_param[IR_SELFTEST_MAX_INDEX];
	unsigned int chipid;
	unsigned int ctrltype;
	unsigned int led_type;
	unsigned int front_cur;
	unsigned int back_cur;
	lm3644tt_mix_ir_single_mode_t front_mode;
	lm3644tt_mix_ir_single_mode_t back_mode;
	lm3644tt_mix_ir_entire_ic_mode_t entire_ic_mode;
	lm3644tt_mix_ir_chip_type_t chip_type;
};

/* Internal varible define */
static struct hw_lm3644tt_mix_ir_private_data_t hw_lm3644tt_mix_ir_pdata;
extern struct hw_flash_ctrl_t hw_lm3644tt_mix_ir_ctrl;
extern struct dsm_client *client_flash;

DEFINE_HISI_FLASH_MUTEX(lm3644tt_mix_ir);

/* Function define */
static int hw_lm3644tt_mix_ir_param_check(char *buf, unsigned long *param,
	int num_of_par);
static int hw_lm3644tt_mix_ir_set_pin(struct hw_flash_ctrl_t   *flash_ctrl,
	lm3644tt_mix_ir_pin_type_t  pin_type, int state)
{
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;
	int rc = 0;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);
	RETURN_ERROR_IF((pin_type<STROBE||pin_type>=MAX_PIN));

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;
	cam_debug("%s pin-type=%d, state=%d", __func__, pin_type, state);

	if ((INVALID_GPIO != pdata->pin[pin_type].pin_id)
		&& (REQUESTED == pdata->pin[pin_type].pin_status)) {
		rc = gpio_direction_output(pdata->pin[pin_type].pin_id, state);
		if (rc < 0)
			cam_err("%s gpio output is err rc=%d", __func__, rc);
	}

	return rc;
}

static int gpio_request_assemble(struct hw_lm3644tt_mix_ir_private_data_t *pdata)
{
	int i  = 0;
	int rc = 0;
	const char* gpio_name[MAX_PIN]= {"flash-strobe", "flash-en", "flash-torch"};

	RETURN_ERROR_ON_NULL(pdata);

	for (i = STROBE; i < MAX_PIN; i++) {
		if ((INVALID_GPIO != pdata->pin[i].pin_id)
			&& (FREED == pdata->pin[i].pin_status)) {
			rc = gpio_request(pdata->pin[i].pin_id, gpio_name[i]);
			if (rc < 0) {
				cam_err("%s failed to request pin %s", __func__, gpio_name[i]);
				break;
			} else {
				pdata->pin[i].pin_status = REQUESTED;
			}
		}
	}

	return rc;
}

static int gpio_free_assemble(struct hw_lm3644tt_mix_ir_private_data_t *pdata)
{
	int i = 0;

	RETURN_ERROR_ON_NULL(pdata);

	for (i = STROBE; i < MAX_PIN; i++) {
		if ((INVALID_GPIO != pdata->pin[i].pin_id)
			&& (REQUESTED == pdata->pin[i].pin_status)) {
			gpio_free(pdata->pin[i].pin_id);
			pdata->pin[i].pin_status = FREED;
		}
	}

	return 0;
}

static int hw_lm3644tt_mix_ir_init(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;
	int rc = 0;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);

	/* init data */
	flash_ctrl->flash_type = FLASH_MIX; /* mix flash */
	flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
		 PINCTRL_STATE_DEFAULT);
	RETURN_ERROR_ON_NULL(flash_ctrl->pctrl);

	/* stub:check other params which need to init */
	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;
	pdata->front_cur = LM3644TT_STANDBY_MODE_CUR; /* init current as 0 */
	pdata->back_cur  = LM3644TT_STANDBY_MODE_CUR; /* init current as 0 */
	pdata->front_mode = SINGLE_STANDBY_MODE;
	pdata->back_mode  = SINGLE_STANDBY_MODE;
	pdata->entire_ic_mode = ENTIRE_IC_STANDBY_MODE;
	flash_ctrl->state.mode = STANDBY_MODE;
	flash_ctrl->state.data = LM3644TT_STANDBY_MODE_CUR; /* set init value 0 */

	rc = gpio_request_assemble(pdata);
	if (rc < 0) {
		cam_err("%s failde to request gpio", __func__);
		goto gpio_fail_handler;
	}

	rc = hw_lm3644tt_mix_ir_set_pin(flash_ctrl, FLASH_EN, LOW);
	if (rc < 0) {
		cam_err("%s failed to set flash_en pin", __func__);
		goto gpio_fail_handler;
	}

	if (WAKE_LOCK_ENABLE == pdata->need_wakelock)
		wakeup_source_init(&pdata->lm3644tt_mix_ir_wakelock,"lm3644tt_mix_ir");

	return rc;

gpio_fail_handler:
	gpio_free_assemble(pdata);
	return rc;
}

static int hw_lm3644tt_mix_ir_exit(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;

	cam_debug("%s enter", __func__);

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);
	RETURN_ERROR_ON_NULL(flash_ctrl->func_tbl);
	RETURN_ERROR_ON_NULL(flash_ctrl->func_tbl->flash_off);

	flash_ctrl->func_tbl->flash_off(flash_ctrl);
	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;
	gpio_free_assemble(pdata);

	flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
		PINCTRL_STATE_IDLE);

	return 0;
}

static void report_dsm(void)
{
	if (!dsm_client_ocuppy(client_flash)) {
		dsm_client_record(client_flash, "flash i2c transfer fail\n");
		dsm_client_notify(client_flash, DSM_FLASH_I2C_ERROR_NO);
		cam_warn("[I/DSM] %s dsm_client_notify", client_flash->client_name);
	}
}

static void check_fault_and_report_dsm(unsigned char fault_val)
{
	if (fault_val & (LM3644TT_OVER_VOLTAGE_PROTECT | LM3644TT_OVER_CURRENT_PROTECT)) {
		if (!dsm_client_ocuppy(client_flash)) {
			dsm_client_record(client_flash, "flash OVP or OCP! FlagReg1[0x%x]\n", fault_val);
			dsm_client_notify(client_flash, DSM_FLASH_OPEN_SHOTR_ERROR_NO);
			cam_warn("[I/DSM] %s dsm_client_notify", client_flash->client_name);
		}
	}
	if (fault_val & LM3644TT_OVER_TEMP_PROTECT) {
		if (!dsm_client_ocuppy(client_flash)) {
			dsm_client_record(client_flash, "flash temperature is too hot! FlagReg1[0x%x]\n", fault_val);
			dsm_client_notify(client_flash, DSM_FLASH_HOT_DIE_ERROR_NO);
			cam_warn("[I/DSM] %s dsm_client_notify", client_flash->client_name);
		}
	}
	if (fault_val & UNDER_VOLTAGE_LOCKOUT) {
		if (!dsm_client_ocuppy(client_flash)) {
			dsm_client_record(client_flash, "flash UVLO! FlagReg1[0x%x]\n", fault_val);
			dsm_client_notify(client_flash, DSM_FLASH_UNDER_VOLTAGE_LOCKOUT_ERROR_NO);
			cam_warn("[I/DSM] %s dsm_client_notify", client_flash->client_name);
		}
	}
}

static int hw_lm3644tt_mix_ir_flash_mode_cfg_calculate(unsigned char *led1_val,
	unsigned char *led2_val,
	unsigned char *reg_mode,
	struct hw_lm3644tt_mix_ir_private_data_t *pdata,
	struct hw_flash_cfg_data *cdata)
{
	unsigned int led1_cur  = 0;
	unsigned int led2_cur  = 0;
	unsigned int front_cur = 0;
	unsigned int back_cur  = 0;
	unsigned int led1_cur_calc  = 0;
	unsigned int led2_cur_calc  = 0;

	RETURN_ERROR_ON_NULL(led1_val);
	RETURN_ERROR_ON_NULL(reg_mode);
	RETURN_ERROR_ON_NULL(pdata);

	front_cur = pdata->front_cur;
	back_cur  = pdata->back_cur;

	if ( front_cur == FLASH_LED_LEVEL_INVALID )
		front_cur = LM3644TT_FLASH_DEFAULT_CUR_LEV;
	if ( back_cur == FLASH_LED_LEVEL_INVALID )
		back_cur = LM3644TT_FLASH_DEFAULT_CUR_LEV;

	/* driver ic : LM3644TT : 1, AW3644 : 2, KTD2687 : 3 */
	cam_info("%s led_type = %d, flash driver ic is %u", __func__,
		pdata->led_type, hw_lm3644tt_mix_ir_pdata.chip_type);
	if ( BACK_FLASH_USE_LED2 == pdata->led_type ) {
		led1_cur = front_cur;
		led2_cur = back_cur;
	} else {
		led1_cur = back_cur;
		led2_cur = front_cur;
	}

	switch (hw_lm3644tt_mix_ir_pdata.chip_type) {
	case KTD2687:
		led1_cur_calc = FLASH_CURRENT_TO_LEVEL_KTD2687(led1_cur);
		led2_cur_calc = FLASH_CURRENT_TO_LEVEL_KTD2687(led2_cur);
		break;
	case LM3644TT:
		led1_cur_calc = FLASH_CURRENT_TO_LEVEL_TI(led1_cur);
		led2_cur_calc = FLASH_CURRENT_TO_LEVEL_TI(led2_cur);
		break;
	case AW3644:
		led1_cur_calc = FLASH_CURRENT_TO_LEVEL_AW3644(led1_cur);
		led2_cur_calc = FLASH_CURRENT_TO_LEVEL_AW3644(led2_cur);
		break;
	default:
		led1_cur_calc = FLASH_CURRENT_TO_LEVEL_TI(led1_cur);
		led2_cur_calc = FLASH_CURRENT_TO_LEVEL_TI(led2_cur);
		break;
	}

	if ((LM3644TT_STANDBY_MODE_CUR != led1_cur) && (LM3644TT_STANDBY_MODE_CUR == led2_cur)) {
		/* using LED1 only */
		/* LED1 = flash1 current value ; disable LED2 reg bit */
		*reg_mode = ((LED1_EN | MODE_FLASH) & LED2_DIS);
		*led1_val = led1_cur_calc;
		*led2_val = LM3644TT_FLASH_LED_VAL_MASK;
	} else if ((LM3644TT_STANDBY_MODE_CUR == led1_cur) && (LM3644TT_STANDBY_MODE_CUR != led2_cur)) {
		/* using LED2 only*/
		/* LED2 = falsh2 current value ; disable LED1 reg bit */
		*reg_mode = ((LED2_EN | MODE_FLASH) & LED1_DIS);
		*led1_val = LM3644TT_FLASH_LED_VAL_MASK;
		*led2_val = led2_cur_calc;
	} else if ((LM3644TT_STANDBY_MODE_CUR != led1_cur) && (LM3644TT_STANDBY_MODE_CUR != led2_cur)) {
		/* using LED1 & LED2 */
		/* LED1 & LED2 = enable LED1 & LED2 reg bit, set two flashs current value */
		*reg_mode = (LED1_EN | LED2_EN | MODE_FLASH);
		*led1_val = led1_cur_calc;
		*led2_val = led2_cur_calc;
	} else {
		cam_err("%s flash current error LED1=%d LED2=%d", __func__, led1_cur, led2_cur);
		return -EINVAL;
	}
	/* strobe mode enter */
	if ((FLASH_STROBE_MODE == cdata->mode) && /* flash strobe mode */
		(LM3644TT_CTRL_TYPE_STROBE == pdata->ctrltype) && /* DTS config the stobe pin */
		(LM3644TT_STANDBY_MODE_CUR == front_cur)) /* is not using front flash */
		*reg_mode = (*reg_mode | STROBE_ENABLE) & MODE_STANDBY_DISABLE;
	else /* I2C mode */
		*reg_mode |= STROBE_DISABLE;

	return 0;
}

static int hw_lm3644tt_mix_ir_torch_mode_cfg_calculate(unsigned char *led1_val,
	unsigned char *led2_val,
	unsigned char *reg_mode,
	struct hw_lm3644tt_mix_ir_private_data_t *pdata)
{
	unsigned int led1_cur  = 0;
	unsigned int led2_cur  = 0;
	unsigned int front_cur = 0;
	unsigned int back_cur  = 0;
	unsigned int led1_cur_calc  = 0;
	unsigned int led2_cur_calc  = 0;

	RETURN_ERROR_ON_NULL(led1_val);
	RETURN_ERROR_ON_NULL(led2_val);
	RETURN_ERROR_ON_NULL(reg_mode);
	RETURN_ERROR_ON_NULL(pdata);

	front_cur = pdata->front_cur;
	back_cur  = pdata->back_cur;

	if ( front_cur == FLASH_LED_LEVEL_INVALID )
		front_cur = LM3644TT_TORCH_DEFAULT_CUR_LEV;
	if ( back_cur == FLASH_LED_LEVEL_INVALID )
		back_cur = LM3644TT_TORCH_DEFAULT_CUR_LEV;

	/* driver ic : LM3644TT : 1, AW3644 : 2, KTD2687 : 3 */
	cam_info("%s led_type = %d, flash driver ic is %u", __func__,
		pdata->led_type, hw_lm3644tt_mix_ir_pdata.chip_type);
	if (BACK_FLASH_USE_LED2 == pdata->led_type) { /* check hardware menu and check DTS !!!!! */
		led1_cur = front_cur;
		led2_cur = back_cur;
	} else {
		led1_cur = back_cur;
		led2_cur = front_cur;
	}

	switch (hw_lm3644tt_mix_ir_pdata.chip_type) {
	case KTD2687:
		led1_cur_calc = TORCH_CURRENT_TO_LEVEL_KTD2687(led1_cur);
		led2_cur_calc = TORCH_CURRENT_TO_LEVEL_KTD2687(led2_cur);
		break;
	case LM3644TT:
		led1_cur_calc = TORCH_CURRENT_TO_LEVEL_TI(led1_cur);
		led2_cur_calc = TORCH_CURRENT_TO_LEVEL_TI(led2_cur);
		break;
	case AW3644:
		led1_cur_calc = TORCH_CURRENT_TO_LEVEL_AW3644(led1_cur);
		led2_cur_calc = TORCH_CURRENT_TO_LEVEL_AW3644(led2_cur);
		break;
	default:
		led1_cur_calc = TORCH_CURRENT_TO_LEVEL_TI(led1_cur);
		led2_cur_calc = TORCH_CURRENT_TO_LEVEL_TI(led2_cur);
		break;
	}

	if ((LM3644TT_STANDBY_MODE_CUR != led1_cur) && (LM3644TT_STANDBY_MODE_CUR == led2_cur)) {
		/* using LED1 only */
		/* LED1 = torch1 current Value ; disable LED2 reg bit */
		*reg_mode = ((LED1_EN | MODE_TORCH) & LED2_DIS);
		*led1_val = led1_cur_calc;
		*led2_val = LM3644TT_TORCH_LED_VAL_MASK;
	} else if ((LM3644TT_STANDBY_MODE_CUR == led1_cur) && (LM3644TT_STANDBY_MODE_CUR != led2_cur)) {
		/* using LED2 only*/
		/* LED2 = torch2 current Value ; disable LED1 reg bit */
		*reg_mode = ((LED2_EN | MODE_TORCH) & LED1_DIS);
		*led1_val = LM3644TT_TORCH_LED_VAL_MASK;
		*led2_val = led2_cur_calc;
	} else if ((LM3644TT_STANDBY_MODE_CUR != led1_cur) && (LM3644TT_STANDBY_MODE_CUR != led2_cur)) {
		/* using LED1 & LED2 */
		/* LED1 & LED2 = enable LED1 & LED2 reg bit, set two torchs current Value */
		*reg_mode = (LED1_EN | LED2_EN | MODE_TORCH);
		*led1_val = led1_cur_calc;
		*led2_val = led2_cur_calc;
	} else {
		cam_err("%s flash current error LED1=%d LED2=%d", __func__, led1_cur, led2_cur);
		return -EINVAL;
	}
	/* touch I2C mode */
	*reg_mode |= STROBE_DISABLE;

	return 0;
}

static int hw_lm3644tt_mix_ir_flash_mode_regs_cfg(struct hw_flash_ctrl_t *flash_ctrl,
	unsigned char led1_val,
	unsigned char led2_val,
	unsigned char reg_mode)
{
	int rc = 0;
	unsigned char reg_fault_clean  = 0;
	struct hw_flash_i2c_fn_t   *i2c_func   = NULL;
	struct hw_flash_i2c_client *i2c_client = NULL;
	int flash_time = 0;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl->i2c_read);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl->i2c_write);

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func   = i2c_client->i2c_func_tbl;

	/* clear error status */
	i2c_func->i2c_read(i2c_client, REG_FLAGS1, &reg_fault_clean);
	check_fault_and_report_dsm(reg_fault_clean);
	i2c_func->i2c_read(i2c_client, REG_FLAGS2, &reg_fault_clean);

	switch (hw_lm3644tt_mix_ir_pdata.chip_type) {
	case KTD2687:
		flash_time = KTD2687_FLASH_TIMEOUT_TIME;
		break;
	case LM3644TT:
	case AW3644:
		flash_time = FLASH_TIMEOUT_TIME;
		break;
	default:
		flash_time = FLASH_TIMEOUT_TIME;
		break;
	}
	rc |= i2c_func->i2c_write(i2c_client, REG_FLASH_TIMEOUT, flash_time);
	rc |= i2c_func->i2c_write(i2c_client, REG_L1_FLASH, led1_val);
	rc |= i2c_func->i2c_write(i2c_client, REG_L2_FLASH, led2_val);
	rc |= i2c_func->i2c_write(i2c_client, REG_MODE, reg_mode);

	cam_info("%s config flash1_val = 0x%02x, flash2_val = 0x%02x, reg_mode = 0x%02x",
		__func__, led1_val, led2_val, reg_mode);

	if (rc < 0)
		report_dsm();

	return rc;
}

static int hw_lm3644tt_mix_ir_torch_mode_regs_cfg(struct hw_flash_ctrl_t *flash_ctrl,
	unsigned char led1_val,
	unsigned char led2_val,
	unsigned char reg_mode)
{
	int rc = 0;
	unsigned char reg_fault_clean  = 0;
	struct hw_flash_i2c_fn_t   *i2c_func   = NULL;
	struct hw_flash_i2c_client *i2c_client = NULL;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl->i2c_read);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl->i2c_write);

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func   = i2c_client->i2c_func_tbl;

	/* clear error status */
	i2c_func->i2c_read(i2c_client, REG_FLAGS1, &reg_fault_clean);
	check_fault_and_report_dsm(reg_fault_clean);
	i2c_func->i2c_read(i2c_client, REG_FLAGS2, &reg_fault_clean);

	rc |= i2c_func->i2c_write(i2c_client, REG_L1_TORCH, led1_val);
	rc |= i2c_func->i2c_write(i2c_client, REG_L2_TORCH, led2_val);
	rc |= i2c_func->i2c_write(i2c_client, REG_MODE, reg_mode);

	cam_info("%s config torch1_val = 0x%02x, torch2_val = 0x%02x, reg_mode = 0x%02x",
		__func__, led1_val, led2_val, reg_mode);

	if (rc < 0)
		report_dsm();

	return rc;
}

static int hw_lm3644tt_mix_ir_action_ic_standby(struct hw_flash_ctrl_t *flash_ctrl)
{
	int rc = 0;
	unsigned char reg_fault_clean = 0;
	struct hw_flash_i2c_fn_t   *i2c_func   = NULL;
	struct hw_flash_i2c_client *i2c_client = NULL;
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl->i2c_read);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl->i2c_write);

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;
	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = i2c_client->i2c_func_tbl;

	/* read back error status */
	i2c_func->i2c_read(i2c_client, REG_FLAGS1, &reg_fault_clean);
	check_fault_and_report_dsm(reg_fault_clean);
	i2c_func->i2c_read(i2c_client, REG_FLAGS2, &reg_fault_clean);

	rc |= i2c_func->i2c_write(i2c_client, REG_MODE, MODE_STANDBY);

	if (rc < 0)
		report_dsm();

	rc |= hw_lm3644tt_mix_ir_set_pin(flash_ctrl, STROBE, LOW);
	rc |= hw_lm3644tt_mix_ir_set_pin(flash_ctrl, TORCH, LOW);
	rc |= hw_lm3644tt_mix_ir_set_pin(flash_ctrl, FLASH_EN, LOW);

	if (pdata->need_wakelock == WAKE_LOCK_ENABLE)
		/**
		 * wake_unlock() will check whether the wakeup source is active before
		 * doing the unlock operation, so there is no dangers for the mutex being
		 * unlocked before locked.
		 */
		__pm_relax(&pdata->lm3644tt_mix_ir_wakelock);/*lint !e455*/

	return rc;
}

static int hw_lm3644tt_mix_ir_action_ic_flash_mode(struct hw_flash_ctrl_t *flash_ctrl, struct hw_flash_cfg_data *cdata)
{
	int rc = 0;
	unsigned char reg_mode  = 0;
	unsigned char led1_val  = 0;
	unsigned char led2_val  = 0;
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;

	hw_lm3644tt_mix_ir_set_pin(flash_ctrl, FLASH_EN,  HIGH);
	hw_lm3644tt_mix_ir_set_pin(flash_ctrl, STROBE, LOW);
	hw_lm3644tt_mix_ir_set_pin(flash_ctrl, TORCH,  LOW);

	rc = hw_lm3644tt_mix_ir_flash_mode_cfg_calculate(&led1_val, &led2_val, &reg_mode, pdata, cdata);
	if (rc < 0) {
		 cam_err("%s flash mode cfg calculate faild", __func__);
		return rc;
	}

	rc = hw_lm3644tt_mix_ir_flash_mode_regs_cfg(flash_ctrl, led1_val, led2_val, reg_mode);
	if (rc < 0) {
		cam_err("%s flash mode regs cfg faild", __func__);
		return rc;
	}

	return rc;
}

static int hw_lm3644tt_mix_ir_action_ic_torch_mode(struct hw_flash_ctrl_t *flash_ctrl)
{

	int rc = 0;
	unsigned char led1_val = 0;
	unsigned char led2_val = 0;
	unsigned char reg_mode = 0;
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;

	hw_lm3644tt_mix_ir_set_pin(flash_ctrl, FLASH_EN,  HIGH);
	hw_lm3644tt_mix_ir_set_pin(flash_ctrl, STROBE, LOW);
	hw_lm3644tt_mix_ir_set_pin(flash_ctrl, TORCH,  LOW);

	rc = hw_lm3644tt_mix_ir_torch_mode_cfg_calculate(&led1_val, &led2_val, &reg_mode, pdata);
	if (rc < 0) {
		cam_err("%s torch mode cfg calculate faild", __func__);
		return rc;
	}

	rc = hw_lm3644tt_mix_ir_torch_mode_regs_cfg(flash_ctrl, led1_val, led2_val, reg_mode);
	if (rc < 0) {
		cam_err("%s torch mode reg cfg faild", __func__);
		return rc;
	}

	hw_lm3644tt_mix_ir_set_pin(flash_ctrl, TORCH,  HIGH);

	return rc;
}

static int hw_lm3644tt_mix_ir_update_inner_status(struct hw_flash_ctrl_t *flash_ctrl,
	struct hw_flash_cfg_data *cdata)
{
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;
	lm3644tt_mix_ir_single_mode_t inner_mode  = SINGLE_STANDBY_MODE;
	unsigned int cur = 0;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(cdata);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;
	cur   = (unsigned int)(cdata->data);

	switch(cdata->mode) {
	case STANDBY_MODE:
		inner_mode = SINGLE_STANDBY_MODE;
		/* flash_ctrl->state will be update when ic standby mode cfg is finished */
		break;
	case FLASH_MODE:
	case FLASH_STROBE_MODE:
		inner_mode = SINGLE_FLASH_MODE;
		/* flash_ctrl->state will be update here, and may be used in thermal protect */
		flash_ctrl->state.mode = cdata->mode;
		flash_ctrl->state.data = cdata->data;
		break;
	default:
		inner_mode = SINGLE_TORCH_MODE; /* set as default */
		/* flash_ctrl->state will be update here, and may be used in thermal protect */
		flash_ctrl->state.mode = cdata->mode;
		flash_ctrl->state.data = cdata->data;
		break;
	}

	if (HWFLASH_POSITION_FORE == flash_ctrl->mix_pos) {
		pdata->front_mode = inner_mode;
		pdata->front_cur  = cur;
		cam_info("%s update front mode:%d, front cur %u", __func__,
			pdata->front_mode, pdata->front_cur);
	} else {
		pdata->back_mode  = inner_mode;
		pdata->back_cur   = cur;
		cam_info("%s update back mode:%d, back cur %u",  __func__,
			pdata->back_mode, pdata->back_cur);
	}

	return 0;
}

static int hw_lm3644tt_mix_ir_get_work_mode_strategy(struct hw_flash_ctrl_t *flash_ctrl,
	lm3644tt_mix_ir_entire_ic_mode_t *ic_work_mode)
{
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;
	lm3644tt_mix_ir_single_mode_t front_mode = SINGLE_STANDBY_MODE;
	lm3644tt_mix_ir_single_mode_t back_mode  = SINGLE_STANDBY_MODE;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(ic_work_mode);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;
	front_mode = pdata->front_mode;
	back_mode  = pdata->back_mode;

	*ic_work_mode = ENTIRE_IC_STANDBY_MODE; /* set as default */

	if ((front_mode | back_mode) == SINGLE_STANDBY_MODE) {
		*ic_work_mode = ENTIRE_IC_STANDBY_MODE;
	} else if (((front_mode | back_mode) & SINGLE_FLASH_MODE) == SINGLE_FLASH_MODE) {
		*ic_work_mode = ENTIRE_IC_FLASH_MODE;
	} else if (((front_mode | back_mode) & SINGLE_TORCH_MODE) == SINGLE_TORCH_MODE) {
		*ic_work_mode = ENTIRE_IC_TORCH_MODE;
	}

	if (hw_lm3644tt_mix_ir_pdata.chip_type == LM3644TT)
		if (((front_mode & SINGLE_FLASH_MODE) == SINGLE_FLASH_MODE) &&
			((back_mode & SINGLE_TORCH_MODE) == SINGLE_TORCH_MODE)) {
			/*
			 * this part is only for lm3644tt, when this type flash-light run faceid task,
			 * the front mode and back mode turn to torch mode, and front current is 350mA,
			 * back current is still 120mA.
			 */
			cam_info("%s LM3644TT back mode is troch mode, front flash mode need to change to front torch mode", __func__);
			*ic_work_mode = ENTIRE_IC_TORCH_MODE;
			pdata->front_cur = LM3644TT_TORCH_FRONT_CUR;
		}

	if (LM3644TT_STANDBY_MODE_CUR == pdata->front_cur
		&& LM3644TT_STANDBY_MODE_CUR == pdata->back_cur)
		*ic_work_mode = ENTIRE_IC_STANDBY_MODE;

	return 0;
}

static int hw_lm3644tt_mix_ir_update_work_mode_dispatch(struct hw_flash_ctrl_t *flash_ctrl,
	lm3644tt_mix_ir_entire_ic_mode_t ic_work_mode,
	struct hw_flash_cfg_data *cdata)
{
	int rc = 0;
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;

	switch(ic_work_mode) {
	case ENTIRE_IC_STANDBY_MODE:
		if (ENTIRE_IC_STANDBY_MODE != pdata->entire_ic_mode) {
			/* only when current mode is not in standby, action the standby mode */
			rc = hw_lm3644tt_mix_ir_action_ic_standby(flash_ctrl);
			pdata->entire_ic_mode  = ENTIRE_IC_STANDBY_MODE;
			flash_ctrl->state.mode = STANDBY_MODE;
			flash_ctrl->state.data = LM3644TT_STANDBY_MODE_CUR;
		}
		break;
	case ENTIRE_IC_FLASH_MODE:
		rc = hw_lm3644tt_mix_ir_action_ic_flash_mode(flash_ctrl, cdata);
		pdata->entire_ic_mode = ENTIRE_IC_FLASH_MODE;
		break;
	case ENTIRE_IC_TORCH_MODE:
		rc = hw_lm3644tt_mix_ir_action_ic_torch_mode(flash_ctrl);
		pdata->entire_ic_mode = ENTIRE_IC_TORCH_MODE;
		break;
	default:
		cam_err("%s invalid ic work mode", __func__);
		rc = -EINVAL;
		break;
	}

	return rc;
}

static int hw_lm3644tt_mix_ir_update_work_mode(struct hw_flash_ctrl_t *flash_ctrl,
	struct hw_flash_cfg_data *cdata)
{
	int rc = 0;
	lm3644tt_mix_ir_entire_ic_mode_t ic_work_mode = ENTIRE_IC_STANDBY_MODE;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(cdata);

	rc = hw_lm3644tt_mix_ir_update_inner_status(flash_ctrl, cdata);
	if (rc < 0) {
		cam_err("%s update inner status failed", __func__);
		goto work_mode_err;
	}

	rc = hw_lm3644tt_mix_ir_get_work_mode_strategy(flash_ctrl, &ic_work_mode);
	if (rc < 0) {
		cam_err("%s get work mode strategy failed", __func__);
		goto work_mode_err;
	}

	rc = hw_lm3644tt_mix_ir_update_work_mode_dispatch(flash_ctrl, ic_work_mode, cdata);
	if (rc < 0) {
		cam_err("%s update work mode dispatch failed", __func__);
		goto work_mode_err;
	}

	return rc;

work_mode_err:
	/* error handler may need to add here */
	return rc;
}

static int hw_lm3644tt_mix_ir_on(struct hw_flash_ctrl_t *flash_ctrl, void *data)
{
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;
	struct hw_flash_cfg_data *cdata = NULL;
	int rc = 0;

	RETURN_ERROR_ON_NULL(data);
	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);

	cdata = (struct hw_flash_cfg_data *)data;
	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;

	cam_info("%s mode=%d, cur=%d", __func__, cdata->mode, cdata->data);

	mutex_lock(flash_ctrl->hw_flash_mutex);

	if (pdata->need_wakelock == WAKE_LOCK_ENABLE)
		/**
		 * if the wake lock source has already been active, repeat call of
		 * 'wake_lock' will just add the event_count of the wake lock source,
		 * and will not cause evil effects.
		 */
		__pm_stay_awake(&pdata->lm3644tt_mix_ir_wakelock);

	rc = hw_lm3644tt_mix_ir_update_work_mode(flash_ctrl,cdata);

	mutex_unlock(flash_ctrl->hw_flash_mutex);

	return rc;
}

static int hw_lm3644tt_mix_ir_off(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_flash_cfg_data cdata = {0};
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;
	int rc = 0;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);

	cam_debug("%s enter", __func__);

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;
	cdata.mode = (flash_mode)SINGLE_STANDBY_MODE;
	cdata.data = LM3644TT_STANDBY_MODE_CUR; /* set standby current as 0 */

	mutex_lock(flash_ctrl->hw_flash_mutex);
	rc = hw_lm3644tt_mix_ir_update_work_mode(flash_ctrl,&cdata);
	mutex_unlock(flash_ctrl->hw_flash_mutex);

	cam_info("%s end", __func__);

	return rc;
}

static int hw_lm3644tt_mix_ir_get_dt_data(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;
	struct device_node *node = NULL;
	int i  = 0;
	int rc = -EINVAL;
	unsigned int pin_tmp[MAX_PIN] = {0};

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);
	RETURN_ERROR_ON_NULL(flash_ctrl->dev);
	RETURN_ERROR_ON_NULL(flash_ctrl->dev->of_node);

	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;
	node = flash_ctrl->dev->of_node;

	rc = of_property_read_u32_array(node, "huawei,flash-pin",
			pin_tmp, (unsigned long)MAX_PIN);
	if (rc < 0) {
		cam_err("%s get dt flash-pin failed line %d", __func__, __LINE__);
		/* if failed, init gpio num as invalid */
		for (i = 0; i < MAX_PIN; i++) {
			pdata->pin[i].pin_id = INVALID_GPIO;
			pdata->pin[i].pin_status = FREED;
		}
		return rc;
	} else {
		for (i = 0; i < MAX_PIN; i++) {
			pdata->pin[i].pin_id = pin_tmp[i];
			pdata->pin[i].pin_status = FREED;
			cam_info("%s pin[%d]=%u", __func__, i, pdata->pin[i].pin_id);
		}
	}

	rc = of_property_read_u32(node, "huawei,flash-chipid",
			&pdata->chipid);
	cam_info("%s hisi,chipid 0x%x, rc %d", __func__,
			pdata->chipid, rc);
	if (rc < 0) {
		cam_err("%s failed %d", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(node, "huawei,flash-ctrltype",
			&pdata->ctrltype);
	cam_info("%s hisi,ctrltype 0x%x, rc %d", __func__,
			pdata->ctrltype, rc);
	if (rc < 0) {
		cam_err("%s failed %d", __func__, __LINE__);
		return rc;
	} else if (pdata->pin[STROBE].pin_id != INVALID_GPIO) {
		pdata->ctrltype = LM3644TT_CTRL_TYPE_STROBE;
		cam_info("%s ctrltype change 0x%x", __func__, pdata->ctrltype);
	}

	rc = of_property_read_u32(node, "huawei,led-type", &pdata->led_type);
	cam_info("%s huawei,led-type %d, rc %d\n", __func__, pdata->led_type, rc);
	if (rc < 0) {
		cam_err("%s read led-type failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(node, "huawei,need-wakelock", (u32 *)&pdata->need_wakelock);
	cam_info("%s huawei,need-wakelock %d, rc %d\n", __func__, pdata->need_wakelock, rc);
	if (rc < 0) {
		pdata->need_wakelock = WAKE_LOCK_DISABLE;
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32_array(node, "huawei,flash-current",
			pdata->ecurrent, CURRENT_MIX_MAX);
	if (rc < 0) {
		cam_err("%s read flash-current failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i = 0; i < CURRENT_MIX_MAX; i++)
			cam_info("%s ecurrent[%d]=%d.\n", __func__, i, pdata->ecurrent[i]);
	}

	rc = of_property_read_u32_array(node, "huawei,selftest-param",
		pdata->selftest_param, IR_SELFTEST_MAX_INDEX);
	if (rc < 0) {
		cam_err("%s read selftest-param failed line %d\n", __func__, __LINE__);
		return rc;
	} else {
		for (i = 0; i < IR_SELFTEST_MAX_INDEX; i++)
			cam_info("%s selftest_param[%d]=%d.\n", __func__, i,
			pdata->selftest_param[i]);
	}

	return rc;
}

static ssize_t hw_lm3644tt_mix_ir_flash_lightness_show(struct device *dev,
	struct device_attribute *attr,
	char *buf)
{
	int rc = 0;
	RETURN_ERROR_ON_NULL(buf);

	/* PAGE_SIZE = 4096 */
	rc = scnprintf(buf, PAGE_SIZE, "front_mode=%d, data=%d; back_mode=%d, data=%d.\n",
		hw_lm3644tt_mix_ir_pdata.front_mode, hw_lm3644tt_mix_ir_pdata.front_cur,
		hw_lm3644tt_mix_ir_pdata.back_mode,  hw_lm3644tt_mix_ir_pdata.back_cur);

	return rc;
}

static ssize_t hw_lm3644tt_mix_ir_flash_lightness_show_f(struct device *dev,
	struct device_attribute *attr,
	char *buf)
{
	int rc = 0;
	RETURN_ERROR_ON_NULL(buf);

	/* show for ir selftest in RT,PAGE_SIZE = 4096 */
	rc = scnprintf(buf, PAGE_SIZE, "%d %d %d %d",
		hw_lm3644tt_mix_ir_pdata.selftest_param[IR_SELFTEST_ON_TIME_INDEX],
		hw_lm3644tt_mix_ir_pdata.selftest_param[IR_SELFTEST_OFF_TIME_INDEX],
		hw_lm3644tt_mix_ir_pdata.selftest_param[IR_SELFTEST_CURRENT_INDEX],
		hw_lm3644tt_mix_ir_pdata.selftest_param[IR_SELFTEST_TIMES_INDEX]);

	return rc;
}

static int hw_lm3644tt_mix_ir_param_check(char *buf, unsigned long *param, int num_of_par)
{
	char *token = NULL;
	unsigned int base = 0;
	int cnt = 0;

	RETURN_ERROR_ON_NULL(buf);
	RETURN_ERROR_ON_NULL(param);

	token = strsep(&buf, " ");

	for (cnt = 0; cnt < num_of_par; cnt++) {
		if (token != NULL) {
			if (strlen(token) < 2) { /* add for check token[1] has valid element */
				base = 10; /* decimal */
			} else {
				/* format 0x** */
				if ((token[1] == 'x') || (token[1] == 'X')) {
					base = 16; /* hex */
				} else {
					base = 10; /* decimal */
				}
			}
			if (strict_strtoul(token, base, &param[cnt]) != 0) {
				return -EINVAL;
			}
			token = strsep(&buf, " ");
		} else{
			cam_info("%s the %d param is null\n", __func__, num_of_par);
		}
	}

	return 0;
}

static ssize_t hw_lm3644tt_mix_ir_flash_lightness_store_imp(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct hw_flash_cfg_data cdata = {0};
	unsigned long param[MAX_LIGHTNESS_PARAM_NUM_RT]={0};
	int rc = 0;
	int flash_id = 0;

	RETURN_ERROR_ON_NULL(buf);

	rc = hw_lm3644tt_mix_ir_param_check((char *)buf, param, MAX_LIGHTNESS_PARAM_NUM_RT);
	if (rc < 0) {
		cam_err("%s failed to check param", __func__);
		return rc;
	}

	flash_id = (int)param[LIGHTNESS_PARAM_FD_INDEX_RT]; /* 0 - flash id */
	cdata.mode = (int)param[LIGHTNESS_PARAM_MODE_INDEX_RT]; /* 1 - mode */
	cdata.data = (int)param[LIGHTNESS_PARAM_CURRENT_INDEX_RT]; /* 2 - current */
	cam_info("%s flash_id=%d, cdata.mode=%d, cdata.data=%d", __func__, flash_id, cdata.mode, cdata.data);

	RETURN_ERROR_OUT_OF_BOUNDS(cdata.mode, STANDBY_MODE, MAX_MODE);
	RETURN_ERROR_OUT_OF_BOUNDS(cdata.data, 0, LM3644TT_FLASH_MAX_CUR); /* 0~1500 mA */
	RETURN_ERROR_OUT_OF_BOUNDS(flash_id, 0, MAX_FLASH_ID); /* 0~0xFF, pass from HAL, but not use just print */

	if (cdata.mode == STANDBY_MODE) {
		rc = hw_lm3644tt_mix_ir_off(&hw_lm3644tt_mix_ir_ctrl);
		if (rc < 0) {
			cam_err("%s flash off error", __func__);
			return rc;
		}
	} else if (cdata.mode == TORCH_MODE) {
		if (HWFLASH_POSITION_FORE == hw_lm3644tt_mix_ir_ctrl.mix_pos) {
			cdata.data = hw_lm3644tt_mix_ir_pdata.ecurrent[CURRENT_TORCH_LEVEL_RT_FRONT];
		} else {
			cdata.data = hw_lm3644tt_mix_ir_pdata.ecurrent[CURRENT_TORCH_LEVEL_RT_BACK];
		}

		cam_info("%s mode=%d, current=%d", __func__, cdata.mode, cdata.data);

		rc = hw_lm3644tt_mix_ir_on(&hw_lm3644tt_mix_ir_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s flash on error", __func__);
			return rc;
		}
	} else if (cdata.mode == FLASH_MODE) {
		cam_info("%s mode=%d, current=%d", __func__, cdata.mode, cdata.data);
		rc = hw_lm3644tt_mix_ir_on(&hw_lm3644tt_mix_ir_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s flash on error", __func__);
			return rc;
		}
	} else {
		cam_err("%s wrong mode=%d", __func__, cdata.mode);
		return -EINVAL;
	}

	return count;
}

static ssize_t hw_lm3644tt_mix_ir_flash_lightness_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf,
	size_t count)
{
	hw_lm3644tt_mix_ir_ctrl.mix_pos = HWFLASH_POSITION_REAR; /* call back flash */
	return hw_lm3644tt_mix_ir_flash_lightness_store_imp(dev, attr, buf, count);
}

static ssize_t hw_lm3644tt_mix_ir_flash_lightness_f_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf,
	size_t count)
{
	hw_lm3644tt_mix_ir_ctrl.mix_pos = HWFLASH_POSITION_FORE; /* call front flash */
	return hw_lm3644tt_mix_ir_flash_lightness_store_imp(dev, attr, buf, count);
}

static ssize_t hw_lm3644tt_mix_ir_flash_mask_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
	int rc = 0;

	RETURN_ERROR_ON_NULL(buf);

	rc = scnprintf(buf, PAGE_SIZE, "flash_mask_disabled=%d.\n",
		hw_lm3644tt_mix_ir_ctrl.flash_mask_enable);

	return rc;
}

static ssize_t hw_lm3644tt_mix_ir_flash_mask_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	RETURN_ERROR_ON_NULL(buf);

	if ('0' == buf[0]) { /* char '0' for mask disable */
		hw_lm3644tt_mix_ir_ctrl.flash_mask_enable = false;
	} else {
		hw_lm3644tt_mix_ir_ctrl.flash_mask_enable = true;
	}
	cam_info("%s flash_mask_enable=%d", __func__,
		hw_lm3644tt_mix_ir_ctrl.flash_mask_enable);
	return (ssize_t)count;
}

static void hw_lm3644tt_mix_ir_torch_brightness_set_imp(struct led_classdev *cdev,
	enum led_brightness brightness)
{
	int rc = 0;
	struct hw_flash_cfg_data cdata = {0};
	unsigned int led_bright = brightness;

	cam_info("%s brightness= %d",__func__,brightness);

	if (LED_OFF == led_bright) {
		rc = hw_lm3644tt_mix_ir_off(&hw_lm3644tt_mix_ir_ctrl);
		if (rc < 0) {
			cam_err("%s pmu_led off error", __func__);
			return;
		}
	} else {
		cdata.mode = TORCH_MODE;
		if (HWFLASH_POSITION_FORE == hw_lm3644tt_mix_ir_ctrl.mix_pos) {
			cdata.data = hw_lm3644tt_mix_ir_pdata.ecurrent[CURRENT_TORCH_LEVEL_MMI_FRONT];
		} else {
			cdata.data = hw_lm3644tt_mix_ir_pdata.ecurrent[CURRENT_TORCH_LEVEL_MMI_BACK];
		}
		cam_info("%s brightness=0x%x, mode=%d, data=%d", __func__, brightness, cdata.mode, cdata.data);
		rc = hw_lm3644tt_mix_ir_on(&hw_lm3644tt_mix_ir_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s flash on error", __func__);
			return;
		}
	}
}

static void hw_lm3644tt_mix_ir_torch_brightness_set(struct led_classdev *cdev,
	enum led_brightness brightness)
{
	hw_lm3644tt_mix_ir_ctrl.mix_pos = HWFLASH_POSITION_REAR;
	hw_lm3644tt_mix_ir_torch_brightness_set_imp(cdev, brightness);
}

static void hw_lm3644tt_mix_ir_torch_brightness_f_set(struct led_classdev *cdev,
	enum led_brightness brightness)
{
	hw_lm3644tt_mix_ir_ctrl.mix_pos = HWFLASH_POSITION_FORE;
	hw_lm3644tt_mix_ir_torch_brightness_set_imp(cdev, brightness);
}

/* for RT */
static struct device_attribute hw_lm3644tt_mix_ir_flash_lightness =
__ATTR(flash_lightness, 0660, hw_lm3644tt_mix_ir_flash_lightness_show,
	hw_lm3644tt_mix_ir_flash_lightness_store); /* 660:-wr-wr--- */

static struct device_attribute hw_lm3644tt_mix_ir_flash_lightness_f =
__ATTR(flash_lightness_f, 0660, hw_lm3644tt_mix_ir_flash_lightness_show_f,
	hw_lm3644tt_mix_ir_flash_lightness_f_store); /* 660:-wr-wr--- */

static struct device_attribute hw_lm3644tt_mix_ir_flash_mask =
__ATTR(flash_mask, 0660, hw_lm3644tt_mix_ir_flash_mask_show,
	hw_lm3644tt_mix_ir_flash_mask_store); /* 660:-wr-wr--- */

extern int register_camerafs_attr(struct device_attribute *attr);
static int hw_lm3644tt_mix_ir_register_attribute(struct hw_flash_ctrl_t *flash_ctrl, struct device *dev)
{
	int rc = 0;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(dev);

	register_camerafs_attr(&hw_lm3644tt_mix_ir_flash_lightness);
	register_camerafs_attr(&hw_lm3644tt_mix_ir_flash_lightness_f);

	flash_ctrl->cdev_torch.name = "torch";
	flash_ctrl->cdev_torch.max_brightness
		= (enum led_brightness)MAX_BRIGHTNESS_FORMMI;
	flash_ctrl->cdev_torch.brightness_set = hw_lm3644tt_mix_ir_torch_brightness_set;
	rc = led_classdev_register((struct device *)dev, &flash_ctrl->cdev_torch);
	if (rc < 0) {
		cam_err("%s failed to register torch classdev", __func__);
		goto err_out;
	}

	flash_ctrl->cdev_torch1.name = "torch_front";
	flash_ctrl->cdev_torch1.max_brightness
		= (enum led_brightness)MAX_BRIGHTNESS_FORMMI;
	flash_ctrl->cdev_torch1.brightness_set = hw_lm3644tt_mix_ir_torch_brightness_f_set;
	rc = led_classdev_register((struct device *)dev, &flash_ctrl->cdev_torch1);
	if (rc < 0) {
		cam_err("%s failed to register torch_front classdev", __func__);
		goto err_create_torch_front_file;
	}

	rc = device_create_file(dev, &hw_lm3644tt_mix_ir_flash_lightness);
	if (rc < 0) {
		cam_err("%s failed to creat flash_lightness attribute", __func__);
		goto err_create_flash_lightness_file;
	}

	rc = device_create_file(dev, &hw_lm3644tt_mix_ir_flash_lightness_f);
	if (rc < 0) {
		cam_err("%s failed to creat flash_f_lightness attribute", __func__);
		goto err_create_flash_f_lightness_file;
	}

	rc = device_create_file(dev, &hw_lm3644tt_mix_ir_flash_mask);
	if (rc < 0) {
		cam_err("%s failed to creat flash_mask attribute", __func__);
		goto err_create_flash_mask_file;
	}

	return 0;

err_create_flash_mask_file:
	device_remove_file(dev, &hw_lm3644tt_mix_ir_flash_lightness_f);
err_create_flash_f_lightness_file:
	device_remove_file(dev, &hw_lm3644tt_mix_ir_flash_lightness);
err_create_flash_lightness_file:
	led_classdev_unregister(&flash_ctrl->cdev_torch1);
err_create_torch_front_file:
	led_classdev_unregister(&flash_ctrl->cdev_torch);
err_out:
	return rc;
}

static int hw_lm3644tt_mix_ir_match(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_flash_i2c_client *i2c_client = NULL;
	struct hw_flash_i2c_fn_t   *i2c_func   = NULL;
	struct hw_lm3644tt_mix_ir_private_data_t *pdata = NULL;
	unsigned char id = 0;
	unsigned char mode = 0;

	RETURN_ERROR_ON_NULL(flash_ctrl);
	RETURN_ERROR_ON_NULL(flash_ctrl->pdata);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl);
	RETURN_ERROR_ON_NULL(flash_ctrl->flash_i2c_client->i2c_func_tbl->i2c_read);

	i2c_client = flash_ctrl->flash_i2c_client;

	/* change to AW3644tt actual slave address 0x63 */
	i2c_client->client->addr = LM3644TT_SLAVE_ADDRESS;
	i2c_func = i2c_client->i2c_func_tbl;
	pdata = (struct hw_lm3644tt_mix_ir_private_data_t *)flash_ctrl->pdata;

	/**
	 * Enable lm3644tt_mix_ir switch to standby current is 10ua,
	 * if match id success, flash_en pin will always be enabled.
	 */
	hw_lm3644tt_mix_ir_set_pin(flash_ctrl, FLASH_EN, HIGH);
	i2c_func->i2c_read(i2c_client, REG_CHIP_ID, &id);

	if (id == LM3644TT_CHIP_ID) {
		hw_lm3644tt_mix_ir_pdata.chip_type = LM3644TT;
		cam_info("%s id=0x%x. chip type is LM3644TT", __func__, id);
	} else if (id == KTD2687_CHIP_ID) {
		loge_if_ret(i2c_func->i2c_read(i2c_client, MODE_TEMP, &mode) < 0);
		if (mode == MODE_TEMP_VALUE) {
			hw_lm3644tt_mix_ir_pdata.chip_type = AW3644;
			cam_info("%s id=0x%x mode=0x%x. chip type is AW3644", __func__, id, mode);
		} else {
			hw_lm3644tt_mix_ir_pdata.chip_type = KTD2687;
			cam_info("%s id=0x%x mode=0x%x. chip type is KTD2687", __func__, id, mode);
		}
	} else {
		cam_err("%s match error, id(0x%x) != 0x%x or 0x%x",
			__func__, id, LM3644TT_CHIP_ID, KTD2687_CHIP_ID);

		/* Enable lm3644tt_mix_ir switch to shutdown when matchid fail, current is 1.3ua */
		hw_lm3644tt_mix_ir_set_pin(flash_ctrl, FLASH_EN, LOW);
		return -EINVAL;
	}

	return 0;
}

static int hw_lm3644tt_mix_ir_remove(struct i2c_client *client)
{
	cam_debug("%s enter", __func__);
	if (NULL == client) {
		cam_err("%s client is NULL", __func__);
		return -EINVAL;
	}
	hw_lm3644tt_mix_ir_ctrl.func_tbl->flash_exit(&hw_lm3644tt_mix_ir_ctrl);

	client->adapter = NULL;
	return 0;
}

static const struct i2c_device_id hw_lm3644tt_mix_ir_id[] = {
	{"lm3644tt_mix_ir", (unsigned long)&hw_lm3644tt_mix_ir_ctrl},
	{}
};

static const struct of_device_id hw_lm3644tt_mix_ir_dt_match[] = {
	{.compatible = "huawei,lm3644tt_mix_ir"},
	{}
};
MODULE_DEVICE_TABLE(of, lm3644tt_mix_ir_dt_match);

static struct i2c_driver hw_lm3644tt_mix_ir_i2c_driver = {
	.probe  = hw_flash_i2c_probe,
	.remove = hw_lm3644tt_mix_ir_remove,
	.id_table   = hw_lm3644tt_mix_ir_id,
	.driver = {
		.name = "hw_lm3644tt_mix_ir",
		.of_match_table = hw_lm3644tt_mix_ir_dt_match,
	},
};

static int __init hw_lm3644tt_mix_ir_module_init(void)
{
	cam_info("%s erter", __func__);
	return i2c_add_driver(&hw_lm3644tt_mix_ir_i2c_driver);
}

static void __exit hw_lm3644tt_mix_ir_module_exit(void)
{
	cam_info("%s enter", __func__);
	i2c_del_driver(&hw_lm3644tt_mix_ir_i2c_driver);
	return;
}

static struct hw_flash_i2c_client hw_lm3644tt_mix_ir_i2c_client;

static struct hw_flash_fn_t hw_lm3644tt_mix_ir_func_tbl = {
	.flash_config = hw_flash_config,
	.flash_init = hw_lm3644tt_mix_ir_init,
	.flash_exit = hw_lm3644tt_mix_ir_exit,
	.flash_on = hw_lm3644tt_mix_ir_on,
	.flash_off = hw_lm3644tt_mix_ir_off,
	.flash_match = hw_lm3644tt_mix_ir_match,
	.flash_get_dt_data = hw_lm3644tt_mix_ir_get_dt_data,
	.flash_register_attribute = hw_lm3644tt_mix_ir_register_attribute,
};

struct hw_flash_ctrl_t hw_lm3644tt_mix_ir_ctrl = {
	.flash_i2c_client = &hw_lm3644tt_mix_ir_i2c_client,
	.func_tbl = &hw_lm3644tt_mix_ir_func_tbl,
	.hw_flash_mutex = &flash_mut_lm3644tt_mix_ir,
	.pdata = (void*)&hw_lm3644tt_mix_ir_pdata,
	.flash_mask_enable = true,
	.state = {
		.mode = STANDBY_MODE,
	},
};

module_init(hw_lm3644tt_mix_ir_module_init);
module_exit(hw_lm3644tt_mix_ir_module_exit);
MODULE_DESCRIPTION("LM3644TT FLASH");
MODULE_LICENSE("GPL v2");
//lint -restore
