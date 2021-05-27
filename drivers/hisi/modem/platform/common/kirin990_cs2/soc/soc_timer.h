#ifndef __SOC_TIMER_H__
#define __SOC_TIMER_H__ 
#ifdef __FASTBOOT__
#include <product_config.h>
#define FASTBOOT_UDELAY_COUNTER_BASE 0xe4052000
#define FASTBOOT_UDELAY_COUNTER_FREQ 0X19200000
#ifdef CONFIG_USE_TIMER_STAMP
#define FASTBOOT_TIMER_BASE 0xF520A000
#define FASTBOOT_TIMER_CURRENTVALUE 0x4
#else
#define FASTBOOT_TIMER_BASE 0XEDF00000
#define FASTBOOT_TIMER_CURRENTVALUE 0x614
#endif
#else
#include <hi_base.h>
#include <bsp_memmap.h>
#include <osl_bio.h>
#include <soc_interrupts.h>
#include <soc_clk.h>
#define L2HAC_CPU_PRIVATE_ADDR 0xF4700000
#ifdef __OS_NRCCPU__
#define SYSTIMER_BASE_ADDR 0xf5208000
#define INT_LVL_SYSTIMER 57
#endif
#define UDELAY_TIMER_CLK 19200000
#define CCORE_SYS_TIMER_CLK 19200000
#define CCORE_SYS_TIMER_BASE_ADDR 0xe0206000
#define CCORE_SYS_TIMER_INT_LVL 52
#define CLK_DEF_TC_INTENABLE (1 << 5)
#define CLK_DEF_TC_INTDISABLE (0 << 5)
#define CLK_DEF_TC_PERIODIC (1 << 6)
#define CLK_DEF_TC_FREERUN 0
#define CLK_DEF_TC_ENABLE (1 << 7)
#define CLK_DEF_TC_DISABLE 0
#define CLK_DEF_TC_COUNT32BIT (1 << 1)
#define CLK_DEF_TC_COUNT16BIT 0
#define CLK_DEF_ENABLE (CLK_DEF_TC_PERIODIC | CLK_DEF_TC_INTENABLE | CLK_DEF_TC_ENABLE | CLK_DEF_TC_COUNT32BIT)
#define CLK_DEF_DISABLE (CLK_DEF_TC_PERIODIC | CLK_DEF_TC_INTDISABLE | CLK_DEF_TC_DISABLE | CLK_DEF_TC_COUNT32BIT)
#ifndef __ASSEMBLY__
static inline void systimer_int_clear(void *addr)
{
    writel(0x1, addr + 0xc);
}
static inline unsigned int systimer_check_enable_success(void)
{
    return 0;
}
#endif
#define TIMER_ARM_FEATURE 
#define ARM_ODD_LOAD_OFFSET 0x20
#define ARM_ODD_VALUE_OFFSET 0x24
#define ARM_ODD_CTRL_OFFSET 0x28
#define ARM_ODD_INTCLR_OFFSET 0x2C
#define ARM_ODD_INTRIS_OFFSET 0x30
#define ARM_ODD_INTMIS_OFFSET 0x34
#define ARM_ODD_BGLOAD_OFFSET 0x38
#define ARM_EVEN_LOAD_OFFSET 0x0
#define ARM_EVEN_VALUE_OFFSET 0x4
#define ARM_EVEN_CTRL_OFFSET 0x8
#define ARM_EVEN_INTCLR_OFFSET 0xC
#define ARM_EVEN_INTRIS_OFFSET 0x10
#define ARM_EVEN_INTMIS_OFFSET 0x14
#define ARM_EVEN_BGLOAD_OFFSET 0x18
#define ESL_SLICE_INCREASE_FLAG 0
#define ESL_SLICE_LOW32BIT 0x4
#define ESL_SLICE_HIGH32BIT 0xc
#define ESL_SLICE_FREQ 32764
#define ESL_SLICE_BASE 0xF520A000
#define SLICE_INCREASE_FLAG 1
#define SLICE_LOW32BIT 0x260
#define SLICE_HIGH32BIT 0x264
#define SLICE_FREQ 32764
#define SLICE_BASE 0xF4001000
#define HRTSLICE_INCREASE_FLAG 1
#define HRSLICE_FREQ 19200000
#define HRTSLICE_LOW32BIT 0x8
#define HRTSLICE_HIGH32BIT 0xc
#define HRTSLICE_BASE 0xe0220000
#endif
#endif
