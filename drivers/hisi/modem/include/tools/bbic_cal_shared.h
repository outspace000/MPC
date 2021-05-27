
#ifndef BBIC_CAL_SHARED_H
#define BBIC_CAL_SHARED_H

#include "vos.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#pragma pack(push, 4)

/*lint -save -e761*/
typedef unsigned short UINT16;
typedef short          INT16;
typedef unsigned char  UINT8;
typedef unsigned int   UINT32;
typedef signed int     INT32;
typedef signed char    SINT8;
/*lint -restore*/

/* PC to UE Msg Min Length: sizeof(BBIC_CAL_COMPONENT_ID_STRU) */
#define BBIC_CAL_MSG_MIN_LENGTH 4

/*
 * RX / tx / mrx cal items support max path num
 */
#define BBIC_CAL_RX_MAX_PATH_NUM  192
#define BBIC_CAL_TX_MAX_PATH_NUM  80
#define BBIC_CAL_MRX_MAX_PATH_NUM (BBIC_CAL_TX_MAX_PATH_NUM)

/* �ɱ䳤�Ⱥ궨�壬5010�Ժ�dataֻռλ,numΪ0 */
#ifdef MODEM_FUSION_VERSION
#define BBIC_CAL_MUTABLE_DATA_LEN 0
#else
#define BBIC_CAL_MUTABLE_DATA_LEN 4
#endif

/*
 * Gsm Point Num
 */
#define BBIC_CAL_GSM_APC_MAX_NUM 64

/*
 * Edge Point Num
 */
#define BBIC_CAL_EDGE_APC_MAX_NUM 32

/*
 * RX IQ Mismatch support max path num
 */
#define BBIC_CAL_RX_IQ_MAX_PATH_NUM 192

/*
 * TX IQ Mismatch support max path num
 */
#define BBIC_CAL_TX_IQ_MAX_PATH_NUM 80

/*
 * TX LOУ׼ʱ��ÿ��path֧֧��У׼��Щ��λ�����֧��4����NV�ṹ������Ӱ��ú궨��
 */

#define BBIC_CAL_TX_LO_MAX_STEP_NUM 4

/*
 * TX Lo Leakage support max path num
 */
#define BBIC_CAL_TX_LO_MAX_PATH_NUM 80

/*
 * IP2 support Max path num
 */
#define BBIC_CAL_IP2_MAX_PATH_NUM 64

/*
 * RX DCOC max list num
 */
#define BBIC_CAL_RX_DCOC_MAX_PATH_NUM 192

/*
 * MRX DCOC max path num
 */
#define BBIC_CAL_MRX_DCOC_MAX_PATH_NUM 80

/*
 * MRX DELAY max path num
 */
#define BBIC_CAL_MRX_DELAY_MAX_PATH_NUM 80

/*
 * TX IQ CAL Max Tx apc cal num
 */
#define BBIC_CAL_TX_APC_MAX_CAL_NUM 20

/*
 * GSM RF TX SLOT MAX NUM
 */
#define BBIC_CAL_GSM_TX_SLOT_NUM 8

/*
 * DCXO RESULT REPORT MAX NUM
 */
#define BBIC_CAL_DCXO_RESULT_IND_NUM 144

/*
 * BBIC_CAL_FREQ_MAX_NUM
 */
#define BBIC_CAL_FREQ_MAX_NUM 32

/*
 * Number of RX MAX VGA
 */
#ifndef RFHAL_CAL_RX_MAX_VGA_NUM
#define RFHAL_CAL_RX_MAX_VGA_NUM 8 /* ���ֺ�NV_MAX_VGA_GAIN_NUMһ�� */
#endif

/*
 * Number of MRX Gain
 */
#ifndef RFHAL_CAL_MRX_GAIN_NUM
#define RFHAL_CAL_MRX_GAIN_NUM 8
#endif

/*
 * IP2 Cal Bandwidth max num
 */
#ifndef RFHAL_CAL_IP2_CAL_BW_NUM
#define RFHAL_CAL_IP2_CAL_BW_NUM 2
#endif

/*
 * RX Cal Max Ant num
 */
#ifndef RFHAL_CAL_MAX_ANT_NUM
#define RFHAL_CAL_MAX_ANT_NUM 2
#endif

/* RX FDIQ�����֧�ִ������� */
#ifndef RFHAL_CAL_RX_FDIQ_MAX_BW_NUM
#define RFHAL_CAL_RX_FDIQ_MAX_BW_NUM 5
#endif

/* RX FDIQ ���VGA��λ���� */
#ifndef RFHAL_CAL_RX_FDIQ_VGA_MAX_NUM
#define RFHAL_CAL_RX_FDIQ_VGA_MAX_NUM 3
#endif

/*
 * RX Cal Max Ant num
 */
#ifndef RFHAL_CAL_RX_FDIQ_TAPS_MAX_NUM
#define RFHAL_CAL_RX_FDIQ_TAPS_MAX_NUM 7
#endif

/*
 * TX FDIQ MAX TAPS
 */
#ifndef RFHAL_CAL_TX_FDIQ_TAPS_MAX_NUM
#define RFHAL_CAL_TX_FDIQ_TAPS_MAX_NUM 2
#endif

/* TX RFGAIN��λ��������20��RF GAIN��λ */
#ifndef RFHAL_CAL_TX_RF_GAIN_MAX_NUM
#define RFHAL_CAL_TX_RF_GAIN_MAX_NUM 20
#endif

/* ��Ч�����ʸ�����֧��2�ֲ����� */
#ifndef RFHAL_CAL_SAMPLE_RATE_MAX_NUM
#define RFHAL_CAL_SAMPLE_RATE_MAX_NUM 2
#endif

/* TX MRX �߲���Ч�����ʸ�����֧��8�ֲ����� */
#ifndef RFHAL_CAL_TX_MRX_SAMPLE_RATE_MAX_NUM
#define RFHAL_CAL_TX_MRX_SAMPLE_RATE_MAX_NUM 8
#endif

/* TXIQУ׼���֧��LPF���� */
#ifndef RFHAL_CAL_LPF_MAX_NUM
#define RFHAL_CAL_LPF_MAX_NUM 3
#endif

/* TXLOУ׼���֧��23������ */
#ifndef RFHAL_CAL_TXLO_LPF_GAIN_MAX_NUM
#define RFHAL_CAL_TXLO_LPF_GAIN_MAX_NUM 23
#endif

/* TXIQУ׼���֧�ִ������� */
#ifndef RFHAL_CAL_TX_FDIQ_BW_MAX_NUM
#define RFHAL_CAL_TX_FDIQ_BW_MAX_NUM 10
#endif

/* ÿ��PATH֧�ֵ��ز���MIMOУ׼��� */
#ifndef RFHAL_CAL_MIMO_RSLT_MAX_NUM
#define RFHAL_CAL_MIMO_RSLT_MAX_NUM 2
#endif

/* MRXIQУ׼���֧�ִ������� */
#ifndef RFHAL_CAL_MRX_FDIQ_BW_MAX_NUM
#define RFHAL_CAL_MRX_FDIQ_BW_MAX_NUM 4
#endif

#ifndef RFHAL_HFCAL_FDIQ_CAL_TAP_NUM
#define RFHAL_HFCAL_FDIQ_CAL_TAP_NUM 5
#endif

#ifndef RFHAL_HFCAL_FDIQ_CAL_VGA_NUM
#define RFHAL_HFCAL_FDIQ_CAL_VGA_NUM 4
#endif

#ifndef RFHAL_HFCAL_TRX_BANDWIDTH_NUM
#define RFHAL_HFCAL_TRX_BANDWIDTH_NUM 6
#endif

#ifndef RFHAL_HFCAL_TRX_MAX_ANT_NUM
#define RFHAL_HFCAL_TRX_MAX_ANT_NUM 4
#endif

#ifndef RFHAL_CAL_TXIQ_PHASE_MAX_NUM
#define RFHAL_CAL_TXIQ_PHASE_MAX_NUM 2
#endif

#ifndef RFHAL_CAL_IRR_TONE_MAX_NUM
#define RFHAL_CAL_IRR_TONE_MAX_NUM 8
#endif

#ifndef RFHAL_HFCAL_MAX_MAS_NUM
#define RFHAL_HFCAL_MAX_MAS_NUM 2
#endif

#ifndef RFHAL_HFCAL_TEMP_MAX_EP_NUM
#define RFHAL_HFCAL_TEMP_MAX_EP_NUM 16
#endif

/* RFIC�ϵ���У׼RXADC */
#ifndef RFHAL_HFCAL_RXADC_INTRA_OFFSET_COEF_NUM
/* һ��RXADCͨ����У׼��8��Offsetϵ��,ÿ��8bit,01subAdc��һ��U16,�Դ����� */
#define RFHAL_HFCAL_RXADC_INTRA_OFFSET_COEF_NUM   4
#endif

#ifndef RFHAL_HFCAL_RXADC_INTRA_CDAC_NUM
#define RFHAL_HFCAL_RXADC_INTRA_CDAC_NUM          16 /* һ��RXADCͨ����У׼��16��CDACϵ�� */
#endif

#ifndef RFHAL_HFCAL_RXADC_INTRA_CDAC_COEF_NUM
#define RFHAL_HFCAL_RXADC_INTRA_CDAC_COEF_NUM     11 /* һ��RXADCͨ����У׼��11��CDACϵ�� */
#endif

#ifndef RFHAL_HFCAL_RXADC_INTER_OFFSET_COEF_NUM
#define RFHAL_HFCAL_RXADC_INTER_OFFSET_COEF_NUM   16 /* һ��RXADCͨ����У׼��16��Offsetϵ��, 14bit */
#endif

#ifndef RFHAL_HFCAL_RXADC_INTER_GAINERR_COEF_NUM
#define RFHAL_HFCAL_RXADC_INTER_GAINERR_COEF_NUM  14 /* һ��RXADCͨ����У׼��12��GainErrorϵ��, 14bit */
#endif

#ifndef RFHAL_HFCAL_RXADC_INTER_SKEW_COEF_NUM
#define RFHAL_HFCAL_RXADC_INTER_SKEW_COEF_NUM     8 /* һ��RXADCͨ����У׼��12��Skewϵ��, 15bit */
#endif

#ifndef UECBT_WRITE_NV_MSG_LEN_INVALID
#define UECBT_WRITE_NV_MSG_LEN_INVALID 0x1040
#endif

#ifndef UECBT_WRITE_NV_DATA_READ_OVERFLOW
#define UECBT_WRITE_NV_DATA_READ_OVERFLOW 0x1041
#endif

#ifndef UECBT_STORE_NV_ID_FULL
#define UECBT_STORE_NV_ID_FULL 0x1042
#endif

#ifndef UECBT_UPDATE_NV_DDR_FAIL
#define UECBT_UPDATE_NV_DDR_FAIL 0x1043
#endif

#ifndef UECBT_WRITE_NV_STATUS_INVALID
#define UECBT_WRITE_NV_STATUS_INVALID 0x1044
#endif

/* ��ҪУ���ķ��书�ʵ�Ϊ64�� */
#define GE_TX_PWR_CONT_NUM 64

#define GE_PA_GAIN_NUM 4

#define GE_RF_GAIN_NUM 2

#define GE_RAMP_PWR_LEVEL_NUM 7

#define GE_RAMP_COEF_NUM 16

#define BBIC_CAL_MAX_WR_MIPI_COUNT 16

#define BBIC_CAL_MAX_RD_MIPI_COUNT 2

#define BBIC_CAL_MAX_REGISTER_COUNT 10

#define BBIC_CAL_GETX_APC_TBL_POINT_MAX_NUM 256

#define BBIC_CAL_GETX_PATH_NUM 8

#define BBIC_CAL_G_TX_PCL_NUM 32

#define BBIC_CAL_GETX_DPD_MRX_GAIN_NUM 1

#define BBIC_CAL_GETX_DPD_STEP_NUM 64

#define BBIC_CAL_GETX_DPD_LUT_POINT_NUM 128

#define BBIC_CAL_GETX_DPD_CAL_TIMES_MAX_NUM 10

#define BBA_CAL_TRX_MNTN_MAX_NUM 500

/* HiRFһ������֧�ֵ����Band���� */
#define BBIC_HFCAL_HIRF_MAX_BAND_NUM 2

/* ֧�ֵ����RFIC���� */
#define BBIC_CAL_MAX_RFIC_NUM 4

/* HFУ׼֧�ֵ����MAS���� */
#define BBIC_HFCAL_MAX_MAS_NUM 2

/* HFУ׼NCP Symbol���ø��� */
#define BBIC_HFCAL_NCP_SYMBOL_NUM 14

/* HFУ׼������߸��������֧��4R */
#define BBIC_HFCAL_MAX_ANT_NUM 4

/* HFRXУ׼VGA���������֧��6 */
#define BBIC_HFCAL_RX_MAX_VGA_NUM 6

/* HF֧�ֵ����Band���� */
#define BBIC_HF_MAX_BAND_NUM 32

/* HF 4ƴƬCPE����6P01��DIE�ĸ��� */
#define BBIC_HF_TRX_MAX_DIE_NUM 8

/* et lut ��ȡRFDSP���õĵ������� */
#define BBIC_ET_LUT_CW_STEP_NUM 64

/* DPDУ׼Ƶ������ */
#define BBIC_DPD_CAL_FEQ_NUM 3

/* DPD Lut���� */
#define BBIC_DPD_NUM 4

/* DPD Ctrl���� */
#define BBIC_DPD_CTRL_NUM (BBIC_DPD_NUM / 2)

/* DPD SPL���� */
#define BBIC_DPD_LUT_NUM 7

/* ETDPD SPL���� */
#define BBIC_ETDPD_LUT_NUM 3

/* DPD IQֵ���� */
#define BBIC_DPD_SPL_NUM 16

/* TX֧������CC���� */
#define TX_MAX_CC_NUM 2

/* TX֧������ANT���� */
#define TX_MAX_ANT_NUM 2

/* RX֧������CC���� */
#define RX_MAX_CC_NUM 5

/* RX֧������ANT���� */
#define RX_MAX_ANT_NUM 8

/* RX֧�ֵ�path������� */
#define RX_MAX_PATH_OFFSET 4

/*
 * 1. ���� M0 ���֧�� Rx:5cc, Tx:2cc
 * 2. ˫�� M0 ���֧�� Rx:3cc, Tx:1cc
 *    ˫�� M1 ���֧�� Rx:1cc, Tx:1cc
 */
#define DOUBLE_MODEM_M0_RX_CC_LIMIT 3
#define DOUBLE_MODEM_M0_TX_CC_LIMIT 1
#define DOUBLE_MODEM_M1_RX_CC_LIMIT 1
#define DOUBLE_MODEM_M1_TX_CC_LIMIT 1

enum TOOL_BBIC_CAL_MSG_TYPE_ENUM {
    /* Self cal for fast calibration */
    ID_TOOL_BBIC_CAL_DCXO_START_REQ      = 0x1001, /* < @sa BBIC_CAL_DCXO_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_RX_IQ_START_REQ     = 0x1002, /* < @sa BBIC_CAL_RX_IQ_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_TX_IQ_START_REQ     = 0x1003, /* < @sa BBIC_CAL_TX_IQ_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_TX_LO_START_REQ     = 0x1004, /* < @sa BBIC_CAL_TX_LO_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_IP2_START_REQ       = 0x1005, /* < @sa BBIC_CAL_IP2_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_MRX_DCOC_START_REQ  = 0x1006, /* < @sa BBIC_CAL_MRX_DCOC_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_RX_DCOC_START_REQ   = 0x1007, /* < @sa BBIC_CAL_RX_DCOC_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_RFIC_SELFCAL_REQ    = 0x1008, /* < @sa BBIC_CAL_MSG_HDR_STRU */
    ID_TOOL_BBIC_CAL_TX_FILTER_REQ       = 0x1009, /* < @sa BBIC_CAL_TX_FLITER_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_MRX_DELAY_REQ       = 0x100A, /* < @sa BBIC_CAL_MRX_DELAY_START_REQ_STRU */
    ID_TOOL_BBIC_HFCAL_TRXFDIQ_REQ       = 0x1010,
    ID_TOOL_BBIC_HFCAL_RXFIIQ_REQ        = 0x1011,
    ID_TOOL_BBIC_HFCAL_RXADC_REQ         = 0x1012,
    ID_TOOL_BBIC_HFCAL_RX_DCOC_START_REQ = 0x1017, /* < @sa BBIC_CAL_HF_RX_DCOC_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_DCXO_DCOC_REQ       = 0x1018, /**< @sa BBIC_CAL_DcxoDcocCalReq */

    /* trx cal for fast calibration */
    ID_TOOL_BBIC_CAL_RX_START_REQ         = 0x1021, /* < @sa BBIC_CAL_RX_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_TX_START_REQ         = 0x1022, /* < @sa BBIC_CAL_TX_START_REQ_STRU */
    ID_TOOL_BBIC_CAL_GETX_POWER_START_REQ = 0x1023, /* < @sa BBIC_CAL_GETX_APC_START_REQ_STRU */

    ID_TOOL_BBIC_HFCAL_RX_START_REQ = 0x1031, /* < @sa BBIC_CAL_HF_RX_START_REQ_STRU */
    ID_TOOL_BBIC_HFCAL_TX_START_REQ = 0x1032, /* < @sa BBIC_CAL_HF_TX_START_REQ_STRU */

    /* self cal for rf debug */
    ID_TOOL_BBIC_CAL_RF_DEBUG_DCXO_CFIX_REQ = 0x1040, /* < @sa BBIC_CAL_RF_DEBUG_DCXO_CFIX_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_IP2_REQ       = 0x1041, /* < @sa BBIC_CAL_RF_DEBUG_IP2_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_RX_DCOC_REQ   = 0x1042, /* < @sa BBIC_CAL_RF_DEBUG_RX_DCOC_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_MRX_DCOC_REQ  = 0x1043, /* < @sa BBIC_CAL_RF_DEBUG_MRX_DCOC_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_TX_IQ_REQ     = 0x1044, /* < @sa BBIC_CAL_RF_DEBUG_TX_IQ_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_TX_LO_REQ     = 0x1045, /* < @sa BBIC_CAL_RF_DEBUG_TX_LO_REQ_STRU */

    /* TRX cal for rf debug */
    ID_TOOL_BBIC_CAL_RF_DEBUG_TX_REQ      = 0x1060, /* < @sa BBIC_CAL_RF_DEBUG_TX_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_GSM_TX_REQ  = 0x1061, /* < @sa BBIC_CAL_RF_DEBUG_GSM_TX_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_RX_REQ      = 0x1062, /* < @sa BBIC_CAL_RF_DEBUG_RX_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_RSSI_REQ    = 0x1063, /* < @sa BBIC_CAL_RF_DEBUG_RSSI_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_RX_EVM_REQ  = 0x1064, /* < @sa BBIC_CAL_RF_DEBUG_RX_EVM_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_DCXO_FE_REQ = 0x1065, /* < @sa BBIC_CAL_RF_DEBUG_DCXO_FE_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_DCXO_REQ    = 0x1066, /* < @sa BBIC_CAL_RF_DEBUG_DCXO_FE_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_TRX_REQ     = 0x1067, /* < @sa BBIC_CAL_RF_DEBUG_TRX_REQ_STRU */
    ID_TOOL_BBIC_CAL_RF_DEBUG_INT_REQ     = 0x1068, /* < @sa BBIC_CAL_RF_DEBUG_INIT_REQ_STRU */

    ID_TOOL_BBIC_HFCAL_RF_DEBUG_TX_REQ   = 0x1070, /* < @sa BBIC_CAL_RF_DEBUG_HF_TX_REQ_STRU */
    ID_TOOL_BBIC_HFCAL_RF_DEBUG_RX_REQ   = 0x1071, /* < @sa BBIC_CAL_RF_DEBUG_HF_RX_REQ_STRU */
    ID_TOOL_BBIC_HFCAL_RF_DEBUG_RSSI_REQ = 0x1072, /* < @sa BBIC_CAL_RF_DEBUG_HF_RSSI_REQ_STRU */
    ID_TOOL_BBIC_HFCAL_ANA_TEMP_REQ      = 0x1073, /* < @sa BBIC_CAL_RF_HF_ANA_TEMP_REQ_PARA_STRU */

    ID_TOOL_BBIC_REGISTER_READ_REQ   = 0x1080,
    ID_TOOL_BBIC_REGISTER_WRITE_REQ  = 0x1081,
    ID_TOOL_BBIC_MIPI_READ_REQ       = 0x1082,
    ID_TOOL_BBIC_MIPI_WRITE_REQ      = 0x1083,
    ID_TOOL_BBIC_ALINK_REG_WRITE_REQ = 0x1084,
    ID_TOOL_BBIC_ALINK_REG_READ_REQ  = 0x1085,
    ID_TOOL_BBIC_TEMP_QRY_REQ        = 0x1086,
    ID_TOOL_BBIC_PLL_QRY_REQ         = 0x1087,
    ID_TOOL_BBIC_DPDT_REQ            = 0x1088,
    ID_TOOL_BBIC_NV_RESET_REQ        = 0x1089,
    ID_TOOL_BBIC_RELOAD_NV_REQ       = 0x1090,
    ID_TOOL_BBIC_SET_BU_TYPE_IND     = 0x1091,
    ID_TOOL_BBIC_TRX_TAS_REQ         = 0x1092,
    ID_TOLL_BBIC_RELOAD_HF_NV_REQ    = 0x1093,

    /* Vcc Lut fast calibration */
    ID_TOOL_BBIC_CAL_TX_VCC_LUT_REQ  = 0x1095,
    ID_TOOL_BBIC_CAL_TX_VCC_COMP_REQ = 0x1096,

    /* ET Delay calibration */
    ID_TOOL_BBIC_CAL_ET_DELAY_REQ = 0x1097,

    /* Pa Gain Delta fast calibration */
    ID_TOOL_BBIC_CAL_PA_GAIN_DELTA_REQ = 0x1098,

    /* DPD calibration */
    ID_TOOL_BBIC_CAL_DPD_START_REQ = 0x1099,

    /* FASTCAL RFDEBUG TX REQ */
    ID_TOOL_BBIC_CT_TX_REQ  = 0x10a0,

    /* MT RX REQ */
    ID_AT_BBIC_CAL_MT_RX_REQ = 0x10a1,

    /* MT RX RSSI REQ */
    ID_AT_BBIC_CAL_MT_RX_RSSI_REQ = 0x10a2,

    /* MT TX REQ */
    ID_AT_BBIC_CAL_MT_TX_REQ = 0x10a3,

    ID_TOOL_BBIC_WRITE_NV_REQ       = 0x8023,
    ID_TOOL_BBIC_NV_WRITE_FLASH_REQ = 0x802D,

    ID_TOOL_BBIC_SET_LTEV_FTM_REQ = 0x90e5,

    ID_TOOL_BBIC_CAL_BUTT
};
typedef UINT16 TOOL_BBIC_CAL_MSG_TYPE_ENUM_UINT16;

enum BBIC_TOOL_CAL_MSG_TYPE_ENUM {
    ID_BBIC_TOOL_CAL_MSG_CNF = 0x2000, /* < @sa BBIC_CAL_MSG_CNF_STRU */

    /* Self cal for fast calibration */
    ID_BBIC_TOOL_CAL_DCXO_RESULT_IND      = 0x2001, /* < @sa BBIC_CAL_DCXO_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RX_IQ_RESULT_IND     = 0x2002, /* < @sa BBIC_CAL_RX_IQ_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_TX_IQ_RESULT_IND     = 0x2003, /* < @sa BBIC_CAL_TX_IQ_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_TX_LO_RESULT_IND     = 0x2004, /* < @sa BBIC_CAL_TX_LO_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_IP2_RESULT_IND       = 0x2005, /* < @sa BBIC_CAL_IP2_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_MRX_DCOC_RESULT_IND  = 0x2006, /* < @sa BBIC_CAL_MRX_DCOC_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RX_DCOC_RESULT_IND   = 0x2007, /* < @sa BBIC_CAL_RX_DCOC_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RFIC_SELFCAL_IND     = 0x2008, /* < @sa BBIC_CAL_RFIC_SELFCAL_IND_STRU */
    ID_BBIC_TOOL_CAL_TX_FILTER_IND        = 0x2009, /* < @sa BBIC_CAL_TX_FLITER_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_MRX_DELAY_IND        = 0x200A, /* < @sa BBIC_CAL_MRX_DELAY_RESULT_IND_STRU */
    ID_BBIC_TOOL_HFCAL_TRXFDIQ_IND        = 0x2010,
    ID_BBIC_TOOL_HFCAL_RXFIIQ_IND         = 0x2011,
    ID_BBIC_TOOL_HFCAL_RXADC_IND          = 0x2012,
    ID_BBIC_TOOL_HFCAL_RX_DCOC_RESULT_IND = 0x2017, /* < @sa BBIC_CAL_HF_RX_DCOC_RESULT_IND_STRU */
    ID_TOOL_BBIC_CAL_DCXO_DCOC_RESULT_IND = 0x2018, /* < @sa BBIC_CAL_DcxoDcocCalInd */

    /* trx cal for fast calibration */
    ID_BBIC_TOOL_CAL_RX_RESULT_IND         = 0x2021, /* < @sa BBIC_CAL_RX_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_TX_RESULT_IND         = 0x2022, /* < @sa BBIC_CAL_TX_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_GETX_POWER_RESULT_IND = 0x2023, /* < @sa BBIC_CAL_GETX_APC_START_IND_STRU */

    ID_BBIC_TOOL_HFCAL_RX_RESULT_IND = 0x2031, /* < @sa BBIC_CAL_HF_RX_RESULT_IND_STRU */
    ID_BBIC_TOOL_HFCAL_TX_RESULT_IND = 0x2032, /* < @sa BBIC_CAL_HF_TX_RESULT_IND_STRU */

    /* self cal for rf debug */
    ID_BBIC_TOOL_CAL_RF_DEBUG_DCXO_RESULT_IND     = 0x2040, /* < @sa BBIC_CAL_RF_DEBUG_DCXO_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_IP2_RESULT_IND      = 0x2041, /* < @sa BBIC_CAL_RF_DEBUG_IP2_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_RX_DCOC_RESULT_IND  = 0x2042, /* < @sa BBIC_CAL_RF_DEBUG_RX_DCOC_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_MRX_DCOC_RESULT_IND = 0x2043, /* < @sa BBIC_CAL_RF_DEBUG_MRX_DCOC_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_TX_IQ_RESULT_IND    = 0x2044, /* < @sa BBIC_CAL_RF_DEBUG_TX_IQ_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_TX_LO_RESULT_IND    = 0x2045, /* < @sa BBIC_CAL_RF_DEBUG_TX_LO_RESULT_IND_STRU */

    /* TRX cal for rf debug */
    ID_BBIC_TOOL_CAL_RF_DEBUG_TX_RESULT_IND = 0x2060, /* < @sa BBIC_CAL_RF_DEBUG_TX_RESULT_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_RX_RSSI_IND   = 0x2061, /* < @sa BBIC_CAL_RF_DEBUG_RX_RSSI_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_RX_EVM_IND    = 0x2062, /* < @sa BBIC_CAL_RF_DEBUG_RX_EVM_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_GTX_MRX_IND   = 0x2063, /* < @sa BBIC_CAL_RF_DEBUG_GTX_MRX_IND_STRU */
    ID_BBIC_TOOL_CAL_RF_DEBUG_DCXO_IND      = 0x2066, /* < @sa BBIC_CAL_RF_DEBUG_GTX_MRX_IND_STRU */

    ID_BBIC_TOOL_HFCAL_RF_DEBUG_RX_RSSI_IND = 0x2071, /* < @sa BBIC_CAL_RF_DEBUG_HF_RX_RSSI_IND_STRU */
    ID_BBIC_TOOL_HFCAL_ANA_TEMP_IND         = 0x2072, /* < @sa BBIC_CAL_RF_HF_ANA_TEMP_IND_STRU */

    ID_BBIC_TOOL_REGISTER_READ_IND   = 0x2080,
    ID_BBIC_TOOL_REGISTER_WRITE_IND  = 0x2081,
    ID_BBIC_TOOL_MIPI_READ_IND       = 0x2082,
    ID_BBIC_TOOL_MIPI_WRITE_IND      = 0x2083,
    ID_BBIC_TOOL_ALINK_REG_READ_IND  = 0x2084,
    ID_BBIC_TOOL_ALINK_REG_WRITE_IND = 0x2085,
    ID_BBIC_TOOL_TEMP_QRY_IND        = 0x2086,
    ID_BBIC_TOOL_PLL_QRY_IND         = 0x2087,
    ID_BBIC_TOOL_DPDT_IND            = 0x2088,
    ID_BBIC_TOOL_NV_RESET_IND        = 0x2089,
    ID_BBIC_TOOL_RELOAD_NV_IND       = 0x2090,
    ID_TOOL_BBIC_TRX_TAS_CNF         = 0x2092,

    ID_BBIC_TOOL_TX_VCC_LUT_RESULT_IND    = 0x2095,
    ID_BBIC_TOOL_ET_DELAY_K_RESULT_IND    = 0x2096, /* < @sa BBIC_CAL_ET_DELAY_K_RESULT_IND_STRU */
    ID_BBIC_TOOL_ET_DELAY_CAL_RESULT_IND  = 0x2097, /* < @sa BBIC_CAL_ET_DELAY_RESULT_IND_STRU */
    ID_BBIC_TOOL_PA_GAIN_DELTA_RESULT_IND = 0x2098,
    ID_BBIC_TOOL_CAL_DPD_RESULT_IND       = 0x2099,

    /* MT TX IND */
    ID_BBIC_CAL_AT_MT_TX_CNF    = 0x20a0,
    ID_BBIC_CAL_AT_MT_TX_PD_IND = 0x20a1,

    /* MT RX IND */
    ID_BBIC_CAL_AT_MT_RX_CNF      = 0x20a2,
    ID_BBIC_CAL_AT_MT_RX_RSSI_IND = 0x20a3,

    ID_BBIC_TOOL_WRITE_NV_CNF       = 0x8024,
    ID_BBIC_TOOL_NV_WRITE_FLASH_CNF = 0x802E,

    ID_BBIC_TOOL_SET_LTEV_FTM_CNF   = 0x90e6,

    ID_BBIC_TOOL_CAL_BUTT
};
typedef UINT16 BBIC_TOOL_CAL_MSG_TYPE_ENUM_UINT16;

enum BBIC_TOOL_CAL_MRTN_MSG_TYPE_ENUM {
    ID_BBIC_TOOL_MNTN_INFO_START = 0x7000,

    ID_BBIC_TOOL_GETX_APC_TBL_MNTN_INFO               = 0x7001, /* APC��У׼ά����Ϣ */
    ID_BBIC_TOOL_GETX_PAGAIN_MNTN_INFO                = 0x7002, /* PAGAINУ׼ά����Ϣ */
    ID_BBIC_TOOL_GETX_FREQCOMP_MNTN_INFO              = 0x7003, /* FREQCOMPУ׼ά����Ϣ */
    ID_BBIC_TOOL_GETX_PRECHARGE_MNTN_INFO             = 0x7004, /* Ԥ���ѹУ׼ά����Ϣ */
    ID_BBIC_TOOL_PA_VCC_EXTRACT_MRXCORR_MNTN_INFO     = 0x7005, /* Lut��ȡmrxcorrά����Ϣ */
    ID_BBIC_TOOL_PA_VCC_CAL_FITTING_SAMPLES_MNTN_INFO = 0x7006, /* LutУ׼������ά����Ϣ */
    ID_BBIC_TOOL_GETX_EDGE_DPD_MNTN_INFO              = 0x7007, /* DPDУ׼ά����Ϣ */
    ID_BBIC_TOOL_RX_MNTN_INFO                         = 0x7008,
    ID_BBIC_TOOL_TX_MNTN_INFO                         = 0x7009,
    ID_BBIC_TOOL_MNTN_INFO_BUTT
};
typedef UINT16 BBIC_TOOL_CAL_MRTN_MSG_TYPE_ENUM_UINT16;

enum BBIC_CAL_SIGNAL_MODE_ENUM {
    BBIC_CAL_SIGNAL_MODE_MODULATE = 0x00, /* < Modulate signal */
    BBIC_CAL_SIGNAL_MODE_TONE     = 0x01, /* < Tone signal */
    BBIC_CAL_SIGNAL_MODE_TWO_TONE = 0x02, /* < Two Tone Signal */
    BBIC_CAL_SIGNAL_MODE_BUTT     = 0x03
};
typedef UINT8 BBIC_CAL_SIGNAL_MODE_ENUM_UINT8;

enum BBIC_CAL_PA_MODE_ENUM {
    BBIC_CAL_PA_GAIN_MODE_HIGH      = 0x00, /* < PA high gain mode */
    BBIC_CAL_PA_GAIN_MODE_MID       = 0x01, /* < PA medium gain mode */
    BBIC_CAL_PA_GAIN_MODE_LOW       = 0x02, /* < PA low gain mode */
    BBIC_CAL_PA_GAIN_MODE_ULTRA_LOW = 0x03, /* < PA ultra low gain mode */
    BBIC_CAL_PA_GAIN_MODE_BUTT      = 0x04
};
typedef UINT8 BBIC_CAL_PA_MODE_ENUM_UINT8;

enum BBIC_CAL_GSM_DATA_TYPE_ENUM {
    BBIC_CAL_GSM_DATA_TYPE_ALL_ZERO = 0x00, /* < All Zero */
    BBIC_CAL_GSM_DATA_TYPE_RANDOM   = 0x01, /* < Random data */
    BBIC_CAL_GSM_DATA_TYPE_STATIC   = 0x02, /* < Static data */
    BBIC_CAL_GSM_DATA_TYPE_BUTT     = 0x03
};
typedef UINT8 BBIC_CAL_GSM_DATA_TYPE_ENUM_UINT8;

enum BBIC_CAL_GSM_RX_MODE_ENUM {
    BBIC_CAL_GSM_RX_MODE_BRUST      = 0x00, /* < Brust Measure */
    BBIC_CAL_GSM_RX_MODE_CONTINUOUS = 0x01, /* < Continuous Measure */
    BBIC_CAL_GSM_RX_MODE_BUTT       = 0x03
};
typedef UINT8 BBIC_CAL_GSM_RX_MODE_ENUM_UINT8;

enum BBIC_CAL_DcxoTempRiseTypeEnum {
    BBIC_CAL_DCXO_TEMP_RISE_TyPE_NONE  = 0x00,
    BBIC_CAL_DCXO_TEMP_RISE_TYPE_AP    = 0x01, /* < Use Ap Tempture rise */
    BBIC_CAL_DCXO_TEMP_RISE_TYPE_CP    = 0x02, /* < Use Cp Tempture rise */
    BBIC_CAL_DCXO_TEMP_RISE_TYPE_AP_CP = 0x03, /* < Use AP AND Cp Tempture rise */
    BBIC_CAL_DCXO_TEMP_RISE_TYPE_BUTT  = 0x04
};
typedef UINT16 BBIC_CAL_DcxoTempRiseTypeUint16;

enum BBIC_CAL_RX_AGC_MODE_ENUM {
    BBIC_CAL_RX_AGC_MODE_FAST = 0x00, /* < Fast Mode */
    BBIC_CAL_RX_AGC_MODE_SLOW = 0x01, /* < Slow Mode */
    BIC_CAL_RX_AGC_MODE_BUTT  = 0x03
};
typedef UINT8 BBIC_CAL_RX_AGC_MODE_ENUM_UINT8;

enum BBIC_CAL_CONFIG_MODE_ENUM {
    BBIC_CAL_CONFIG_MODE_GAIN_INDEX     = 0x0000, /* GAIN Indexģʽ,��Ҫ��Gain Index��NV���л�ȡ��������� */
    BBIC_CAL_CONFIG_MODE_GAIN_CODE      = 0x0001, /* Gain Codeģʽ,ֱ��Ӧ�ø���������� */
    BBIC_CAL_CONFIG_MODE_GAIN_SUB_INDEX = 0x0002, /* ��Ƶ�����·ֱ�����Hi6P01��Hi6370��Gain Index */
    BBIC_CAL_CONFIG_MODE_BUTT           = 0x0003
};
typedef UINT8 BBIC_CAL_CONFIG_MODE_ENUM_UINT8;

enum RAT_MODE_ENUM {
    RAT_MODE_GSM   = 0x0000,
    RAT_MODE_WCDMA = 0x0001,
    RAT_MODE_CDMA  = 0x0002,
    RAT_MODE_LTE   = 0x0003,
    RAT_MODE_NR    = 0x0004,
    RAT_MODE_BUTT  = 0x0005,
    RAT_MODE_NORAT = 0xFFFF,
};
typedef UINT16 RAT_MODE_ENUM_UINT16;

enum STEP_WIDTH_ENUM {
    STEP_WIDTH_DEFAULT = 0x00, /* < PHY DEFINE */
    STEP_WIDTH_1MS     = 0x01, /* < 1 ms Step Width */
    STEP_WIDTH_2MS     = 0x02, /* < 2 ms Step Width */
    STEP_WIDTH_5MS     = 0x03, /* < 5 ms Step Width */
    STEP_WIDTH_10MS    = 0x04, /* < 10 ms Step Width */
    STEP_WIDTH_20MS    = 0x05, /* < 20 ms Step Width */
    STEP_WIDTH_40MS    = 0x06, /* < 40 ms Step Width */
    STEP_WIDTH_EASYRF_BUTT
};
typedef UINT8 STEP_WIDTH_ENUM_UINT8;

/*
 *  Name: BAND_ENUM_UINT16
 *  Description: Band Indication. Range [1..66]. Defined per RAT below. 3GPP
 * Band
 * Definitions (TS 25.101-c20 and TS 36.101-c20)
 * 4G      3G      2G       CDMA
 * 1       I                BC6
 * 2       II      1900     BC1
 * 3       III     1800     BC8
 * 4       IV               BC15
 * 5       V       850      BC0
 * 6       VI
 * 7       VII              BC13
 * 8       VIII    900      BC9
 * 9       IX               BC4
 * 10      X
 * 11      XI
 * 12      XII
 * 13      XIII             BC7
 * 14      XIV
 * 17
 * 18
 * 19      XIX
 * 20      XX
 * 21      XXI
 * 22      XXII
 * 23
 * 24
 * 25      XXV
 * 26      XXVI
 * 27                       BC10
 * 28
 * 29
 * 30
 * 31                       BC5A0
 * 32
 * 33      a1
 * 34      a2
 * 35      b1
 * 36      b2
 * 37      c
 * 38      d
 * 39      f
 * 40      e
 * 41
 * ...
 * 66
 */
enum BAND_ENUM {
    BAND_1    = 0x0001,
    BAND_2    = 0x0002,
    BAND_3    = 0x0003,
    BAND_4    = 0x0004,
    BAND_5    = 0x0005,
    BAND_6    = 0x0006,
    BAND_7    = 0x0007,
    BAND_8    = 0x0008,
    BAND_9    = 0x0009,
    BAND_10   = 0x000A,
    BAND_11   = 0x000B,
    BAND_12   = 0x000C,
    BAND_13   = 0x000D,
    BAND_14   = 0x000E,
    BAND_15   = 0x000F,
    BAND_16   = 0x0010,
    BAND_17   = 0x0011,
    BAND_18   = 0x0012,
    BAND_19   = 0x0013,
    BAND_20   = 0x0014,
    BAND_21   = 0x0015,
    BAND_22   = 0x0016,
    BAND_23   = 0x0017,
    BAND_24   = 0x0018,
    BAND_25   = 0x0019,
    BAND_26   = 0x001A,
    BAND_27   = 0x001B,
    BAND_28   = 0x001C,
    BAND_29   = 0x001D,
    BAND_30   = 0x001E,
    BAND_31   = 0x001F,
    BAND_32   = 0x0020,
    BAND_33   = 0x0021,
    BAND_34   = 0x0022,
    BAND_35   = 0x0023,
    BAND_36   = 0x0024,
    BAND_37   = 0x0025,
    BAND_38   = 0x0026,
    BAND_39   = 0x0027,
    BAND_40   = 0x0028,
    BAND_41   = 0x0029,
    BAND_42   = 0x002A,
    BAND_43   = 0x002B,
    BAND_44   = 0x002C,
    BAND_45   = 0x002D,
    BAND_46   = 0x002E,
    BAND_47   = 0x002F,
    BAND_48   = 0x0030,
    BAND_49   = 0x0031,
    BAND_50   = 0x0032,
    BAND_51   = 0x0033,
    BAND_52   = 0x0034,
    BAND_53   = 0x0035,
    BAND_54   = 0x0036,
    BAND_55   = 0x0037,
    BAND_56   = 0x0038,
    BAND_57   = 0x0039,
    BAND_58   = 0x003A,
    BAND_59   = 0x003B,
    BAND_60   = 0x003C,
    BAND_61   = 0x003D,
    BAND_62   = 0x003E,
    BAND_63   = 0x003F,
    BAND_64   = 0x0040,
    BAND_65   = 0x0041,
    BAND_66   = 0x0042,
    BAND_70   = 0x0046,
    BAND_71   = 0x0047,
    BAND_74   = 0x004A,
    BAND_75   = 0x004B,
    BAND_76   = 0x004C,
    BAND_77   = 0x004D,
    BAND_78   = 0x004E,
    BAND_79   = 0x004F,
    BAND_80   = 0x0050,
    BAND_81   = 0x0051,
    BAND_82   = 0x0052,
    BAND_83   = 0x0053,
    BAND_84   = 0x0054,
    BAND_257  = 0x0101,
    BAND_258  = 0x0102,
    BAND_259  = 0x0103,
    BAND_260  = 0x0104,
    BAND_261  = 0x0105,
    BAND_BUTT = 0x0106,
};
typedef UINT16 BAND_ENUM_UINT16;

/*
 * Description: Bandwidth
 */
enum BANDWIDTH_ENUM {
    BANDWIDTH_200K   = 0x0000, /* < GSM */
    BANDWIDTH_1M2288 = 0x0001, /* < 1x/EVDO */
    BANDWIDTH_1M28   = 0x0002, /* < TDSCDMA */
    BANDWIDTH_1M4    = 0x0003, /* < LTE 1.4M */
    BANDWIDTH_3M     = 0x0004, /* < LTE 3M */
    BANDWIDTH_5M     = 0x0005,
    BANDWIDTH_10M    = 0x0006,
    BANDWIDTH_15M    = 0x0007,
    BANDWIDTH_20M    = 0x0008,
    BANDWIDTH_25M    = 0x0009,
    BANDWIDTH_30M    = 0x000A,
    BANDWIDTH_40M    = 0x000B,
    BANDWIDTH_50M    = 0x000C,
    BANDWIDTH_60M    = 0x000D,
    BANDWIDTH_80M    = 0x000E,
    BANDWIDTH_90M    = 0x000F,
    BANDWIDTH_100M   = 0x0010,
    BANDWIDTH_200M   = 0x0011,
    BANDWIDTH_400M   = 0x0012,
    BANDWIDTH_800M   = 0x0013,
    BANDWIDTH_1G     = 0x0014,
    BANDWIDTH_BUTT   = 0x0015
};
typedef UINT16 BANDWIDTH_ENUM_UINT16;

/*
 * Description: AGC work type. (Interfere type)
 */
enum AGC_WORK_TYPE_ENUM {
    AGC_WORK_TYPE_NOBLOCK = 0x0000, /* < No Block */
    AGC_WORK_TYPE_BLOCK   = 0x0001,
    AGC_WORK_TYPE_ACS     = 0x0002, /* < Adjacent Channel Selectivity */
    AGC_WORK_TYPE_BUTT    = 0x0003
};
typedef UINT16 AGC_WORK_TYPE_ENUM_UINT16;

enum POWER_CTRL_MODE_ENUM {
    POWER_CTRL_MODE_POWER         = 0x00, /* < Power Mode */
    POWER_CTRL_MODE_RFIC_REGISTER = 0x01, /* < RFIC Register Mode */
    POWER_CTRL_MODE_GSM_VRAMP     = 0x02, /* < GSM Vramp mode */
    POWER_CTRL_MODE_BUTT          = 0x03
};
typedef UINT8 POWER_CTRL_MODE_ENUM_UINT8;

enum HfPowerCtrlModeEnum {
    HF_POWER_CTRL_MODE_POWER         = 0x00, /* *< Power Mode */
    HF_POWER_CTRL_MODE_RFIC_REGISTER = 0x01, /* *< RFIC Register Mode */
    HF_POWER_CTRL_MODE_SUBPOWER      = 0x02, /* *< Sub Power mode */
    HF_POWER_CTRL_MODE_BUTT          = 0x03
};
typedef UINT8 HF_POWER_CTRL_MODE_ENUM_UINT8;

enum SIGNAL_TYPE_ENUM {
    SIGNAL_TYPE_CW   = 0x0000,
    SIGNAL_TYPE_DW   = 0x0001,
    SIGNAL_TYPE_MODU = 0x0002,
    SIGNAL_TYPE_BUTT
};
typedef UINT16 SIGNAL_TYPE_ENUM_UINT16;

enum MODU_TYPE_ENUM {
    MODU_TYPE_LTE_BPSK     = 0x0000, /* < BPSK */
    MODU_TYPE_LTE_PI2_BPSK = 0x0001, /* < PI/2 BPSK */
    MODU_TYPE_LTE_QPSK     = 0x0002,
    MODU_TYPE_LTE_16QAM    = 0x0003,
    MODU_TYPE_LTE_64QAM    = 0x0004,
    MODU_TYPE_LTE_256QAM   = 0x0005,
    MODU_TYPE_GMSK         = 0x0006,
    MODU_TYPE_8PSK         = 0x0007,
    MODU_TYPE_BUTT
};
typedef UINT16 MODU_TYPE_ENUM_UINT16;

enum WAVEFORM_TYPE_ENUM {
    WAVEFORM_TYPE_CP_OFDM    = 0x0000,
    WAVEFORM_TYPE_DFT_S_OFDM = 0x0001,
    WAVEFORM_TYPE_BUTT
};
typedef UINT16 WAVEFORM_TYPE_ENUM_UINT16;

enum MRX_ESTIMATE_ENUM {
    MRX_ESTIMATE_POWER_MODE = 0x00, /* < MRX estimate with power mode */
    MRX_ESTIMATE_GAIN_MODE  = 0x01, /* < MRX estimate with gain mode */
    MRX_ESTIMATE_BUTT
};
typedef UINT8 MRX_ESTIMATE_ENUM_UINT8;

enum MRX_PATH_ENUM {
    MRX_R_PATH       = 0x00, /* ѡ��R PATH */
    MRX_RCCR_RC_PATH = 0x01, /* ѡ��RC path */
    MRX_RCCR_CR_PATH = 0x02, /* ѡ��CR path */
    MRX_PATH_BUTT
};
typedef UINT16 MRX_PATH_ENUM_UINT16;

enum G_TX_MODU_ENUM {
    G_TX_MODU_GMSK = 0x00, /* < GMSK modulation */
    G_TX_MODU_8PSK = 0x01, /* < 8PSK modulation */
    G_TX_MODU_BUTT
};
typedef UINT16 G_TX_MODU_ENUM_UINT16;

enum CAL_RESULT_ITEM_NAME_ENUM {
    CAL_RESULT_ITEM_NAME_GMSK_APC = 0x0000,

    /* ������������У׼������� */

    CAL_RESULT_ITEM_NAME_BUTT
};
typedef UINT16 CAL_RESULT_ITEM_NAME_ENUM_UINT16;

enum CAL_RESULT_WRITE_TYPE_ENUM {
    CAL_RESULT_WRITE_TYPE_NORMAL  = 0x0000, /* ����У׼�����µĽ��д�� */
    CAL_RESULT_WRITE_TYPE_CO_BAND = 0x0001, /* CO-BAND�����µĽ��д�� */

    CAL_RESULT_TYPE_BUTT
};
typedef UINT16 CAL_RESULT_WRITE_TYPE_ENUM_UINT16;

/*
 * desc: ����reload nv������ͳһsub6g/mmw reload nv API
 */
enum BBA_CAL_ReloadNvTypeEnum {
    BBA_CAL_RELOAD_NV_TYPE_LF = 0x0000,
    BBA_CAL_RELOAD_NV_TYPE_HF,

    BBA_CAL_RELOAD_NV_TYPE_BUTT
};
typedef UINT16 BBA_CAL_RELOAD_NV_TYPE_ENUM_UINT16;

enum BBIC_CAL_RX_SYS_STATE_ENUM {
    BBIC_CAL_RX_SYS_STATE_MAIN_CHAN_INTRA_FREQ = 0x0000, /* Main and Intra-frequency */
    BBIC_CAL_RX_SYS_STATE_MAIN_CHAN_INTER_FREQ = 0x0001, /* Main and Inter-frequency/Slave Mode */
    BBIC_CAL_RX_SYS_STATE_AUX_CHAN_INTRA_FREQ  = 0x0002, /* Auxiliary and Intra-frequency */
    BBIC_CAL_RX_SYS_STATE_AUX_CHAN_INTER_FREQ  = 0x0003, /* Auxiliary and Inter-frequency/Slave Mode */
    BBIC_CAL_RX_SYS_STATE_BUTT                 = 0x0004
};
typedef UINT16 BBIC_CAL_RX_SYS_STATE_ENUM_UINT16;

enum BBIC_CAL_START_MODE_ENUM {
    BBIC_CAL_START_MODE_ACTIVATE = 0x0000, /* Full Activation */
    BBIC_CAL_START_MODE_STANDBY  = 0x0001, /* Standby, Partial Activation */
    BBIC_CAL_START_MODE_BUTT     = 0x0002
};
typedef UINT16 BBIC_CAL_START_MODE_ENUM_UINT16;

enum BBIC_CAL_HF_ANT_TYPE_ENUM {
    BBIC_CAL_HF_ANT_TYPE_BROAD_SIDE = 0x00,
    BBIC_CAL_HF_ANT_TYPE_END_FIRE   = 0x01,
    BBIC_CAL_HF_ANT_TYPE_BUTT       = 0x02
};
typedef UINT8 BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8;

enum BBIC_CAL_RFIC_TYPE_ENUM {
    BBIC_CAL_RFIC_TYPE_HI6365 = 0x0000,
    BBIC_CAL_RFIC_TYPE_HI6370 = 0x0001,
    BBIC_CAL_RFIC_TYPE_BUTT   = 0x0002
};
typedef UINT16 BBIC_CAL_RFIC_TYPE_ENUM_UINT16;

enum BBIC_CAL_RFIC_ID_ENUM {
    BBIC_CAL_RFIC_ID_0    = 0x0000,
    BBIC_CAL_RFIC_ID_1    = 0x0001,
    BBIC_CAL_RFIC_ID_2    = 0x0002,
    BBIC_CAL_RFIC_ID_3    = 0x0003,
    BBIC_CAL_RFIC_ID_BUTT = 0x0004
};
typedef UINT16 BBIC_CAL_RFIC_ID_ENUM_UINT16;

enum BBIC_CAL_PA_VCC_CAL_FLAG_ENUM {
    BBIC_CAL_PA_VCC_CAL_FLAG_LAB     = 0x00,
    BBIC_CAL_PA_VCC_CAL_FLAG_FACTORY = 0x01,
    BBIC_CAL_PA_VCC_CAL_FLAG_BUTT    = 0x02
};
typedef UINT16 BBIC_CAL_PA_VCC_CAL_FLAG_ENUM_UINT16;

enum BBIC_CAL_PA_VCC_LOG_FLAG_ENUM {
    BBIC_CAL_PA_VCC_LOG_FLAG_OFF     = 0x00,
    BBIC_CAL_PA_VCC_LOG_FLAG_MRXCORR = 0x01,
    BBIC_CAL_PA_VCC_LOG_FLAG_SAMPLES = 0x02,
    BBIC_CAL_PA_VCC_LOG_FLAG_BOTH    = 0x03,
    BBIC_CAL_PA_VCC_LOG_FLAG_BUTT    = 0x04
};
typedef UINT16 BBIC_CAL_PA_VCC_LOG_FLAG_ENUM_UINT16;

enum BBIC_CAL_PA_VCC_CAL_TYPE_ENUM {
    BBIC_CAL_PA_VCC_CAL_TYPE_APT_VCC_COMP    = 0x00,
    BBIC_CAL_PA_VCC_CAL_TYPE_ET_VCC_COMP     = 0x01,
    BBIC_CAL_PA_VCC_CAL_TYPE_APTDPD_VCC_COMP = 0x02,
    BBIC_CAL_PA_VCC_CAL_TYPE_ETDPD_VCC_COMP  = 0x03,
    BBIC_CAL_PA_VCC_CAL_TYPE_ET_DELAY        = 0x04,
    BBIC_CAL_PA_VCC_CAL_TYPE_ETDPD_DELAY     = 0x05,
    BBIC_CAL_PA_VCC_CAL_TYPE_BUTT            = 0x6
};
typedef UINT8 BBIC_CAL_PA_VCC_CAL_TYPE_ENUM_UINT8;

enum BBIC_CAL_HF_FE_STATE_ENUM {
    BBIC_CAL_HF_FE_STATE_OFF  = 0x00,
    BBIC_CAL_HF_FE_STATE_ON   = 0x01,
    BBIC_CAL_HF_FE_STATE_IDLE = 0x02,
    BBIC_CAL_HF_FE_STATE_BUTT = 0x03
};
typedef UINT8 BBIC_CAL_HF_FE_STATE_ENUM_UINT8;

enum NR_SCS_TYPE_COMM_ENUM {
    NR_SCS_TYPE_COMM_15   = 0x00,
    NR_SCS_TYPE_COMM_30   = 0x01,
    NR_SCS_TYPE_COMM_60   = 0x02,
    NR_SCS_TYPE_COMM_120  = 0x03,
    NR_SCS_TYPE_COMM_240  = 0x04,
    NR_SCS_TYPE_COMM_BUTT = 0x05,
};
typedef UINT8 NR_SCS_TYPE_COMM_ENUM_UINT8;

enum BBIC_TEMP_CHANNEL_TYPE_ENUM {
    BBIC_TEMP_CHANNEL_TYPE_LOGIC = 0,
    BBIC_TEMP_CHANNEL_TYPE_PHY   = 1,

    BBIC_TEMP_CHANNEL_TYPE_BUTT,
};
typedef UINT16 BBIC_TEMP_CHANNEL_TYPE_ENUM_UINT16;

/*
 * �ṹ˵��: DPDT���̴���ҵ������ö��
 */
enum BBIC_DPDT_OPERTYPE_ENUM {
    BBIC_DPDT_OPERTYPE_SET = 0,
    BBIC_DPDT_OPERTYPE_GET = 1,
    BBIC_DPDT_OPERTYPE_BUTT
};
typedef VOS_UINT16 BBIC_DPDT_OPERTYPE_ENUM_UINT16;

/*
 * �ṹ˵��: DPDT���̴���ҵ������ö��
 */
enum BBA_CAL_HFRX_CALTYPE_ENUM {
    CAL_HFRX_NOM2M   = 0,
    CAL_HFRX_BASEPWR = 1,
    CAL_HFRX_PHASE   = 2,
};
typedef UINT8 BBA_CAL_HFRX_CALTYPE_ENUM_UINT8;

/*
 * �ṹ˵��: DPDT���̴���ҵ������ö��
 */
enum BBA_CAL_HFTX_CALTYPE_ENUM {
    CALTYPE_NOM2M   = 0,
    CALTYPE_BASEPWR = 1,
    CALTYPE_PHASE   = 2,
};
typedef UINT8 BBA_CAL_HFTX_CALTYPE_ENUM_UINT8;

/*
 * �ṹ˵��: DPDT���̴���ҵ������ö��
 */
enum BBIC_CAL_DCXO_SET_ENUM {
    BBIC_DCXO_SET_DISABLE = 0,
    BBIC_DCXO_SET_ENABLE  = 1,

    BBIC_DCXO_SET_BUTT
};
typedef UINT16 BBIC_CAL_DCXO_SET_ENUM_UINT16;

/*
 * Description: �ź�Դ��ʽ
 */
enum BBIC_CAL_SIGNAL_TYPE_ENUM {
    BBIC_CAL_SIGNAL_TYPE_TONE = 0x00, /* ����ģʽ */
    BBIC_CAL_SIGNAL_TYPE_DUAL_TONE,   /* ˫��ģʽ */
    BBIC_CAL_SIGNAL_TYPE_MODU,        /* ����ģʽ */
    BBIC_CAL_SIGNAL_TYPE_QUAD,        /* ����ģʽ */
    BBIC_CAL_SIGNAL_TYPE_TYPE_BUTT,
};
typedef UINT16 BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16;

/*
 * Description: ETM��λģʽö�ٶ���
 */
enum BBIC_CAL_ETM_GAIN_MODE_ENUM {
    BBIC_CAL_ETM_MODE_AUTO = 0x00, /* ETM�Զ�ģʽ */
    BBIC_CAL_ETM_MODE_HIGH = 0x01, /* ETM������ģʽ */
    BBIC_CAL_ETM_MODE_MID  = 0x02, /* ETM������ģʽ */
    BBIC_CAL_ETM_MODE_BUTT = 0x03
};
typedef UINT8 BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8;

/*
 * Description: DPD��λģʽö�ٶ���
 */
enum BBIC_CAL_DPD_LUT_INDEX_ENUM {
    BBIC_CAL_DPD_LUT_INDEX_AUTO = 0x00, /* �Զ�ģʽ */
    BBIC_CAL_DPD_LUT_INDEX_0    = 0x01,
    BBIC_CAL_DPD_LUT_INDEX_1    = 0x02,
    BBIC_CAL_DPD_LUT_INDEX_2    = 0x03,
    BBIC_CAL_DPD_LUT_INDEX_3    = 0x04,
    BBIC_CAL_DPD_LUT_INDEX_BUTT = 0x05
};
typedef UINT8 BBIC_CAL_DPD_LUT_INDEX_ENUM_UINT8;

/*
 * Description: ҵ�������ģʽ����
 */
enum BBIC_CAL_SYS_STATUS_ENUM {
    BBIC_CAL_SYS_STATUS_SERVICE = 0x00, /* ҵ��ģʽ */
    BBIC_CAL_SYS_STATUS_LISTEN  = 0x01, /* ����ģʽ */
    BBIC_CAL_SYS_STATUS_BUTT
};
typedef UINT8 BBIC_CAL_SYS_STATUS_ENUM_UINT8;

/*
 * Description: ModemID
 */
enum BBIC_CAL_MODEM_ID_ENUM {
    BBIC_CAL_MODEM0_ID = 0x00, /* ���� */
    BBIC_CAL_MODEM1_ID = 0x01, /* ���� */
    BBIC_CAL_MODEM_ID_BUTT
};
typedef UINT16 BBIC_CAL_MODEM_ID_ENUM_UINT16;

/*
 * Description: ��Ƶ�����ü�����߹ر�
 */
enum BBIC_CAL_BAND_CFG_MODE_ENUM {
    BBIC_CAL_BAND_CFG_MODE_ON  = 0x00, /* ��Band���ü��� */
    BBIC_CAL_BAND_CFG_MODE_OFF = 0x01, /* ��Band���ùر� */
    BBIC_CAL_BAND_CFG_MODE_BUTT
};
typedef UINT8 BBIC_CAL_BAND_CFG_MODE_ENUM_UINT8;

/*
 * Description: DSDS����
 */
enum BBIC_CAL_DSDS_TYPE_ENUM {
    BBIC_CAL_DSDS_TYPE_SINGAL_MODEM = 0x00, /* �������� */
    BBIC_CAL_DSDS_TYPE_DSDS2        = 0x01, /* DSDS2.0 */
    BBIC_CAL_DSDS_TYPE_DSDS3        = 0x02, /* DSDS3.0 */
    BBIC_CAL_DSDS_TYPE_BUTT
};
typedef UINT8 BBIC_CAL_DSDS_TYPE_ENUM_UINT8;

/*
 * desc: HF chs״̬����ǰֻ��0:ֱ����1:��������״̬
 */
enum BBACAL_HfChsStateEnum {
    BBACAL_HF_CHS_STATE_DIRECT_CONNECT = 0x00,
    BBACAL_HF_CHS_STATE_CROSS_OVER,
    BBACAL_HF_CHS_STATE_BUTT
};
typedef VOS_UINT8 BBACAL_HF_CHS_STATE_ENUM_UINT8;

/*
 * desc: HF port��������ǰֻ֧��2R/4R
 */
enum BBACAL_HfPortNumDefEnum {
    BBACAL_HF_PORT_NUM_DEF_TWO  = 0x02,
    BBACAL_HF_PORT_NUM_DEF_FOUR = 0x04,
    BBACAL_HF_PORT_NUM_DEF_BUTT = 0x0f,
};
typedef VOS_UINT8 BBACAL_HF_PORT_NUM_DEF_ENUM_UINT8;

/*
 * Description: TRX��RFDSP�Ľ�������
 */
enum TrxOption {
    TRX_OPTION_TX_START = 0,
    TRX_OPTION_TX_APC,
    TRX_OPTION_TX_STOP,
    TRX_OPTION_RX_START,
    TRX_OPTION_RX_AGC,
    TRX_OPTION_RX_STOP,
    TRX_OPTION_MRX_DC,
    TRX_OPTION_TX_LOADNV,
    TRX_OPTION_RX_LOADNV,
    TRX_OPTION_SYNC,

    TRX_OPTION_MNTN
};
typedef UINT16 TrxOptionUint16;

/*
 * Name        :
 * Description : ComponentTypeö��ֵ
 */
enum BBIC_CAL_COMPONENT_TYPE_ENUM {
    BBIC_CAL_COMPONENT_TYPE_LTE = 0,
    BBIC_CAL_COMPONENT_TYPE_TDS,
    BBIC_CAL_COMPONENT_TYPE_GSM,
    BBIC_CAL_COMPONENT_TYPE_UMTS,
    BBIC_CAL_COMPONENT_TYPE_CDMA,
    BBIC_CAL_COMPONENT_TYPE_NR,
    BBIC_CAL_COMPONENT_TYPE_LTEV2X = 7,
    BBIC_CAL_COMPONENT_TYPE_BUTT,
    BBIC_CAL_COMPONENT_TYPE_COMM   = 0xf,
};
typedef UINT8 BBIC_CAL_COMPONENT_TYPE_ENUM_UINT8;

#define BBIC_CAL_COMM_STRU_DEFINE_BEGIN

/*
 * Description: Component ID
 */
typedef struct {
    UINT32 uwMsgId : 16;
    UINT32 uwRsv : 8;
    UINT32 uwComponentType : 4;
    UINT32 uwComponentID : 4;
} BBIC_CAL_COMPONENT_ID_STRU;

/*
 * Description: rx cal item path list define
 */
typedef struct {
    UINT16 uhwPathNum; /* < Path num */
    UINT16 uhwRsv;
    UINT16 uhwPathIndex[BBIC_CAL_RX_MAX_PATH_NUM]; /* < RX Path Index */
} BBIC_CAL_RX_PATH_LIST_STRU;

/*
 * Description: rf cal item path list define
 */
typedef struct {
    UINT16                uhwPathIndex; /* < Path Index */
    MODU_TYPE_ENUM_UINT16 uhwModuType;
} BBIC_CAL_RF_PATH_INFO_STRU;

/*
 * Description: tx cal item path list define
 */
typedef struct {
    UINT16                     uhwPathNum; /* < valid path num */
    UINT16                     uhwRsv;
    /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_RF_PATH_INFO_STRU auhwPathInfo[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_TX_PATH_LIST_STRU;

/*
 * Name        : BBIC_CAL_MRX_PATH_LIST_STRU
 * Description : MRx cal item path list define
 */
typedef BBIC_CAL_TX_PATH_LIST_STRU BBIC_CAL_MRX_PATH_LIST_STRU;

/*
 * Description: Msg cnf struct
 */
typedef struct {
    UINT16 uhwRecMsgInd;
    UINT16 uhwRsv;
    UINT32 uwErrorCode;
} BBIC_CAL_MSG_CNF_PARA_STRU;

typedef struct {
    UINT32 uwRficGainCtrl; /* < RFIC CTRL */
    INT32  swDbbAtten;     /* < Dbb atten */
} TX_REG_CTRL_STRU;

/*
 * Description: PA config
 */
typedef struct {
    INT16  shwPaVccPwr; /* PA Vcc Target Power */
    INT16  shwPaVcc;    /* Vcc Code */
    UINT16 uhwPaBias;
    UINT16 uhwPaBias1;
    UINT16 uhwPaBias2;
    UINT16 uhwPaBias3;
    UINT8  ucPaVccMode : 1; /* < PA Vcc power mode ,0:apt , 1:et */
    UINT8  ucVccType : 2;   /* 0: ��ʾʹ��APC��������Vcc; 1: ��ʾʹ��Pa Vcc���ʲ�Vcc;
                         2: ��ʾֱ��ʹ��Vcc */
    UINT8                             ucRsv : 5;
    UINT8                             ucTxPaMode; /* < PA Mode, reference BBIC_CAL_PA_MODE_ENUM_UINT8 */
    BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8 enEtmMode;  /* ETM��λ����ģʽ, ���嶨��ο�BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8 */
    UINT8                             ucRsv1;
} TX_PA_CONFIG_STRU;

/*
 * Description: PA Vcc Cal config
 */
typedef struct {
    INT16 shwPaVccPwr;     /* < PA Vcc ctrl , Target Power using to search aptcode or Vcc mv */
    UINT8 ucPaVccMode : 1; /* < PA Vcc power mode ,0:apt , 1:et */
    UINT8 ucPaVccFlag : 2; /* < Pa Vcc mode, 0:lab vcc, 1: factory vcc, reference BBIC_CAL_PA_VCC_FLAG_ENUM_UINT8 */
    UINT8 ucDpdEn : 2;     /* 0:��ʾDPD off; 1: ��ʾDPD Bypass; 2: ��ʾDPD On */
    /* ETM��λ����ģʽ, ���嶨��ο�BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8 */
    BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8 enEtmMode : 2;
    UINT8                             ucResv : 1;
    UINT8                             ucTxPaMode; /* < PA Mode, reference BBIC_CAL_PA_MODE_ENUM_UINT8 */
} TX_PA_VCC_CAL_CONFIG_STRU;
/*
 * Description: Power para, Power mode or RFIC code mode
 */
typedef union {
    UINT16           uhwGsmTxVramp;   /* < Choice(POWER_CTRL_MODE_GSM_VRAMP) Gsm Tx Vpa Ctrl */
    INT16            shwTxPower;      /* < Choice(POWER_CTRL_MODE_POWER) Power */
    TX_REG_CTRL_STRU stTxRegCtrlPara; /* < Choice(POWER_CTRL_MODE_RFIC_REGISTER) RFIC Ctrl */
} TX_POWER_CFG_UNION;

/*
 * Description: LTE specific cal Tx APC parameters.
 */
typedef struct {
    UINT8 ucRbStart; /* < Freq comp for edge RB */
    UINT8 ucRbNum;   /* < Freq comp for edge RB */
    UINT8 aucRsv[2];
} LTE_TX_PARA_STRU;

/*
 * Description: Format FLOAT, 15bit :Exponent bit, 32bit :Tail bit
 */
typedef struct {
    UINT16 uhwExponent; /* < bit15:sign bit, other bit is exponent bit */
    UINT16 uhwRsv;
    UINT32 uwTail;
} BBIC_CAL_FLT_FORMAT_E15_T32_STRU;

/*
 * Description: IQ result struct
 */
typedef struct {
    INT16 sAmplitude; /* < A Value */
    INT16 sPhase;     /* < Phase */
} BBIC_CAL_IQ_RESULT_STRU;

/*
 * Description: LO result struct
 */
typedef struct {
    INT16 shwICode;      /* < DCI CODE */
    INT16 shwQCode;      /* < DCQ CODE */
} BBIC_CAL_LO_CODE_STRU; /* < ���ֺ�RFHAL_CAL_TX_LO_CODE_STRUһ�� */

/*
 * Description: LO result struct
 */
typedef struct {
    UINT16                shwMaxLpfGain; /* У׼�����LPF GAIN */
    UINT16                shwMinLpfGain; /* У׼����СLPF GAIN */
    BBIC_CAL_LO_CODE_STRU astTxLoCode[RFHAL_CAL_TXLO_LPF_GAIN_MAX_NUM];
} BBIC_CAL_LO_RESULT_STRU;

/*
 * Description: LO result struct
 */
typedef struct {
    UINT16                usLpfGain;
    UINT16                usRsv;
    BBIC_CAL_LO_CODE_STRU stTxLoResult;
} BBIC_CAL_LPFGAIN_LO_RESULT_STRU;

/*
 * Description: IP2 result struct
 */
typedef struct {
    INT16 shwICode; /* < DCI CODE */
    INT16 shwQCode; /* < DCQ CODE */
} BBIC_CAL_IP2_IQ_CODE_STRU;

/*
 * Description: IQ result struct
 */
typedef struct {
    UINT16 uhwDcICode;   /* < DCI CODE */
    UINT16 uhwDcQCode;   /* < DCQ CODE */
    INT16  shwRemainDcI; /* < I Remain dc */
    INT16  shwRemainDcQ; /* < Q Remain dc */
} BBIC_CAL_DC_RESULT_STRU;

/*
 * Description: RX AGC Gain Ctrl stru, use index mode
 */
typedef struct {
    UINT16                    uhwAgcTableIndex; /* < AGC���Ʊ� */
    UINT16                    uhwAgcGainIndex;  /* < [0]--Ant0,[1]--ANT1 */
    AGC_WORK_TYPE_ENUM_UINT16 enWorkType;       /* < AGC Work Type */
    UINT16                    uhwRsv;
} RX_AGC_GAIN_INDEX_STRU;

/*
 * Description: RX AGC Gain Ctrl stru, use code mode
 */
typedef struct {
    UINT16                  uhwLnaGainIndex; /* < Lna Gain Index */
    UINT16                  uhwAgcCode;      /* < AGC Gain Code */
    BBIC_CAL_DC_RESULT_STRU stRxDcConfig;
} RX_AGC_GAIN_CODE_STRU;

/*
 * Description: AGC����������
 */
typedef union {
    RX_AGC_GAIN_INDEX_STRU stAgcGainIndex; /* AGC����ΪAGC GAIN Indexģʽ����Ч */
    RX_AGC_GAIN_CODE_STRU  stAgcGainCode;  /* AGC����ΪAGC GAIN Codeģʽ����Ч */
} BBIC_CAL_RX_AGC_GAIN_CONFIG_UNION;

/*
 * Description: IP2��ȡAGC��λ���õĽṹ��
 */
typedef struct {
    BBIC_CAL_CONFIG_MODE_ENUM_UINT8   enRxCfgMode; /* AGC����ΪAGC GAIN Codeģʽ����Ч */
    UINT8                             ucRsv[3];
    BBIC_CAL_RX_AGC_GAIN_CONFIG_UNION unRxAgcInfo;
} BBIC_CAL_IP2_AGC_GAIN_CONFIG_STRU;

/*
 * Name        : BBIC_CAL_RXIQ_AGC_GAIN_CONFIG_STRU
 * Description : RXIQ AGC���õĽṹ��
 */
typedef BBIC_CAL_IP2_AGC_GAIN_CONFIG_STRU BBIC_CAL_RXIQ_AGC_GAIN_CONFIG_STRU;
typedef BBIC_CAL_IP2_AGC_GAIN_CONFIG_STRU BBIC_CAL_AGC_GAIN_PARA_STRU;

/*
 * Description: MRX Gain ctrl mode , use index.
 */
typedef struct {
    MRX_PATH_ENUM_UINT16 enMrxPath;
    UINT16               uhwMrxGainIndex; /* < Mrx Gain index */
} MRX_AGC_GAIN_INDEX_STRU;

/*
 * Description: MRX Gain ctrl mode , use code(need dc result under this mode).
 */
typedef struct {
    UINT32                  uwMrxGainCode; /* < Mrx Gain Code */
    BBIC_CAL_DC_RESULT_STRU stMrxDcConfig;
} MRX_AGC_GAIN_CODE_STRU;

/*
 * Description: MRX��������������
 */
typedef union {
    UINT16                 uhwMrxGainIndex; /* MRX GAIN Indexģʽ����Ч */
    MRX_AGC_GAIN_CODE_STRU stMrxGainCode;   /* MRX GAIN Codeģʽ����Ч */
} MRX_GAIN_CONFIG_UNION;

/*
 * Description: bbic cal result path infomation.
 */
typedef struct {
    UINT32                     uwPathErrorCode;
    UINT32                     uwRsv1; /* < Ԥ����������ʹ�ã���¼���̸澯��Ϣ */
    BBIC_CAL_RF_PATH_INFO_STRU stPathInfo;
    UINT16                     uhwRsv2; /* Ԥ����Nvʹ�� */
    UINT16                     uhwRsv3; /* Ԥ����Nvʹ�� */
} BBIC_CAL_RESULT_PATH_INFO_STRU;

typedef struct {
    BAND_ENUM_UINT16     enBand;
    RAT_MODE_ENUM_UINT16 enRatMode;
    UINT16               uhwUpLinkFlag; /* �Ƿ�������path */
    UINT16 uhwPathIndex; /* nr��fr1��fr2����ͨ��band�������֣�gsm�ĵ��Ʒ�ʽ������ͨ��pathIndex�����֣��Ƿ���Ҫ��չ */
    UINT16 uhwAntMap;    /* ��Ҫ������Щant���ã���ǰ�����Ȳ�֧�֣�����ȫF���� */
    UINT16 auhwRsv[3];
} BBIC_CAL_NV_RESET_PATH_CFG_STRU;

typedef struct {
    UINT16                          uhwPathNum; /* < ��ЧPATH���� */
    UINT16                          uhwRsv;
    /* < �����鰴����������壬ʵ��ʹ��ʱ����pathNum����̬ʹ�� */
    BBIC_CAL_NV_RESET_PATH_CFG_STRU astPathCfg[BBIC_CAL_RX_MAX_PATH_NUM];
} BBIC_CAL_NV_RESET_REQ_PARA_STRU;

#define BBIC_CAL_SELF_CAL_STRU_BEGIN

/*
 * Description: DCXO Self Cal REQ
 */
typedef struct {
    UINT16 uhwListNum; /* RX DCУ׼���PATH���� */
    UINT16 uhwRsv;
    UINT8  aucData[4];
} BBIC_CAL_COMM_SELFCAL_START_REQ_PARA_STRU;

/*
 * Description: DCXO Self Cal REQ
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT16 uhwListNum; /* Path/BAND������ */
    UINT16 uhwRsv;
    UINT8  aucData[4];
} BBIC_CAL_COMM_SELFCAL_RESULT_IND_PARA_STRU;

/*
 * Description: RX FIIQУ׼ÿ��PATH������
 */
typedef struct {
    BAND_ENUM_UINT16      enBand;              /* Ƶ��,��Path NV���л�ȡ */
    RAT_MODE_ENUM_UINT16  enRatMode;           /* ģʽ,��Path NV���л�ȡ */
    UINT16                uhwDlPathIndex;      /* ����PATH Index, �ӹ��߻�ȡ */
    BANDWIDTH_ENUM_UINT16 enBandWidth;         /* ����,������̶����� */
    UINT32                uwRxFreqInfo;        /* ����������Ƶ��,��λ100KHZ,�ӹ��߻�ȡ */
    UINT16                uhwFdiqAlgMode : 1;  /* FDIQУ׼ʱ��Ч��0��ʾʱ��ģʽ��1��ʾƵ��ģʽ */
    UINT16                uhwFdiqFragMode : 1; /* FDIQУ׼ʱƵ��ģʽ����Ч��0��ʾ���ֶΣ�1��ʾ�ֶ� */
    UINT16                uhwFdiqRsv : 2;
    UINT16                uhwFdiqFragIdx : 4; /* FDIQУ׼ʱ�ֶγ�������Ч���ֶ�������1��ʾ��һ�Σ�2��ʾ�ڶ��� */
    UINT16                uhwRetestIdx : 3;   /* ���С�źŵĳ��� ��Ҫ���У׼ �ñ�����ʶ��ǰ�ǵڼ����ز� ������1��ʼ */
    UINT16                uhwRsv : 5;
    UINT8                 ucRsv;
    UINT8                 ucAntCfgMap; /* ��������,���߻�����ܷ���У׼��ĳ�������źţ���Ҫ�ӹ��߻�ȡ */
    /* AGC GAIN����,���������Ǳ�����ǿ���뵵λ��Ҫƥ�䣬����ӹ��߻�ȡ */
    BBIC_CAL_RXIQ_AGC_GAIN_CONFIG_STRU astAgcConfig[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RX_IQ_PATH_CONFIG_STRU;

typedef struct {
    UINT16                          uhwMaxPathNum; /* ���PATH���� */
    UINT16                          uhwRsv;
    BBIC_CAL_RX_IQ_PATH_CONFIG_STRU astCalList[BBIC_CAL_RX_IQ_MAX_PATH_NUM]; /* ÿ��PATH��RX IQ������Ϣ */
} BBIC_CAL_RX_IQ_START_REQ_PARA_STRU;

/*
 * Description: ÿ��PATH��RX FIIQ���
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    /* ÿ��PATH��RX IQУ׼���,���֧��2R,[0]��ʾ����,[1]��ʾ�ּ� */
    BBIC_CAL_IQ_RESULT_STRU astRxIqInd[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RX_FIIQ_RESULT_PATH_STRU;

/*
 * Description: RX FIIQ�ϱ����
 */
typedef struct {
    UINT32                            uwErrorCode;
    UINT16                            uhwMaxPathNum; /* ���PATH���� */
    UINT16                            uhwRsv;
    BBIC_CAL_RX_FIIQ_RESULT_PATH_STRU astCalInd[BBIC_CAL_RX_IQ_MAX_PATH_NUM]; /* ÿ��PAHT��RX FIIQ��� */
} BBIC_CAL_RX_FIIQ_RESULT_IND_PARA_STRU;

/*
 * Description: IQ�˲�ϵ��,RX FDIQʹ��
 */
typedef struct {
    INT16 shwCoeffI; /* RX FDIQ I·�˲�ϵ�� */
    INT16 shwCoeffQ; /* RX FDIQ Q·�˲�ϵ�� */
} BBIC_CAL_RXIQ_COEFF_STRU;

/*
 * Description: IQ�˲�ϵ��,TX FDIQʹ��
 */
typedef struct {
    INT16 shwCoeffI; /* TX FDIQ I·�˲�ϵ�� */
    INT16 shwCoeffQ; /* TX FDIQ Q·�˲�ϵ�� */
} BBIC_CAL_IQ_COEFF_STRU;

/*
 * Description: RX FDIQ���
 */
typedef struct {
    UINT16                   uhwFdiqTaps; /* �˲���ϵ�����������15�� */
    UINT16                   uhwRsv;
    BBIC_CAL_RXIQ_COEFF_STRU astFdiqCoeff[RFHAL_CAL_RX_FDIQ_TAPS_MAX_NUM]; /* ÿ�׵��˲���ϵ��ֵ */
} BBIC_CAL_RX_FDIQ_RESULT_STRU;

/*
 * Description: ÿ��PATH��RX FDIQУ׼���
 */
typedef struct {
    UINT8 tonePowdB[RFHAL_CAL_IRR_TONE_MAX_NUM]; /* ÿ�������źŹ���, ��λdB */
    UINT8 imagPowdB[RFHAL_CAL_IRR_TONE_MAX_NUM]; /* ÿ�����Ĳο�����, ��λdB */
    SINT8 iRRRslt[RFHAL_CAL_IRR_TONE_MAX_NUM];   /* IRR������, ���֧��8���� */
} BBIC_CAL_IrrResultStru;

/*
 * Description: ÿ��PATH��RX FDIQУ׼���
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT16                         uhwFdiqAlgMode : 1;  /* FDIQУ׼ʱ��Ч��0��ʾʱ��ģʽ��1��ʾƵ��ģʽ */
    UINT16                         uhwFdiqFragMode : 1; /* FDIQУ׼ʱƵ��ģʽ����Ч��0��ʾ���ֶΣ�1��ʾ�ֶ� */
    UINT16                         uhwFdiqRsv : 2;
    UINT16                         uhwFdiqFragIdx : 4; /* FDIQУ׼ʱ�ֶγ�������Ч���ֶ�������1��ʾ��һ�Σ�2��ʾ�ڶ��� */
    UINT16                         uhwRsv : 8;
    UINT16                         uhwRsv2;
    BBIC_CAL_RX_FDIQ_RESULT_STRU   astRxIqInd[RFHAL_CAL_MAX_ANT_NUM]; /* 2R���ߵ�RX IQУ׼���,[0]��ʾ����,[1]��ʾ�ּ� */
    BBIC_CAL_IrrResultStru         irrRslt;                           /* IRR������ */
} BBIC_CAL_RX_FDIQ_RESULT_PATH_STRU;

/*
 * Description: RX FDIQУ׼���
 */
typedef struct {
    UINT32                            uwErrorCode;
    UINT16                            uhwMaxPathNum; /* ���PATH���� */
    UINT16                            uhwRsv;
    BBIC_CAL_RX_FDIQ_RESULT_PATH_STRU astCalInd[BBIC_CAL_RX_IQ_MAX_PATH_NUM]; /* ÿ��PATHУ׼��� */
} BBIC_CAL_RX_FDIQ_RESULT_IND_PARA_STRU;

/*
 * Description: ÿ��PATH��TX IQ������Ϣ
 */
typedef struct {
    BAND_ENUM_UINT16     enBand;         /* Ƶ��,��Path NV���л�ȡ */
    RAT_MODE_ENUM_UINT16 enRatMode;      /* ģʽ,��Path NV���л�ȡ */
    UINT32               uwTxFreqInfo;   /* ����Ƶ��,��λ100KHZ, ��Path NV���л�ȡ */
    UINT16               uhwUlPathIndex; /* ����PATH Index, �ӹ��߻�ȡ */
    UINT16 uhwLpfConfig; /* LPF����,��ʱ�ӹ��߻�ȡ,�����Ż�,��256QAM�̶�һ��LPF����,256QAM��Ҫ֧��7��LPF���� */
    UINT16 uhwRsv;
    UINT16 uhwValidCnt;                                        /* ��ЧRF GAIN��λ,��Path NV���л�ȡ */
    TX_REG_CTRL_STRU astRficPara[BBIC_CAL_TX_APC_MAX_CAL_NUM]; /* RF GAIN����,���֧��20��,��Path NV���л�ȡ */
    /* ÿ��RF GAIN��Ӧ��MRX��λ,����ÿ��RF GAIN��Ӧ�Ĺ���ֵ�����õ�,��Path NV���л�ȡ */
    UINT16           auhwMrxGainIndex[BBIC_CAL_TX_APC_MAX_CAL_NUM];
} BBIC_CAL_TX_IQ_PATH_CONFIG_STRU;

/*
 * Description: TX IQУ׼REQ�ṹ��
 */
typedef struct {
    UINT16                          uhwPathNum; /* ʵ��PATH���� */
    UINT16                          uhwRsv;
    /* < �����鰴�������������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_TX_IQ_PATH_CONFIG_STRU astCalList[BBIC_CAL_TX_IQ_MAX_PATH_NUM];
} BBIC_CAL_TX_IQ_START_REQ_PARA_STRU;

/*
 * Description: TX FDIQУ׼���
 */
typedef struct {
    BBIC_CAL_IQ_COEFF_STRU astFdiqCoeff[RFHAL_CAL_TX_FDIQ_TAPS_MAX_NUM]; /* ÿ�׵��˲���ϵ��ֵ */
} BBIC_CAL_TX_FDIQ_RESULT_STRU;

/*
 * Name        : BBIC_CAL_MRX_FDIQ_RESULT_STRU
 * Description : MRX FDIQУ׼���
 */
typedef BBIC_CAL_TX_FDIQ_RESULT_STRU BBIC_CAL_MRX_FDIQ_RESULT_STRU;

/*
 * Discription: ÿ��phase�ĸ��������µ�У׼�����ÿ����������Ҫ����DPO ON��DPD OFF��
 *              ����20M��������ֻ����1�ִ���,��10������
 */
typedef struct {
    /* ÿ�ִ�����֧��DPDON��DPD OFF���ֲ�����,��10�ִ���������20M(����20M)ֻ����һ�ִ��� */
    BBIC_CAL_TX_FDIQ_RESULT_STRU astTxFdiqBwRslt[RFHAL_CAL_TX_FDIQ_BW_MAX_NUM][RFHAL_CAL_SAMPLE_RATE_MAX_NUM];
} BBIC_CAL_TX_FDIQ_BW_STRU;

/*
 * Description: TX IQУ׼���
 */
typedef struct {
    BBIC_CAL_TX_FDIQ_BW_STRU stTxFdiq4phaseRslt;
    BBIC_CAL_TX_FDIQ_BW_STRU stTxFdiq8phaseRslt;
} BBIC_CAL_TX_FDIQ_PHASE_STRU;

/*
 * Description: ÿ��PATH��TXIQУ׼���
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo; /* Ƶ�� */
    /* TX IQУ׼��������֧��4��LPF��ÿ��LPF֧��2�ֲ����� */
    BBIC_CAL_TX_FDIQ_PHASE_STRU astTxIqInd[RFHAL_CAL_MIMO_RSLT_MAX_NUM];
    /* MRX IQУ׼��������ִ����������ֲ����� */
    BBIC_CAL_MRX_FDIQ_RESULT_STRU astMrxIqInd[RFHAL_CAL_MIMO_RSLT_MAX_NUM][RFHAL_CAL_MRX_FDIQ_BW_MAX_NUM];
    /* irr������ */
    BBIC_CAL_IrrResultStru irrRslt[RFHAL_CAL_TXIQ_PHASE_MAX_NUM][RFHAL_CAL_LPF_MAX_NUM];
} BBIC_CAL_TX_IQ_PATH_STRU;

/*
 * Description: TX IQУ׼���
 */
typedef struct {
    UINT32                   uwErrorCode;
    UINT16                   uhwPathNum; /* ��Ч��Path���� */
    UINT16                   uhwRsv;
     /* < �����鰴�������������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_TX_IQ_PATH_STRU astTxIqInd[BBIC_CAL_TX_IQ_MAX_PATH_NUM];
} BBIC_CAL_TX_IQ_RESULT_IND_PARA_STRU;

/*
 * Description: ÿ��PATH��TX LO������Ϣ
 */
typedef struct {
    BAND_ENUM_UINT16     enBand;                               /* Ƶ��,��Path NV���л�ȡ */
    RAT_MODE_ENUM_UINT16 enRatMode;                            /* ģʽ,��Path NV���л�ȡ */
    UINT32               uwTxFreqInfo;                         /* ����Ƶ��,��λ100KHZ, ��Path NV���л�ȡ */
    UINT16               uhwUlPathIndex;                       /* ����PATH Index, �ӹ��߻�ȡ */
    UINT16               uhwValidCnt;                          /* ��ЧRF GAIN��λ,��Path NV���л�ȡ */
    /* У׼���������ֻ��ҪУ׼4Phase��8Phase�����BB Gain����СBB Gain4��Apc Code,��Path NV���л�ȡ */
    TX_REG_CTRL_STRU astRficPara[BBIC_CAL_TX_LO_MAX_STEP_NUM];
    /* У׼���������ֻ��ҪУ׼4Phase��8Phase�����BB Gain����СBB Gain 4��ApcCode,��Path NV���л�ȡ */
    UINT16 auhwMrxGainIndex[BBIC_CAL_TX_LO_MAX_STEP_NUM];
} BBIC_CAL_TX_LO_PATH_CONFIG_STRU;

/*
 * Description: TX LOУ׼REQ�ṹ��
 */
typedef struct {
    UINT16                          uhwPathNum; /* < ��Ч��Path���� */
    UINT16                          uhwRsv;
    /* < �����鰴�������������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_TX_LO_PATH_CONFIG_STRU astCalList[BBIC_CAL_TX_IQ_MAX_PATH_NUM];
} BBIC_CAL_TX_LO_START_REQ_PARA_STRU;

/*
 * Description: TX IQMISMATCH Cal result for any path
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo; /* Ƶ�� */
    BBIC_CAL_LO_RESULT_STRU        st4PhaseResult;
    BBIC_CAL_LO_RESULT_STRU        st8PhaseResult;
} BBIC_CAL_TX_LO_PATH_STRU;

/*
 * Description: TX LO�ϱ����
 */
typedef struct {
    UINT32                   uwErrorCode;
    UINT16                   uhwPathNum; /* ��Ч��PATH���� */
    UINT16                   uhwRsv;
     /* �����鰴�������������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_TX_LO_PATH_STRU astTxLoInd[BBIC_CAL_TX_LO_MAX_PATH_NUM];
} BBIC_CAL_TX_LO_RESULT_IND_PARA_STRU;

/*
 * Dsecription: IP2 У׼Any Path Config�ṹ��
 */
typedef struct {
    UINT16 uhwBand;             /* * Band Id ���� */
    UINT16 enCaRatMode;         /* * Ca ��ʽ */
    UINT16 uhwDlPathIndex;      /* * ����Path���� ���� */
    UINT16 uhwBandConfigIndex;  /* * Band Config��Դ����, ֻ��CA��ʹ�� */
    UINT16 uhwIp2ResourceIndex; /* * IP2������Դ���� */
    UINT16 uhwRsv;
} BBIC_CAL_IP2_PATH_CONFIG_STRU;

/*
 * Dsecription: RXIP2 У׼REQ����PC�·�
 */
typedef struct {
    UINT16                        uhwPathNum;
    UINT16                        uhwRsv;
     /* * < �����鰴�������������壬ʵ��ʹ��ʱ����uhwMaxSegmentNum����̬ʹ�� */
    BBIC_CAL_IP2_PATH_CONFIG_STRU astCalList[BBIC_CAL_IP2_MAX_PATH_NUM];
} BBIC_CAL_IP2_START_REQ_PARA_STRU;

/*
 * Dsecription: RXIP2 У׼����ṹ��
 */
typedef struct {
    INT16  shwICode;          /* < DCI Code */
    INT16  shwQCode;          /* < DCQ Code */
    INT32  swImd2;            /* IMD2ֵ,����תDb�������߿ڵ�ֵ */
    INT16  shwIp2RunCodeI[6]; /* �����м��� */
    INT16  shwIp2RunCodeQ[6]; /* �����м��� */
    INT32  swRunImd2[6];      /* IMD2ֵ,����תDb�������߿ڵ�ֵ */
    INT16  shwTxPower;        /* У׼ʱ���� */
    UINT16 uhwRsv;            /* ���� */
} BBIC_CAL_IP2_IQ_RESULT_STRU;

typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;

    /*
     * IP2У׼���,��Ҫ���ֵ��ز���MIMO�����ҵ��ز�����MIMO����Ҫ���ֶ��ִ���:0խ����1 ����
     * [0][0]--���ز�խ����IP2У׼���, [0][1]--���ز�������IP2У׼���
     * [1][0]--MIMOխ����IP2У׼���,   [1][1]--MIMO������IP2У׼���
     */
    BBIC_CAL_IP2_IQ_RESULT_STRU astResult[RFHAL_CAL_MIMO_RSLT_MAX_NUM][RFHAL_CAL_IP2_CAL_BW_NUM];
} BBIC_CAL_IP2_PATH_RESULT_STRU;

/*
 * Dsecription: IP2 У׼CNF���ϱ���PC��
 */
typedef struct {
    UINT32                        uwErrorCode;
    UINT16                        uhwPathNum;
    UINT16                        uhwRsv;
    /*
     * < �����鰴�������������壬ʵ��ʹ��ʱ����uhwMaxSegmentNum����̬ʹ��
     */
    BBIC_CAL_IP2_PATH_RESULT_STRU astCalResult[BBIC_CAL_IP2_MAX_PATH_NUM];

} BBIC_CAL_IP2_RESULT_IND_PARA_STRU;

/*
 * Description: MRX DCOC cal configuration
 */
typedef struct {
    BAND_ENUM_UINT16        enBand;                                  /* Ƶ��,��Path NV���л�ȡ */
    RAT_MODE_ENUM_UINT16    enRatMode;                               /* ģʽ,��Path NV���л�ȡ */
    UINT32                  uwTxFreqInfo;                            /* Ƶ��, ��λ100KHZ,��Path NV���л�ȡ */
    UINT16                  uhwUlPathIndex;                          /* ����PATH Index, �ӹ��߻�ȡ */
    UINT16                  uhwMrxValidCnt;                          /* ��ЧMRX��λ����,��Path NV���л�ȡ */
    MRX_AGC_GAIN_INDEX_STRU astMrxGainIndex[RFHAL_CAL_MRX_GAIN_NUM]; /* MRX Gain����,��Path NV���л�ȡ */
} BBIC_CAL_MRX_DCOC_CONFIG_STRU;

/*
 * Description: MRX DCOCУ׼����ԭ��
 */
typedef struct {
    UINT16                        uhwPathNum; /* < ��ЧPATH���� */
    UINT16                        uhwRsv;
     /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_MRX_DCOC_CONFIG_STRU astCalList[BBIC_CAL_MRX_DCOC_MAX_PATH_NUM];
} BBIC_CAL_MRX_DCOC_START_REQ_PARA_STRU;

/*
 * Description: ÿ��PATH��MRX DCOC����ϱ�
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT16                         uhwRpathMrxGainCnt; /* MRX GAIN��λ���� */
    UINT16                         uhwRccrpathMrxGainCnt;
    BBIC_CAL_DC_RESULT_STRU        astMrxDcRInd[RFHAL_CAL_MRX_GAIN_NUM];    /* MRX DC����ϱ�,���֧��8��MRX GAIN */
    BBIC_CAL_DC_RESULT_STRU        astMrxDcRccrInd[RFHAL_CAL_MRX_GAIN_NUM]; /* MRX DC����ϱ�,���֧��8��MRX GAIN */
} BBIC_CAL_MRX_DCOC_PATH_STRU;

/*
 * Description: MRX DCOCУ׼����ϱ�
 */
typedef struct {
    UINT32                      uwErrorCode;
    UINT16                      uhwPathNum; /* < ��ЧPATH���� */
    UINT16                      uhwRsv;
    /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_MRX_DCOC_PATH_STRU astCalInd[BBIC_CAL_MRX_DCOC_MAX_PATH_NUM];
} BBIC_CAL_MRX_DCOC_RESULT_IND_PARA_STRU;

/*
 * Description: ÿ������������
 */
typedef struct {
    BANDWIDTH_ENUM_UINT16 enBandWith;      /* �������� */
    UINT16                usValidCnt;      /* ��Ч�����ʸ��� */
    UINT16                asSampleRate[2]; /* ���������� */
} BBIC_CAL_MRX_DELAY_BW_CONFIG_STRU;

/*
 * Description: ÿ��PATH��Ӧ��MRX DELAY����
 */
typedef struct {
    BAND_ENUM_UINT16                  enBand;         /* Ƶ��,��Path NV���л�ȡ */
    RAT_MODE_ENUM_UINT16              enRatMode;      /* ģʽ,��Path NV���л�ȡ */
    UINT32                            uwTxFreqInfo;   /* Ƶ��, ��λ100khz, ��Path NV���л�ȡ */
    UINT16                            uhwUlPathIndex; /* ����PATH Index, �ӹ��߻�ȡ */
    UINT16                            uhwRsv;
    BBIC_CAL_MRX_DELAY_BW_CONFIG_STRU stBwCofig; /* SE�������������ֻУ׼һ������ */
} BBIC_CAL_MRX_DELAY_CONFIG_STRU;

/*
 * Description: MRX DELAYУ׼REQ��Ϣ
 */
typedef struct {
    UINT16                         uhwPathNum; /* ��ЧPATH���� */
    UINT16                         uhwRsv;
    /* �����鰴����������壬ʵ�ʸ���uhwPathNum����̬ʹ�� */
    BBIC_CAL_MRX_DELAY_CONFIG_STRU astCalList[BBIC_CAL_MRX_DELAY_MAX_PATH_NUM];
} BBIC_CAL_MRX_DELAY_START_REQ_PARA_STRU;

/*
 * Description: ÿ�������µ�MRX DELAY�ϱ����
 */
typedef struct {
    BANDWIDTH_ENUM_UINT16 enBandWith;             /* ���� */
    UINT16                usValidCnt;             /* �ô����µĲ����ʸ��������֧��2�������� */
    UINT16                ahwSampleRateResult[2]; /* ÿ�������ʵ�У׼��� */
} BBIC_CAL_MRX_DELAY_BW_RESULT_STRU;

/*
 * Description: ÿ��Path��Mrx Delay����ϱ�
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU    stPathInfo;
    BBIC_CAL_MRX_DELAY_BW_RESULT_STRU astMrxDelayInd; /* SE�������������ֻУ׼һ������ */
} BBIC_CAL_MRX_DELAY_PATH_STRU;

/*
 * Description: ���PATH��MRX DELAY�ϱ����
 */
typedef struct {
    UINT32                       uwErrorCode;
    UINT16                       uhwPathNum; /* ��ЧPATH���� */
    UINT16                       uhwRsv;
    /* �����鰴����������壬ʵ�ʸ���uhwPathNum����̬ʹ�� */
    BBIC_CAL_MRX_DELAY_PATH_STRU astCalInd[BBIC_CAL_MRX_DELAY_MAX_PATH_NUM];
} BBIC_CAL_MRX_DELAY_RESULT_IND_PARA_STRU;

/*
 * Description:��ʱ��ʹ��
 */
typedef struct {
    UINT16                 uhwAgcValidCnt;
    UINT16                 uhwRsv;
    RX_AGC_GAIN_INDEX_STRU astAgcIndex[RFHAL_CAL_RX_MAX_VGA_NUM];
} BBIC_CAL_RX_AGC_CODE_LIST_STRU;

/*
 * Description:
 */
typedef struct {
    BAND_ENUM_UINT16               enBand;         /* Ƶ��,��Path NV���л�ȡ */
    RAT_MODE_ENUM_UINT16           enRatMode;      /* ģʽ,��Path NV���л�ȡ */
    UINT32                         uwFreqInfo;     /* Ƶ��,��Path NV���л�ȡ,��λ100KHZ */
    UINT16                         uhwDlPathIndex; /* DL��ԴPath Index���ӹ����·� */
    BANDWIDTH_ENUM_UINT16          enBandWidth;    /* У׼����, ��ģ�̶�1.4M,���������̶� */
    UINT8                          ucAntCfgMap;    /* ��������MAP,��Path NV���л�ȡ */
    UINT8                          aucRsv[3];
    BBIC_CAL_RX_AGC_CODE_LIST_STRU astRxAgcCfg[RFHAL_CAL_MAX_ANT_NUM]; /* RX DCУ׼�б�,��NV���л�ȡ */
} BBIC_CAL_RX_DCOC_CONFIG_STRU;

/*
 * Description: Rx DCOC Cal Req
 */
typedef struct {
    UINT16                       uhwPathNum; /* RX DCУ׼���PATH���� */
    UINT16                       uhwRsv;
    /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_RX_DCOC_CONFIG_STRU astCalList[BBIC_CAL_RX_DCOC_MAX_PATH_NUM];
} BBIC_CAL_RX_DCOC_START_REQ_PARA_STRU;

/*
 * desc : dcxo����У׼���ӵ�path��dcocУ׼���̣�������ֹ�λ�������ߺ�ɾ��
 */
typedef struct {
    BAND_ENUM_UINT16                    band;        /* Ƶ��,��Path NV���л�ȡ */
    RAT_MODE_ENUM_UINT16                ratMode;     /* ģʽ,��Path NV���л�ȡ */
    UINT16                              dlPathIndex; /* DL��ԴPath Index���ӹ����·� */
    UINT8                               antCfgMap;   /* ��������MAP,��Path NV���л�ȡ */
    UINT8                               rsv;
    RX_AGC_GAIN_INDEX_STRU              rxAgcCfg[RFHAL_CAL_MAX_ANT_NUM]; /* RX DCУ׼�б�,��NV���л�ȡ */
} BBIC_CAL_DcxoSelfCalDcocReqPara;

/*
 * Description: ÿ�����ߵ�RX DCOC�ϱ����
 */
typedef struct {
    /* ÿ��VGA��У׼��������֧��16�� */
    BBIC_CAL_DC_RESULT_STRU astRxDcInd[RFHAL_CAL_MIMO_RSLT_MAX_NUM][RFHAL_CAL_RX_MAX_VGA_NUM];
} BBIC_CAL_RX_DCOC_ANT_STRU;

/*
 * Description: ÿ��PATH��RX DCOC�ϱ����
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    BBIC_CAL_RX_DCOC_ANT_STRU      astRxDcInd[RFHAL_CAL_MAX_ANT_NUM]; /* 2R��RX DC�����0��ʾ�������,1��ʾ�ּ���� */
} BBIC_CAL_RX_DCOC_PATH_STRU;

/*
 * Description: ���PATH��RX DC�ϱ����,Ŀǰ��֧��192��PATH
 */
typedef struct {
    UINT32                     uwErrorCode;
    UINT16                     uhwPathNum; /* Path������ */
    UINT16                     uhwRsv;
    /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_RX_DCOC_PATH_STRU astCalInd[BBIC_CAL_RX_DCOC_MAX_PATH_NUM];
} BBIC_CAL_RX_DCOC_RESULT_IND_PARA_STRU;

/*
 * Description: rf setting req
 */
typedef struct {
    BBIC_CAL_TX_PATH_LIST_STRU stPathInfo; /* < Path info */
} BBIC_CAL_GE_RF_SETTING_REQ_PARA_STRU;

/*
 * Description: Rx DCOC any list result Ind
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT16                         auhwRfSettingIndex[GE_RF_GAIN_NUM]; /* û��ʹ�õ�RF Gainֱ����0 */
} GE_RF_SETTING_CAL_RESULT_STRU;

/*
 * Description: rf setting req
 */
typedef struct {
    UINT32                        uwErrorCode;
    UINT16                        uhwPathNum; /* < valid path num */
    UINT16                        uhwRsv;
     /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    GE_RF_SETTING_CAL_RESULT_STRU astData[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_GE_RF_SETTING_IND_PARA_STRU;

/*
 * Description: ����path��������Ϣ
 */
typedef struct {
    RAT_MODE_ENUM_UINT16 enRatMode;      /* ģʽ */
    UINT16               uhwUlPathIndex; /* DL��ԴPath Index���ӹ����·� */
    UINT32               uwRsv[3];       /* ����λ,��չ�� */
} BBIC_CAL_RAT_SELFCAL_PATH_CONFIG_STRU;

/*
 * Description: ����path����У׼��У׼����ԭ��
 */
typedef struct {
    UINT16 uhwPathNum; /* < ��ЧPATH���� */
    UINT16 uhwRsv;
    /*
     * ֧�ֱ䳤�������������ʵ����д��BBIC_CAL_TX_MAX_PATH_NUMֻ�Ǿ�������Ҫ��֤�·����ϱ�����Ϣ������16KB
     */
    BBIC_CAL_RAT_SELFCAL_PATH_CONFIG_STRU astPath[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_TX_FILTER_START_REQ_PARA_STRU;

/*
 * �ṹ˵����TX FILTER RC2codeֵ
 */
typedef struct {
    INT16 ashwDacPhase[4]; /* 4��DAC��λ */
} BBIC_CAL_TX_FILTER_SINGLE_MODE_STRU;

/*
 * Description: TX filterУ׼���
 */
typedef struct {
    BBIC_CAL_TX_FILTER_SINGLE_MODE_STRU astLpfMode[7]; /* 7��LPF MODE */
} BBIC_CAL_TX_FILTER_RESLUT_STRU;

/*
 * Description: ÿ��PATH��У׼���
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT32                         uwPathDataLen; /* ��ǰpath�Ľṹ�峤��,������stPathInfo��uwPathDataLen */
    BBIC_CAL_TX_FILTER_RESLUT_STRU stPathRsltPara;
} BBIC_CAL_TX_FILTER_IND_PATH_STRU;

/*
 * Description: ���PATH��TX FILTER�ϱ����,Ŀǰ��֧��80��PATH
 */
typedef struct {
    UINT32                           uwErrorCode;
    UINT16                           uhwPathNum; /* Path������ */
    UINT16                           uhwRsv;
    BBIC_CAL_TX_FILTER_IND_PATH_STRU astPathPara[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_TX_FILTER_RESULT_IND_PARA_STRU;

/*
 * Description: ����path��������Ϣ
 */
typedef struct {
    RAT_MODE_ENUM_UINT16 enRatMode;      /* ģʽ */
    UINT16               uhwUlPathIndex; /* ��ԴPath Index���ӹ����·� */
    UINT16               uhwBandWidth;   /* ���� */
    UINT16               uhwRsv;         /* ������չ�� */
    UINT32               uwMrxDelayInit; /* mrx delay��ʼֵ */
    INT32                swMrxDelayStep; /* mrx delay��ȡ����step */
} BBIC_CAL_SELFCAL_PATH_CONFIG_STRU;

/*
 * Description: ����path����У׼��У׼����ԭ��
 */
typedef struct {
    UINT16 uhwPathNum; /* < ��ЧPATH���� */
    UINT16 uhwRsv;
    /*
     * ֧�ֱ䳤�������������ʵ����д��BBIC_CAL_TX_MAX_PATH_NUMֻ�Ǿ�������Ҫ��֤�·����ϱ�����Ϣ������16KB
     */
    BBIC_CAL_SELFCAL_PATH_CONFIG_STRU astPath[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_MRX_DELAY_REQ_PARA_STRU;

/*
 * Description: ÿ��PATH��MrxDelayУ׼���
 */
typedef struct {
    UINT16 uhwValidCnt;
    UINT16 uhwRsv;
    UINT16 auhwMrxDelay[RFHAL_CAL_TX_MRX_SAMPLE_RATE_MAX_NUM];
} BBIC_CAL_MRX_DELAY_VALUE_STRU;

/*
 * Description: ÿ��PATH��У׼���
 */
typedef struct {
    UINT32                        uwErrCode;
    UINT16                        uhwPathIndex;
    UINT16                        uhwBandWidth;
    BBIC_CAL_MRX_DELAY_VALUE_STRU stPathIndPara;
} BBIC_CAL_MRX_DELAY_IND_PATH_STRU;

#define BBIC_CAL_TRX_CAL_STRU_BEGIN
/*
 * Description:
 */
typedef struct {
    TX_POWER_CFG_UNION        unPowerConfig;  /* < Selector(enPowerParaType) Power config */
    TX_PA_VCC_CAL_CONFIG_STRU stPaPara;       /* < PA VCC and bias config */
    MRX_AGC_GAIN_INDEX_STRU   stMrxGainIndex; /* < Mrx Gain Index */
} BBIC_CAL_TX_STEP_STRU;

/*
 * Description: tx trigger when RX calibration
 */
typedef struct {
    RAT_MODE_ENUM_UINT16  enRatMode;      /* < Rat Mode */
    BAND_ENUM_UINT16      enBand;         /* < Band No. */
    UINT16                uhwTxPathIndex; /* < Tx Path Index */
    UINT8                 agcGainIndex;
    UINT8                 triggerAntMap;
    UINT32                uwFreqInfo; /* < Center freqency of each band, the unit is Khz */
    BBIC_CAL_TX_STEP_STRU stStepData; /* < Total Step Data Cfg */
} BBIC_CAL_RX_TX_TRIG_CONFIG_STRU;

/*
 * Description: RX any path config
 */
typedef struct {
    BAND_ENUM_UINT16     enBand;       /* < Band Number */
    RAT_MODE_ENUM_UINT16 enRatMode;    /* < Rat Mode */
    UINT16               uhwPathIndex; /* < Path Index */
    UINT16               uhwFreqNum;   /* < Frequency cnt */
} BBIC_CAL_RX_PATH_CONFIG_STRU;

/*
 * Description: RX any frequency config
 */
typedef struct {
    UINT32 uwFreqInfo;     /* < Center freqency of each band,the unit is Khz */
    UINT16 uwRxPatternNum; /* < Rx Patten cnt */
    UINT16 uwStepNum;      /* < AGC Gain Index number */
} BBIC_CAL_RX_FREQ_CONFIG_STRU;

/*
 * Description: RX AGC Step Config struct
 */
typedef struct {
    RX_AGC_GAIN_INDEX_STRU astRxAgcConfig[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RX_AGC_STEP_CONFIG_STRU;

/*
 * Description:
 */
typedef struct {
    UINT16                          uhwTriggerMode;   /* < ������ʽ, 0 - ��ʾRX����, 1 - ��ʾTX���� */
    INT16                           hwRxTriggerLevel; /* < RX������ʽʱ�����źŵ�ǿ�ȣ���λΪ1/8dBm */
    BBIC_CAL_RX_TX_TRIG_CONFIG_STRU stTrxTriggerCfg;

    STEP_WIDTH_ENUM_UINT8 enStepWidth; /* < Step width, Unit is us */
    UINT8                 ucAntCfgMap; /* < BIT0--ANT0,BIT1--ANT1 */
    UINT16                uhwRsv;
    UINT16                uhwPathNum;    /* < Path Config num */
    UINT16                uhwFreqNum;    /* < Freq Config Num */
    UINT16                uhwPatternNum; /* < Pattern Config Num */
    UINT16                uhwStepNum;    /* < Step Config num */
    /*
     * Data Segment, ausData, format:
     *  BBIC_CAL_RX_PATH_CONFIG_STRU astPathConfig[n];      Any Path cfg, n=usPathConfigNum
     *  BBIC_CAL_RX_FREQ_CONFIG_STRU astFreqConfig[n];      Any Freq cfg, n=usFreqConfigNum
     *  UINT32                       aulRxPatternConfig[n]; Total Pattern
     * cfg,n=usPatternConfigNum,��װ��Լ����bit0��ʼȡֵ,
     *  ����������ȡֵ BBIC_CAL_RX_AGC_STEP_CONFIG_STRU   stAgcGainCode[n]; AGC Gain
     * Code
     */
#ifdef MODEM_FUSION_VERSION
#pragma warning(disable:4200)
#endif
    UINT8 aucData[BBIC_CAL_MUTABLE_DATA_LEN];
} BBIC_CAL_RX_START_REQ_PARA_STRU;

/*
 * Description: RX Cal Result report Ind
 */
typedef struct {
    INT16 ashwRssiAnt[RFHAL_CAL_MAX_ANT_NUM]; /* < Rssi report,0--Ant0,1--Ant1 */
} BBIC_CAL_RX_RSSI_RESULT_STRU;

/*
 * Description: RX Cal Result report Ind
 */
typedef struct {
    UINT32 uhwErrorCode;
    UINT16 uhwCalTempNum; /* < cal Temp Cnt, one path one temp */
    UINT16 uhwRssiNum;    /* < Rssi Cnt,Main Rssi cnt + Div Rssi Cnt */
    /*
     * Data segment, aucData, format:
     * INT32                       asCalTemp[n];  Cal temp list
     * BBIC_CAL_RX_RSSI_RESULT_STRU    stRssi[n];     Rssi Result list
     */
#ifdef MODEM_FUSION_VERSION
#pragma warning(disable:4200)
#endif
    UINT8 aucData[BBIC_CAL_MUTABLE_DATA_LEN];
} BBIC_CAL_RX_RESULT_IND_PARA_STRU;

/*
 * Description: TX any step config for a frequency
 */
typedef struct {
    UINT32                uwFreqInfo;    /* < Center freqency of each band, the unit is Khz */
    UINT16                uhwStepNum;    /* < Step Num */
    UINT16                uhwPatternNum; /* < Pattern Num, aulTxPatternConfig[(usPatternNum + 31)/32] */
    BANDWIDTH_ENUM_UINT16 enBandWidth;   /* < Bandwidth */
    UINT16                uhwCtuneEn : 4;
    UINT16                uhwCtuneIndex : 4;
    UINT16                uhwRsv : 8;
} BBIC_CAL_TX_FREQ_CONFIG_STRU;

/*
 * Description: TX any path config
 */
typedef struct {
    RAT_MODE_ENUM_UINT16 enRatMode;      /* < Rat Mode */
    BAND_ENUM_UINT16     enBand;         /* < Band No. */
    UINT16               uhwTxPathIndex; /* < Tx Path Index */
    UINT16               uhwFreqNum;     /* < Freq Num */
} BBIC_CAL_TX_PATH_CONFIG_STRU;

typedef struct {
    STEP_WIDTH_ENUM_UINT8      enStepWidth;     /* < Step width, Unit is us */
    POWER_CTRL_MODE_ENUM_UINT8 enPowerCtrlMode; /* < Select Power ctrl mode */
    SIGNAL_TYPE_ENUM_UINT16    enSignalType;    /* < Apt����,���Ʋ����� */
    MODU_TYPE_ENUM_UINT16      enModuType;
    UINT16                     uhwMrxEnable;  /* < Mrx Enable or Disable, 1--Enable, 0--Disable */
    UINT16                     uhwPathNum;    /* < Path Config num */
    UINT16                     uhwFreqNum;    /* < Freq Config num */
    UINT16                     uhwPatternNum; /* < Pattern Config num */
    UINT16                     uhwStepNum;    /* < Step Config num */
    /*
     * Data Segment, ausData, format:
     *  BBIC_CAL_TX_PATH_CONFIG_STRU astPathConfig[n];      Any Path cfg, n=usPathConfigNum
     *  BBIC_CAL_TX_FREQ_CONFIG_STRU astFreqConfig[n];      Any Freq cfg, n=usFreqConfigNum
     *  UINT32                       aulTxPatternConfig[n]; Total Pattern Cfg,n=ceil(usPatternConfigNum / 32
     * ),��װ��Լ����bit0��ʼȡֵ,����������ȡֵ BBIC_CAL_TX_STEP_STRU        astStepData[n];        Total Step Data Cfg
     */
#ifdef MODEM_FUSION_VERSION
#pragma warning(disable:4200)
#endif
    UINT8 aucData[BBIC_CAL_MUTABLE_DATA_LEN];
} BBIC_CAL_TX_START_REQ_PARA_STRU;

typedef struct {
    RAT_MODE_ENUM_UINT16  enRatMode;      /* Rat Mode */
    BAND_ENUM_UINT16      enBand;         /* Band No. */
    UINT16                uhwTxPathIndex; /* Tx Path Index */
    BANDWIDTH_ENUM_UINT16 enBandWidth;    /* Bandwidth ,reference BANDWIDTH_ENUM_UINT16 */
    UINT32                uwFreqInfo;     /* Center Freq of each Band, the unit is kHz */
} BBIC_CAL_PA_VCC_PATH_CONFIG_STRU;

typedef struct {
    BBIC_CAL_PA_VCC_CAL_FLAG_ENUM_UINT16 uhwCalFlag : 1;     /* У׼����ȡģʽ, 0: ��ȡ��1:У׼ */
    UINT16                               uhwMrxCorrType : 1; /* 0:���� ,1:���ֵ */
    BBIC_CAL_PA_VCC_LOG_FLAG_ENUM_UINT16 uhwLogFlag : 2;     /* ά�⿪��, 0: �ر�ά�⣬1: �ϱ�ԭʼ���������� MrxCorr��
                                                       2: �ϱ���ϵ����� Samples��3: ǰ���߾��ϱ� */
    UINT16 uhwRsv : 12;
    UINT16 uhwPathNum; /* path num */

    /*
     * aucData segment, format:
     * BBIC_CAL_PA_VCC_PATH_CONFIG_STRU   astPathCfg[n]; path config list, n = uhwPathNum
     */
    UINT8 aucData[4];
} BBIC_CAL_VCC_START_REQ_PARA_STRU;

typedef struct {
    RAT_MODE_ENUM_UINT16             enRatMode;         /* Rat Mode */
    BAND_ENUM_UINT16                 enBand;            /* Band No. */
    UINT16                           uhwTxPathIndex;    /* Tx Path Index */
    BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16 enSignalType;      /* < ֻ��ʹ��4�������ģʽ */
    UINT32                           uwFreqInfo;        /* Center Freq of each Band, the unit is kHz */
    MODU_TYPE_ENUM_UINT16            enModType;         /* valid under modulation signal */
    WAVEFORM_TYPE_ENUM_UINT16        enWaveType;        /* valid under nr-sub6g modulation signal, */
    UINT32                           uwBandWidthBitMap; /* ÿ��bit����BANDWIDTH_ENUM��Ӧ������Ч */
} BBIC_CAL_ET_DELAY_PATH_CONFIG_STRU;

typedef struct {
    UINT16 uhwCalFlag; /* 0: Kֵ��1:��Ƶ����2:У׼ */
    UINT16 uhwPathNum; /* path num */

    /*
     * aucData segment, format:
     * BBIC_CAL_ET_DELAY_PATH_CONFIG_STRU   astPathCfg[n]; path config list, n = uhwPathNum
     */
    UINT8 aucData[4];
} BBIC_CAL_ET_DELAY_START_REQ_PARA_STRU;

/*
 * Description: RF DEBUG COMMON Config para
 */
typedef struct {
    MODEM_ID_ENUM_UINT16             enModemId;     /* < Modem Id */
    RAT_MODE_ENUM_UINT16             enRatMode;     /* < Rat Mode */
    BAND_ENUM_UINT16                 enBand;        /* < Band No. */
    BANDWIDTH_ENUM_UINT16            enBandWith;    /* < BandWidth */
    BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16 uhwSignalType; /* < refer to BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16 */
    MODU_TYPE_ENUM_UINT16            enModType;     /* < valid under modulation signal */
    WAVEFORM_TYPE_ENUM_UINT16        enWaveType;    /* < valid under nr-sub6g modulation signal, */
    UINT16                           uhwMimoType;   /* < Mimo����,Ŀǰ����MTʹ��: 2 - 2T/2R, 4 - 4R, 8 - 8R */
    UINT32                           uwTxFreqInfo;  /* < Tx Frequence info, unit is khz */
    UINT32                           uwRxFreqInfo;  /* < Rx Frequence info, unit is khz */
    UINT16                           uhwUlPath;     /* < Ul Path Info */
    UINT16                           uhwDlPath;     /* < Dl Path Info */
} BBIC_CAL_RF_DEBUG_COMMON_PARA_STRU;

typedef struct {
    BBIC_CAL_RF_DEBUG_COMMON_PARA_STRU stPathCfg;       /* path config info */
    UINT8                              ucTxEnable;      /* 1--Tx enable, 0--Tx Disable */
    POWER_CTRL_MODE_ENUM_UINT8         enPowerCtrlMode; /* Power Ctrl Mode */
    SINT8 scDbbAdjust; /* dbb adjust value ,used to adjust default rficCtrl, only POWER_CTRL_MODE_POWER mode valid, unit
                          0.1dB */
    BBIC_CAL_PA_VCC_CAL_TYPE_ENUM_UINT8 enPaVccCalType; /* cal type ,distinguish apt/apt dpd/et/et dpd comp, apt/et
                                                           tfcomp, reference to BBIC_CAL_PA_VCC_CAL_TYPE_ENUM_UINT8 */
    TX_PA_VCC_CAL_CONFIG_STRU         stPaPara;
    TX_POWER_CFG_UNION                unPowerPara;
    INT16                             shwDpdPower;
    UINT16                            uhwEtIntDelay;
    BBIC_CAL_DPD_LUT_INDEX_ENUM_UINT8 ucDpdGainMode;
    UINT8                             aucRsv[3];
} BBIC_CAL_PA_VCC_COMPRESS_REQ_PARA_STRU;

typedef BBIC_CAL_PA_VCC_PATH_CONFIG_STRU BBIC_CAL_PA_GAIN_DELTA_PATH_CONFIG_STRU;

typedef struct {
    UINT16 uhwPathNum; /* path num */
    UINT16 uhwRsv;

    /*
     * aucData segment, format:
     * BBIC_CAL_PA_GAIN_DELTA_PATH_CONFIG_STRU
     *                                   astPathCfg[n]; path config list, n = uhwPathNum
     */
    UINT8 aucData[4];
} BBIC_CAL_PA_GAIN_DELTA_REQ_PARA_STRU;

typedef struct {
    RAT_MODE_ENUM_UINT16             enRatMode;        /* Rat Mode */
    BAND_ENUM_UINT16                 enBand;           /* Band No. */
    BANDWIDTH_ENUM_UINT16            enDpdBandWidth;   /* Bandwidth ,reference BANDWIDTH_ENUM_UINT16 */
    BANDWIDTH_ENUM_UINT16            enEtDpdBandWidth; /* Bandwidth ,reference BANDWIDTH_ENUM_UINT16 */
    UINT16                           uhwTxPathIndex;   /* Tx Path Index */
    MODU_TYPE_ENUM_UINT16            enModType;        /* < valid under modulation signal */
    WAVEFORM_TYPE_ENUM_UINT16        enWaveType;       /* < valid under nr-sub6g modulation signal, */
    BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16 enSignalType;     /* < ֻ��ʹ��4�������ģʽ */
    UINT16                           uhwRsv;
    UINT16                           uhwFreqNum;
    UINT32                           auwFreqInfo[BBIC_DPD_CAL_FEQ_NUM]; /* unit is Khz */
} BBIC_CAL_DPD_PATH_CONFIG_STRU;

typedef struct {
    UINT16 uhwPathNum; /* path num */
    UINT16 uhwRsv;
    /*
     * aucData segment, format:
     * BBIC_CAL_DPD_PATH_CONFIG_STRU   astPathCfg[n]; path config list, n = uhwPathNum
     */
    UINT8 aucData[4];
} BBIC_CAL_DPD_START_REQ_PARA_STRU;

typedef struct {
    BBIC_CAL_RF_PATH_INFO_STRU stPathInfo; /* < Path Index */
    UINT16                     uhwMask;    /* < 0 Enable 1 Disable
                                                            bit0 : RfSetting,
                                                            bit1 : Apc,
                                                            bit2 : Ramp,
                                                            bit3 : FreqComp,
                                                            bit4 : Edge Dpd */
    UINT16 uhwRsv;
} BBIC_CAL_GETX_PATH_INFO_STRU;

/*
 * Dsecription: 2G TX У׼REQ
 */
typedef struct {
    UINT16                  uhwPathNum;                                    /* < valid path num */
    SIGNAL_TYPE_ENUM_UINT16 enSingleType;                                  /* < ���� or ����  ��APC��У׼ʹ�� */
     /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    BBIC_CAL_GETX_PATH_INFO_STRU astPathCalInfo[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_GE_TX_REQ_PARA_STRU;

/*
 * Description: bbic cal result path infomation.
 */
typedef struct {
    UINT32                     uwPathErrorCode;
    UINT32                     uwRsv1; /* < Ԥ����������ʹ�ã���¼���̸澯��Ϣ */
    BBIC_CAL_RF_PATH_INFO_STRU stPathInfo;
    UINT16                     uhwRsv2; /* Ԥ����Nvʹ�� */
    UINT16                     uhwRsv3; /* Ԥ����Nvʹ�� */
} BBIC_CAL_GETX_RESULT_PATH_INFO_STRU;

typedef struct {
    UINT32 auwRfSettingCode[GE_RF_GAIN_NUM]; /* û��ʹ�õ�RF Gainֱ����0 */
} GETX_RFSETTING_CAL_RESULT_STRU;

typedef struct {
    INT16  hwPower; /* ��λ0.1dB�����ʿ���Ϊ�� */
    UINT16 uhwDac;
} BBIC_CAL_GETX_APC_POINT_STRU;

/*
 * Description: ���ʵ�ѹ��
 */
typedef struct {
    UINT16                       auhwValidNum[GE_RF_GAIN_NUM]; /* ���ű�����Ч��������ֻ��һ�ű�ʱ���ڶ��ű�����Ϊ0 */
    /* ÿ�����power��dacֵ������ʱֻ��һ�ű���0��ʼ�����������ű�ʱ����һ�ű���0��ʼ���ڶ��ű���32��ʼ */
    BBIC_CAL_GETX_APC_POINT_STRU astApcPoint[GE_TX_PWR_CONT_NUM];
} BBIC_CAL_GETX_POWER_DAC_TABLE_STRU;

typedef struct {
    BBIC_CAL_GETX_POWER_DAC_TABLE_STRU stGeTxApcTbl;                   /* ��ֻ��һ�ű��ڶ��ű���0 */
    INT16                              ashwPaGainRslt[GE_PA_GAIN_NUM]; /* �ĵ�PagainУ׼��� */
    INT16 ashwPaPrechgVolt[BBIC_CAL_G_TX_PCL_NUM]; /* У׼���Ԥ���ѹ GMSK 2�� EDGE 32�� ȡ���λ */
} GETX_APC_CAL_RESULT_STRU;

typedef struct {
    SINT8 ascFreqCompValue[BBIC_CAL_FREQ_MAX_NUM]; /* <ÿ��32��Ƶ�� */
} BBIC_CAL_TX_FREQ_COMP_RESULT_PARA;

typedef struct {
    BBIC_CAL_TX_FREQ_COMP_RESULT_PARA astGainFreqResult[GE_PA_GAIN_NUM]; /* <�ĵ�  ÿ��32���� */
} GETX_FREQ_COMP_CAL_RESULT_STRU;

typedef struct {
    UINT16 uhwRampPoint;
    UINT16 uhwRsv;
    UINT16 ahwRampUp[GE_RAMP_COEF_NUM];
    UINT16 ahwRampDown[GE_RAMP_COEF_NUM];
} GE_RAMP_COFF_CAL_DATA_STRU;

typedef struct {
    GE_RAMP_COFF_CAL_DATA_STRU stCalRampCoffData[GE_RAMP_PWR_LEVEL_NUM];
} GE_RAMP_CAL_RESULT_STRU;

typedef struct {
     /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwPathNum����̬ʹ�� */
    GE_RAMP_CAL_RESULT_STRU astData[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_GE_RAMP_IND_PARA_STRU;

typedef struct {
    INT16 shwLutI;
    INT16 shwLutQ;
} BBIC_CAL_GETX_DPD_LUT_RSLT_STRU;

typedef struct {
    BBIC_CAL_GETX_DPD_LUT_RSLT_STRU auhwLutRslt[BBIC_CAL_GETX_DPD_LUT_POINT_NUM];
    /*
     * BBIC_CAL_GETX_DPD_LUT_POINT_NUM 128
     * 128�� DPD LUT�����
     */
    UINT16 auhwReferDac; /* * �ο�Dac */
    INT16  shwDcValue;   /* * DC��� */
} BBIC_CAL_GETX_DPD_PATH_RESULT_PARA;

typedef struct {
    UINT16                             uhwDpdLutTblNum;
    UINT16                             uhwRsv;
    BBIC_CAL_GETX_DPD_PATH_RESULT_PARA astDpdRsltPara[GE_PA_GAIN_NUM];
    UINT16                             auhwStepV[GE_PA_GAIN_NUM]; /* * GE_PA_GAIN_NUM 4 Ԥ���ӿڣ���Ӧ�ĵ�RFPA��λ */
} GETX_DPD_CAL_RESULT_STRU;

typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo; /* < Comm Path Result * */
    UINT16                         uhwMask;    /* < bit0:RfSetting,
                                                          bit1:Apc,
                                                          bit2:Ramp,
                                                          bit3 FreqComp,
                                                          bit4 Dpd */
    INT16                          shwTemperature;
    GETX_RFSETTING_CAL_RESULT_STRU stRfSettingData; /* < rfsetting Path Result * */
    GETX_APC_CAL_RESULT_STRU       stTxApcData;     /* < apc pagain precharge Path Result * */
    GE_RAMP_CAL_RESULT_STRU        stRampData;      /* < ramp Path Result * */
    GETX_FREQ_COMP_CAL_RESULT_STRU stFreqCompData;  /* < freq comp Path Result * */
    GETX_DPD_CAL_RESULT_STRU       stDpdData;       /* < dpd Path Result * */
} BBIC_CAL_GETX_PATH_RESULT_PRAR_STRU;

typedef struct {
    UINT32                              uwErrorCode; /* < ����Path��ErrorCode */
    UINT16                              uhwPathNum;  /* < valid path num */
    UINT16                              uhwRsv;
     /* < ÿ��Path��У׼��� ����ʵ���·���Path������̬ʹ�� */
    BBIC_CAL_GETX_PATH_RESULT_PRAR_STRU astPathRslt[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_GE_TX_IND_PARA_STRU;

typedef struct {
    INT16 shwDfeDci;
    INT16 shwDfeDcq;
} BBIC_CAL_GETX_DPD_STEP_RSLT_STRU;

typedef struct {
    UINT16                           uhwCwValue;
    UINT16                           uhwRsv;
    BBIC_CAL_GETX_DPD_STEP_RSLT_STRU stIqValue;
} BBIC_CAL_GETX_DPD_STEP_INFO_STRU;

typedef struct {
    BBIC_CAL_GETX_DPD_STEP_INFO_STRU astStepRslt[128];
} BBIC_CAL_GETX_DPD_ORIG_RSLT_PARA_STRU;

typedef struct {
    UINT16 uhwValidTxGainNum; /* ��Ч��λ���� */
    UINT16 uhwTxGainEnMask;   /* ��λ�Ƿ���Ч: bit0 bit1 bit2 bit3 ��λ 0 1 2 3 �Ƿ���Ч */
    BBIC_CAL_GETX_DPD_ORIG_RSLT_PARA_STRU astLutTblOrigRslt[4]; /* ÿ����λ(LUT��)����Ӧ��IQԭʼ��� */
} BBIC_CAL_GETX_DPD_ORIG_PATH_RSLT_STRU;

typedef struct {
    UINT16 uhwPathLoop; /* < valid path num */
    UINT16 uhwPathIndex;
    BBIC_CAL_GETX_DPD_ORIG_PATH_RSLT_STRU stOrigPathRslt; /* < ÿ��Path��У׼��� ����ʵ���·���Path������̬ʹ�� */
} BBIC_CAL_GETX_EDGE_DPD_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_GETX_EDGE_DPD_MNTN_INFO_STRU stPara; /* EDGE DPDУ׼��ά����Ϣ */
} BBIC_CAL_GETX_EDGE_DPD_MNTN_MSG_STRU;

/*
 * Description: TX CAL all path report IND struct
 */
typedef struct {
    UINT32 uhwErrorCode;
    UINT16 uhwCalTempCnt;   /* < cal temp cnt, one path one temp */
    UINT16 uhwMrxResultCnt; /* < Mrx Result cnt */
    /*
     * Data segment, aucData, format:
     * INT32    alCalTemp[n];    Cal temp list, message must 4 byte alignment
     * UINT32   aulMrxResult[n]; Mrx Rrsult list, message must 4 byte alignment
     * UINT32   aulTxResult[n];  Tx Rrsult list, message must 4 byte alignment
     */
    UINT8 aucData[4];
} BBIC_CAL_TX_RESULT_IND_PARA_STRU;

/*
 * Description: TX CAL one path result struct
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    /*
     * ��ǰpath��У׼�¶�
     */
    INT32 lCalTemp;
    /*
     * Apt/Et Lut����������NV�ṹ����
     */
    UINT8 ucAptIsoGainLutNum;
    UINT8 uhAptEclLutNum;
    UINT8 ucEtLutNum;

    UINT8 ucRsv;

    /*
     * apt IsoGain 4X H/M/L/UL       [A0][A1][A2][A3]
     * A0 = a0*2, A1 = a1 * 2^21, A2 = a2 * 2^21, A3  = a3 * 2^33
     * Note : lut using AptCode vs Power
     */
    INT32 wAptIsoGainLutPolyCoef[4][4];
    INT32 wAptEclLutPolyCoef[2][4];

    /*
     * et IsoGain / ECl Lut H/M        [A0][A1][A2][A3]
     *  A0 = a0*2, A1 = a1 * 2^21, A2 = a2 * 2^21, A3  = a3 * 2^33
     * Note: lut using PaVcc(mv) vs Power
     */
    INT32 wEtIsoGainLutPolyCoef[2][4];
    INT32 wEtEclLutPolyCoef[2][4];
} BBA_CAL_PA_VCC_PATH_IND_STRU;

/*
 * Description: TX CAL PA VCC all path report IND struct
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT16 uhwPathResultCnt; /* cal path num */
    UINT16 uhwRsv;
    /*
     * Data segment, aucData, format:
     * BBA_CAL_PA_VCC_PATH_IND_STRU   astPathCalResult[n];  lut result ind, n = uhwPathResultCnt
     */
    UINT8 aucData[4];
} BBIC_CAL_PA_VCC_IND_RESULT_PARA_STRU;

/*
 * Description: PA gain delta�ĵ�pathУ׼���
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;

    UINT16 uhwEtMap;    /* ��bit0��ʼ����bitλ��ʾ2�ű� */
    UINT16 uhwDpdMap;   /* ��bit0��ʼ����bitλ��ʾ4�ű� */
    UINT16 uhwEtDpdMap; /* ��bit0��ʼ����bitλ��ʾ4�ű� */
    UINT16 uhwRsv;

    INT16 shwEtPaGainDelta[2];    /* ��bitλ��λ�ô�Ž�� */
    INT16 shwDpdPaGainDelta[BBIC_DPD_NUM];   /* ��bitλ��λ�ô�Ž�� */
    INT16 shwEtDpdPaGainDelta[BBIC_DPD_NUM]; /* ��bitλ��λ�ô�Ž�� */

} BBIC_CAL_PA_GAIN_DELTA_PATH_RESULT_STRU;

/*
 * Description: PA gain delta�Ķ�path����ϱ�������log��ӡ
 */
typedef struct {
    UINT32 uwErrCode;
    UINT16 uhwPathResultCnt;
    UINT16 uhwRsv;

    /*
     * Data segment, aucData, format:
     * BBIC_CAL_PA_GAIN_DELTA_PATH_RESULT_STRU
     *                                 astPathCalResult[n];  pa gain delta result ind, n = uhwPathResultCnt
     */
    UINT8 aucData[4];
} BBIC_CAL_PA_GAIN_DELTA_IND_PARA_STRU;

/*
 * Description: TX CAL PA VCC one path one pa mode mrx coor return
 *                  ��Path��ȡ����У׼��PA���淵��mrxԭʼ����
 *                  ����Apt��ET����ģʽ
 *                  �������ϱ���PHY����������ϵ�ʱ��ֱ���ϱ�
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    INT16                          hwCalVcc; /* AptCode or Vcc Mv */

    UINT16                    uhwRsv;      /* Ԥ�� */
    TX_PA_VCC_CAL_CONFIG_STRU stPaModeCfg; /* pa mode info */

    INT32 swMrxCoorRe[BBIC_ET_LUT_CW_STEP_NUM]; /* < vcc mrx coor I value */
    INT32 swMrxCoorIm[BBIC_ET_LUT_CW_STEP_NUM]; /* < vcc mrx coor Q value */
} BBIC_CAL_PA_VCC_MRXCOOR_IND_PARA_STRU;

/*
 * Description: Pa Vcc��ȡ���� У׼���ݽ�����ϵ�����������
 *              У׼�����а�path��ӦPA���浵λУ׼���������������Ϣ,У׼������ͳһ�ϱ�LUT���
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    TX_PA_VCC_CAL_CONFIG_STRU      stPaModeCfg; /* PA������Ϣ������apt/et mode */

    UINT32 uwCalVccNum;             /* У׼��ѹ���� */
    UINT32 uwCrossPointNum;         /* ���н���ĸ��� */
    UINT32 uwVccWrongFlag;          /* ���GAIN С��ISOGAIN ��bit 0 ��ʼ��bit��0��ʾ��λֵû�н��� */
    UINT32 uwISOWrongFlag;          /* ��СGAIN ����ISOGAIN ��bit 0 ��ʼ��bit��0��ʾ��λֵû�н��� */
    UINT16 auhwVccList[32];         /* У׼��vccֵ */
    UINT16 auhwIsoEclVccTable[32];  /* �����Vccֵ */
    UINT32 auwIsoPoutTableLine[32]; /* ISO�����Pout������ֵ */
    UINT32 auwEclPoutTableLine[32]; /* ECL�����Pout������ֵ */
    UINT32 auwIsoPinTableLine[32];  /* ISO�����Pin������ֵ */
    UINT32 auwEclPinTableLine[32];  /* ECL�����Pin������ֵ */
    UINT32 auwIsoIndex[32];         /* ISO��������� */
    UINT32 auwEclIndex[32];         /* ECL��������� */
} BBIC_CAL_PA_VC_SAMPLES_IND_PARA_STRU;

typedef struct {
    INT16 ashwIData[BBIC_DPD_SPL_NUM];
    INT16 ashwQData[BBIC_DPD_SPL_NUM];
} BBA_CAL_DPD_SPL_DATA_STRU;

typedef struct {
    BBA_CAL_DPD_SPL_DATA_STRU astDpdSplData[BBIC_DPD_LUT_NUM];
} BBA_CAL_DPD_LUT_STRU;

typedef struct {
    BBA_CAL_DPD_SPL_DATA_STRU astEtDpdSplData[BBIC_ETDPD_LUT_NUM];
} BBA_CAL_ETDPD_LUT_STRU;

/*
 * Description: DPD CAL one freq result struct
 */
typedef struct {
    UINT32                 uwFreqInfo; /* < unit is Khz */
    UINT16                 dpdMap;  /* ��bit0��ʼ����bitλ��ʾ4�ű� */
    UINT16                 etDpdMap;/* ��bit0��ʼ����bitλ��ʾ4�ű� */
    BBA_CAL_DPD_LUT_STRU   astDpdLut[BBIC_DPD_NUM];   /* ��bitλ��λ�ô�Ž�� */
    BBA_CAL_ETDPD_LUT_STRU astEtDpdLut[BBIC_DPD_NUM]; /* ��bitλ��λ�ô�Ž�� */
} BBA_CAL_DPD_FREQ_IND_STRU;

/*
 * Description: DPD CAL one path result struct
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    INT32                          swCalTemp; /* ��ǰpath��У׼�¶� */
    UINT16                         uhwRsv;
    UINT16                         uhwFreqNum;
    BBA_CAL_DPD_FREQ_IND_STRU      astDpdResult[BBIC_DPD_CAL_FEQ_NUM]; /* ��Ч��������uhwFreqNum��ȡ */
} BBA_CAL_DPD_PATH_IND_STRU;

typedef struct {
    UINT32 uwErrorCode;
    UINT16 uhwPathResultCnt; /* cal path num */
    UINT16 uhwRsv;
    /*
     * Data segment, aucData, format:
     * BBA_CAL_DPD_PATH_IND_STRU   astPathCalResult[n];  n = uhwPathResultCnt
     */
    UINT8 aucData[4];
} BBIC_CAL_DPD_IND_RESULT_PARA_STRU;

/*
 * Description:ÿһ��ET��λ��ET Delay Kֵ��Ϣ
 */
typedef struct {
    UINT16 uhwEtPaGainMode;
    UINT16 uhwEtDelayKValue;
} BBA_CAL_ET_DELAY_K_PAMODE_INFO_STRU;

/*
 * Description: TX CAL one path result struct
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT16                         uhwEtPaGainNum;  // ET��Ч��λ����
    UINT16                         uhwRsv;
    BBA_CAL_ET_DELAY_K_PAMODE_INFO_STRU astEtDelayKInfo[2];
} BBA_CAL_ET_DELAY_K_PATH_IND_STRU;

/*
 * Description: TX CAL PA VCC all path report IND struct
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT16 uhwPathResultCnt; /* cal path num */
    UINT16 uhwRsv;
    /*
     * Data segment, aucData, format:
     * BBA_CAL_ET_DELAY_K_PATH_IND_STRU   astPathCalResult[n];  lut result ind, n = uhwPathResultCnt
     */
    UINT8 aucData[4];
} BBIC_CAL_ET_DELAY_K_IND_RESULT_PARA_STRU;

/*
 * Description:ÿһ��ET��λ��ET DelayУ׼����Ƶ����ȡ�Ľ����Ϣ
 */
typedef struct {
    UINT16 uhwEtPaGainMode; /* ��ǰPA��λ */
    UINT16 uhwEtIntDelay;
    UINT16 uhwEtFracDelay;
    INT16  shwCalTemp;
} BBA_CAL_ET_DELAY_PA_MODE_INFO_STRU;

/*
 * Description:ÿһ��������ET DelayУ׼����Ƶ����ȡ�Ľ����Ϣ
 */
typedef struct {
    UINT16                             uhwEtBandWidth; /* ����ֵ */
    UINT16                             uhwEtPaGainNum; /* ��ЧET��λ���� */
    BBA_CAL_ET_DELAY_PA_MODE_INFO_STRU astEtDelayInfo[2];
} BBA_CAL_ET_DELAY_BANDWIDTH_INFO_STRU;
/*
 * Description: ET Delay CAL one path result struct
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT16                         uhwCalFlag;        /* 1:��Ƶ����2:У׼ */
    UINT16                         uhwEtBandWidthNum; /* ��ЧET�������� */
    /*
     * Data segment, aucData, format:
     * BBA_CAL_ET_DELAY_BANDWIDTH_INFO_STRU   astEtBandWtidhInfo[n];  n = uhwEtBandWidthNum
     */
    UINT8 aucData[4];
} BBA_CAL_ET_DELAY_PATH_IND_STRU;

/*
 * Description: TX CAL PA VCC all path report IND struct
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT16 uhwPathResultCnt; /* cal path num */
    UINT16 uhwRsv;
    /*
     * Data segment, aucData, format:
     * BBA_CAL_ET_DELAY_PATH_IND_STRU   astPathCalResult[n];  lut result ind, n = uhwPathResultCnt
     */
    UINT8 aucData[4];
} BBIC_CAL_ET_DELAY_IND_RESULT_PARA_STRU;

#define BBIC_CAL_RF_DEBUG_TRX_STRU_BEGIN

/*
 * Description: TX baseband signal cfg
 */
typedef struct {
    UINT16 uhwSignalCnt;    /* < ������ȡֵ��Χ[1,2,4] */
    UINT16 uhwCwFreqEn : 1; /* < 0: RFDSP��������; 1:ʹ�������ֵ */
    UINT16 uhwRsv : 15;
    INT32  aswCwFreqHz[4]; /* < �з���������ֵ��ʾ+ƫ�ƣ���ֵ��ʾ-ƫ�ƣ���λHz */
} TX_BB_SIGNAL_CW_STRU;

/*
 * Description: RF DEBUG TX Power Config para
 */
typedef struct {
    POWER_CTRL_MODE_ENUM_UINT8 enPowerCtrlMode; /* < Power Ctrl Mode */
    UINT8                      ucRsv;
    UINT16                     uhwVIq; /* < IQ Value,if signal tone */
    TX_PA_CONFIG_STRU          stPaPara;
    TX_POWER_CFG_UNION         unPowerPara;
    UINT32                     rfSetttingCode; /* 2G RF setting������ */
} BBIC_CAL_RF_DEBUG_TX_POWER_PARA_STRU;

/*
 * Description: RF DEBUG TX Power Config para
 */
typedef struct {
    UINT16                          uhwMrxEanble; /* < Mrx Enable, 1--Enable, 0--Disable */
    MRX_ESTIMATE_ENUM_UINT8         enMrxEstMode; /* < Mrx Measure Mode */
    BBIC_CAL_CONFIG_MODE_ENUM_UINT8 enMrxCfgCode;
    MRX_GAIN_CONFIG_UNION           unMrxConfig; /* < Mrx Gain Code */
} BBIC_CAL_RF_DEBUG_MRX_PARA_STRU;

/*
 * Description: Wcdma Upa Config
 */
typedef struct {
    UINT16 uhwBec;
    UINT16 uhwBed1;
    UINT16 uhwBed2;
    UINT16 uhwBc;
    UINT16 uhwBd;
    UINT16 uhwTxSlotFormat; /* < Slot Format,Qpsk or 16Qam */
    UINT16 uhwTxChanNum;    /* < Tx chan Num, Max value is 4 */
    UINT16 uhwRsv;
} BBIC_CAL_RF_DEBUG_WCDMA_UPA_PARA_STRU;

/*
 * Description: Wcdma DPA Config
 */
typedef struct {
    UINT16 uhwBc;
    UINT16 uhwBd;
    UINT16 uhwBhs;
    UINT16 uhwRsv;
} BBIC_CAL_RF_DEBUG_WCDMA_DPA_PARA_STRU;

/*
 * Description: Wcdma DPA Config
 */
typedef struct {
    UINT16 uhwUpaEnable; /* < Upa Enable,1--Enable,0--Disable */
    UINT16 uhwDpaEnable; /* < Dpa Enable,1--Enable,0--Disable */
    BBIC_CAL_RF_DEBUG_WCDMA_UPA_PARA_STRU stWcdmaUpaPara;
    BBIC_CAL_RF_DEBUG_WCDMA_DPA_PARA_STRU stWcdmaDpaPara;
} BBIC_CAL_RF_DEBUG_WCDMA_PARA_STRU;

typedef struct {
    NR_SCS_TYPE_COMM_ENUM_UINT8 enScsType; /* < ���ز���� */
    UINT8                       ucRsv;
    WAVEFORM_TYPE_ENUM_UINT16   nrWaveType; /* NRģ�����ź�ʹ�ã��������ͣ�CPOFDM����DFT S OFDM */
    UINT16                      uhwRbStart; /* < ��������ֻ֧��type1 - start RB */
    UINT16                      uhwRbNum;   /* < ��������ֻ֧��type1 - numbers of RB */
} NR_TX_MODU_PARA_STRU;

/*
 * Description: Wcdma DPA Config
 */
typedef union {
    LTE_TX_PARA_STRU                  stLteRbPara;
    BBIC_CAL_RF_DEBUG_WCDMA_PARA_STRU stWcdmaPara;
    NR_TX_MODU_PARA_STRU              stNrModuPara;
} BBIC_CAL_RF_DEBUG_DEPENDED_PARA_UNION;

/*
 * Description: RF DEBUG�Ĺ������ò���
 */
typedef struct {
    MODEM_ID_ENUM_UINT16             modemId; /* Modem ID */
    RAT_MODE_ENUM_UINT16             ratMode; /* ģʽ */
    UINT16                           rsv;
    BBIC_CAL_SYS_STATUS_ENUM_UINT8   sysStatus;      /* ҵ��ģʽ��������ģʽ */
    BBIC_CAL_DSDS_TYPE_ENUM_UINT8    dsdsType;       /* DSDS���ͣ�DSDS2.0����DSDS3.0 */
    UINT8                            modemStatus;    /* Modem0���ߺ�����״̬,1��ʾModem0���ߣ�0��ʾModem0���� */
    UINT8                            txCfgPriority;  /* DSDS3.0�ĳ���,TX�������ȼ�,ȡֵ��Χ0~15 */
    BBIC_CAL_GSM_RX_MODE_ENUM_UINT8  gsmRxMode;      /* GSM RX����ģʽ,ֻ��2G RXʹ�� */
    BBIC_CAL_RX_AGC_MODE_ENUM_UINT8  rxAgcMode;      /* 2G FAST��SLOWģʽ, ֻ��2G RXʹ�� */
    BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16 signalType;     /* �ź�����,֧�ֵ�����˫���������������ź� */
    MODU_TYPE_ENUM_UINT16            modType;        /* ����ǵ��Ʒ�ʽ�������ѡ��QPSK��16QAM��64QAM��256QAM */
    TX_BB_SIGNAL_CW_STRU             stTxSignalPara; /* �����ǰ�źŷǵ����ź�,����Ҫ���õ���Ƶ��,��λHz */
} BBIC_CAL_RF_DEBUG_TRX_COMM_PARA_STRU;

/*
 * Description: RF DEBUGÿ������PATH�����ò���
 */
typedef struct {
    UINT16 txPowerEn : 1; /* TX���ʲ�������ʹ�ܣ����ʹ�ܣ���APC�����л���������TX������ز�������������,
                             1--TX��������ʹ��, 0--TX�������ò�ʹ�� */
    UINT16                            txAptEn : 1;     /* TX APT��������ʹ�ܣ�1--Tx APT enable, 0--TX APT Disable */
    UINT16                            cwAmEn : 1;      /* �������ȿɵ���ʹ��, 1: On, 0: Off */
    UINT16                            dpdEn : 2;       /* 0:��ʾDPD off; 1: ��ʾDPD Bypass; 2: ��ʾDPD On */
    UINT16                            dpdTrainEn : 1;  /* 0:��ʾDPD ��ѵ��; 1: ��ʾDPD ����ѵ�� */
    UINT16                            etDelayEn : 1;   /* EtDelay����ʹ��, 1--Enable, 0--Disable */
    UINT16                            rfSettingEn : 1; /* RF SETTING����ʹ�� */
    UINT16                            uhwRsv : 8;
    BBIC_CAL_DPD_LUT_INDEX_ENUM_UINT8 enDpdGainMode;
    UINT8                             aucRsv[3];
    INT16                             dpdPower; /* DPD������� */
    UINT16                            etIntDelay;
    UINT16                            etFracDelay;
    BBIC_CAL_RF_DEBUG_TX_POWER_PARA_STRU txPowerPara;
    BBIC_CAL_RF_DEBUG_MRX_PARA_STRU mRxPara;
} BBIC_CAL_RF_DEBUG_TX_PATH_PARA_STRU;

/*
 * Description: RF DEBUGÿ������PATH�����ò���
 */
typedef struct {
    UINT16 rxAgcCfgEn : 1; /* Agc����ʹ�ܣ�1--RX AGC����, 0--RX AGC������ */
    UINT16 evmCfgEn : 1;   /* EVM����ʹ�ܣ�1--RX EVM����, 0--RX EVM������ */
    UINT16 rssiReport : 2; /* ����RSSI�ϱ���־, 0--RSSI���ϱ�,
                              1--WB RSSI�ϱ���
                              2--NB RSSI�ϱ�
                              3--Corr RSSI�ϱ�����ʱ��֧��2��3�ĳ��� */
    UINT16                      uhwRsv : 12;
    UINT16                      ucRsv1;      /* ���ֽڶ��� */
    BBIC_CAL_AGC_GAIN_PARA_STRU agcGainPara; /* AGC GAIN���ò��� */
} BBIC_CAL_RF_DEBUG_RX_PATH_PARA_STRU;

/*
 * Description: ÿ��Band�µ�TX���ò�������band��صĲ���;
 */
typedef struct {
    BBIC_CAL_BAND_CFG_MODE_ENUM_UINT8 bandCfgMode; /* ��Band���ü�����߹رգ�������ü��
                                                       ������TXSTART����TX APC��
                                                       �Ƿ�����Startȡ�����������startCfgEn�Ƿ�ʹ�� */
    UINT8 startCfgEn;                              /* TX/RX�Ƿ�����Start��1--��ʾstatr����ʹ�ܣ�
����Ҫ����Startͨ����0--��ʾ������ʹ��,���ز���CA�¶���Ҫʹ�� */
    BAND_ENUM_UINT16 bandId;                       /* Ƶ��ID */
    UINT8            extBand;                      /* �Ƿ�Ϊ��չƵ�� */
    UINT8            ulCfgPathEn; /* ����Path����ʹ��,1--��ʾʹ�ܣ�0--��ʾ��ʹ��,���ʹ���˸ò���,��ulCfgPath������Ч */
    UINT8            ucRsv[2];    /* ���ֽڶ��� */

    BANDWIDTH_ENUM_UINT16 bandWidth; /* ���� */
    RAT_MODE_ENUM_UINT16  ratMode;   /* ģʽ */
    BBIC_CAL_RF_DEBUG_DEPENDED_PARA_UNION unTxRatPara;      /* ���и�ģ�������ò��� */
    UINT32 txFreqKhz; /* TX����Ƶ��,��λKHZ */
    UINT16 ulCfgPath; /* ��������PATH����band��antNum����2���������Ч,CA�²�ʹ��,CA�²�ʹ�� */
    UINT8  antNum;    /* ���߸���,�������֧��2T,�������֧��8R */
    UINT8  antMap;    /* AntMap, bit0 - ant0, bit-ant1,Ŀǰֻ��MTʹ�ã���ǰֻ֧�ֵ�T���� */

    BBIC_CAL_RF_DEBUG_TX_PATH_PARA_STRU txPathPara[TX_MAX_ANT_NUM]; /* ���֧��2T��ÿT������ */
} BBIC_CAL_RF_DEBUG_TX_BAND_PARA_STRU;

/*
 * Description: ÿ��Band�µ�RX���ò�������band��صĲ���;
 */
typedef struct {
    BBIC_CAL_BAND_CFG_MODE_ENUM_UINT8 bandCfgMode; /* ��Band���ü�����߹رգ�������ü��
                                                       ������TXSTART����TX APC��
                                                       �Ƿ�����Startȡ�����������startCfgEn�Ƿ�ʹ�� */
    UINT8 startCfgEn;                              /* TX/RX�Ƿ�����Start��1--��ʾstatr����ʹ�ܣ�
����Ҫ����Startͨ����0--��ʾ������ʹ��,���ز���CA�¶���Ҫʹ�� */
    BAND_ENUM_UINT16 bandId;                       /* Ƶ��ID */
    UINT8            extBand;                      /* �Ƿ�Ϊ��չƵ�� */
    UINT8            dlCfgPathEn; /* ����Path����ʹ��,1--��ʾʹ�ܣ�0--��ʾ��ʹ��,���ʹ���˸ò���,��ulCfgPath������Ч */
    UINT8            ucRsv[2];    /* ���ֽڶ��� */
    BANDWIDTH_ENUM_UINT16 bandWidth; /* ���� */
    RAT_MODE_ENUM_UINT16  ratMode;   /* ģʽ */
    UINT32                rxFreqKhz; /* RX����Ƶ��,��λKHZ */
    UINT16                dlCfgPath; /* ��������PATH����band��antNum����2���������Ч,CA�²�ʹ�� */
    UINT8                 antNum;    /* ���߸���,�������֧��2T,�������֧��8R�������2R1T�������dlcfgPath��Ч */
    UINT8                 antMap;    /* HiRF��ֻ֧��:BIT0--ANT0,BIT1--ANT1��MT��֧��BIT0~7,���Ǳ��밴2Rʹ�� */
    BBIC_CAL_RF_DEBUG_RX_PATH_PARA_STRU rxPathPara[RX_MAX_ANT_NUM]; /* ���֧��8R��ÿR������ */
} BBIC_CAL_RF_DEBUG_RX_BAND_PARA_STRU;

/*
 * Description: TX Slow debug config para, except GSM
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_TRX_COMM_PARA_STRU bandCommPara;                                /* TRX�������ò��� */
    UINT16                               ccIndex; /* ��ǰ����CC INDEX */
    UINT16                               usRsv;
    BBIC_CAL_RF_DEBUG_TX_BAND_PARA_STRU  txBandCfgPara; /* ÿ��TX Band���ò��������֧��2CC */
} BBIC_CAL_RF_DEBUG_TX_PARA_STRU;

/*
 * Description: RX REQ PARA
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_TRX_COMM_PARA_STRU bandCommPara;                                /* TRX�������ò��� */
    UINT16                               ccIndex; /* ��ǰ����CC INDEX */
    UINT16                               usRsv;
    BBIC_CAL_RF_DEBUG_RX_BAND_PARA_STRU  rxBandCfgPara; /* ÿ��RX Band���ò���,���֧��5CC */
} BBIC_CAL_RF_DEBUG_RX_PARA_STRU;

/*
 * Description: RF DEBUG TRX���ò���,���Ե�������TX(��2G����)����RX��
 *              Ҳ����ͬʱ����TX����RX��֧�ֵ��ز���CA������;
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_TRX_COMM_PARA_STRU bandCommPara;     /* TRX�������ò��� */
    UINT16 txBandCnt; /* TXƵ�θ�����0��ʾ������TX; ���ز�����1;
                         CA������2,���֧��2CC */
    UINT16 rxBandCnt; /* RXƵ�θ�����0��ʾ������RX; ���ز�����1;
                         CA������2~5,���֧��5CC */

    BBIC_CAL_RF_DEBUG_TX_BAND_PARA_STRU txBandCfgPara[TX_MAX_CC_NUM]; /* ÿ��TX Band���ò��������֧��2CC */
    BBIC_CAL_RF_DEBUG_RX_BAND_PARA_STRU rxBandCfgPara[RX_MAX_CC_NUM]; /* ÿ��RX Band���ò���,���֧��5CC */
} BBIC_CAL_RF_DEBUG_TRX_PARA_STRU;

typedef struct {
    VOS_UINT16 errorCode;
    VOS_UINT16 nvLoadFlag;
    VOS_UINT16 rxClosedFlag[BBIC_CAL_MODEM_ID_BUTT];
} BBIC_CAL_RF_DEBUG_RM_CNF_PARA_STRU;

/*
 * Description: GSM TX Slow debug config para
 */
typedef struct {
    G_TX_MODU_ENUM_UINT16 uhwModuType;
    UINT16                uhwRsv;
    BBIC_CAL_RF_DEBUG_TX_POWER_PARA_STRU stTxPowerPara;
    MRX_AGC_GAIN_CODE_STRU stMRxPara;
} G_TX_SINGLE_SLOT_PARA_STRU;

/*
 * Description: GSM TX Slow debug config para
 */
typedef struct {
    UINT16                             uhwTxEnable;  /* < 1--Tx enable, 0--Tx Disable */
    UINT16                             uhwMrxEanble; /* < Mrx Enable, 1--Enable, 0--Disable */
    BBIC_CAL_RF_DEBUG_COMMON_PARA_STRU stCommonInfo;
    UINT16                             uhwDataPattern; /* < 0��All 0��1��All 1��2��Random */
    MRX_ESTIMATE_ENUM_UINT8            enMrxEstMode;   /* < Mrx Measure Mode */
    UINT8                              ucRsv;
    UINT16                             uhwRsv;
    UINT16                             uhwSlotCnt; /* < ����ʱ϶������
                                         1~4 - ����ָ������ʹ����Щʱ϶��DSP�Զ�����1~4ʱ϶����
                                         8 - 8ʱ϶ȫ����ʹ�õ�һ��astSlotCfg�Ĳ��������� */
    G_TX_SINGLE_SLOT_PARA_STRU astSlotPara[4];     /* < ÿ��ʱ϶��������� */
} BBIC_CAL_RF_DEBUG_G_TX_PARA_STRU;

/*
 * Description: TX Slow debug config para,  only for GSM
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_COMMON_PARA_STRU stCommonInfo;
    UINT16                             uhwTxEnable; /* < 1--Tx enable, 0--Tx Disable */

    BBIC_CAL_GSM_DATA_TYPE_ENUM_UINT8 enDataPatten;
    UINT8                             ucSlotCnt;
    BBIC_CAL_RF_DEBUG_TX_POWER_PARA_STRU stSlotPower[BBIC_CAL_GSM_TX_SLOT_NUM];
} BBIC_CAL_RF_DEBUG_GSM_TX_PARA_STRU;

/*
 * Description: Tx Result Ind
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT32 uwRsv;
    UINT32 swTxCorrValue;
    UINT32 swMrxCorrValue;
    INT16  shwAntPower;    /* ���߿ڹ���, ��λGUC: 0.1db ; L/NR: 0.125db */
    INT16  shwRsv;         /* ����λ */
    INT32  swMrxRealValue; /* �����ʵ��ֵ */
    INT32  swMrxImagValue; /* ������鲿ֵ */
} BBIC_CAL_RF_DEBUG_TX_RESULT_IND_PARA_STRU;

/*
 * Description: Tx Result Ind
 */
typedef struct {
    UINT32 errorCode;
    UINT32 validCnt;
    BBIC_CAL_RF_DEBUG_TX_RESULT_IND_PARA_STRU txIndPara;
} BBIC_CAL_RF_DEBUG_TX_REPORT_PARA_STRU;

/*
 * Description: Tx Result Ind
 */
typedef struct {
    UINT32 errorCode;
    UINT32 rsv;
    UINT32 indFlag; /* �Ƿ�ΪIND��Ϣ�������IND��Ϣ��������1����������0 */
    UINT32 txCorrValue;
    UINT32 mrxCorrValue;
    INT16  antPower; /* ���߿ڹ���, ��λGUC: 0.1db ; L/NR: 0.125db */
    INT16  rsv1;
    INT32  swMrxRealValue; /* �����ʵ��ֵ */
    INT32  swMrxImagValue; /* ������鲿ֵ */
} BBIC_CAL_RF_DEBUG_TX_CNF_PARA_STRU;

/*
 * Description: Tx Result Ind
 */
typedef struct {
    UINT32 swTxCorrValue;
    UINT32 swMrxCorrValue;
    INT16  antPower;
    INT16  rsv;
} GSM_MRX_IND_SINGLE_SLOT_STRU;

/*
 * Description: Tx Result Ind
 */
typedef struct {
    UINT32                       uwErrorCode;
    UINT32                       uwRsv;
    GSM_MRX_IND_SINGLE_SLOT_STRU astSlotValue[BBIC_CAL_GSM_TX_SLOT_NUM];
} BBIC_CAL_RF_DEBUG_GTX_MRX_IND_PARA_STRU;

/*
 * Description: RX Rssi Ind
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT32 uwRsv;
    INT16  ashwRssi[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_RX_RSSI_IND_PARA_STRU;

/*
 * Description: RX Rssi Ind
 */
typedef struct {
    UINT32 errorCode;
    UINT16 indFlag; /* IND�ϱ���־�������IND��������1����������0 */
    UINT16 validAntNum;
    INT16  ashwRssi[RX_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_RX_CNF_PARA_STRU;

/*
 * Description: ÿ��Band�µ�RSSI�ϱ������֧��8R
 */
typedef struct {
    UINT16 validAntNum;
    UINT16 usRsv;
    INT16  rxRssi[RX_MAX_ANT_NUM];
} BBIC_CAL_RX_RSSI_IND_BAND_STRU;

/*
 * Description: ���CC��RSSI�ϱ������֧��5CC
 */
typedef struct {
    UINT32                         errorCode;
    UINT32                         uwRsv;
    UINT16                         validCcNum;
    UINT16                         usRsv;
    BBIC_CAL_RX_RSSI_IND_BAND_STRU rssiRpt[RX_MAX_CC_NUM];
} BBIC_CAL_RF_DEBUG_RX_RSSI_REPORT_PARA_STRU;

/*
 * Description: any ant rx evm result
 */
typedef struct {
    INT16 uhwCurEvm;
    INT16 uhwAvgEvm;
    INT16 uhwMinEvm;
    INT16 uhwMaxEvm;
    INT16 uhwFreqErr;
    INT16 uhwRsv;
} BBIC_CAL_RF_DEBUG_RX_EVM_ANT_STRU;

/*
 * Description: rx evm result
 */
typedef struct {
    UINT32                            uwErrorCode;
    UINT32                            uwRsv;
    BBIC_CAL_RF_DEBUG_RX_EVM_ANT_STRU astEvmInd[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_RX_EVM_IND_PARA_STRU;

#define BBIC_CAL_RF_DEBUG_SELF_CAL_STRU_BEGIN

/*
 * Description: DCXO C1&C2 Fix
 */
typedef struct {
    UINT16 uhwC1Fix;
    UINT16 uhwC2Fix;
} BBIC_CAL_RF_DEBUG_DCXO_CFIX_PARA_STRU;

/*
 * Description: DCXO C1&C2 Fix
 */
typedef struct {
    INT32 swTemperature; /* < Unit is 0.001degree */
    INT32 swFreqError;   /* < Unit is Hz */
} BBIC_CAL_RF_DEBUG_DCXO_RESULT_STRU;

/*
 * Description: DCXO Result Report
 */
typedef struct {
    UINT32                             uwErrorCode;
    UINT16                             uhwValidCnt;
    UINT16                             uhwRsv;
    BBIC_CAL_RF_DEBUG_DCXO_RESULT_STRU astDcxoResult[BBIC_CAL_DCXO_RESULT_IND_NUM];
} BBIC_CAL_RF_DEBUG_DCXO_RESULT_IND_PARA_STRU;

typedef struct {
    RAT_MODE_ENUM_UINT16  enRatMode; /* < Rat Mode */
    BAND_ENUM_UINT16      enBand;    /* < Band No. */
    BANDWIDTH_ENUM_UINT16 enBandWith;
    UINT16                uhwPath;
    UINT32                uwFreqInfo; /* < Frequency info, unit is khz */
} BBIC_CAL_IP2_COMMON_CFG_STRU;

typedef struct {
    UINT32 bitByteCnt : 5;     /* Byte Cnt */
    UINT32 bitMipiPortSel : 3; /* MIPI PORTѡ�� */
    UINT32 bitSlaveId : 4;     /* Savle Id */
    UINT32 bitRegAddr : 16;    /* �Ĵ�����ַ */
    UINT32 bitRsv : 4;
} BBIC_CAL_MIPIDEV_CMD_STRU;

typedef struct {
    UINT32 bitByte0 : 8;
    UINT32 bitByte1 : 8;
    UINT32 bitByte2 : 8;
    UINT32 bitByte3 : 8;
} BBIC_CAL_MIPIDEV_DATA_STRU;

typedef struct {
    BBIC_CAL_MIPIDEV_CMD_STRU  stCmd;
    BBIC_CAL_MIPIDEV_DATA_STRU stData;
} BBIC_CAL_MIPIDEV_UNIT_STRU;

/*
 * Description:IP2 CA������
 */
typedef struct {
    UINT16                     uhwCaFlag; /* �Ƿ�ΪCA��Path��0--���ز���1--CA */
    UINT16                     uhwRsv;
    BBIC_CAL_MIPIDEV_UNIT_STRU astCaMipi[8];     /* ���CA��У׼�������Ҫ��������CA�Ĺ���MIPIָ�
                                            BBIC cal����CA���Copy���Ӧ��MIPIָ�� */
    BBIC_CAL_MIPIDEV_UNIT_STRU astCaMipiTrig[4]; /* MIPI Trigָ�� */
} BBIC_CAL_IP2_CA_CONFIG_STRU;

/*
 * Description: RF DEBUG IP2 Req
 */
typedef struct {
    BBIC_CAL_IP2_COMMON_CFG_STRU stTxCommonCfg;
    BBIC_CAL_IP2_COMMON_CFG_STRU stRxCommonCfg;
    INT16                        shwTxPower; /* < GUC:0x1db, L/NR:1/8db */

    UINT8 ucRxAntCfgMap : 2; /* < BIT0--ANT0,BIT1--ANT1 */
    UINT8 ucRsv : 6;
    UINT8 ucRsv2;

    BBIC_CAL_IP2_AGC_GAIN_CONFIG_STRU stRxAgcGainCfg;
    BBIC_CAL_IP2_IQ_CODE_STRU         stIp2Code;
    BBIC_CAL_IP2_CA_CONFIG_STRU       stIp2CaCfg;
} BBIC_CAL_RF_DEBUG_IP2_REQ_PARA_STRU;

/*
 * Description: IP2 Result IP2
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT32 uwRsv;
    INT32  aswImd2Value[2]; /* < 0: խ�����,1: ������� */
} BBIC_CAL_RF_DEBUG_IP2_RESULT_IND_PARA_STRU;

/*
 * Description: RX DCOC Req
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_COMMON_PARA_STRU stCommonInfo;
    UINT16                             uhwRsv;
    UINT8                              ucAntCfgMap; /* < BIT0--ANT0,BIT1--ANT1 */
    UINT8                              ucRsv;
    RX_AGC_GAIN_CODE_STRU              astRxDcConfig[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_RX_DCOC_REQ_PARA_STRU;

/*
 * Description: RX DCOC Result PARA
 */
typedef struct {
    UINT32                  uwErrorCode;
    UINT32                  uwRsv;
    BBIC_CAL_DC_RESULT_STRU astRxDcResult[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_RX_DCOC_IND_PARA_STRU;

/*
 * Description: Mrx dcoc req para
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_COMMON_PARA_STRU stCommonInfo;
    MRX_AGC_GAIN_CODE_STRU             stMrxGainCofig;
} BBIC_CAL_RF_DEBUG_MRX_DCOC_REQ_PARA_STRU;

/*
 * Description: mrx DCOC Result PARA
 */
typedef struct {
    UINT32                  uwErrorCode;
    UINT32                  uwRsv;
    BBIC_CAL_DC_RESULT_STRU stRxDcResult;
} BBIC_CAL_RF_DEBUG_MRX_DCOC_IND_PARA_STRU;

typedef struct {
    BBIC_CAL_RF_DEBUG_COMMON_PARA_STRU stCommonInfo;
    TX_BB_SIGNAL_CW_STRU               stTxSignalPara;
    MRX_AGC_GAIN_INDEX_STRU            stMrxGainIndex;
    POWER_CTRL_MODE_ENUM_UINT8         enPowerCtrlMode; /* < Power Ctrl Mode */
    UINT8                              aucRsv[3];
    TX_POWER_CFG_UNION                 unPowerPara;
} BBIC_CAL_RF_DEBUG_TX_IQ_REQ_PARA_STRU;

typedef struct {
    UINT32                  uwErrorCode;
    UINT32                  uwRsv;
    BBIC_CAL_IQ_RESULT_STRU stTxIqInd;
} BBIC_CAL_RF_DEBUG_TX_IQ_IND_PARA_STRU;

typedef BBIC_CAL_RF_DEBUG_TX_IQ_REQ_PARA_STRU BBIC_CAL_RF_DEBUG_TX_LO_REQ_PARA_STRU;

typedef struct {
    UINT32                          uwErrorCode;
    UINT32                          uwRsv;
    BBIC_CAL_LPFGAIN_LO_RESULT_STRU stTxLoInd;
} BBIC_CAL_RF_DEBUG_TX_LO_IND_PARA_STRU;

#define BBIC_CAL_RF_DEBUG_PHY_STRU_BEGIN

typedef struct {
    UINT8                           ucRxEanble; /* < 1--Rx enable, 0--Rx Disable */
    BBIC_CAL_RX_AGC_MODE_ENUM_UINT8 enRxAgcMode;
    UINT16                          uhwRsv;
    UINT16                          uhwRxPathIndex;
    UINT8                           ucRsv;
    UINT8                           ucAntCfgMap;                       /* < BIT0--ANT0,BIT1--ANT1 */
    RX_AGC_GAIN_CODE_STRU           astAntInfo[RFHAL_CAL_MAX_ANT_NUM]; /* < Configuration of Mian /Div antenna path */
    UINT32                          uwRxFreq;                          /* < Rx Freq, unit khz */
} BBIC_CAL_PHY_RX_PARA_STRU;

typedef struct {
    UINT8                           ucTxEanble;   /* < 1--Tx enable, 0--Tx Disable */
    BBIC_CAL_SIGNAL_MODE_ENUM_UINT8 enSignalMode; /* < Modulation or single Tone */
    UINT16                          uhwRsv;
    UINT16                          uhwTxPathIndex;
    MODU_TYPE_ENUM_UINT16           enModType; /* < Modulation Type */
    UINT32                          uwTxFreq;  /* < Tx Freq, unit khz */
} BBIC_CAL_PHY_TX_PARA_STRU;

typedef struct {
    MODEM_ID_ENUM_UINT16              enModemId; /* < Modem Id */
    BAND_ENUM_UINT16                  enBand;    /* < Band Id */
    BBIC_CAL_PHY_RX_PARA_STRU         stRxPara;
    BBIC_CAL_PHY_RX_PARA_STRU         stTxPara;
    BBIC_CAL_RF_DEBUG_WCDMA_PARA_STRU stWDpaUpaPara; /* < Wcdma DPA/UPA config */
} BBIC_CAL_WPHY_CONFIG_PARA_STRU;

typedef struct {
    MODEM_ID_ENUM_UINT16      enModemId; /* < Modem Id */
    BAND_ENUM_UINT16          enBand;
    BBIC_CAL_PHY_RX_PARA_STRU stRxPara;
    BBIC_CAL_PHY_RX_PARA_STRU stTxPara;
} BBIC_CAL_CPHY_CONFIG_PARA_STRU;

typedef struct {
    MODEM_ID_ENUM_UINT16      enModemId; /* < Modem Id */
    BAND_ENUM_UINT16          enBand;
    BBIC_CAL_PHY_RX_PARA_STRU stRxPara;
    BBIC_CAL_PHY_RX_PARA_STRU stTxPara;
    LTE_TX_PARA_STRU          stRbConfig;
} BBIC_CAL_LPHY_CONFIG_PARA_STRU;

typedef struct {
    MODEM_ID_ENUM_UINT16 enModemId; /* < Modem Id */
    UINT16               uhwRsv;
    UINT8                ucAntNum;    /* < the valid Ant num */
    UINT8                ucAntCfgMap; /* < BIT0--ANT0,BIT1--ANT1 */
    UINT16               uhwMeasNum;
} BBIC_CAL_NB_RSSI_PARA_STRU;

typedef struct {
    UINT16 enErrorCode;
    UINT8  ucAntNum;    /* < the valid Ant num */
    UINT8  ucAntCfgMap; /* < BIT0--ANT0,BIT1--ANT1 */
    INT16  ashwRssi[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_NB_RSSI_IND_PARA_STRU;

typedef struct {
    BBIC_CAL_RFIC_TYPE_ENUM_UINT16 enRficType;
    BBIC_CAL_RFIC_ID_ENUM_UINT16   enRficId;
} BBIC_CAL_RFIC_INFO_STRU;

typedef struct {
    UINT16                  uhwRficCnt; /* < max cnt: 4 */
    UINT16                  uhwRsv;
    BBIC_CAL_RFIC_INFO_STRU astRficInfo[BBIC_CAL_MAX_RFIC_NUM];
} BBIC_CAL_RFIC_SELFCAL_REQ_PARA_STRU;

typedef struct {
    UINT32 errorCode;
    UINT32 rsv1;     /* Ԥ����DSP��¼���̸澯��Ϣ */
    UINT16 testItem; /* �������У׼ö�� */
    UINT16 rsv2;     /* ��ȷ���Ƿ�����NV ID */
    UINT16 rsv3;     /* ��ȷ���Ƿ�����NV LENGTH */
    UINT16 dataLength;
    UINT8  dataBuff[4]; /* �䳤����ʽ����ÿ��У׼����ȷ�� */
    /*
     * �������Ľṹ��:
     * NV_RF_SELFCAL_R_CAL_STRU
     * NV_RF_SELF_RC_RXFLT_CAL_STRU
     * NV_RF_SELFCAL_VTH_CAL_STRU
     * NV_RF_SELFCAL_VCO_SF_DTC_STRU
     * NV_RF_SELFCAL_MRX_ADC_STRU
     * NV_RF_SELFCAL_RX_FB_DAC_STRU
     * NV_RF_SELFCAL_TX_DAC_CAL_STRU
     * NV_RF_SELFCAL_TX_FILTER_BALUN_STRU
     * NV_RF_SELFCAL_FASTLOCK_STRU
     */
} RficSelfCalItemInd;

typedef struct {
    UINT32                  uwErrorcode;
    BBIC_CAL_RFIC_INFO_STRU stRficInfo;
    UINT16                  uhwCnt;
    UINT16                  uhwRsv;
    UINT8                   aucData[4]; /* < �䳤�����ݸ�ʽ�������¸�ʽ�� */
    /* ÿ������У׼�����ݵĸ�ʽ  RficSelfCalItemInd */
} BBIC_CAL_RFIC_SELFCAL_IND_PARA_STRU;

typedef struct {
    BBIC_CAL_TX_PATH_LIST_STRU stCalList;
} BBIC_CAL_GE_RAMP_REQ_PARA_STRU;

typedef struct {
    UINT16 uhwSrcPathIndex;
    UINT16 uhwSrcRatMode;
} BBIC_CAL_RESULT_SOURCE_STRUCT;

typedef struct {
    UINT16 uhwDataLength;
    UINT16 uhwRsv;
    /* ������ʼ��ַ������ʵ�ʳ���ΪuhwDataLength */
} BBIC_CAL_RESULT_DATA_STRUCT;

typedef union {
    BBIC_CAL_RESULT_SOURCE_STRUCT stCalResultSrcInfo; /* ����CAL_RESULT_WRITE_TYPE_CO_BANDʱ��Ч */
    BBIC_CAL_RESULT_DATA_STRUCT   stCalResultData;    /* ����CAL_RESULT_WRITE_TYPE_NORMALʱ��Ч */
} BBIC_CAL_RESULT_DATA_UNION;

typedef struct {
    CAL_RESULT_ITEM_NAME_ENUM_UINT16  uhwItemName;
    UINT16                            uhwPathIndex;
    RAT_MODE_ENUM_UINT16              uhwRatMode;
    CAL_RESULT_WRITE_TYPE_ENUM_UINT16 uhwWriteType;
    BBIC_CAL_RESULT_DATA_UNION        stWriteData;
} BBIC_CAL_RESULT_INFO_STRUCT;

typedef struct {
    UINT16 uhwCalResultCnt; /* < ��Ҫд���ItemName���� */
    UINT16 rsv;
    UINT8  aucData[4]; /* < �䳤�����ݸ�ʽ˵������ */
    /*
     * �ṹ������ BBIC_CAL_RESULT_INFO_STRUCT
     */
} BBIC_CAL_RESULT_WRITE_REQ_PARA_STRU;

typedef struct {
    UINT32                           uwErrorCode;
    CAL_RESULT_ITEM_NAME_ENUM_UINT16 uhwErrorItemName;
    UINT16                           uhwErrorPathIndex;
    RAT_MODE_ENUM_UINT16             uhwErrorRatMode;
    UINT16                           uhwRsv;
} BBIC_CAL_RESULT_WRITE_CNF_PARA_STRU;

typedef struct {
    UINT32                     uwMipiNum;
    BBIC_CAL_MIPIDEV_UNIT_STRU astData[BBIC_CAL_MAX_WR_MIPI_COUNT];
} BBIC_CAL_WRITE_MIPI_DATA_REQ_STRU;

/*
 * Description: ��MIPI������Ϣ
 */
typedef struct {
    UINT8                     uwMipiNum;
    UINT8                     readSpeedType;
    UINT8                     rsv[2];
    BBIC_CAL_MIPIDEV_CMD_STRU astCMD[BBIC_CAL_MAX_RD_MIPI_COUNT];
} BBIC_CAL_READ_MIPI_DATA_REQ_STRU;

typedef struct {
    UINT32 uwRegisterAddr;
    UINT32 uwRegisterData;
} BBIC_CAL_CPU_REGISTER_UNIT_STRU;

/*
 * Description: дCPU REG������Ϣ
 */
typedef struct {
    UINT32                          uwCpuRegisterNum;
    BBIC_CAL_CPU_REGISTER_UNIT_STRU astCpuData[BBIC_CAL_MAX_REGISTER_COUNT];
} BBIC_CAL_WRITE_REG_DATA_REQ_STRU;

/*
 * Description: ��CPU REG������Ϣ
 */
typedef struct {
    UINT32 uwCpuRegisterNum;
    UINT32 astCpuAddress[BBIC_CAL_MAX_REGISTER_COUNT];
} BBIC_CAL_READ_REG_DATA_REQ_STRU;

/*
 * Name        : BBIC_CAL_WRITE_MIPI_DATA_REQ_STRU
 * Description : ��MIPI���
 */
typedef BBIC_CAL_WRITE_MIPI_DATA_REQ_STRU BBIC_CAL_READ_MIPI_DATA_IND_STRU;

/*
 * Name        : BBIC_CAL_WRITE_REG_DATA_REQ_STRU
 * Description : ��CPU REG���
 */
typedef BBIC_CAL_WRITE_REG_DATA_REQ_STRU BBIC_CAL_READ_REG_DATA_IND_STRU;

#define BBIC_CAL_MNTN_INFO

typedef struct {
    UINT32 uwMrxResult;     /* MRX�ϱ�ֵ */
    UINT16 uhwMrxGainIndex; /* ÿ����У׼ʱ��MRX��λ */
    UINT16 uhwRsv;
    INT16  hwPower; /* ��λ0.1dB�����ʿ���Ϊ�� */
    UINT16 uhwDac;  /* Dacֵ */
} BBIC_CAL_GETX_APC_POINT_INFO_STRU;

typedef struct {
    UINT32 uwMrxResult;     /* MRX�ϱ�ֵ */
    UINT16 uhwMrxGainIndex; /* ÿ����У׼ʱ��MRX��λ */
    UINT16 uhwFreqInfo;     /* ÿ����У׼ʱ��Ƶ�� */
    INT16  hwPower;         /* ��λ0.1dB�����ʿ���Ϊ�� */
    UINT16 uhwDac;          /* Dacֵ */
} BBIC_CAL_GETX_FREQCOMP_POINT_INFO_STRU;

typedef struct {
    UINT32                            uwErrorCode;                   /* APC��У׼ÿ��Path��У׼��� */
    UINT16                            uhwPathLoop;                   /* ��ǰPath���� */
    UINT16                            uhwPathIndex;                  /* ��ǰPath��NV��Դ���� */
    UINT16                            uhwModuType;                   /* ��ǰPath��ModuType */
    UINT16                            uhwLinerInfo;                  /* ��ǰPath�����Է�������Ϣ */
    UINT16                            uhwFreqInfo;                   /* ��ǰPath������Ƶ�� */
    UINT8                             ucTxGainIndex[GE_RF_GAIN_NUM]; /* ��ǰPath��APCУ׼ʱ����Ӧ��RF PA��λ������� */
    UINT32                            auwStepNum[GE_RF_GAIN_NUM];    /* ÿ��APCԭʼ����STEP���� */
     /* ÿ��STEP������ */
    BBIC_CAL_GETX_APC_POINT_INFO_STRU astStepPara[GE_RF_GAIN_NUM * BBIC_CAL_GETX_APC_TBL_POINT_MAX_NUM];
} BBIC_CAL_GETX_APC_TBL_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_GETX_APC_TBL_MNTN_INFO_STRU stPara; /* APC��У׼�ľ���ά����Ϣ */
} BBIC_CAL_GETX_APC_TBL_MNTN_MSG_STRU;

typedef struct {
    INT16  shwPower;
    UINT16 uhwDGain;
    INT32  swDcComp;
} BBA_CAL_GETX_DCOFFSET_STEP_RSLT_INFO;

typedef struct {
    UINT32 uwErrorCode;                /* ��ǰPath��У׼��� */
    UINT16 uhwPathLoop;                /* ��ǰPath���� */
    UINT16 uhwPathIndex;               /* ��ǰPath��NV��Դ���� */
    UINT16 uhwModuType;                /* ��ǰPath��ModuType */
    UINT16 uhwLinerInfo;               /* ��ǰPath�����Է�������Ϣ */
    UINT16 uhwFreqInfo;                /* ��ǰPath������Ƶ�� */
    UINT16 auwStepNum[GE_RF_GAIN_NUM]; /* STEP���� */
    BBA_CAL_GETX_DCOFFSET_STEP_RSLT_INFO astPreChargeRsltInfo[GE_RF_GAIN_NUM][64];
} BBIC_CAL_GETX_PRECHARGE_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_GETX_PRECHARGE_MNTN_INFO_STRU stPara; /* Ԥ���ѹУ׼�ľ���ά����Ϣ */
} BBIC_CAL_GETX_PRECHARGE_MNTN_MSG_STRU;

typedef struct {
    UINT32                            uwErrorCode;  /* ��ǰPath��У׼��� */
    UINT16                            uhwPathIndex; /* ��ǰPath��NV��Դ���� */
    UINT16                            uhwModuType;  /* ��ǰPath��ModuType */
    UINT16                            uhwLinerInfo; /* ��ǰPath�����Է�������Ϣ */
    UINT16                            uhwFreqInfo;  /* ��ǰPath������Ƶ�� */
    UINT16                            uhwTxGainNum; /* ��ǰPath RF PA��λ������� */
    UINT16                            uhwRsv;
    BBIC_CAL_GETX_APC_POINT_INFO_STRU astStepPara[GE_PA_GAIN_NUM]; /* ��ǰPathÿ����λ��ԭʼ���� */
} BBIC_CAL_GETX_PAGAIN_PATH_MNTN_INFO;

typedef struct {
    UINT32                              uwErrorCode; /* У׼��� */
    UINT16                              uhwPathNum;  /* Path���� */
    UINT16                              uhwRsv;
    BBIC_CAL_GETX_PAGAIN_PATH_MNTN_INFO astPaGainPathInfo[BBIC_CAL_GETX_PATH_NUM]; /* ÿ��Path��У׼ԭʼ����������Ϣ */
} BBIC_CAL_GETX_PAGAIN_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_GETX_PAGAIN_MNTN_INFO_STRU stPara; /* PAGAINУ׼�ľ���ά����Ϣ */
} BBIC_CAL_GETX_PAGAIN_MNTN_MSG_STRU;

typedef struct {
    UINT32 uwErrorCode;  /* ��ǰPath��У׼��� */
    UINT16 uhwPathIndex; /* ��ǰPath��NV��Դ���� */
    UINT16 uhwModuType;  /* ��ǰPath��ModuType */
    UINT16 uhwLinerInfo; /* ��ǰPath�����Է�������Ϣ */
    UINT16 uhwRsv;
    UINT16 uhwTxGainNum; /* ��ǰPath RF PA��λ������� */
    UINT16 uhwFreqNum;   /* ��ǰPath Ƶ������������� */
    /* ��ǰPathÿ��Ƶ��ÿ����λ��ԭʼ���� */
    BBIC_CAL_GETX_FREQCOMP_POINT_INFO_STRU astStepPara[GE_PA_GAIN_NUM][BBIC_CAL_FREQ_MAX_NUM];
} BBIC_CAL_GETX_FREQCOMP_PATH_MNTN_INFO;

typedef struct {
    UINT32 uwErrorCode; /* У׼��� */
    UINT16 uhwPathNum;  /* Path���� */
    UINT16 uhwRsv;
	 /* ÿ��Path��У׼ԭʼ����������Ϣ */
    BBIC_CAL_GETX_FREQCOMP_PATH_MNTN_INFO astFreqCompPathInfo[BBIC_CAL_GETX_PATH_NUM];
} BBIC_CAL_GETX_FREQCOMP_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_GETX_FREQCOMP_MNTN_INFO_STRU stPara; /* FREQCOMPУ׼�ľ���ά����Ϣ */
} BBIC_CAL_GETX_FREQCOMP_MNTN_MSG_STRU;

/*
 * Description: ÿ�ν�����ά����Ϣ
 */
typedef struct {
    UINT32          reqTimeMc;
    UINT32          timeUs;
    TrxOptionUint16 opType;
    UINT16          stepIndex;
} BBA_CAL_TrxMntnOpInfo;

/*
 * Description: ÿ��PATH��ά����Ϣ
 */
typedef struct {
    UINT16                ratMode;     /* ��ʽ       */
    UINT16                pathIndex;   /* PATH����  */
    UINT16                opNum;       /* Ƶ������ */
    UINT16                temperature; /* �¶�    */
    BBA_CAL_TrxMntnOpInfo opInfo[BBA_CAL_TRX_MNTN_MAX_NUM];
} BBA_CAL_TrxMntnInfo;

/*
 * Description: TRXά����Ϣ
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU componentId;
    BBA_CAL_TrxMntnInfo        mntnInfo;
} BBA_CAL_TrxMntnMsg;

#define BBIC_CAL_RF_DEBUG_HF_TRX_STRU_BEGIN
/*
 * Hi6370 & Hi6P01
 */

/*
 * Description: RF DEBUG CA para
 */
typedef struct {
    BBIC_CAL_RX_SYS_STATE_ENUM_UINT16 enSysState;  /* < PCC/SCC, Inter/Intra */
    BBIC_CAL_START_MODE_ENUM_UINT16   enStartMode; /* < ����/���� */
} BBIC_CAL_RF_DEBUG_HF_CA_PARA_STRU;

/*
 * Description: RF DEBUG HF COMMON Config para
 */
typedef struct {
    BAND_ENUM_UINT16                    enBand;                              /* < Band No */
    BANDWIDTH_ENUM_UINT16               enBandWith;                          /* < BandWidth */
    UINT32                              uwTxFreqInfo;                        /* < Tx Frequence info, unit is khz */
    UINT32                              uwRxFreqInfo;                        /* < Rx Frequence info, unit is khz */
    UINT8                               ucChanNum;                           /* < 1R/2R: 2, 4R: 4 */
    UINT8                               ucChanMap;                           /* < 1R: 0x1/0x2, 2R: 0x3, 4R: 0xF */
    UINT8                               aucMasState[BBIC_HFCAL_MAX_MAS_NUM]; /* < 0: AIP 1/3, 1: AIP 2/4 */
    BBIC_CAL_RF_DEBUG_HF_CA_PARA_STRU   stCaInfo;                            /* < CA info */
} BBIC_CAL_RF_DEBUG_HF_BAND_PARA_STRU;

/*
 * Description: RX AGC Gain Ctrl stru, use index mode
 */
typedef struct {
    UINT16                    uhwAgcGainIndex;
    AGC_WORK_TYPE_ENUM_UINT16 enWorkType; /* < AGC Work Type */
} HF_RX_AGC_GAIN_INDEX_STRU;

/*
 * Description: RX AGC Gain Ctrl stru, use code mode
 */
typedef struct {
    UINT16                  uhwIfAgcCode; /* < Hi6370 If AGC Gain Code */
    UINT16                  uhwHfAgcCode; /* < Hi6P02 Hf AGC Gain Code */
    BBIC_CAL_DC_RESULT_STRU stRxDcConfig;
} HF_RX_AGC_GAIN_CODE_STRU;

/*
 * Description: HF RX AGC Gain Ctrl stru, use sub index mode
 */
typedef struct {
    UINT16                    uhwIfAgcIndex; /* < Hi6370 If Agc Gain Index */
    UINT16                    uhwHfAgcIndex; /* < Hi6P01 Hf AGC Gain Index */
    AGC_WORK_TYPE_ENUM_UINT16 enWorkType;    /* < AGC Work Type */
    UINT16                    uhwRsv;
} HF_RX_AGC_GAIN_SUB_INDEX_STRU;

/*
 * Description: HF RX AGC����������
 */
typedef union {
    HF_RX_AGC_GAIN_INDEX_STRU     stAgcGainIndex;    /* AGC����ΪAGC GAIN Indexģʽ����Ч */
    HF_RX_AGC_GAIN_SUB_INDEX_STRU stAgcGainSubIndex; /* AGC����ΪAGC GAIN SUB Indexģʽ����Ч */
    HF_RX_AGC_GAIN_CODE_STRU      stAgcGainCode;     /* AGC����ΪAGC GAIN Codeģʽ����Ч */
} BBIC_CAL_HF_RX_AGC_GAIN_CONFIG_UNION;

/*
 * ��������У׼ֻ������BaseDieId BeamIndex,У׼Die����
 * Description: HF M2M���ýṹ
 */
typedef struct {
    UINT32                          ulBaseDieId; /* ��׼Die��Id */
    UINT32                          ulCalDieId;  /* У׼Die��Id */
    UINT8                           ucRsv;
    UINT8                           ucBeamIndex;
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 enAntType;                              /* �̶�BBIC_CAL_HF_ANT_TYPE_BROAD_SIDE */
    UINT8                           ucAntUnitCtrl;                          /* 0-ȫ����1-Map;M2MУ׼Ϊ:1�� */
    UINT8                           aucAntUnitMap[BBIC_HF_TRX_MAX_DIE_NUM]; /* �ò�����HIRFʹ�� */
} BBIC_CAL_M2M_CFG_STRU;

/*
 * hirfÿ�����ߵ�beam cfg����ǰantUintCtrlȫ��
 */
typedef struct {
    UINT8                           beamIndex;
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 antType;                             /* �������� */
    UINT8                           antUnitCtrl;                         /* 0-ȫ����1-Map;M2MУ׼Ϊ:1�� */
    UINT8                           rsv;
    UINT8                           antUnitMap[BBIC_HF_TRX_MAX_DIE_NUM]; /* �ò�����HIRFʹ�� */
} BBIC_CAL_RfdebugM2mCfg;

/*
 * Description: HF RX AGC STEP���ýṹ
 */
typedef struct {
    BBIC_CAL_HF_RX_AGC_GAIN_CONFIG_UNION unAgcGainCfg; /* AGC����ģʽ */
    BBIC_CAL_M2M_CFG_STRU                stM2MCfg;     /* M2MУ׼���� */
} BBIC_CAL_HF_RX_AGC_STEP_CONFIG_STRU;

/*
 * Description: RF DEBUG HF Rx Cfg para
 */
typedef struct {
    UINT8                           ucRssiReport;    /* < 1 -- Rssi Report Eanble, 0 -- Rssi Report Disable */
    UINT8                           ucRssiType;      /* < 1 -- WB Rssi, 2 -- FFT Rssi, 3 -- NB Rssi */
    UINT8                           ucAnaRssiReport; /* < 1 -- Ana Rssi Report Eanble, 0 -- Ana Rssi Report Disable */
    BBIC_CAL_CONFIG_MODE_ENUM_UINT8 enRxCfgMode;
    BBIC_CAL_HF_RX_AGC_GAIN_CONFIG_UNION aunAntInfo[BBIC_HFCAL_MAX_ANT_NUM];
    BBIC_CAL_RfdebugM2mCfg               antM2mCfg[BBIC_HFCAL_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_HF_RX_PARA_STRU;

/*
 * Description: HF RX Info
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_HF_BAND_PARA_STRU stBandPara;
    BBIC_CAL_RF_DEBUG_HF_RX_PARA_STRU   stRxPara;
} BBIC_CAL_RF_DEBUG_HF_RX_BAND_INFO_STRU;

/*
 * Description: HF RX REQ PARA
 */
typedef struct {
    MODEM_ID_ENUM_UINT16            enModemId;     /* < Modem Id */
    RAT_MODE_ENUM_UINT16            enRatMode;     /* < Rat Mode */
    UINT32                          uwRsv;         /* < For Mask */
    UINT16                          uhwSignalType; /* < signal type: 0 - cw, 1 - modulation wave */
    MODU_TYPE_ENUM_UINT16           enModType;     /* < valid under modulation signal */
    UINT8                           ucRxEnable;    /* < 1--Rx enable, 0--Rx Disable */
    BBIC_CAL_HF_FE_STATE_ENUM_UINT8 enHffeState;   /* < Hi6P01 State: 2-- Idle, 1-- Enablen, 0-- Disable */
    UINT8                           ucChsState;    /* < 1-- ͨ������, 0--ͨ�������� */
    UINT8                           ucBandNum;     /* < 1 or 2 */
    BBIC_CAL_RF_DEBUG_HF_RX_BAND_INFO_STRU astBandInfo[BBIC_HFCAL_HIRF_MAX_BAND_NUM];
} BBIC_CAL_RF_DEBUG_HF_RX_REQ_PARA_STRU;

/*
 * Description: HF RX Rssi
 */
typedef struct {
    INT16  hwAnaRssi;
    UINT16 uwWbRssiValidCnt;
    INT16  ahwWbRssi[BBIC_HFCAL_NCP_SYMBOL_NUM]; /* < ����uhwBeamSwitchMap��Ӧ��bitλ��� */
} BBIC_CAL_RF_HF_RX_RSSI_STRU;

/*
 * Description: HF RX Rssi Ind
 */
typedef struct {
    UINT32                      uwErrorCode;
    UINT16                      uhwRsv;
    UINT16                      uhwValidCnt;
    BBIC_CAL_RF_HF_RX_RSSI_STRU astRssiResult[BBIC_HFCAL_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_HF_RX_RSSI_IND_PARA_STRU;

typedef struct {
    UINT32 uwIfApcGainCode; /* < Hi6370��Code */
    UINT32 uwHfApcIndex;    /* < Hi6P01��Index */
    INT32  dbbGain0;
    INT32  dbbGain1; /* *< У׼ʱ��Ч */
} HF_TX_REG_CTRL_STRU;

typedef struct {
    INT16  ifTxPower; /* ��Ƶ���� */
    INT16  rsv;
    UINT32 hfApcGainCode; /* ��Ƶ������ */
} HfTxApcCfgSubPower;

/*
 * Description: Power para, Power mode or RFIC code mode
 */
typedef union {
    INT16               shwTxPower;      /* < Choice(POWER_CTRL_MODE_POWER) Power */
    HF_TX_REG_CTRL_STRU stTxRegCtrlPara; /* < Choice(POWER_CTRL_MODE_RFIC_REGISTER) RFIC Ctrl */
    HfTxApcCfgSubPower  apcSubPower;
} HF_TX_POWER_CFG_UNION;

typedef struct {
    HF_TX_POWER_CFG_UNION unTxPowerCfg;
    BBIC_CAL_M2M_CFG_STRU stM2MCfg;
} HF_TX_STEP_CFG_STRU;

/*
 * Description: RF DEBUG HF Tx Cfg para
 */
typedef struct {
    TX_BB_SIGNAL_CW_STRU            stTxSignalPara;
    POWER_CTRL_MODE_ENUM_UINT8      enPowerCtrlMode; /* < Power Ctrl Mode */
    UINT8                           lockTrimEn;  /* ����״̬,1:����ʹ��trimIndex��0:��rfdsp���� */
    UINT8                           trimIndex;   /* ʵ��ʹ�õ�trimidx:[0,15] */
    UINT8                           rsv;
    HF_TX_POWER_CFG_UNION           aunPowerPara[BBIC_HFCAL_MAX_ANT_NUM];
    BBIC_CAL_RfdebugM2mCfg          antM2mCfg[BBIC_HFCAL_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_HF_TX_PARA_STRU;

/*
 * Description: HF TX Info
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_HF_BAND_PARA_STRU stBandPara;
    BBIC_CAL_RF_DEBUG_HF_TX_PARA_STRU   stTxPara;
} BBIC_CAL_RF_DEBUG_HF_TX_BAND_INFO_STRU;

/*
 * Description: HF TX REQ PARA
 */
typedef struct {
    MODEM_ID_ENUM_UINT16            enModemId;     /* < Modem Id */
    RAT_MODE_ENUM_UINT16            enRatMode;     /* < Rat Mode */
    UINT32                          uwRsv;         /* < For Mask */
    UINT16                          uhwSignalType; /* < signal type: 0 - cw, 1 - modulation wave */
    MODU_TYPE_ENUM_UINT16           enModType;     /* < valid under modulation signal */
    WAVEFORM_TYPE_ENUM_UINT16       enWaveType;    /* < valid under modulation signal */
    UINT8                           duplexType;
    UINT8                           rsv;
    NR_TX_MODU_PARA_STRU            stTxModuPara;
    UINT8                           ucTxEnable;  /* < 1--Tx enable, 0--Tx Disable */
    BBIC_CAL_HF_FE_STATE_ENUM_UINT8 enHffeState; /* < Hi6P01 State: 2-- Idle, 1-- Enablen, 0-- Disable */
    UINT8                           ucChsState;  /* < 1-- ͨ������, 0--ͨ�������� */
    UINT8                           ucBandNum;   /* < 1 or 2 */
    BBIC_CAL_RF_DEBUG_HF_TX_BAND_INFO_STRU astBandInfo[BBIC_HFCAL_HIRF_MAX_BAND_NUM];
} BBIC_CAL_RF_DEBUG_HF_TX_REQ_PARA_STRU;

/*
 * Description: HF Hi6P01 TEMP REQ
 */
typedef struct {
    BAND_ENUM_UINT16 enBand;                               /* < Band No */
    UINT8            hffeStatus;                           /* 0-ֻ��Hi6370���¶ȣ�1/2-Hi6370+6P01���¶� */
    UINT8            ucChsState;                           /* < 1-- ͨ������, 0--ͨ�������� */
    UINT8            ucChanNum;                            /* < 1R/2R: 2, 4R: 4 */
    UINT8            ucChanMap;                            /* < 1R: 0x1/0x2, 2R: 0x3, 4R: 0xF */
    UINT8            aucMasState[RFHAL_HFCAL_MAX_MAS_NUM]; /* *< 0: AIP 1/3, 1: AIP 2/4,ֻ��hffeStatus��0ʱ��Ч */
     /* *< ��������boardside/endfire��ֻ��hffeStatus��0ʱ��Ч */
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 aenAntType[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
} BBIC_CAL_RF_HF_ANA_TEMP_REQ_PARA_STRU;

/*
 * Description: HF Hi6P01 TEMP Ind
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT32 uwRsv;
    UINT16 rficTempNum;
    UINT16 hffeTempNum;
    INT16  rficTempData[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
    INT16  hffeTempData[RFHAL_HFCAL_TEMP_MAX_EP_NUM];
} BBIC_CAL_RF_HF_ANA_TEMP_IND_PARA_STRU;

#define BBIC_CAL_HF_TRX_CAL_STRU_BEGIN

/*
 * Description: tx trigger when RX calibration
 */
typedef struct {
    RAT_MODE_ENUM_UINT16            enRatMode;  /* < Rat Mode */
    BAND_ENUM_UINT16                enBand;     /* < Band No. */
    UINT32                          uwFreqInfo; /* < Center freqency of each band, the unit is Khz */
    UINT8                           ucChsState; /* < 1-- ͨ������, 0--ͨ�������� */
    UINT8                           ucChanNum;  /* < 1R/2R: 2 */
    UINT8                           ucChanMap;  /* < 1R: 0x1/0x2, 2R: 0x3 */
    UINT8                           ucMasState; /* < 0: AIP 1/3, 1: AIP 2/4 */
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 enAntType;
    UINT8                           ucBeamIndex; /* < У׼���ô�ֱ���� */
    UINT16                          uhwRsv;
    HF_TX_POWER_CFG_UNION           stStepData; /* < Step Data Cfg */
} BBIC_CAL_HF_RX_TX_TRIG_CONFIG_STRU;

/*
 * Description: TRX any path config
 */
typedef struct {
    RAT_MODE_ENUM_UINT16            enRatMode;  /* < Rat Mode */
    BAND_ENUM_UINT16                enBand;     /* < Band Number */
    UINT16                          uhwFreqNum; /* < Freq Num */
    UINT8                           ucChsState; /* < 1-- ͨ������, 0--ͨ�������� */
    UINT8                           ucChanNum;  /* < 1R/2R: 2 */
    UINT8                           ucChanMap;  /* < 1R: 0x1/0x2, 2R: 0x3 */
    UINT8                           ucMasState; /* < 0: AIP 1/3, 1: AIP 2/4 */
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 enAntType;
    UINT8                           ucBeamIndex; /* < У׼���ô�ֱ���� */
    UINT8                           lockTrimEn;  /* ����״̬,1:����ʹ��trimIndex��0:��rfdsp���� */
    UINT8                           trimIndex;   /* ʵ��ʹ�õ�trimidx:[0,15] */
    UINT16                          rsv;
} BBIC_CAL_HF_TRX_PATH_CONFIG_STRU;

typedef struct {
    UINT16                             uhwTriggerMode;   /* < ������ʽ, 0 - ��ʾRX����, 1 - ��ʾTX���� */
    INT16                              hwRxTriggerLevel; /* < RX������ʽʱ�����źŵ�ǿ�ȣ���λ0.1dBm */
    BBIC_CAL_HF_RX_TX_TRIG_CONFIG_STRU stTxTrigger;

    STEP_WIDTH_ENUM_UINT8           enStepWidth; /* < Step width, Unit is us */
    BBIC_CAL_CONFIG_MODE_ENUM_UINT8 enRxCfgMode;
    BBIC_CAL_HF_FE_STATE_ENUM_UINT8 enHffeState; /* < Hi6P01 State: 2-- Idle, 1-- Enablen, 0-- Disable */
    BBA_CAL_HFRX_CALTYPE_ENUM_UINT8 enM2mEnable;
    UINT16                          uhwPathNum;    /* < Path Config num */
    UINT16                          uhwFreqNum;    /* < Freq Config Num */
    UINT16                          uhwPatternNum; /* < Pattern Config Num */
    UINT16                          uhwStepNum;    /* < Step Config num */
    /*
     * Data Segment, ausData, format:
     *  BBIC_CAL_HF_TRX_PATH_CONFIG_STRU astPathConfig[n];      Any Path cfg, n=usPathConfigNum
     *  BBIC_CAL_RX_FREQ_CONFIG_STRU astFreqConfig[n];      Any Freq cfg, n=usFreqConfigNum
     *  UINT32                       aulRxPatternConfig[n]; Total Pattern
     * cfg,n=usPatternConfigNum,��װ��Լ����bit0��ʼȡֵ,
     *  ����������ȡֵ BBIC_CAL_HF_RX_AGC_STEP_CONFIG_STRU   astAgcStepCfg[n]; AGC Gain
     * Cfg
     */
    UINT8 aucData[4];
} BBIC_CAL_HF_RX_START_REQ_PARA_STRU;

/*
 * Description: HF RX Rssi
 */
typedef struct {
    INT16 ahwAnaRssi[2]; /* < 1RĬ��ȡ[0] */
    INT16 ahwWbRssi[2];  /* < 1RĬ��ȡ[0] */
} HF_RX_RSSI_STRU;

/*
 * Description: RX Cal Result report Ind
 */
typedef struct {
    UINT32 uhwErrorCode;
    UINT16 uhwCalTempNum; /* < cal Temp Cnt, one path one temp */
    UINT16 uhwRssiNum;    /* < Rssi Cnt */
    /*
     * Data segment, aucData, format:
     * INT16    alCalTemp[n];      Hi6370 Cal temp list
     * INT16    alAnaCalTemp[n];   Hi6P01 Cal temp list
     * HF_RX_RSSI_STRU    stRssi[n];     Rssi Result list
     */
    UINT8 aucData[4];
} BBIC_CAL_HF_RX_RESULT_IND_PARA_STRU;

typedef struct {
    STEP_WIDTH_ENUM_UINT8           enStepWidth;     /* < Step width, Unit is us */
    HF_POWER_CTRL_MODE_ENUM_UINT8   enPowerCtrlMode; /* *< Select Power ctrl mode */
    BBIC_CAL_HF_FE_STATE_ENUM_UINT8 enHffeState;     /* < Hi6P01 State: 2-- Idle, 1-- Enablen, 0-- Disable */
    BBA_CAL_HFTX_CALTYPE_ENUM_UINT8 enM2mCtrl;       /* < 0-TxУ׼��1-M2M��������У׼��2-M2M��λУ׼ */
    SIGNAL_TYPE_ENUM_UINT16         enSignalType;    /* < �ź�Դ���� */
    MODU_TYPE_ENUM_UINT16           enModuType;      /* < �������� */
    UINT16                          uhwPathNum;      /* < Path Config num */
    UINT16                          uhwFreqNum;      /* < Freq Config num */
    UINT16                          uhwPatternNum;   /* < Pattern Config num */
    UINT16                          uhwStepNum;      /* < Step Config num */
    /*
     * Data Segment, ausData, format:
     *  BBIC_CAL_HF_TRX_PATH_CONFIG_STRU astPathConfig[n];   Any Path cfg, n=usPathConfigNum
     *  BBIC_CAL_TX_FREQ_CONFIG_STRU astFreqConfig[n];      Any Freq cfg, n=usFreqConfigNum
     *  UINT32                       aulTxPatternConfig[n]; Total Pattern Cfg,n=ceil(usPatternConfigNum / 32
     * ),��װ��Լ����bit0��ʼȡֵ,����������ȡֵ HF_TX_STEP_CFG_STRU          astStepData[n];        Total Step Data Cfg
     */
    UINT8 aucData[4];
} BBIC_CAL_HF_TX_START_REQ_PARA_STRU;

/*
 * Description: TX CAL all path report IND struct
 */
typedef struct {
    UINT32 uhwErrorCode;
    UINT16 uhwCalTempCnt; /* < cal temp cnt, one path one temp */
    UINT16 uhwReserved;   /* < cal temp cnt, one path one temp */
    /*
     * Data segment, aucData, format:
     * INT16    ahwCalTemp[n];      Hi6370 Cal temp list
     * INT16    ahwAnaCalTemp[n];   Hi6P01 Cal temp list
     */
    UINT8 aucData[4];
} BBIC_CAL_HF_TX_RESULT_IND_PARA_STRU;

#define BBIC_CAL_HF_SELF_CAL_STRU_BEGIN

typedef struct {
    RAT_MODE_ENUM_UINT16  enRatMode;   /* ģʽ */
    BAND_ENUM_UINT16      enBand;      /* Ƶ�� */
    UINT32                uwFreqInfo;  /* Ƶ��,��Path NV���л�ȡ,��λ100KHZ */
    BANDWIDTH_ENUM_UINT16 enBandWidth; /* У׼���� */
    UINT16                uhwRxPathNum;
    UINT16                auhwRxPathIdx[2];
} BBIC_CAL_HF_RX_DCOC_CONFIG_STRU;

/*
 * Description: Rx DCOC Cal Req
 */
typedef struct {
    UINT16                          uhwBandNum; /* RX DCУ׼Band���� */
    UINT16                          uhwRsv;
     /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwBandNum����̬ʹ�� */
    BBIC_CAL_HF_RX_DCOC_CONFIG_STRU astCalList[BBIC_HF_MAX_BAND_NUM];
} BBIC_CAL_HF_RX_DCOC_START_REQ_PARA_STRU;

/*
 * Description: ÿ��BAND��RX DCOC�ϱ����
 */
typedef struct {
    UINT32                  uwErrorCode;
    UINT32                  uwValidCnt; /* < 2: 2R, 4: 4R */
    BBIC_CAL_DC_RESULT_STRU astRxDcInd[BBIC_HFCAL_MAX_ANT_NUM][BBIC_HFCAL_RX_MAX_VGA_NUM];
} BBIC_CAL_HF_RX_DCOC_BAND_STRU;

/*
 * Description: ���PATH��RX DC�ϱ����
 */
typedef struct {
    UINT32                        uwErrorCode;
    UINT16                        uhwBandNum; /* Band��Ч���� */
    UINT16                        uhwRsv;
    /* < �����鰴����������壬ʵ��ʹ��ʱ����uhwBandNum����̬ʹ�� */
    BBIC_CAL_HF_RX_DCOC_BAND_STRU astCalInd[BBIC_HF_MAX_BAND_NUM];
} BBIC_CAL_HF_RX_DCOC_RESULT_IND_PARA_STRU;

/*
 * Description: �¶Ȼ�ȡ�ӿ�
 */
typedef struct {
    BBIC_TEMP_CHANNEL_TYPE_ENUM_UINT16 enChannelType;
    INT16                              hwChannelNum;
} BBIC_CAL_TEMP_QRY_REQ_PARA_STRU;

/*
 * Description: �¶Ȼ�ȡ�ϱ��ӿ�
 */
typedef struct {
    UINT32                             uwErrorCode;
    BBIC_TEMP_CHANNEL_TYPE_ENUM_UINT16 enChannelType;
    INT16                              hwChannelNum;
    INT32                              wTemperature;
} BBIC_CAL_TEMP_QRY_IND_PARA_STRU;

/*
 * Description: PLL״̬��ȡ�ӿ�
 */
typedef struct {
    RAT_MODE_ENUM_UINT16  enRatMode; /* Ratģʽ */
    MODU_TYPE_ENUM_UINT16 enModType; /* ����ģʽ GSMʹ�� */
    UINT16                uhwBand;   /* Band */
    UINT16                uhwRsv;
} BBIC_CAL_PLL_QRY_REQ_PARA_STRU;

/*
 * Description: PLL״̬��ȡ�ϱ��ӿ�
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT32 uwRxPllStatus;
    UINT32 uwTxPllStatus;
} BBIC_CAL_PLL_QRY_IND_PARA_STRU;

/*
 * Description: DPDT���ýӿ�
 */
typedef struct {
    RAT_MODE_ENUM_UINT16           enRatMode;
    BBIC_DPDT_OPERTYPE_ENUM_UINT16 enOperType; /* ����DPDT״̬���ǻ�ȡDPDT״̬, 0--��ʾ����DPDT״̬,1--��ȡDPDT״̬ */
    UINT32                         uwValue;    /* Ŀǰֻ���˵�8bit����4bit��ʾTAS/MAS״̬,��4bit��ʾHALL״̬,
���е�4BIT��������:
0: TAS-ֱͨ  MAS-ֱͨ
1: TAS-����  MAS-ֱͨ
2: TAS-ֱͨ  MAS-����
3: TAS-����  MAS-���� */
    UINT16 uhwModemWorkType;                   /* ҵ��������,0--��ʾҵ��1--���� */
    UINT16 uhwRsv;
} BBIC_CAL_DPDT_REQ_PARA_STRU;

/*
 * Description: DPDT�����ϱ��ӿ�
 */
typedef struct {
    UINT32                         uwErrorCode;
    BBIC_DPDT_OPERTYPE_ENUM_UINT16 unOperType;
    UINT16                         uhwRsv;
    UINT32                         uwValue;
} BBIC_CAL_DPDT_IND_PARA_STRU;

/*
 * Description: TRX TAS���õľ������
 */
typedef struct {
    UINT16 ratMode;
    UINT16 band;
    UINT32 trxTasValue;
} BBIC_CAL_SetTrxTasReqParaStru;

/*
 * Description: TRX TAS���ý���ϱ��ӿ�
 */
typedef struct {
    UINT32 errorCode;
} BBIC_CAL_SetTrxTasCnfParaStru;

/*
 * Description: PLL״̬��ȡ����ϱ���Ϣ�ṹ��
 */
typedef struct {
    BBIC_CAL_DCXO_SET_ENUM_UINT16 enSetType;
    VOS_UINT16                    usBand;
    UINT32                        txArfcn; /* ����Ƶ��� */
} BBIC_CAL_DCXO_REQ_PARA_STRU;

/*
 * desc: dcxo����У׼��Ϣ����
 */
typedef struct {
    RAT_MODE_ENUM_UINT16                    ratMode;               /* Rat Mode */
    BAND_ENUM_UINT16                        bandNo;                /* Band No. */
    UINT32                                  rxFreqInfo;            /* RxƵ��,��λKHZ */

    UINT16                                  txPathIndex;           /* Tx Path Index */
    UINT16                                  dlPathIndex;           /* ����Path Index */
    UINT16                                  rxAntMap;              /* ������������map,Rx��������mapѡȡ������������ */
    INT16                                   rxSigIor;              /* �Ǳ����õ����߿ڹ���,������ʽ��1/8��λ�·� */
    TX_POWER_CFG_UNION                      pwrCfg;                /**< Selector(enPowerParaType) Power config */
    TX_PA_VCC_CAL_CONFIG_STRU               paVccCfg;              /* pa vcc���� */
    RX_AGC_GAIN_INDEX_STRU                  rxAgcIndex;            /* ��������IOR��Ӧ��RX AGC GAIN Index, �ӹ����·�*/
} BBIC_CAL_DcxoSelfCalPara;

/*
 * desc: dcxo����У׼�������
 */
typedef struct {
    UINT32                              errorCode;           /* DCXOУ׼������ */
    UINT16                              c2Fix;               /* C2У׼��� */
    UINT16                              c1Fix;               /* C1У׼��� */
    INT32                               calTemp;             /* C1&C2У׼���¶�,��λ0.001 */
    INT32                               initFreqInfo;        /* C1&C2У׼��Ƶ�����,��λHZ */
    BBIC_CAL_FLT_FORMAT_E15_T32_STRU    aValue[4];           /* A0A1У׼���,���A2A3ϵ����У׼,���ϱ�Ĭ��NV��ֵ
                                                               [0]:A0У׼ϵ��,
                                                               [1]:A1У׼ϵ��,
                                                               [2]:A2У׼ϵ��,
                                                               [3]:A3У׼ϵ��  */
    UINT32                              a0A1Enable;          /* A0A1У׼ʹ�� */
    INT32                               refXoTemp;           /* A0A1�ο��¶� */
    INT32                               beforeTemperatureUp; /* A0A1У׼ǰ�¶� */
    INT32                               afterTemperatureUp; /* A0A1У׼���¶� */
} BBIC_CAL_DcxoSelfCalRslt;

/*
 * Description: ��ƵFDIQ����Band��������Ϣ�ṹ��
 */
typedef struct {
    RAT_MODE_ENUM_UINT16 enRatMode; /* ģʽ */
    BAND_ENUM_UINT16     enBand;    /* Ƶ�� */
    UINT8                chsState;  /* 1-- ͨ������, 0--ͨ�������� */
    UINT8                portNum;   /* �˿����� */
    UINT8                portMap;   /* *< 1R: 0x1/0x2, 2R: 0x3 */
    UINT8                rsv;
    UINT32               uwRsv[2];
} BBIC_CAL_HF_SELFCAL_BAND_CONFIG_STRU;

/* װ���ض���rx adc�ṹ����ǰ����mmw��֧���� */
typedef struct {
    UINT16 offsetI[RFHAL_HFCAL_RXADC_INTRA_OFFSET_COEF_NUM];
    UINT16 offsetQ[RFHAL_HFCAL_RXADC_INTRA_OFFSET_COEF_NUM];
} BBIC_CAL_SelfCalRxAdcIntraOffsetRst;

typedef struct {
    UINT16 cDacCoef[RFHAL_HFCAL_RXADC_INTRA_CDAC_NUM][RFHAL_HFCAL_RXADC_INTRA_CDAC_COEF_NUM];
} BBIC_CAL_SelfCalRxAdcIntraCdacRst;

typedef struct {
    UINT16 offsetMode1Coef[RFHAL_HFCAL_RXADC_INTER_OFFSET_COEF_NUM];
    UINT16 offsetMode2Coef[RFHAL_HFCAL_RXADC_INTER_OFFSET_COEF_NUM]; /* InterOffset: 14-bit */
} BBIC_CAL_SelfCalRxAdcInterOffsetRst;

typedef struct {
    UINT16 gainErrMode1Coef[RFHAL_HFCAL_RXADC_INTER_GAINERR_COEF_NUM];
    UINT16 gainErrMode2Coef[RFHAL_HFCAL_RXADC_INTER_GAINERR_COEF_NUM]; /* InterOffset: 14-bit */
} BBIC_CAL_SelfCalRxAdcInterGainErrRst;

typedef struct {
    UINT16 skewMode1Coef[RFHAL_HFCAL_RXADC_INTER_SKEW_COEF_NUM];
    UINT16 skewMode2Coef[RFHAL_HFCAL_RXADC_INTER_SKEW_COEF_NUM];
} BBIC_CAL_SelfCalRxAdcInterSkewRst;

typedef struct {
    BBIC_CAL_SelfCalRxAdcIntraOffsetRst offset;
    BBIC_CAL_SelfCalRxAdcIntraCdacRst   cDac;
} BBIC_CAL_HfSelfCalRxAdcIntraChanRst;

typedef struct {
    BBIC_CAL_SelfCalRxAdcInterOffsetRst  offset;
    BBIC_CAL_SelfCalRxAdcInterGainErrRst gainError;
    BBIC_CAL_SelfCalRxAdcInterSkewRst    skew;
} BBIC_CAL_HfSelfCalRxAdcInterChanRst;

typedef struct {
    BBIC_CAL_HfSelfCalRxAdcIntraChanRst intraChan;
    BBIC_CAL_HfSelfCalRxAdcInterChanRst interChan;
} BBIC_CAL_RficHfSelfCalRxAdcChanRst;

typedef struct {
    UINT16 bandNum; /* ��Чband���� */
    UINT16 rsv;
    /* ֧�ֱ䳤�����������ʵ����д����֤�·����ϱ���Ϣ������16KB */
    BBIC_CAL_HF_SELFCAL_BAND_CONFIG_STRU bandArr[BBIC_HF_MAX_BAND_NUM];
} BBIC_CAL_RficHfRxAdcCalReqPara;

typedef struct {
    UINT32                             errCode;
    UINT16                             afeChanIndex;
    UINT16                             rsv;
    BBIC_CAL_RficHfSelfCalRxAdcChanRst rxAdcCal;
} BBIC_CAL_RficHfRxAdcPortCalRst;

typedef struct {
    UINT32 errorCode;
    UINT16 afeChanNum;
    UINT16 rsv;
    /* ֧�ֱ䳤�����������ʵ����д����֤�·����ϱ���Ϣ������16KB */
    BBIC_CAL_RficHfRxAdcPortCalRst hfRxAdcValue[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
} BBIC_CAL_RficHfRxAdcCalIndPara;

/*
 * Description: ��ƵFDIQУ׼��������ṹ��
 */
typedef struct {
    UINT16 uhwBandNum; /* ��Чband���� */
    UINT16 uwRsv;
    /* ֧�ֱ䳤�����������ʵ����д����֤�·����ϱ���Ϣ������16KB */
    BBIC_CAL_HF_SELFCAL_BAND_CONFIG_STRU astBand[BBIC_HF_MAX_BAND_NUM];
} BBIC_CAL_HF_SELFCAL_FDIQ_REQ_PARA_STRU;

/*
 * �ṹ˵��: IQ �ӽṹ��
 */
typedef struct {
    INT16 shwI; /* I· */
    INT16 shwQ; /* Q· */
} BBIC_CAL_HF_COMM_IQ_UNIT_STRU;

/*
 * �ṹ˵��: FDIQ�����Ĳ���У׼���
 */
typedef struct {
    BBIC_CAL_HF_COMM_IQ_UNIT_STRU astFdiqCalResultTap[RFHAL_HFCAL_FDIQ_CAL_TAP_NUM]; /* FDIQ Cal Result Tap */
} BBIC_CAL_HF_FDIQ_CAL_RESULT_TAP_STRU;

/*
 * �ṹ˵��: FDIQ�����Ĳ���У׼���
 */
typedef struct {
    /* RX FDIQ Cal Result VGA */
    BBIC_CAL_HF_FDIQ_CAL_RESULT_TAP_STRU astRxFdiqCalResultVga[RFHAL_HFCAL_FDIQ_CAL_VGA_NUM];
} BBIC_CAL_HF_FDIQ_CAL_RESULT_VGA_STRU;

/*
 * �ṹ˵��: RX FDIQ�����Ĳ���У׼���
 */
typedef struct {
     /* RX FDIQ Cal Result VGA */
    BBIC_CAL_HF_FDIQ_CAL_RESULT_VGA_STRU astRxFdiqCalResultBw[RFHAL_HFCAL_TRX_BANDWIDTH_NUM];
} BBIC_CAL_HF_RX_FDIQ_CAL_RESULT_STRU;

/*
 * �ṹ˵��: TX FDIQ�����Ĳ���У׼���
 */
typedef struct {
     /* RX FDIQ Cal Result VGA */
    BBIC_CAL_HF_FDIQ_CAL_RESULT_TAP_STRU astTxFdiqCalResultBw[RFHAL_HFCAL_TRX_BANDWIDTH_NUM];
} BBIC_CAL_HF_TX_FDIQ_CAL_RESULT_STRU;

/*
 * �ṹ˵��: TRX FDIQ�����Ĳ���У׼���
 */
typedef struct {
    BBIC_CAL_HF_RX_FDIQ_CAL_RESULT_STRU stRxFdiqCalResult; /* RX FDIQ Cal Result */
    BBIC_CAL_HF_TX_FDIQ_CAL_RESULT_STRU stTxFdiqCalResult; /* TX FDIQ Cal Result */
} BBIC_CAL_HF_TRX_FDIQ_CAL_RESULT_STRU;

/*
 * Description: FDIQ״̬��ȡ����ϱ���Ϣ�ṹ��
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT32 uwRsv1;
    UINT16 afeChanIndex;
    UINT16 uhwRsv2;
    UINT32 uwDataLen;

    BBIC_CAL_HF_TRX_FDIQ_CAL_RESULT_STRU stData;
} BBIC_CAL_HF_SELFCAL_IND_PORT_STRU;

/*
 * Description: FDIQ״̬��ȡ����ϱ���Ϣ�ṹ��
 */
typedef struct {
    UINT32                            uwErrorCode;
    UINT16                            afeChanNum;
    UINT16                            uhwRsv;
    BBIC_CAL_HF_SELFCAL_IND_PORT_STRU astData[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
} BBIC_CAL_HF_SELFCAL_IF_IND_PARA_STRU;

/*
 * Description: FIIQ״̬��ȡ����ϱ���Ϣ�ṹ��
 */
typedef struct {
    UINT32                  ulErrorCode;
    UINT32                  ulRsv1;
    UINT16                  usPortIndex;
    UINT16                  usRsv2;
    BBIC_CAL_IQ_RESULT_STRU stRxFiiqInd;
} BBIC_CAL_HF_RX_FIIQ_IND_PORT_STRU;

/*
 * Description: FIIQ״̬��ȡ����ϱ���Ϣ�ṹ��
 */
typedef struct {
    UINT32                            ulErrorCode;
    UINT16                            usPortNum;
    UINT16                            usRsv;
    BBIC_CAL_HF_RX_FIIQ_IND_PORT_STRU astData[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
} BBIC_CAL_HF_RX_FIIQ_RESULT_IND_PARA_STRU;

typedef struct {
    RAT_MODE_ENUM_UINT16            enRatMode;   /* ģʽ */
    BAND_ENUM_UINT16                enBand;      /* Ƶ�� */
    UINT32                          ulFreqInfo;  /* Ƶ�㣬�������� */
    BANDWIDTH_ENUM_UINT16           enBandWidth; /* У׼���� */
    UINT8                           ucChsState;  /* 1-ͨ�����棬0-������ */
    UINT8                           ucPortNum;   /* Port Num:1,2,4 */
    UINT8                           ucPortMap;
    BBIC_CAL_CONFIG_MODE_ENUM_UINT8 enAgcCfgMode;
    UINT8                           rsv[2];
    BBIC_CAL_HF_RX_AGC_GAIN_CONFIG_UNION aunAntInfo[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
} BBIC_CAL_HF_RX_FIIQ_CONFIG_STRU;

typedef struct {
    UINT16                          usBandNum;
    UINT16                          usRsv;
    BBIC_CAL_HF_RX_FIIQ_CONFIG_STRU astBand[BBIC_HF_MAX_BAND_NUM];
} BBIC_CAL_HF_RX_FIIQ_START_REQ_PARA_STRU;

/* For Hids */
typedef struct {
    UINT16                        uhwPathNum; /* path num */
    UINT16                        uhwRsv;
    BBIC_CAL_DPD_PATH_CONFIG_STRU astPathCfg[2];
} BBIC_CAL_DPD_START_REQ_PARA_HIDS_STRU;

typedef struct {
    UINT32                    uwErrorCode;
    UINT16                    uhwPathResultCnt; /* cal path num */
    UINT16                    uhwRsv;
    BBA_CAL_DPD_PATH_IND_STRU astPathCalResult[2];
} BBIC_CAL_DPD_IND_RESULT_PARA_HIDS_STRU;

#define BBIC_CAL_MT_STRU_BEGIN


typedef struct {
    UINT8                       ucTxEnable;     /* 1--Tx enable, 0--Tx Disable,��ӦFTXON�Ĳ���<switch> */
    UINT8                       ucIsSingleTone; /* �Ƿ��ǵ�����VOS_TRUE:��ʾ������ VOS_FALSE: ��ʾ���� */
    UINT8                       ucTxPaMode;     /* PA Mode, ��Ӧ^PFA�����еĲ���<level> */
    NR_SCS_TYPE_COMM_ENUM_UINT8 enScsType;      /* ���ز��������Ӧ^FCHAN �����е�<��Ӧ^FCHAN �����е�<band_width> */
    UINT16                      usMrxEanble;    /* Mrx Enable, 1--Enable, 0--Disable,��Ҫ���FPOWDET,Ĭ��Ϊenable, */
    /* Mimo����,Ŀǰ����MTʹ��:1 - 1T/1R, 2 - 2T/2R, 4 - 4R, 8 - 8R�� ��Ӧ^TSELRF�еĲ���<mimo_type> */
    UINT16 usMimoType;
    UINT16                usAntMap; /* ��ʾ�ڼ������ߣ����ǵ����ߣ���Ĭ��д1,��Ӧ^TSELRF�еĲ���<group> */
    /* ���Ʋ��Σ���Ӧ^FWAVE�����е�<type>������ʱ������GSM������GMSK������EDGE������8PSK */
    MODU_TYPE_ENUM_UINT16 enModType;
    MODEM_ID_ENUM_UINT16       enModemId;       /* Modem Id, ĿǰĬ��Ϊmodem0 */
    RAT_MODE_ENUM_UINT16       enRatMode;       /* Rat Mode, ��Ӧ^FCHAN �����е�<mode> */
    BAND_ENUM_UINT16           enBand;          /* Band No., ��Ӧ^FCHAN �����е�<band> */
    BANDWIDTH_ENUM_UINT16      enBandWith;      /* BandWidth, ��Ӧ^FCHAN �����е�<band_width> */
    UINT32                     ulFreqInfo;      /* Rx/Tx��Ƶ�ʣ�ͨ��^FCHAN �����е�<channel>ת������ */
    POWER_CTRL_MODE_ENUM_UINT8 enPowerCtrlMode; /* < Power Ctrl Mode */

    UINT8                      rbCfgEnable;     /* 1--RB config enable, 0--RB config disable,��ӦXXX<XXX> */
    UINT16                     rbNumCfg;        /* Config RB number,��ӦXXX<XXX> */
    UINT16                     rbStartCfg;      /* Config RB start point,��ӦXXX<XXX> */
    UINT8                      ucRsv[2];        /* Ԥ��λ������ */
    TX_POWER_CFG_UNION         unPowerPara;
} BBIC_CAL_MT_TX_REQ_PARA;

typedef struct {
    UINT8                       ucTxEnable;     /* 1--Tx enable, 0--Tx Disable,��ӦFTXON�Ĳ���<switch> */
    UINT8                       ucIsSingleTone; /* �Ƿ��ǵ�����VOS_TRUE:��ʾ������ VOS_FALSE: ��ʾ���� */
    UINT8                       ucTxPaMode;     /* PA Mode, ��Ӧ^PFA�����еĲ���<level> */
    NR_SCS_TYPE_COMM_ENUM_UINT8 enScsType;      /* ���ز��������Ӧ^FCHAN �����е�<��Ӧ^FCHAN �����е�<band_width> */
    UINT16                      usMrxEanble;    /* Mrx Enable, 1--Enable, 0--Disable,��Ҫ���FPOWDET,Ĭ��Ϊenable, */
    /* Mimo����,Ŀǰ����MTʹ��:1 - 1T/1R, 2 - 2T/2R, 4 - 4R, 8 - 8R�� ��Ӧ^TSELRF�еĲ���<mimo_type> */
    UINT16 usMimoType;
    UINT16                usAntMap; /* ��ʾ�ڼ������ߣ����ǵ����ߣ���Ĭ��д1,��Ӧ^TSELRF�еĲ���<group> */
    /* ���Ʋ��Σ���Ӧ^FWAVE�����е�<type>������ʱ������GSM������GMSK������EDGE������8PSK */
    MODU_TYPE_ENUM_UINT16 enModType;
    MODEM_ID_ENUM_UINT16       enModemId;       /* Modem Id, ĿǰĬ��Ϊmodem0 */
    RAT_MODE_ENUM_UINT16       enRatMode;       /* Rat Mode, ��Ӧ^FCHAN �����е�<mode> */
    BAND_ENUM_UINT16           enBand;          /* Band No., ��Ӧ^FCHAN �����е�<band> */
    BANDWIDTH_ENUM_UINT16      enBandWith;      /* BandWidth, ��Ӧ^FCHAN �����е�<band_width> */
    UINT32                     ulFreqInfo;      /* Rx/Tx��Ƶ�ʣ�ͨ��^FCHAN �����е�<channel>ת������ */
    POWER_CTRL_MODE_ENUM_UINT8 enPowerCtrlMode; /* < Power Ctrl Mode */

    UINT8                      ucRsv[3];        /* Ԥ��λ������ */
    TX_POWER_CFG_UNION         unPowerPara;
} BBIC_CAL_DCXO_MT_TX_REQ_PARA;

typedef struct {
    UINT32 errorCode;    /* ������ */
    UINT32 mrxCorrValue; /* MRX����ֵ */
    INT16  antPower;     /* ���߿ڶ�Ӧ�Ĺ���ֵ����λGUC 0.1db��L/NR: 1/8db */
    INT16  rsv;          /* ���ֽڶ��� */
} BBIC_CAL_MT_TX_PD_IND_PARA;


typedef struct {
    UINT8                 ucRxEnable; /* 1--Rx enable, 0--Rx Disable */
    UINT8                 ucRev;
    UINT16                uhwAgcGainIndex; /* ��Ӧ^FAGCGAIN�����<level> */
    MODEM_ID_ENUM_UINT16  enModemId;       /* Modem Id, ĿǰĬ��Ϊmodem0 */
    RAT_MODE_ENUM_UINT16  enRatMode;       /* Rat Mode, ��Ӧ^FCHAN �����е�<mode> */
    BAND_ENUM_UINT16      enBand;          /* Band No., ��Ӧ^FCHAN �����е�<band> */
    BANDWIDTH_ENUM_UINT16 enBandWith;      /* BandWidth, ��Ӧ^FCHAN �����е�<band_width> */
    /* Mimo����,Ŀǰ����MTʹ��:1 - 1T/1R, 2 - 2T/2R, 4 - 4R, 8 - 8R�� ��Ӧ^TSELRF�еĲ���<mimo_type> */
    UINT16 usMimoType;
    UINT16 usAntMap;   /* ��ʾ�ڼ������ߣ����ǵ����ߣ���Ĭ��д1,��Ӧ^TSELRF�еĲ���<group> */
    UINT32 dlFreqInfo; /* Rx/Tx��Ƶ�ʣ�ͨ��^FCHAN �����е�<channel>ת������ */
} BBIC_CAL_MT_RX_REQ_PARA;

/*
 * Description: RX Rssi Ind
 */
typedef struct {
    UINT32 errorCode;
    INT16  rssi[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_MT_RX_RSSI_IND_PARA;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
