
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

/* 可变长度宏定义，5010以后data只占位,num为0 */
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
 * TX LO校准时，每个path支支持校准哪些档位，最多支持4档，NV结构体变更会影响该宏定义
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
#define RFHAL_CAL_RX_MAX_VGA_NUM 8 /* 保持和NV_MAX_VGA_GAIN_NUM一致 */
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

/* RX FDIQ的最大支持带宽个数 */
#ifndef RFHAL_CAL_RX_FDIQ_MAX_BW_NUM
#define RFHAL_CAL_RX_FDIQ_MAX_BW_NUM 5
#endif

/* RX FDIQ 最大VGA档位个数 */
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

/* TX RFGAIN档位个数，共20个RF GAIN档位 */
#ifndef RFHAL_CAL_TX_RF_GAIN_MAX_NUM
#define RFHAL_CAL_TX_RF_GAIN_MAX_NUM 20
#endif

/* 有效采样率个数，支持2种采样率 */
#ifndef RFHAL_CAL_SAMPLE_RATE_MAX_NUM
#define RFHAL_CAL_SAMPLE_RATE_MAX_NUM 2
#endif

/* TX MRX 高采有效采样率个数，支持8种采样率 */
#ifndef RFHAL_CAL_TX_MRX_SAMPLE_RATE_MAX_NUM
#define RFHAL_CAL_TX_MRX_SAMPLE_RATE_MAX_NUM 8
#endif

/* TXIQ校准最大支持LPF个数 */
#ifndef RFHAL_CAL_LPF_MAX_NUM
#define RFHAL_CAL_LPF_MAX_NUM 3
#endif

/* TXLO校准最大支持23档个数 */
#ifndef RFHAL_CAL_TXLO_LPF_GAIN_MAX_NUM
#define RFHAL_CAL_TXLO_LPF_GAIN_MAX_NUM 23
#endif

/* TXIQ校准最大支持带宽个数 */
#ifndef RFHAL_CAL_TX_FDIQ_BW_MAX_NUM
#define RFHAL_CAL_TX_FDIQ_BW_MAX_NUM 10
#endif

/* 每个PATH支持单载波和MIMO校准结果 */
#ifndef RFHAL_CAL_MIMO_RSLT_MAX_NUM
#define RFHAL_CAL_MIMO_RSLT_MAX_NUM 2
#endif

/* MRXIQ校准最大支持带宽个数 */
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

/* RFIC上电自校准RXADC */
#ifndef RFHAL_HFCAL_RXADC_INTRA_OFFSET_COEF_NUM
/* 一个RXADC通道内校准共8个Offset系数,每个8bit,01subAdc共一个U16,以此类推 */
#define RFHAL_HFCAL_RXADC_INTRA_OFFSET_COEF_NUM   4
#endif

#ifndef RFHAL_HFCAL_RXADC_INTRA_CDAC_NUM
#define RFHAL_HFCAL_RXADC_INTRA_CDAC_NUM          16 /* 一个RXADC通道内校准共16个CDAC系数 */
#endif

#ifndef RFHAL_HFCAL_RXADC_INTRA_CDAC_COEF_NUM
#define RFHAL_HFCAL_RXADC_INTRA_CDAC_COEF_NUM     11 /* 一个RXADC通道内校准共11个CDAC系数 */
#endif

#ifndef RFHAL_HFCAL_RXADC_INTER_OFFSET_COEF_NUM
#define RFHAL_HFCAL_RXADC_INTER_OFFSET_COEF_NUM   16 /* 一个RXADC通道间校准共16个Offset系数, 14bit */
#endif

#ifndef RFHAL_HFCAL_RXADC_INTER_GAINERR_COEF_NUM
#define RFHAL_HFCAL_RXADC_INTER_GAINERR_COEF_NUM  14 /* 一个RXADC通道间校准共12个GainError系数, 14bit */
#endif

#ifndef RFHAL_HFCAL_RXADC_INTER_SKEW_COEF_NUM
#define RFHAL_HFCAL_RXADC_INTER_SKEW_COEF_NUM     8 /* 一个RXADC通道内校准共12个Skew系数, 15bit */
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

/* 需要校正的发射功率点为64个 */
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

/* HiRF一次配置支持的最大Band个数 */
#define BBIC_HFCAL_HIRF_MAX_BAND_NUM 2

/* 支持的最大RFIC个数 */
#define BBIC_CAL_MAX_RFIC_NUM 4

/* HF校准支持的最大MAS个数 */
#define BBIC_HFCAL_MAX_MAS_NUM 2

/* HF校准NCP Symbol配置个数 */
#define BBIC_HFCAL_NCP_SYMBOL_NUM 14

/* HF校准最大天线个数，最大支持4R */
#define BBIC_HFCAL_MAX_ANT_NUM 4

/* HFRX校准VGA个数，最大支持6 */
#define BBIC_HFCAL_RX_MAX_VGA_NUM 6

/* HF支持的最大Band个数 */
#define BBIC_HF_MAX_BAND_NUM 32

/* HF 4拼片CPE单个6P01中DIE的个数 */
#define BBIC_HF_TRX_MAX_DIE_NUM 8

/* et lut 提取RFDSP配置的单音阶数 */
#define BBIC_ET_LUT_CW_STEP_NUM 64

/* DPD校准频点数量 */
#define BBIC_DPD_CAL_FEQ_NUM 3

/* DPD Lut数量 */
#define BBIC_DPD_NUM 4

/* DPD Ctrl数量 */
#define BBIC_DPD_CTRL_NUM (BBIC_DPD_NUM / 2)

/* DPD SPL数量 */
#define BBIC_DPD_LUT_NUM 7

/* ETDPD SPL数量 */
#define BBIC_ETDPD_LUT_NUM 3

/* DPD IQ值数量 */
#define BBIC_DPD_SPL_NUM 16

/* TX支持最大的CC个数 */
#define TX_MAX_CC_NUM 2

/* TX支持最大的ANT个数 */
#define TX_MAX_ANT_NUM 2

/* RX支持最大的CC个数 */
#define RX_MAX_CC_NUM 5

/* RX支持最大的ANT个数 */
#define RX_MAX_ANT_NUM 8

/* RX支持的path最大数量 */
#define RX_MAX_PATH_OFFSET 4

/*
 * 1. 单卡 M0 最大支持 Rx:5cc, Tx:2cc
 * 2. 双卡 M0 最大支持 Rx:3cc, Tx:1cc
 *    双卡 M1 最大支持 Rx:1cc, Tx:1cc
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

    ID_BBIC_TOOL_GETX_APC_TBL_MNTN_INFO               = 0x7001, /* APC表校准维测信息 */
    ID_BBIC_TOOL_GETX_PAGAIN_MNTN_INFO                = 0x7002, /* PAGAIN校准维测信息 */
    ID_BBIC_TOOL_GETX_FREQCOMP_MNTN_INFO              = 0x7003, /* FREQCOMP校准维测信息 */
    ID_BBIC_TOOL_GETX_PRECHARGE_MNTN_INFO             = 0x7004, /* 预充电压校准维测信息 */
    ID_BBIC_TOOL_PA_VCC_EXTRACT_MRXCORR_MNTN_INFO     = 0x7005, /* Lut提取mrxcorr维测信息 */
    ID_BBIC_TOOL_PA_VCC_CAL_FITTING_SAMPLES_MNTN_INFO = 0x7006, /* Lut校准样本对维测信息 */
    ID_BBIC_TOOL_GETX_EDGE_DPD_MNTN_INFO              = 0x7007, /* DPD校准维测信息 */
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
    BBIC_CAL_CONFIG_MODE_GAIN_INDEX     = 0x0000, /* GAIN Index模式,需要拿Gain Index从NV项中获取增益控制字 */
    BBIC_CAL_CONFIG_MODE_GAIN_CODE      = 0x0001, /* Gain Code模式,直接应用该增益控制字 */
    BBIC_CAL_CONFIG_MODE_GAIN_SUB_INDEX = 0x0002, /* 高频场景下分别配置Hi6P01和Hi6370的Gain Index */
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
    MRX_R_PATH       = 0x00, /* 选择R PATH */
    MRX_RCCR_RC_PATH = 0x01, /* 选择RC path */
    MRX_RCCR_CR_PATH = 0x02, /* 选择CR path */
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

    /* 待补充完整的校准结果定义 */

    CAL_RESULT_ITEM_NAME_BUTT
};
typedef UINT16 CAL_RESULT_ITEM_NAME_ENUM_UINT16;

enum CAL_RESULT_WRITE_TYPE_ENUM {
    CAL_RESULT_WRITE_TYPE_NORMAL  = 0x0000, /* 正常校准场景下的结果写入 */
    CAL_RESULT_WRITE_TYPE_CO_BAND = 0x0001, /* CO-BAND场景下的结果写入 */

    CAL_RESULT_TYPE_BUTT
};
typedef UINT16 CAL_RESULT_WRITE_TYPE_ENUM_UINT16;

/*
 * desc: 新增reload nv参数，统一sub6g/mmw reload nv API
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
 * 结构说明: DPDT流程处理业务类型枚举
 */
enum BBIC_DPDT_OPERTYPE_ENUM {
    BBIC_DPDT_OPERTYPE_SET = 0,
    BBIC_DPDT_OPERTYPE_GET = 1,
    BBIC_DPDT_OPERTYPE_BUTT
};
typedef VOS_UINT16 BBIC_DPDT_OPERTYPE_ENUM_UINT16;

/*
 * 结构说明: DPDT流程处理业务类型枚举
 */
enum BBA_CAL_HFRX_CALTYPE_ENUM {
    CAL_HFRX_NOM2M   = 0,
    CAL_HFRX_BASEPWR = 1,
    CAL_HFRX_PHASE   = 2,
};
typedef UINT8 BBA_CAL_HFRX_CALTYPE_ENUM_UINT8;

/*
 * 结构说明: DPDT流程处理业务类型枚举
 */
enum BBA_CAL_HFTX_CALTYPE_ENUM {
    CALTYPE_NOM2M   = 0,
    CALTYPE_BASEPWR = 1,
    CALTYPE_PHASE   = 2,
};
typedef UINT8 BBA_CAL_HFTX_CALTYPE_ENUM_UINT8;

/*
 * 结构说明: DPDT流程处理业务类型枚举
 */
enum BBIC_CAL_DCXO_SET_ENUM {
    BBIC_DCXO_SET_DISABLE = 0,
    BBIC_DCXO_SET_ENABLE  = 1,

    BBIC_DCXO_SET_BUTT
};
typedef UINT16 BBIC_CAL_DCXO_SET_ENUM_UINT16;

/*
 * Description: 信号源格式
 */
enum BBIC_CAL_SIGNAL_TYPE_ENUM {
    BBIC_CAL_SIGNAL_TYPE_TONE = 0x00, /* 单音模式 */
    BBIC_CAL_SIGNAL_TYPE_DUAL_TONE,   /* 双音模式 */
    BBIC_CAL_SIGNAL_TYPE_MODU,        /* 调制模式 */
    BBIC_CAL_SIGNAL_TYPE_QUAD,        /* 四音模式 */
    BBIC_CAL_SIGNAL_TYPE_TYPE_BUTT,
};
typedef UINT16 BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16;

/*
 * Description: ETM档位模式枚举定义
 */
enum BBIC_CAL_ETM_GAIN_MODE_ENUM {
    BBIC_CAL_ETM_MODE_AUTO = 0x00, /* ETM自动模式 */
    BBIC_CAL_ETM_MODE_HIGH = 0x01, /* ETM高增益模式 */
    BBIC_CAL_ETM_MODE_MID  = 0x02, /* ETM中增益模式 */
    BBIC_CAL_ETM_MODE_BUTT = 0x03
};
typedef UINT8 BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8;

/*
 * Description: DPD档位模式枚举定义
 */
enum BBIC_CAL_DPD_LUT_INDEX_ENUM {
    BBIC_CAL_DPD_LUT_INDEX_AUTO = 0x00, /* 自动模式 */
    BBIC_CAL_DPD_LUT_INDEX_0    = 0x01,
    BBIC_CAL_DPD_LUT_INDEX_1    = 0x02,
    BBIC_CAL_DPD_LUT_INDEX_2    = 0x03,
    BBIC_CAL_DPD_LUT_INDEX_3    = 0x04,
    BBIC_CAL_DPD_LUT_INDEX_BUTT = 0x05
};
typedef UINT8 BBIC_CAL_DPD_LUT_INDEX_ENUM_UINT8;

/*
 * Description: 业务和侦听模式定义
 */
enum BBIC_CAL_SYS_STATUS_ENUM {
    BBIC_CAL_SYS_STATUS_SERVICE = 0x00, /* 业务模式 */
    BBIC_CAL_SYS_STATUS_LISTEN  = 0x01, /* 侦听模式 */
    BBIC_CAL_SYS_STATUS_BUTT
};
typedef UINT8 BBIC_CAL_SYS_STATUS_ENUM_UINT8;

/*
 * Description: ModemID
 */
enum BBIC_CAL_MODEM_ID_ENUM {
    BBIC_CAL_MODEM0_ID = 0x00, /* 主卡 */
    BBIC_CAL_MODEM1_ID = 0x01, /* 副卡 */
    BBIC_CAL_MODEM_ID_BUTT
};
typedef UINT16 BBIC_CAL_MODEM_ID_ENUM_UINT16;

/*
 * Description: 该频段配置激活或者关闭
 */
enum BBIC_CAL_BAND_CFG_MODE_ENUM {
    BBIC_CAL_BAND_CFG_MODE_ON  = 0x00, /* 该Band配置激活 */
    BBIC_CAL_BAND_CFG_MODE_OFF = 0x01, /* 该Band配置关闭 */
    BBIC_CAL_BAND_CFG_MODE_BUTT
};
typedef UINT8 BBIC_CAL_BAND_CFG_MODE_ENUM_UINT8;

/*
 * Description: DSDS类型
 */
enum BBIC_CAL_DSDS_TYPE_ENUM {
    BBIC_CAL_DSDS_TYPE_SINGAL_MODEM = 0x00, /* 单卡场景 */
    BBIC_CAL_DSDS_TYPE_DSDS2        = 0x01, /* DSDS2.0 */
    BBIC_CAL_DSDS_TYPE_DSDS3        = 0x02, /* DSDS3.0 */
    BBIC_CAL_DSDS_TYPE_BUTT
};
typedef UINT8 BBIC_CAL_DSDS_TYPE_ENUM_UINT8;

/*
 * desc: HF chs状态，当前只有0:直连，1:交叉两种状态
 */
enum BBACAL_HfChsStateEnum {
    BBACAL_HF_CHS_STATE_DIRECT_CONNECT = 0x00,
    BBACAL_HF_CHS_STATE_CROSS_OVER,
    BBACAL_HF_CHS_STATE_BUTT
};
typedef VOS_UINT8 BBACAL_HF_CHS_STATE_ENUM_UINT8;

/*
 * desc: HF port数量，当前只支持2R/4R
 */
enum BBACAL_HfPortNumDefEnum {
    BBACAL_HF_PORT_NUM_DEF_TWO  = 0x02,
    BBACAL_HF_PORT_NUM_DEF_FOUR = 0x04,
    BBACAL_HF_PORT_NUM_DEF_BUTT = 0x0f,
};
typedef VOS_UINT8 BBACAL_HF_PORT_NUM_DEF_ENUM_UINT8;

/*
 * Description: TRX和RFDSP的交互类型
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
 * Description : ComponentType枚举值
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
    /* < 该数组按照最大来定义，实际使用时根据uhwPathNum来动态使用 */
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
    UINT8  ucVccType : 2;   /* 0: 表示使用APC功率来查Vcc; 1: 表示使用Pa Vcc功率查Vcc;
                         2: 表示直接使用Vcc */
    UINT8                             ucRsv : 5;
    UINT8                             ucTxPaMode; /* < PA Mode, reference BBIC_CAL_PA_MODE_ENUM_UINT8 */
    BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8 enEtmMode;  /* ETM档位控制模式, 具体定义参考BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8 */
    UINT8                             ucRsv1;
} TX_PA_CONFIG_STRU;

/*
 * Description: PA Vcc Cal config
 */
typedef struct {
    INT16 shwPaVccPwr;     /* < PA Vcc ctrl , Target Power using to search aptcode or Vcc mv */
    UINT8 ucPaVccMode : 1; /* < PA Vcc power mode ,0:apt , 1:et */
    UINT8 ucPaVccFlag : 2; /* < Pa Vcc mode, 0:lab vcc, 1: factory vcc, reference BBIC_CAL_PA_VCC_FLAG_ENUM_UINT8 */
    UINT8 ucDpdEn : 2;     /* 0:表示DPD off; 1: 表示DPD Bypass; 2: 表示DPD On */
    /* ETM档位控制模式, 具体定义参考BBIC_CAL_ETM_GAIN_MODE_ENUM_UINT8 */
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
} BBIC_CAL_LO_CODE_STRU; /* < 保持和RFHAL_CAL_TX_LO_CODE_STRU一致 */

/*
 * Description: LO result struct
 */
typedef struct {
    UINT16                shwMaxLpfGain; /* 校准的最大LPF GAIN */
    UINT16                shwMinLpfGain; /* 校准的最小LPF GAIN */
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
    UINT16                    uhwAgcTableIndex; /* < AGC控制表 */
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
 * Description: AGC配置联合体
 */
typedef union {
    RX_AGC_GAIN_INDEX_STRU stAgcGainIndex; /* AGC配置为AGC GAIN Index模式下生效 */
    RX_AGC_GAIN_CODE_STRU  stAgcGainCode;  /* AGC配置为AGC GAIN Code模式下生效 */
} BBIC_CAL_RX_AGC_GAIN_CONFIG_UNION;

/*
 * Description: IP2提取AGC档位配置的结构体
 */
typedef struct {
    BBIC_CAL_CONFIG_MODE_ENUM_UINT8   enRxCfgMode; /* AGC配置为AGC GAIN Code模式下生效 */
    UINT8                             ucRsv[3];
    BBIC_CAL_RX_AGC_GAIN_CONFIG_UNION unRxAgcInfo;
} BBIC_CAL_IP2_AGC_GAIN_CONFIG_STRU;

/*
 * Name        : BBIC_CAL_RXIQ_AGC_GAIN_CONFIG_STRU
 * Description : RXIQ AGC配置的结构体
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
 * Description: MRX增益配置联合体
 */
typedef union {
    UINT16                 uhwMrxGainIndex; /* MRX GAIN Index模式下有效 */
    MRX_AGC_GAIN_CODE_STRU stMrxGainCode;   /* MRX GAIN Code模式下有效 */
} MRX_GAIN_CONFIG_UNION;

/*
 * Description: bbic cal result path infomation.
 */
typedef struct {
    UINT32                     uwPathErrorCode;
    UINT32                     uwRsv1; /* < 预留给物理层使用，记录过程告警信息 */
    BBIC_CAL_RF_PATH_INFO_STRU stPathInfo;
    UINT16                     uhwRsv2; /* 预留给Nv使用 */
    UINT16                     uhwRsv3; /* 预留给Nv使用 */
} BBIC_CAL_RESULT_PATH_INFO_STRU;

typedef struct {
    BAND_ENUM_UINT16     enBand;
    RAT_MODE_ENUM_UINT16 enRatMode;
    UINT16               uhwUpLinkFlag; /* 是否是上行path */
    UINT16 uhwPathIndex; /* nr的fr1和fr2可以通过band号来区分，gsm的调制方式现在是通过pathIndex来区分，是否需要扩展 */
    UINT16 uhwAntMap;    /* 需要清理那些ant配置，当前可以先不支持，按照全F处理 */
    UINT16 auhwRsv[3];
} BBIC_CAL_NV_RESET_PATH_CFG_STRU;

typedef struct {
    UINT16                          uhwPathNum; /* < 有效PATH个数 */
    UINT16                          uhwRsv;
    /* < 该数组按照最大来定义，实际使用时根据pathNum来动态使用 */
    BBIC_CAL_NV_RESET_PATH_CFG_STRU astPathCfg[BBIC_CAL_RX_MAX_PATH_NUM];
} BBIC_CAL_NV_RESET_REQ_PARA_STRU;

#define BBIC_CAL_SELF_CAL_STRU_BEGIN

/*
 * Description: DCXO Self Cal REQ
 */
typedef struct {
    UINT16 uhwListNum; /* RX DC校准最大PATH个数 */
    UINT16 uhwRsv;
    UINT8  aucData[4];
} BBIC_CAL_COMM_SELFCAL_START_REQ_PARA_STRU;

/*
 * Description: DCXO Self Cal REQ
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT16 uhwListNum; /* Path/BAND最大个数 */
    UINT16 uhwRsv;
    UINT8  aucData[4];
} BBIC_CAL_COMM_SELFCAL_RESULT_IND_PARA_STRU;

/*
 * Description: RX FIIQ校准每个PATH的配置
 */
typedef struct {
    BAND_ENUM_UINT16      enBand;              /* 频段,从Path NV项中获取 */
    RAT_MODE_ENUM_UINT16  enRatMode;           /* 模式,从Path NV项中获取 */
    UINT16                uhwDlPathIndex;      /* 下行PATH Index, 从工具获取 */
    BANDWIDTH_ENUM_UINT16 enBandWidth;         /* 带宽,物理层固定配置 */
    UINT32                uwRxFreqInfo;        /* 仪器的配置频率,单位100KHZ,从工具获取 */
    UINT16                uhwFdiqAlgMode : 1;  /* FDIQ校准时有效，0表示时域模式，1表示频域模式 */
    UINT16                uhwFdiqFragMode : 1; /* FDIQ校准时频域模式下有效，0表示不分段，1表示分段 */
    UINT16                uhwFdiqRsv : 2;
    UINT16                uhwFdiqFragIdx : 4; /* FDIQ校准时分段场景下有效，分段索引，1表示第一段，2表示第二段 */
    UINT16                uhwRetestIdx : 3;   /* 针对小信号的场景 需要多次校准 该变量标识当前是第几次重测 计数从1开始 */
    UINT16                uhwRsv : 5;
    UINT8                 ucRsv;
    UINT8                 ucAntCfgMap; /* 天线配置,工具会根据能否并行校准给某个天线信号，需要从工具获取 */
    /* AGC GAIN配置,工具配置仪表功率强度与档位需要匹配，建议从工具获取 */
    BBIC_CAL_RXIQ_AGC_GAIN_CONFIG_STRU astAgcConfig[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RX_IQ_PATH_CONFIG_STRU;

typedef struct {
    UINT16                          uhwMaxPathNum; /* 最大PATH个数 */
    UINT16                          uhwRsv;
    BBIC_CAL_RX_IQ_PATH_CONFIG_STRU astCalList[BBIC_CAL_RX_IQ_MAX_PATH_NUM]; /* 每个PATH的RX IQ配置信息 */
} BBIC_CAL_RX_IQ_START_REQ_PARA_STRU;

/*
 * Description: 每个PATH的RX FIIQ结果
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    /* 每个PATH的RX IQ校准结果,最大支持2R,[0]表示主集,[1]表示分集 */
    BBIC_CAL_IQ_RESULT_STRU astRxIqInd[RFHAL_CAL_MAX_ANT_NUM];
} BBIC_CAL_RX_FIIQ_RESULT_PATH_STRU;

/*
 * Description: RX FIIQ上报结果
 */
typedef struct {
    UINT32                            uwErrorCode;
    UINT16                            uhwMaxPathNum; /* 最大PATH个数 */
    UINT16                            uhwRsv;
    BBIC_CAL_RX_FIIQ_RESULT_PATH_STRU astCalInd[BBIC_CAL_RX_IQ_MAX_PATH_NUM]; /* 每个PAHT的RX FIIQ结果 */
} BBIC_CAL_RX_FIIQ_RESULT_IND_PARA_STRU;

/*
 * Description: IQ滤波系数,RX FDIQ使用
 */
typedef struct {
    INT16 shwCoeffI; /* RX FDIQ I路滤波系数 */
    INT16 shwCoeffQ; /* RX FDIQ Q路滤波系数 */
} BBIC_CAL_RXIQ_COEFF_STRU;

/*
 * Description: IQ滤波系数,TX FDIQ使用
 */
typedef struct {
    INT16 shwCoeffI; /* TX FDIQ I路滤波系数 */
    INT16 shwCoeffQ; /* TX FDIQ Q路滤波系数 */
} BBIC_CAL_IQ_COEFF_STRU;

/*
 * Description: RX FDIQ结果
 */
typedef struct {
    UINT16                   uhwFdiqTaps; /* 滤波器系数阶数，最大15阶 */
    UINT16                   uhwRsv;
    BBIC_CAL_RXIQ_COEFF_STRU astFdiqCoeff[RFHAL_CAL_RX_FDIQ_TAPS_MAX_NUM]; /* 每阶的滤波器系数值 */
} BBIC_CAL_RX_FDIQ_RESULT_STRU;

/*
 * Description: 每个PATH的RX FDIQ校准结果
 */
typedef struct {
    UINT8 tonePowdB[RFHAL_CAL_IRR_TONE_MAX_NUM]; /* 每个音的信号功率, 单位dB */
    UINT8 imagPowdB[RFHAL_CAL_IRR_TONE_MAX_NUM]; /* 每个音的参考功率, 单位dB */
    SINT8 iRRRslt[RFHAL_CAL_IRR_TONE_MAX_NUM];   /* IRR计算结果, 最大支持8个音 */
} BBIC_CAL_IrrResultStru;

/*
 * Description: 每个PATH的RX FDIQ校准结果
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT16                         uhwFdiqAlgMode : 1;  /* FDIQ校准时有效，0表示时域模式，1表示频域模式 */
    UINT16                         uhwFdiqFragMode : 1; /* FDIQ校准时频域模式下有效，0表示不分段，1表示分段 */
    UINT16                         uhwFdiqRsv : 2;
    UINT16                         uhwFdiqFragIdx : 4; /* FDIQ校准时分段场景下有效，分段索引，1表示第一段，2表示第二段 */
    UINT16                         uhwRsv : 8;
    UINT16                         uhwRsv2;
    BBIC_CAL_RX_FDIQ_RESULT_STRU   astRxIqInd[RFHAL_CAL_MAX_ANT_NUM]; /* 2R天线的RX IQ校准结果,[0]表示主集,[1]表示分集 */
    BBIC_CAL_IrrResultStru         irrRslt;                           /* IRR计算结果 */
} BBIC_CAL_RX_FDIQ_RESULT_PATH_STRU;

/*
 * Description: RX FDIQ校准结果
 */
typedef struct {
    UINT32                            uwErrorCode;
    UINT16                            uhwMaxPathNum; /* 最大PATH个数 */
    UINT16                            uhwRsv;
    BBIC_CAL_RX_FDIQ_RESULT_PATH_STRU astCalInd[BBIC_CAL_RX_IQ_MAX_PATH_NUM]; /* 每个PATH校准结果 */
} BBIC_CAL_RX_FDIQ_RESULT_IND_PARA_STRU;

/*
 * Description: 每个PATH的TX IQ配置信息
 */
typedef struct {
    BAND_ENUM_UINT16     enBand;         /* 频段,从Path NV项中获取 */
    RAT_MODE_ENUM_UINT16 enRatMode;      /* 模式,从Path NV项中获取 */
    UINT32               uwTxFreqInfo;   /* 上行频率,单位100KHZ, 从Path NV项中获取 */
    UINT16               uhwUlPathIndex; /* 上行PATH Index, 从工具获取 */
    UINT16 uhwLpfConfig; /* LPF配置,暂时从工具获取,后续优化,非256QAM固定一种LPF配置,256QAM需要支持7种LPF配置 */
    UINT16 uhwRsv;
    UINT16 uhwValidCnt;                                        /* 有效RF GAIN档位,从Path NV项中获取 */
    TX_REG_CTRL_STRU astRficPara[BBIC_CAL_TX_APC_MAX_CAL_NUM]; /* RF GAIN配置,最大支持20档,从Path NV项中获取 */
    /* 每档RF GAIN对应的MRX档位,根据每档RF GAIN对应的功率值索引得到,从Path NV项中获取 */
    UINT16           auhwMrxGainIndex[BBIC_CAL_TX_APC_MAX_CAL_NUM];
} BBIC_CAL_TX_IQ_PATH_CONFIG_STRU;

/*
 * Description: TX IQ校准REQ结构体
 */
typedef struct {
    UINT16                          uhwPathNum; /* 实际PATH个数 */
    UINT16                          uhwRsv;
    /* < 该数组按照最大个数来定义，实际使用时根据uhwPathNum来动态使用 */
    BBIC_CAL_TX_IQ_PATH_CONFIG_STRU astCalList[BBIC_CAL_TX_IQ_MAX_PATH_NUM];
} BBIC_CAL_TX_IQ_START_REQ_PARA_STRU;

/*
 * Description: TX FDIQ校准结果
 */
typedef struct {
    BBIC_CAL_IQ_COEFF_STRU astFdiqCoeff[RFHAL_CAL_TX_FDIQ_TAPS_MAX_NUM]; /* 每阶的滤波器系数值 */
} BBIC_CAL_TX_FDIQ_RESULT_STRU;

/*
 * Name        : BBIC_CAL_MRX_FDIQ_RESULT_STRU
 * Description : MRX FDIQ校准结果
 */
typedef BBIC_CAL_TX_FDIQ_RESULT_STRU BBIC_CAL_MRX_FDIQ_RESULT_STRU;

/*
 * Discription: 每个phase的各个带宽下的校准结果；每个带宽下需要区分DPO ON和DPD OFF；
 *              其中20M带宽以下只保存1种带宽,共10个带宽
 */
typedef struct {
    /* 每种带宽下支持DPDON和DPD OFF二种采样率,共10种带宽，其中20M(包含20M)只保存一种带宽 */
    BBIC_CAL_TX_FDIQ_RESULT_STRU astTxFdiqBwRslt[RFHAL_CAL_TX_FDIQ_BW_MAX_NUM][RFHAL_CAL_SAMPLE_RATE_MAX_NUM];
} BBIC_CAL_TX_FDIQ_BW_STRU;

/*
 * Description: TX IQ校准结果
 */
typedef struct {
    BBIC_CAL_TX_FDIQ_BW_STRU stTxFdiq4phaseRslt;
    BBIC_CAL_TX_FDIQ_BW_STRU stTxFdiq8phaseRslt;
} BBIC_CAL_TX_FDIQ_PHASE_STRU;

/*
 * Description: 每个PATH的TXIQ校准结果
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo; /* 频段 */
    /* TX IQ校准结果，最大支持4个LPF，每个LPF支持2种采样率 */
    BBIC_CAL_TX_FDIQ_PHASE_STRU astTxIqInd[RFHAL_CAL_MIMO_RSLT_MAX_NUM];
    /* MRX IQ校准结果，区分带宽，不区分采样率 */
    BBIC_CAL_MRX_FDIQ_RESULT_STRU astMrxIqInd[RFHAL_CAL_MIMO_RSLT_MAX_NUM][RFHAL_CAL_MRX_FDIQ_BW_MAX_NUM];
    /* irr计算结果 */
    BBIC_CAL_IrrResultStru irrRslt[RFHAL_CAL_TXIQ_PHASE_MAX_NUM][RFHAL_CAL_LPF_MAX_NUM];
} BBIC_CAL_TX_IQ_PATH_STRU;

/*
 * Description: TX IQ校准结果
 */
typedef struct {
    UINT32                   uwErrorCode;
    UINT16                   uhwPathNum; /* 有效的Path数量 */
    UINT16                   uhwRsv;
     /* < 该数组按照最大个数来定义，实际使用时根据uhwPathNum来动态使用 */
    BBIC_CAL_TX_IQ_PATH_STRU astTxIqInd[BBIC_CAL_TX_IQ_MAX_PATH_NUM];
} BBIC_CAL_TX_IQ_RESULT_IND_PARA_STRU;

/*
 * Description: 每个PATH的TX LO配置信息
 */
typedef struct {
    BAND_ENUM_UINT16     enBand;                               /* 频段,从Path NV项中获取 */
    RAT_MODE_ENUM_UINT16 enRatMode;                            /* 模式,从Path NV项中获取 */
    UINT32               uwTxFreqInfo;                         /* 上行频率,单位100KHZ, 从Path NV项中获取 */
    UINT16               uhwUlPathIndex;                       /* 上行PATH Index, 从工具获取 */
    UINT16               uhwValidCnt;                          /* 有效RF GAIN档位,从Path NV项中获取 */
    /* 校准方案变更，只需要校准4Phase和8Phase，最大BB Gain、最小BB Gain4个Apc Code,从Path NV项中获取 */
    TX_REG_CTRL_STRU astRficPara[BBIC_CAL_TX_LO_MAX_STEP_NUM];
    /* 校准方案变更，只需要校准4Phase和8Phase，最大BB Gain、最小BB Gain 4个ApcCode,从Path NV项中获取 */
    UINT16 auhwMrxGainIndex[BBIC_CAL_TX_LO_MAX_STEP_NUM];
} BBIC_CAL_TX_LO_PATH_CONFIG_STRU;

/*
 * Description: TX LO校准REQ结构体
 */
typedef struct {
    UINT16                          uhwPathNum; /* < 有效的Path数量 */
    UINT16                          uhwRsv;
    /* < 该数组按照最大个数来定义，实际使用时根据uhwPathNum来动态使用 */
    BBIC_CAL_TX_LO_PATH_CONFIG_STRU astCalList[BBIC_CAL_TX_IQ_MAX_PATH_NUM];
} BBIC_CAL_TX_LO_START_REQ_PARA_STRU;

/*
 * Description: TX IQMISMATCH Cal result for any path
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo; /* 频段 */
    BBIC_CAL_LO_RESULT_STRU        st4PhaseResult;
    BBIC_CAL_LO_RESULT_STRU        st8PhaseResult;
} BBIC_CAL_TX_LO_PATH_STRU;

/*
 * Description: TX LO上报结果
 */
typedef struct {
    UINT32                   uwErrorCode;
    UINT16                   uhwPathNum; /* 有效的PATH数量 */
    UINT16                   uhwRsv;
     /* 该数组按照最大个数来定义，实际使用时按照uhwPathNum来动态使用 */
    BBIC_CAL_TX_LO_PATH_STRU astTxLoInd[BBIC_CAL_TX_LO_MAX_PATH_NUM];
} BBIC_CAL_TX_LO_RESULT_IND_PARA_STRU;

/*
 * Dsecription: IP2 校准Any Path Config结构体
 */
typedef struct {
    UINT16 uhwBand;             /* * Band Id 废弃 */
    UINT16 enCaRatMode;         /* * Ca 制式 */
    UINT16 uhwDlPathIndex;      /* * 下行Path索引 废弃 */
    UINT16 uhwBandConfigIndex;  /* * Band Config资源索引, 只在CA下使用 */
    UINT16 uhwIp2ResourceIndex; /* * IP2配置资源索引 */
    UINT16 uhwRsv;
} BBIC_CAL_IP2_PATH_CONFIG_STRU;

/*
 * Dsecription: RXIP2 校准REQ，由PC下发
 */
typedef struct {
    UINT16                        uhwPathNum;
    UINT16                        uhwRsv;
     /* * < 该数组按照最大个数来定义，实际使用时根据uhwMaxSegmentNum来动态使用 */
    BBIC_CAL_IP2_PATH_CONFIG_STRU astCalList[BBIC_CAL_IP2_MAX_PATH_NUM];
} BBIC_CAL_IP2_START_REQ_PARA_STRU;

/*
 * Dsecription: RXIP2 校准结果结构体
 */
typedef struct {
    INT16  shwICode;          /* < DCI Code */
    INT16  shwQCode;          /* < DCQ Code */
    INT32  swImd2;            /* IMD2值,线性转Db折算天线口的值 */
    INT16  shwIp2RunCodeI[6]; /* 运行中间结果 */
    INT16  shwIp2RunCodeQ[6]; /* 运行中间结果 */
    INT32  swRunImd2[6];      /* IMD2值,线性转Db折算天线口的值 */
    INT16  shwTxPower;        /* 校准时功率 */
    UINT16 uhwRsv;            /* 保留 */
} BBIC_CAL_IP2_IQ_RESULT_STRU;

typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;

    /*
     * IP2校准结果,需要区分单载波和MIMO，并且单载波或者MIMO下需要区分二种带宽:0窄带，1 宽带
     * [0][0]--单载波窄带的IP2校准结果, [0][1]--单载波宽带的IP2校准结果
     * [1][0]--MIMO窄带的IP2校准结果,   [1][1]--MIMO宽带的IP2校准结果
     */
    BBIC_CAL_IP2_IQ_RESULT_STRU astResult[RFHAL_CAL_MIMO_RSLT_MAX_NUM][RFHAL_CAL_IP2_CAL_BW_NUM];
} BBIC_CAL_IP2_PATH_RESULT_STRU;

/*
 * Dsecription: IP2 校准CNF，上报给PC侧
 */
typedef struct {
    UINT32                        uwErrorCode;
    UINT16                        uhwPathNum;
    UINT16                        uhwRsv;
    /*
     * < 该数组按照最大个数来定义，实际使用时根据uhwMaxSegmentNum来动态使用
     */
    BBIC_CAL_IP2_PATH_RESULT_STRU astCalResult[BBIC_CAL_IP2_MAX_PATH_NUM];

} BBIC_CAL_IP2_RESULT_IND_PARA_STRU;

/*
 * Description: MRX DCOC cal configuration
 */
typedef struct {
    BAND_ENUM_UINT16        enBand;                                  /* 频段,从Path NV项中获取 */
    RAT_MODE_ENUM_UINT16    enRatMode;                               /* 模式,从Path NV项中获取 */
    UINT32                  uwTxFreqInfo;                            /* 频率, 单位100KHZ,从Path NV项中获取 */
    UINT16                  uhwUlPathIndex;                          /* 上行PATH Index, 从工具获取 */
    UINT16                  uhwMrxValidCnt;                          /* 有效MRX档位个数,从Path NV项中获取 */
    MRX_AGC_GAIN_INDEX_STRU astMrxGainIndex[RFHAL_CAL_MRX_GAIN_NUM]; /* MRX Gain配置,从Path NV项中获取 */
} BBIC_CAL_MRX_DCOC_CONFIG_STRU;

/*
 * Description: MRX DCOC校准请求原语
 */
typedef struct {
    UINT16                        uhwPathNum; /* < 有效PATH个数 */
    UINT16                        uhwRsv;
     /* < 该数组按照最大来定义，实际使用时根据uhwPathNum来动态使用 */
    BBIC_CAL_MRX_DCOC_CONFIG_STRU astCalList[BBIC_CAL_MRX_DCOC_MAX_PATH_NUM];
} BBIC_CAL_MRX_DCOC_START_REQ_PARA_STRU;

/*
 * Description: 每个PATH的MRX DCOC结果上报
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT16                         uhwRpathMrxGainCnt; /* MRX GAIN档位个数 */
    UINT16                         uhwRccrpathMrxGainCnt;
    BBIC_CAL_DC_RESULT_STRU        astMrxDcRInd[RFHAL_CAL_MRX_GAIN_NUM];    /* MRX DC结果上报,最大支持8档MRX GAIN */
    BBIC_CAL_DC_RESULT_STRU        astMrxDcRccrInd[RFHAL_CAL_MRX_GAIN_NUM]; /* MRX DC结果上报,最大支持8档MRX GAIN */
} BBIC_CAL_MRX_DCOC_PATH_STRU;

/*
 * Description: MRX DCOC校准结果上报
 */
typedef struct {
    UINT32                      uwErrorCode;
    UINT16                      uhwPathNum; /* < 有效PATH个数 */
    UINT16                      uhwRsv;
    /* < 该数组按照最大来定义，实际使用时根据uhwPathNum来动态使用 */
    BBIC_CAL_MRX_DCOC_PATH_STRU astCalInd[BBIC_CAL_MRX_DCOC_MAX_PATH_NUM];
} BBIC_CAL_MRX_DCOC_RESULT_IND_PARA_STRU;

/*
 * Description: 每个带宽的配置
 */
typedef struct {
    BANDWIDTH_ENUM_UINT16 enBandWith;      /* 带宽配置 */
    UINT16                usValidCnt;      /* 有效采用率个数 */
    UINT16                asSampleRate[2]; /* 采用率配置 */
} BBIC_CAL_MRX_DELAY_BW_CONFIG_STRU;

/*
 * Description: 每个PATH对应的MRX DELAY配置
 */
typedef struct {
    BAND_ENUM_UINT16                  enBand;         /* 频段,从Path NV项中获取 */
    RAT_MODE_ENUM_UINT16              enRatMode;      /* 模式,从Path NV项中获取 */
    UINT32                            uwTxFreqInfo;   /* 频率, 单位100khz, 从Path NV项中获取 */
    UINT16                            uhwUlPathIndex; /* 上行PATH Index, 从工具获取 */
    UINT16                            uhwRsv;
    BBIC_CAL_MRX_DELAY_BW_CONFIG_STRU stBwCofig; /* SE方案变更，产线只校准一个带宽 */
} BBIC_CAL_MRX_DELAY_CONFIG_STRU;

/*
 * Description: MRX DELAY校准REQ消息
 */
typedef struct {
    UINT16                         uhwPathNum; /* 有效PATH个数 */
    UINT16                         uhwRsv;
    /* 该数组按照最大来定义，实际根据uhwPathNum来动态使用 */
    BBIC_CAL_MRX_DELAY_CONFIG_STRU astCalList[BBIC_CAL_MRX_DELAY_MAX_PATH_NUM];
} BBIC_CAL_MRX_DELAY_START_REQ_PARA_STRU;

/*
 * Description: 每个带宽下的MRX DELAY上报结果
 */
typedef struct {
    BANDWIDTH_ENUM_UINT16 enBandWith;             /* 带宽 */
    UINT16                usValidCnt;             /* 该带宽下的采样率个数，最大支持2个采样率 */
    UINT16                ahwSampleRateResult[2]; /* 每个采样率的校准结果 */
} BBIC_CAL_MRX_DELAY_BW_RESULT_STRU;

/*
 * Description: 每个Path的Mrx Delay结果上报
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU    stPathInfo;
    BBIC_CAL_MRX_DELAY_BW_RESULT_STRU astMrxDelayInd; /* SE方案变更，产线只校准一个带宽 */
} BBIC_CAL_MRX_DELAY_PATH_STRU;

/*
 * Description: 多个PATH的MRX DELAY上报结果
 */
typedef struct {
    UINT32                       uwErrorCode;
    UINT16                       uhwPathNum; /* 有效PATH个数 */
    UINT16                       uhwRsv;
    /* 该数组按照最大来定义，实际根据uhwPathNum来动态使用 */
    BBIC_CAL_MRX_DELAY_PATH_STRU astCalInd[BBIC_CAL_MRX_DELAY_MAX_PATH_NUM];
} BBIC_CAL_MRX_DELAY_RESULT_IND_PARA_STRU;

/*
 * Description:暂时不使用
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
    BAND_ENUM_UINT16               enBand;         /* 频段,从Path NV项中获取 */
    RAT_MODE_ENUM_UINT16           enRatMode;      /* 模式,从Path NV项中获取 */
    UINT32                         uwFreqInfo;     /* 频率,从Path NV项中获取,单位100KHZ */
    UINT16                         uhwDlPathIndex; /* DL资源Path Index，从工具下发 */
    BANDWIDTH_ENUM_UINT16          enBandWidth;    /* 校准带宽, 各模固定1.4M,物理层代码固定 */
    UINT8                          ucAntCfgMap;    /* 天线配置MAP,从Path NV项中获取 */
    UINT8                          aucRsv[3];
    BBIC_CAL_RX_AGC_CODE_LIST_STRU astRxAgcCfg[RFHAL_CAL_MAX_ANT_NUM]; /* RX DC校准列表,从NV项中获取 */
} BBIC_CAL_RX_DCOC_CONFIG_STRU;

/*
 * Description: Rx DCOC Cal Req
 */
typedef struct {
    UINT16                       uhwPathNum; /* RX DC校准最大PATH个数 */
    UINT16                       uhwRsv;
    /* < 该数组按照最大来定义，实际使用时根据uhwPathNum来动态使用 */
    BBIC_CAL_RX_DCOC_CONFIG_STRU astCalList[BBIC_CAL_RX_DCOC_MAX_PATH_NUM];
} BBIC_CAL_RX_DCOC_START_REQ_PARA_STRU;

/*
 * desc : dcxo下行校准增加单path的dcoc校准过程，后续拆分工位方案上线后删除
 */
typedef struct {
    BAND_ENUM_UINT16                    band;        /* 频段,从Path NV项中获取 */
    RAT_MODE_ENUM_UINT16                ratMode;     /* 模式,从Path NV项中获取 */
    UINT16                              dlPathIndex; /* DL资源Path Index，从工具下发 */
    UINT8                               antCfgMap;   /* 天线配置MAP,从Path NV项中获取 */
    UINT8                               rsv;
    RX_AGC_GAIN_INDEX_STRU              rxAgcCfg[RFHAL_CAL_MAX_ANT_NUM]; /* RX DC校准列表,从NV项中获取 */
} BBIC_CAL_DcxoSelfCalDcocReqPara;

/*
 * Description: 每根天线的RX DCOC上报结果
 */
typedef struct {
    /* 每档VGA的校准结果，最大支持16档 */
    BBIC_CAL_DC_RESULT_STRU astRxDcInd[RFHAL_CAL_MIMO_RSLT_MAX_NUM][RFHAL_CAL_RX_MAX_VGA_NUM];
} BBIC_CAL_RX_DCOC_ANT_STRU;

/*
 * Description: 每个PATH的RX DCOC上报结果
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    BBIC_CAL_RX_DCOC_ANT_STRU      astRxDcInd[RFHAL_CAL_MAX_ANT_NUM]; /* 2R的RX DC结果，0表示主集结果,1表示分集结果 */
} BBIC_CAL_RX_DCOC_PATH_STRU;

/*
 * Description: 多个PATH的RX DC上报结果,目前共支持192个PATH
 */
typedef struct {
    UINT32                     uwErrorCode;
    UINT16                     uhwPathNum; /* Path最大个数 */
    UINT16                     uhwRsv;
    /* < 该数组按照最大来定义，实际使用时根据uhwPathNum来动态使用 */
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
    UINT16                         auhwRfSettingIndex[GE_RF_GAIN_NUM]; /* 没有使用的RF Gain直接填0 */
} GE_RF_SETTING_CAL_RESULT_STRU;

/*
 * Description: rf setting req
 */
typedef struct {
    UINT32                        uwErrorCode;
    UINT16                        uhwPathNum; /* < valid path num */
    UINT16                        uhwRsv;
     /* < 该数组按照最大来定义，实际使用时根据uhwPathNum来动态使用 */
    GE_RF_SETTING_CAL_RESULT_STRU astData[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_GE_RF_SETTING_IND_PARA_STRU;

/*
 * Description: 单个path的配置信息
 */
typedef struct {
    RAT_MODE_ENUM_UINT16 enRatMode;      /* 模式 */
    UINT16               uhwUlPathIndex; /* DL资源Path Index，从工具下发 */
    UINT32               uwRsv[3];       /* 保留位,扩展用 */
} BBIC_CAL_RAT_SELFCAL_PATH_CONFIG_STRU;

/*
 * Description: 区分path的自校准项校准请求原语
 */
typedef struct {
    UINT16 uhwPathNum; /* < 有效PATH个数 */
    UINT16 uhwRsv;
    /*
     * 支持变长，数组个数按照实际填写，BBIC_CAL_TX_MAX_PATH_NUM只是举例，需要保证下发和上报的消息不超过16KB
     */
    BBIC_CAL_RAT_SELFCAL_PATH_CONFIG_STRU astPath[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_TX_FILTER_START_REQ_PARA_STRU;

/*
 * 结构说明：TX FILTER RC2code值
 */
typedef struct {
    INT16 ashwDacPhase[4]; /* 4个DAC相位 */
} BBIC_CAL_TX_FILTER_SINGLE_MODE_STRU;

/*
 * Description: TX filter校准结果
 */
typedef struct {
    BBIC_CAL_TX_FILTER_SINGLE_MODE_STRU astLpfMode[7]; /* 7个LPF MODE */
} BBIC_CAL_TX_FILTER_RESLUT_STRU;

/*
 * Description: 每个PATH的校准结果
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT32                         uwPathDataLen; /* 当前path的结构体长度,不包括stPathInfo和uwPathDataLen */
    BBIC_CAL_TX_FILTER_RESLUT_STRU stPathRsltPara;
} BBIC_CAL_TX_FILTER_IND_PATH_STRU;

/*
 * Description: 多个PATH的TX FILTER上报结果,目前共支持80个PATH
 */
typedef struct {
    UINT32                           uwErrorCode;
    UINT16                           uhwPathNum; /* Path最大个数 */
    UINT16                           uhwRsv;
    BBIC_CAL_TX_FILTER_IND_PATH_STRU astPathPara[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_TX_FILTER_RESULT_IND_PARA_STRU;

/*
 * Description: 单个path的配置信息
 */
typedef struct {
    RAT_MODE_ENUM_UINT16 enRatMode;      /* 模式 */
    UINT16               uhwUlPathIndex; /* 资源Path Index，从工具下发 */
    UINT16               uhwBandWidth;   /* 带宽 */
    UINT16               uhwRsv;         /* 保留扩展用 */
    UINT32               uwMrxDelayInit; /* mrx delay初始值 */
    INT32                swMrxDelayStep; /* mrx delay提取遍历step */
} BBIC_CAL_SELFCAL_PATH_CONFIG_STRU;

/*
 * Description: 区分path的自校准项校准请求原语
 */
typedef struct {
    UINT16 uhwPathNum; /* < 有效PATH个数 */
    UINT16 uhwRsv;
    /*
     * 支持变长，数组个数按照实际填写，BBIC_CAL_TX_MAX_PATH_NUM只是举例，需要保证下发和上报的消息不超过16KB
     */
    BBIC_CAL_SELFCAL_PATH_CONFIG_STRU astPath[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_MRX_DELAY_REQ_PARA_STRU;

/*
 * Description: 每个PATH的MrxDelay校准结果
 */
typedef struct {
    UINT16 uhwValidCnt;
    UINT16 uhwRsv;
    UINT16 auhwMrxDelay[RFHAL_CAL_TX_MRX_SAMPLE_RATE_MAX_NUM];
} BBIC_CAL_MRX_DELAY_VALUE_STRU;

/*
 * Description: 每个PATH的校准结果
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
    UINT16                          uhwTriggerMode;   /* < 触发方式, 0 - 表示RX触发, 1 - 表示TX触发 */
    INT16                           hwRxTriggerLevel; /* < RX触发方式时下行信号的强度，单位为1/8dBm */
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
     * cfg,n=usPatternConfigNum,和装备约定从bit0开始取值,
     *  并且是连续取值 BBIC_CAL_RX_AGC_STEP_CONFIG_STRU   stAgcGainCode[n]; AGC Gain
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
    SIGNAL_TYPE_ENUM_UINT16    enSignalType;    /* < Apt需求,调制波需求 */
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
     * ),和装备约定从bit0开始取值,并且是连续取值 BBIC_CAL_TX_STEP_STRU        astStepData[n];        Total Step Data Cfg
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
    BBIC_CAL_PA_VCC_CAL_FLAG_ENUM_UINT16 uhwCalFlag : 1;     /* 校准或提取模式, 0: 提取，1:校准 */
    UINT16                               uhwMrxCorrType : 1; /* 0:线性 ,1:相关值 */
    BBIC_CAL_PA_VCC_LOG_FLAG_ENUM_UINT16 uhwLogFlag : 2;     /* 维测开关, 0: 关闭维测，1: 上报原始样本点数据 MrxCorr，
                                                       2: 上报拟合点数据 Samples，3: 前两者均上报 */
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
    BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16 enSignalType;      /* < 只能使用4音或调制模式 */
    UINT32                           uwFreqInfo;        /* Center Freq of each Band, the unit is kHz */
    MODU_TYPE_ENUM_UINT16            enModType;         /* valid under modulation signal */
    WAVEFORM_TYPE_ENUM_UINT16        enWaveType;        /* valid under nr-sub6g modulation signal, */
    UINT32                           uwBandWidthBitMap; /* 每个bit代表BANDWIDTH_ENUM对应带宽生效 */
} BBIC_CAL_ET_DELAY_PATH_CONFIG_STRU;

typedef struct {
    UINT16 uhwCalFlag; /* 0: K值，1:温频补，2:校准 */
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
    UINT16                           uhwMimoType;   /* < Mimo配置,目前仅在MT使用: 2 - 2T/2R, 4 - 4R, 8 - 8R */
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
    BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16 enSignalType;     /* < 只能使用4音或调制模式 */
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
 * Dsecription: 2G TX 校准REQ
 */
typedef struct {
    UINT16                  uhwPathNum;                                    /* < valid path num */
    SIGNAL_TYPE_ENUM_UINT16 enSingleType;                                  /* < 单音 or 调制  给APC表校准使用 */
     /* < 该数组按照最大来定义，实际使用时根据uhwPathNum来动态使用 */
    BBIC_CAL_GETX_PATH_INFO_STRU astPathCalInfo[BBIC_CAL_TX_MAX_PATH_NUM];
} BBIC_CAL_GE_TX_REQ_PARA_STRU;

/*
 * Description: bbic cal result path infomation.
 */
typedef struct {
    UINT32                     uwPathErrorCode;
    UINT32                     uwRsv1; /* < 预留给物理层使用，记录过程告警信息 */
    BBIC_CAL_RF_PATH_INFO_STRU stPathInfo;
    UINT16                     uhwRsv2; /* 预留给Nv使用 */
    UINT16                     uhwRsv3; /* 预留给Nv使用 */
} BBIC_CAL_GETX_RESULT_PATH_INFO_STRU;

typedef struct {
    UINT32 auwRfSettingCode[GE_RF_GAIN_NUM]; /* 没有使用的RF Gain直接填0 */
} GETX_RFSETTING_CAL_RESULT_STRU;

typedef struct {
    INT16  hwPower; /* 单位0.1dB，功率可能为负 */
    UINT16 uhwDac;
} BBIC_CAL_GETX_APC_POINT_STRU;

/*
 * Description: 功率电压表
 */
typedef struct {
    UINT16                       auhwValidNum[GE_RF_GAIN_NUM]; /* 两张表的有效个数，当只有一张表时，第二张表数量为0 */
    /* 每个点的power和dac值，饱和时只有一张表从0开始，线性有两张表时，第一张表从0开始，第二张表从32开始 */
    BBIC_CAL_GETX_APC_POINT_STRU astApcPoint[GE_TX_PWR_CONT_NUM];
} BBIC_CAL_GETX_POWER_DAC_TABLE_STRU;

typedef struct {
    BBIC_CAL_GETX_POWER_DAC_TABLE_STRU stGeTxApcTbl;                   /* 若只有一张表第二张表填0 */
    INT16                              ashwPaGainRslt[GE_PA_GAIN_NUM]; /* 四挡Pagain校准结果 */
    INT16 ashwPaPrechgVolt[BBIC_CAL_G_TX_PCL_NUM]; /* 校准后的预充电压 GMSK 2档 EDGE 32档 取最大档位 */
} GETX_APC_CAL_RESULT_STRU;

typedef struct {
    SINT8 ascFreqCompValue[BBIC_CAL_FREQ_MAX_NUM]; /* <每档32个频点 */
} BBIC_CAL_TX_FREQ_COMP_RESULT_PARA;

typedef struct {
    BBIC_CAL_TX_FREQ_COMP_RESULT_PARA astGainFreqResult[GE_PA_GAIN_NUM]; /* <四档  每档32个点 */
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
     /* < 该数组按照最大来定义，实际使用时根据uhwPathNum来动态使用 */
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
     * 128阶 DPD LUT表结果
     */
    UINT16 auhwReferDac; /* * 参考Dac */
    INT16  shwDcValue;   /* * DC结果 */
} BBIC_CAL_GETX_DPD_PATH_RESULT_PARA;

typedef struct {
    UINT16                             uhwDpdLutTblNum;
    UINT16                             uhwRsv;
    BBIC_CAL_GETX_DPD_PATH_RESULT_PARA astDpdRsltPara[GE_PA_GAIN_NUM];
    UINT16                             auhwStepV[GE_PA_GAIN_NUM]; /* * GE_PA_GAIN_NUM 4 预留接口，对应四档RFPA档位 */
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
    UINT32                              uwErrorCode; /* < 所有Path的ErrorCode */
    UINT16                              uhwPathNum;  /* < valid path num */
    UINT16                              uhwRsv;
     /* < 每个Path的校准结果 根据实际下发的Path数量动态使用 */
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
    UINT16 uhwValidTxGainNum; /* 有效档位数量 */
    UINT16 uhwTxGainEnMask;   /* 档位是否有效: bit0 bit1 bit2 bit3 档位 0 1 2 3 是否有效 */
    BBIC_CAL_GETX_DPD_ORIG_RSLT_PARA_STRU astLutTblOrigRslt[4]; /* 每个档位(LUT表)所对应的IQ原始结果 */
} BBIC_CAL_GETX_DPD_ORIG_PATH_RSLT_STRU;

typedef struct {
    UINT16 uhwPathLoop; /* < valid path num */
    UINT16 uhwPathIndex;
    BBIC_CAL_GETX_DPD_ORIG_PATH_RSLT_STRU stOrigPathRslt; /* < 每个Path的校准结果 根据实际下发的Path数量动态使用 */
} BBIC_CAL_GETX_EDGE_DPD_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_GETX_EDGE_DPD_MNTN_INFO_STRU stPara; /* EDGE DPD校准的维测信息 */
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
     * 当前path的校准温度
     */
    INT32 lCalTemp;
    /*
     * Apt/Et Lut表个数，与NV结构对齐
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
 * Description: PA gain delta的单path校准结果
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;

    UINT16 uhwEtMap;    /* 从bit0开始按照bit位表示2张表 */
    UINT16 uhwDpdMap;   /* 从bit0开始按照bit位表示4张表 */
    UINT16 uhwEtDpdMap; /* 从bit0开始按照bit位表示4张表 */
    UINT16 uhwRsv;

    INT16 shwEtPaGainDelta[2];    /* 按bit位的位置存放结果 */
    INT16 shwDpdPaGainDelta[BBIC_DPD_NUM];   /* 按bit位的位置存放结果 */
    INT16 shwEtDpdPaGainDelta[BBIC_DPD_NUM]; /* 按bit位的位置存放结果 */

} BBIC_CAL_PA_GAIN_DELTA_PATH_RESULT_STRU;

/*
 * Description: PA gain delta的多path结果上报，用于log打印
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
 *                  按Path提取或者校准的PA增益返回mrx原始数据
 *                  区分Apt及ET两种模式
 *                  样本对上报由PHY在做矩阵拟合的时候直接上报
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    INT16                          hwCalVcc; /* AptCode or Vcc Mv */

    UINT16                    uhwRsv;      /* 预留 */
    TX_PA_VCC_CAL_CONFIG_STRU stPaModeCfg; /* pa mode info */

    INT32 swMrxCoorRe[BBIC_ET_LUT_CW_STEP_NUM]; /* < vcc mrx coor I value */
    INT32 swMrxCoorIm[BBIC_ET_LUT_CW_STEP_NUM]; /* < vcc mrx coor Q value */
} BBIC_CAL_PA_VCC_MRXCOOR_IND_PARA_STRU;

/*
 * Description: Pa Vcc提取或者 校准数据进行拟合的样本对数据
 *              校准过程中按path相应PA增益档位校准结果返回样本对信息,校准结束后统一上报LUT结果
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    TX_PA_VCC_CAL_CONFIG_STRU      stPaModeCfg; /* PA增益信息，包括apt/et mode */

    UINT32 uwCalVccNum;             /* 校准电压数量 */
    UINT32 uwCrossPointNum;         /* 所有交点的个数 */
    UINT32 uwVccWrongFlag;          /* 最大GAIN 小于ISOGAIN 从bit 0 开始按bit置0表示该位值没有交点 */
    UINT32 uwISOWrongFlag;          /* 最小GAIN 大于ISOGAIN 从bit 0 开始按bit置0表示该位值没有交点 */
    UINT16 auhwVccList[32];         /* 校准的vcc值 */
    UINT16 auhwIsoEclVccTable[32];  /* 交点的Vcc值 */
    UINT32 auwIsoPoutTableLine[32]; /* ISO交点的Pout的线性值 */
    UINT32 auwEclPoutTableLine[32]; /* ECL交点的Pout的线性值 */
    UINT32 auwIsoPinTableLine[32];  /* ISO交点的Pin的线性值 */
    UINT32 auwEclPinTableLine[32];  /* ECL交点的Pin的线性值 */
    UINT32 auwIsoIndex[32];         /* ISO交点的坐标 */
    UINT32 auwEclIndex[32];         /* ECL交点的坐标 */
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
    UINT16                 dpdMap;  /* 从bit0开始按照bit位表示4张表 */
    UINT16                 etDpdMap;/* 从bit0开始按照bit位表示4张表 */
    BBA_CAL_DPD_LUT_STRU   astDpdLut[BBIC_DPD_NUM];   /* 按bit位的位置存放结果 */
    BBA_CAL_ETDPD_LUT_STRU astEtDpdLut[BBIC_DPD_NUM]; /* 按bit位的位置存放结果 */
} BBA_CAL_DPD_FREQ_IND_STRU;

/*
 * Description: DPD CAL one path result struct
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    INT32                          swCalTemp; /* 当前path的校准温度 */
    UINT16                         uhwRsv;
    UINT16                         uhwFreqNum;
    BBA_CAL_DPD_FREQ_IND_STRU      astDpdResult[BBIC_DPD_CAL_FEQ_NUM]; /* 有效个数根据uhwFreqNum来取 */
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
 * Description:每一个ET档位的ET Delay K值信息
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
    UINT16                         uhwEtPaGainNum;  // ET有效档位个数
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
 * Description:每一个ET档位的ET Delay校准和温频补提取的结果信息
 */
typedef struct {
    UINT16 uhwEtPaGainMode; /* 当前PA档位 */
    UINT16 uhwEtIntDelay;
    UINT16 uhwEtFracDelay;
    INT16  shwCalTemp;
} BBA_CAL_ET_DELAY_PA_MODE_INFO_STRU;

/*
 * Description:每一个带宽的ET Delay校准和温频补提取的结果信息
 */
typedef struct {
    UINT16                             uhwEtBandWidth; /* 带宽值 */
    UINT16                             uhwEtPaGainNum; /* 有效ET档位个数 */
    BBA_CAL_ET_DELAY_PA_MODE_INFO_STRU astEtDelayInfo[2];
} BBA_CAL_ET_DELAY_BANDWIDTH_INFO_STRU;
/*
 * Description: ET Delay CAL one path result struct
 */
typedef struct {
    BBIC_CAL_RESULT_PATH_INFO_STRU stPathInfo;
    UINT16                         uhwCalFlag;        /* 1:温频补；2:校准 */
    UINT16                         uhwEtBandWidthNum; /* 有效ET带宽个数 */
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
    UINT16 uhwSignalCnt;    /* < 个数，取值范围[1,2,4] */
    UINT16 uhwCwFreqEn : 1; /* < 0: RFDSP自行配置; 1:使用下面的值 */
    UINT16 uhwRsv : 15;
    INT32  aswCwFreqHz[4]; /* < 有符号数，正值表示+偏移，负值表示-偏移，单位Hz */
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
    UINT32                     rfSetttingCode; /* 2G RF setting控制字 */
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
    NR_SCS_TYPE_COMM_ENUM_UINT8 enScsType; /* < 子载波间隔 */
    UINT8                       ucRsv;
    WAVEFORM_TYPE_ENUM_UINT16   nrWaveType; /* NR模调制信号使用，波形类型，CPOFDM或者DFT S OFDM */
    UINT16                      uhwRbStart; /* < 非信令下只支持type1 - start RB */
    UINT16                      uhwRbNum;   /* < 非信令下只支持type1 - numbers of RB */
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
 * Description: RF DEBUG的公共配置参数
 */
typedef struct {
    MODEM_ID_ENUM_UINT16             modemId; /* Modem ID */
    RAT_MODE_ENUM_UINT16             ratMode; /* 模式 */
    UINT16                           rsv;
    BBIC_CAL_SYS_STATUS_ENUM_UINT8   sysStatus;      /* 业务模式或者侦听模式 */
    BBIC_CAL_DSDS_TYPE_ENUM_UINT8    dsdsType;       /* DSDS类型，DSDS2.0或者DSDS3.0 */
    UINT8                            modemStatus;    /* Modem0拉高和拉低状态,1表示Modem0拉高，0表示Modem0拉低 */
    UINT8                            txCfgPriority;  /* DSDS3.0的场景,TX配置优先级,取值范围0~15 */
    BBIC_CAL_GSM_RX_MODE_ENUM_UINT8  gsmRxMode;      /* GSM RX配置模式,只有2G RX使用 */
    BBIC_CAL_RX_AGC_MODE_ENUM_UINT8  rxAgcMode;      /* 2G FAST和SLOW模式, 只有2G RX使用 */
    BBIC_CAL_SIGNAL_TYPE_ENUM_UINT16 signalType;     /* 信号类型,支持单音、双音、四音、调制信号 */
    MODU_TYPE_ENUM_UINT16            modType;        /* 如果是调制方式，则可以选择QPSK、16QAM、64QAM、256QAM */
    TX_BB_SIGNAL_CW_STRU             stTxSignalPara; /* 如果当前信号非调制信号,则需要配置单音频率,单位Hz */
} BBIC_CAL_RF_DEBUG_TRX_COMM_PARA_STRU;

/*
 * Description: RF DEBUG每个下行PATH的配置参数
 */
typedef struct {
    UINT16 txPowerEn : 1; /* TX功率参数配置使能，如果使能，则APC配置中会重新配置TX功率相关参数，否则不配置,
                             1--TX功率配置使能, 0--TX功率配置不使能 */
    UINT16                            txAptEn : 1;     /* TX APT参数配置使能，1--Tx APT enable, 0--TX APT Disable */
    UINT16                            cwAmEn : 1;      /* 单音幅度可调整使能, 1: On, 0: Off */
    UINT16                            dpdEn : 2;       /* 0:表示DPD off; 1: 表示DPD Bypass; 2: 表示DPD On */
    UINT16                            dpdTrainEn : 1;  /* 0:表示DPD 不训练; 1: 表示DPD 启动训练 */
    UINT16                            etDelayEn : 1;   /* EtDelay配置使能, 1--Enable, 0--Disable */
    UINT16                            rfSettingEn : 1; /* RF SETTING配置使能 */
    UINT16                            uhwRsv : 8;
    BBIC_CAL_DPD_LUT_INDEX_ENUM_UINT8 enDpdGainMode;
    UINT8                             aucRsv[3];
    INT16                             dpdPower; /* DPD查表功率 */
    UINT16                            etIntDelay;
    UINT16                            etFracDelay;
    BBIC_CAL_RF_DEBUG_TX_POWER_PARA_STRU txPowerPara;
    BBIC_CAL_RF_DEBUG_MRX_PARA_STRU mRxPara;
} BBIC_CAL_RF_DEBUG_TX_PATH_PARA_STRU;

/*
 * Description: RF DEBUG每个下行PATH的配置参数
 */
typedef struct {
    UINT16 rxAgcCfgEn : 1; /* Agc配置使能，1--RX AGC配置, 0--RX AGC不配置 */
    UINT16 evmCfgEn : 1;   /* EVM配置使能，1--RX EVM配置, 0--RX EVM不配置 */
    UINT16 rssiReport : 2; /* 控制RSSI上报标志, 0--RSSI不上报,
                              1--WB RSSI上报，
                              2--NB RSSI上报
                              3--Corr RSSI上报，暂时不支持2和3的场景 */
    UINT16                      uhwRsv : 12;
    UINT16                      ucRsv1;      /* 四字节对齐 */
    BBIC_CAL_AGC_GAIN_PARA_STRU agcGainPara; /* AGC GAIN配置参数 */
} BBIC_CAL_RF_DEBUG_RX_PATH_PARA_STRU;

/*
 * Description: 每个Band下的TX配置参数，和band相关的参数;
 */
typedef struct {
    BBIC_CAL_BAND_CFG_MODE_ENUM_UINT8 bandCfgMode; /* 该Band配置激活或者关闭，如果配置激活，
                                                       则配置TXSTART或者TX APC，
                                                       是否配置Start取决于下面变量startCfgEn是否使能 */
    UINT8 startCfgEn;                              /* TX/RX是否重新Start，1--表示statr配置使能，
则需要重新Start通道，0--表示不配置使能,单载波和CA下都需要使用 */
    BAND_ENUM_UINT16 bandId;                       /* 频段ID */
    UINT8            extBand;                      /* 是否为扩展频段 */
    UINT8            ulCfgPathEn; /* 上行Path配置使能,1--表示使能，0--表示不使能,如果使能了该参数,则ulCfgPath配置有效 */
    UINT8            ucRsv[2];    /* 四字节对齐 */

    BANDWIDTH_ENUM_UINT16 bandWidth; /* 带宽 */
    RAT_MODE_ENUM_UINT16  ratMode;   /* 模式 */
    BBIC_CAL_RF_DEBUG_DEPENDED_PARA_UNION unTxRatPara;      /* 上行各模差异配置参数 */
    UINT32 txFreqKhz; /* TX配置频率,单位KHZ */
    UINT16 ulCfgPath; /* 上行配置PATH，单band和antNum等于2的情况下有效,CA下不使用,CA下不使用 */
    UINT8  antNum;    /* 天线个数,上行最大支持2T,下行最大支持8R */
    UINT8  antMap;    /* AntMap, bit0 - ant0, bit-ant1,目前只有MT使用，当前只支持单T工作 */

    BBIC_CAL_RF_DEBUG_TX_PATH_PARA_STRU txPathPara[TX_MAX_ANT_NUM]; /* 最大支持2T，每T的配置 */
} BBIC_CAL_RF_DEBUG_TX_BAND_PARA_STRU;

/*
 * Description: 每个Band下的RX配置参数，和band相关的参数;
 */
typedef struct {
    BBIC_CAL_BAND_CFG_MODE_ENUM_UINT8 bandCfgMode; /* 该Band配置激活或者关闭，如果配置激活，
                                                       则配置TXSTART或者TX APC，
                                                       是否配置Start取决于下面变量startCfgEn是否使能 */
    UINT8 startCfgEn;                              /* TX/RX是否重新Start，1--表示statr配置使能，
则需要重新Start通道，0--表示不配置使能,单载波和CA下都需要使用 */
    BAND_ENUM_UINT16 bandId;                       /* 频段ID */
    UINT8            extBand;                      /* 是否为扩展频段 */
    UINT8            dlCfgPathEn; /* 下行Path配置使能,1--表示使能，0--表示不使能,如果使能了该参数,则ulCfgPath配置有效 */
    UINT8            ucRsv[2];    /* 四字节对齐 */
    BANDWIDTH_ENUM_UINT16 bandWidth; /* 带宽 */
    RAT_MODE_ENUM_UINT16  ratMode;   /* 模式 */
    UINT32                rxFreqKhz; /* RX配置频率,单位KHZ */
    UINT16                dlCfgPath; /* 下行配置PATH，单band和antNum等于2的情况下有效,CA下不使用 */
    UINT8                 antNum;    /* 天线个数,上行最大支持2T,下行最大支持8R，如果是2R1T的情况，dlcfgPath生效 */
    UINT8                 antMap;    /* HiRF下只支持:BIT0--ANT0,BIT1--ANT1，MT下支持BIT0~7,但是必须按2R使用 */
    BBIC_CAL_RF_DEBUG_RX_PATH_PARA_STRU rxPathPara[RX_MAX_ANT_NUM]; /* 最大支持8R，每R的配置 */
} BBIC_CAL_RF_DEBUG_RX_BAND_PARA_STRU;

/*
 * Description: TX Slow debug config para, except GSM
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_TRX_COMM_PARA_STRU bandCommPara;                                /* TRX公共配置参数 */
    UINT16                               ccIndex; /* 当前配置CC INDEX */
    UINT16                               usRsv;
    BBIC_CAL_RF_DEBUG_TX_BAND_PARA_STRU  txBandCfgPara; /* 每个TX Band配置参数，最大支持2CC */
} BBIC_CAL_RF_DEBUG_TX_PARA_STRU;

/*
 * Description: RX REQ PARA
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_TRX_COMM_PARA_STRU bandCommPara;                                /* TRX公共配置参数 */
    UINT16                               ccIndex; /* 当前配置CC INDEX */
    UINT16                               usRsv;
    BBIC_CAL_RF_DEBUG_RX_BAND_PARA_STRU  rxBandCfgPara; /* 每个RX Band配置参数,最大支持5CC */
} BBIC_CAL_RF_DEBUG_RX_PARA_STRU;

/*
 * Description: RF DEBUG TRX配置参数,可以单独配置TX(除2G以外)或者RX，
 *              也可以同时配置TX或者RX，支持单载波和CA的配置;
 */
typedef struct {
    BBIC_CAL_RF_DEBUG_TRX_COMM_PARA_STRU bandCommPara;     /* TRX公共配置参数 */
    UINT16 txBandCnt; /* TX频段个数，0表示不配置TX; 单载波配置1;
                         CA则配置2,最大支持2CC */
    UINT16 rxBandCnt; /* RX频段个数，0表示不配置RX; 单载波配置1;
                         CA则配置2~5,最大支持5CC */

    BBIC_CAL_RF_DEBUG_TX_BAND_PARA_STRU txBandCfgPara[TX_MAX_CC_NUM]; /* 每个TX Band配置参数，最大支持2CC */
    BBIC_CAL_RF_DEBUG_RX_BAND_PARA_STRU rxBandCfgPara[RX_MAX_CC_NUM]; /* 每个RX Band配置参数,最大支持5CC */
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
    UINT16                             uhwDataPattern; /* < 0：All 0；1：All 1；2：Random */
    MRX_ESTIMATE_ENUM_UINT8            enMrxEstMode;   /* < Mrx Measure Mode */
    UINT8                              ucRsv;
    UINT16                             uhwRsv;
    UINT16                             uhwSlotCnt; /* < 配置时隙个数，
                                         1~4 - 不需指定具体使用哪些时隙，DSP自动配置1~4时隙发射
                                         8 - 8时隙全开，使用第一个astSlotCfg的参数来配置 */
    G_TX_SINGLE_SLOT_PARA_STRU astSlotPara[4];     /* < 每个时隙的配置情况 */
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
    INT16  shwAntPower;    /* 天线口功率, 单位GUC: 0.1db ; L/NR: 0.125db */
    INT16  shwRsv;         /* 保留位 */
    INT32  swMrxRealValue; /* 复相关实部值 */
    INT32  swMrxImagValue; /* 复相关虚部值 */
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
    UINT32 indFlag; /* 是否为IND消息，如果是IND消息，则配置1，否则配置0 */
    UINT32 txCorrValue;
    UINT32 mrxCorrValue;
    INT16  antPower; /* 天线口功率, 单位GUC: 0.1db ; L/NR: 0.125db */
    INT16  rsv1;
    INT32  swMrxRealValue; /* 复相关实部值 */
    INT32  swMrxImagValue; /* 复相关虚部值 */
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
    UINT16 indFlag; /* IND上报标志，如果是IND，则配置1，否则配置0 */
    UINT16 validAntNum;
    INT16  ashwRssi[RX_MAX_ANT_NUM];
} BBIC_CAL_RF_DEBUG_RX_CNF_PARA_STRU;

/*
 * Description: 每个Band下的RSSI上报，最大支持8R
 */
typedef struct {
    UINT16 validAntNum;
    UINT16 usRsv;
    INT16  rxRssi[RX_MAX_ANT_NUM];
} BBIC_CAL_RX_RSSI_IND_BAND_STRU;

/*
 * Description: 多个CC的RSSI上报，最大支持5CC
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
    UINT32 bitMipiPortSel : 3; /* MIPI PORT选择 */
    UINT32 bitSlaveId : 4;     /* Savle Id */
    UINT32 bitRegAddr : 16;    /* 寄存器地址 */
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
 * Description:IP2 CA的配置
 */
typedef struct {
    UINT16                     uhwCaFlag; /* 是否为CA的Path，0--单载波、1--CA */
    UINT16                     uhwRsv;
    BBIC_CAL_MIPIDEV_UNIT_STRU astCaMipi[8];     /* 如果CA的校准情况，需要单独配置CA的公共MIPI指令，
                                            BBIC cal根据CA组合Copy相对应的MIPI指令 */
    BBIC_CAL_MIPIDEV_UNIT_STRU astCaMipiTrig[4]; /* MIPI Trig指令 */
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
    INT32  aswImd2Value[2]; /* < 0: 窄带结果,1: 宽带结果 */
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
    UINT32 rsv1;     /* 预留给DSP记录过程告警信息 */
    UINT16 testItem; /* 定义成自校准枚举 */
    UINT16 rsv2;     /* 待确定是否添加NV ID */
    UINT16 rsv3;     /* 待确定是否添加NV LENGTH */
    UINT16 dataLength;
    UINT8  dataBuff[4]; /* 变长，格式根据每个校准项来确定 */
    /*
     * 具体九项的结构体:
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
    UINT8                   aucData[4]; /* < 变长，数据格式参照以下格式来 */
    /* 每个单个校准项内容的格式  RficSelfCalItemInd */
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
    /* 数据起始地址，数据实际长度为uhwDataLength */
} BBIC_CAL_RESULT_DATA_STRUCT;

typedef union {
    BBIC_CAL_RESULT_SOURCE_STRUCT stCalResultSrcInfo; /* 仅在CAL_RESULT_WRITE_TYPE_CO_BAND时有效 */
    BBIC_CAL_RESULT_DATA_STRUCT   stCalResultData;    /* 仅在CAL_RESULT_WRITE_TYPE_NORMAL时有效 */
} BBIC_CAL_RESULT_DATA_UNION;

typedef struct {
    CAL_RESULT_ITEM_NAME_ENUM_UINT16  uhwItemName;
    UINT16                            uhwPathIndex;
    RAT_MODE_ENUM_UINT16              uhwRatMode;
    CAL_RESULT_WRITE_TYPE_ENUM_UINT16 uhwWriteType;
    BBIC_CAL_RESULT_DATA_UNION        stWriteData;
} BBIC_CAL_RESULT_INFO_STRUCT;

typedef struct {
    UINT16 uhwCalResultCnt; /* < 需要写入的ItemName个数 */
    UINT16 rsv;
    UINT8  aucData[4]; /* < 变长，数据格式说明如下 */
    /*
     * 结构体数组 BBIC_CAL_RESULT_INFO_STRUCT
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
 * Description: 读MIPI请求信息
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
 * Description: 写CPU REG请求信息
 */
typedef struct {
    UINT32                          uwCpuRegisterNum;
    BBIC_CAL_CPU_REGISTER_UNIT_STRU astCpuData[BBIC_CAL_MAX_REGISTER_COUNT];
} BBIC_CAL_WRITE_REG_DATA_REQ_STRU;

/*
 * Description: 读CPU REG请求信息
 */
typedef struct {
    UINT32 uwCpuRegisterNum;
    UINT32 astCpuAddress[BBIC_CAL_MAX_REGISTER_COUNT];
} BBIC_CAL_READ_REG_DATA_REQ_STRU;

/*
 * Name        : BBIC_CAL_WRITE_MIPI_DATA_REQ_STRU
 * Description : 读MIPI结果
 */
typedef BBIC_CAL_WRITE_MIPI_DATA_REQ_STRU BBIC_CAL_READ_MIPI_DATA_IND_STRU;

/*
 * Name        : BBIC_CAL_WRITE_REG_DATA_REQ_STRU
 * Description : 读CPU REG结果
 */
typedef BBIC_CAL_WRITE_REG_DATA_REQ_STRU BBIC_CAL_READ_REG_DATA_IND_STRU;

#define BBIC_CAL_MNTN_INFO

typedef struct {
    UINT32 uwMrxResult;     /* MRX上报值 */
    UINT16 uhwMrxGainIndex; /* 每个点校准时的MRX档位 */
    UINT16 uhwRsv;
    INT16  hwPower; /* 单位0.1dB，功率可能为负 */
    UINT16 uhwDac;  /* Dac值 */
} BBIC_CAL_GETX_APC_POINT_INFO_STRU;

typedef struct {
    UINT32 uwMrxResult;     /* MRX上报值 */
    UINT16 uhwMrxGainIndex; /* 每个点校准时的MRX档位 */
    UINT16 uhwFreqInfo;     /* 每个点校准时的频点 */
    INT16  hwPower;         /* 单位0.1dB，功率可能为负 */
    UINT16 uhwDac;          /* Dac值 */
} BBIC_CAL_GETX_FREQCOMP_POINT_INFO_STRU;

typedef struct {
    UINT32                            uwErrorCode;                   /* APC表校准每个Path的校准结果 */
    UINT16                            uhwPathLoop;                   /* 当前Path索引 */
    UINT16                            uhwPathIndex;                  /* 当前Path的NV资源索引 */
    UINT16                            uhwModuType;                   /* 当前Path的ModuType */
    UINT16                            uhwLinerInfo;                  /* 当前Path的线性非线性信息 */
    UINT16                            uhwFreqInfo;                   /* 当前Path的中心频点 */
    UINT8                             ucTxGainIndex[GE_RF_GAIN_NUM]; /* 当前Path在APC校准时所对应的RF PA档位组合索引 */
    UINT32                            auwStepNum[GE_RF_GAIN_NUM];    /* 每张APC原始表的STEP数量 */
     /* 每个STEP的数据 */
    BBIC_CAL_GETX_APC_POINT_INFO_STRU astStepPara[GE_RF_GAIN_NUM * BBIC_CAL_GETX_APC_TBL_POINT_MAX_NUM];
} BBIC_CAL_GETX_APC_TBL_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_GETX_APC_TBL_MNTN_INFO_STRU stPara; /* APC表校准的具体维测信息 */
} BBIC_CAL_GETX_APC_TBL_MNTN_MSG_STRU;

typedef struct {
    INT16  shwPower;
    UINT16 uhwDGain;
    INT32  swDcComp;
} BBA_CAL_GETX_DCOFFSET_STEP_RSLT_INFO;

typedef struct {
    UINT32 uwErrorCode;                /* 当前Path的校准结果 */
    UINT16 uhwPathLoop;                /* 当前Path索引 */
    UINT16 uhwPathIndex;               /* 当前Path的NV资源索引 */
    UINT16 uhwModuType;                /* 当前Path的ModuType */
    UINT16 uhwLinerInfo;               /* 当前Path的线性非线性信息 */
    UINT16 uhwFreqInfo;                /* 当前Path的中心频点 */
    UINT16 auwStepNum[GE_RF_GAIN_NUM]; /* STEP数量 */
    BBA_CAL_GETX_DCOFFSET_STEP_RSLT_INFO astPreChargeRsltInfo[GE_RF_GAIN_NUM][64];
} BBIC_CAL_GETX_PRECHARGE_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_GETX_PRECHARGE_MNTN_INFO_STRU stPara; /* 预充电压校准的具体维测信息 */
} BBIC_CAL_GETX_PRECHARGE_MNTN_MSG_STRU;

typedef struct {
    UINT32                            uwErrorCode;  /* 当前Path的校准结果 */
    UINT16                            uhwPathIndex; /* 当前Path的NV资源索引 */
    UINT16                            uhwModuType;  /* 当前Path的ModuType */
    UINT16                            uhwLinerInfo; /* 当前Path的线性非线性信息 */
    UINT16                            uhwFreqInfo;  /* 当前Path的中心频点 */
    UINT16                            uhwTxGainNum; /* 当前Path RF PA档位组合数量 */
    UINT16                            uhwRsv;
    BBIC_CAL_GETX_APC_POINT_INFO_STRU astStepPara[GE_PA_GAIN_NUM]; /* 当前Path每个档位的原始数据 */
} BBIC_CAL_GETX_PAGAIN_PATH_MNTN_INFO;

typedef struct {
    UINT32                              uwErrorCode; /* 校准结果 */
    UINT16                              uhwPathNum;  /* Path数量 */
    UINT16                              uhwRsv;
    BBIC_CAL_GETX_PAGAIN_PATH_MNTN_INFO astPaGainPathInfo[BBIC_CAL_GETX_PATH_NUM]; /* 每个Path的校准原始结果和相关信息 */
} BBIC_CAL_GETX_PAGAIN_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_GETX_PAGAIN_MNTN_INFO_STRU stPara; /* PAGAIN校准的具体维测信息 */
} BBIC_CAL_GETX_PAGAIN_MNTN_MSG_STRU;

typedef struct {
    UINT32 uwErrorCode;  /* 当前Path的校准结果 */
    UINT16 uhwPathIndex; /* 当前Path的NV资源索引 */
    UINT16 uhwModuType;  /* 当前Path的ModuType */
    UINT16 uhwLinerInfo; /* 当前Path的线性非线性信息 */
    UINT16 uhwRsv;
    UINT16 uhwTxGainNum; /* 当前Path RF PA档位组合数量 */
    UINT16 uhwFreqNum;   /* 当前Path 频点数量组合数量 */
    /* 当前Path每个频点每个档位的原始数据 */
    BBIC_CAL_GETX_FREQCOMP_POINT_INFO_STRU astStepPara[GE_PA_GAIN_NUM][BBIC_CAL_FREQ_MAX_NUM];
} BBIC_CAL_GETX_FREQCOMP_PATH_MNTN_INFO;

typedef struct {
    UINT32 uwErrorCode; /* 校准结果 */
    UINT16 uhwPathNum;  /* Path数量 */
    UINT16 uhwRsv;
	 /* 每个Path的校准原始结果和相关信息 */
    BBIC_CAL_GETX_FREQCOMP_PATH_MNTN_INFO astFreqCompPathInfo[BBIC_CAL_GETX_PATH_NUM];
} BBIC_CAL_GETX_FREQCOMP_MNTN_INFO_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_GETX_FREQCOMP_MNTN_INFO_STRU stPara; /* FREQCOMP校准的具体维测信息 */
} BBIC_CAL_GETX_FREQCOMP_MNTN_MSG_STRU;

/*
 * Description: 每次交互的维测信息
 */
typedef struct {
    UINT32          reqTimeMc;
    UINT32          timeUs;
    TrxOptionUint16 opType;
    UINT16          stepIndex;
} BBA_CAL_TrxMntnOpInfo;

/*
 * Description: 每个PATH的维测信息
 */
typedef struct {
    UINT16                ratMode;     /* 制式       */
    UINT16                pathIndex;   /* PATH索引  */
    UINT16                opNum;       /* 频点数量 */
    UINT16                temperature; /* 温度    */
    BBA_CAL_TrxMntnOpInfo opInfo[BBA_CAL_TRX_MNTN_MAX_NUM];
} BBA_CAL_TrxMntnInfo;

/*
 * Description: TRX维测消息
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
    BBIC_CAL_START_MODE_ENUM_UINT16   enStartMode; /* < 配置/激活 */
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
 * Description: HF RX AGC配置联合体
 */
typedef union {
    HF_RX_AGC_GAIN_INDEX_STRU     stAgcGainIndex;    /* AGC配置为AGC GAIN Index模式下生效 */
    HF_RX_AGC_GAIN_SUB_INDEX_STRU stAgcGainSubIndex; /* AGC配置为AGC GAIN SUB Index模式下生效 */
    HF_RX_AGC_GAIN_CODE_STRU      stAgcGainCode;     /* AGC配置为AGC GAIN Code模式下生效 */
} BBIC_CAL_HF_RX_AGC_GAIN_CONFIG_UNION;

/*
 * 基础功率校准只需配置BaseDieId BeamIndex,校准Die忽略
 * Description: HF M2M配置结构
 */
typedef struct {
    UINT32                          ulBaseDieId; /* 基准Die的Id */
    UINT32                          ulCalDieId;  /* 校准Die的Id */
    UINT8                           ucRsv;
    UINT8                           ucBeamIndex;
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 enAntType;                              /* 固定BBIC_CAL_HF_ANT_TYPE_BROAD_SIDE */
    UINT8                           ucAntUnitCtrl;                          /* 0-全开，1-Map;M2M校准为:1； */
    UINT8                           aucAntUnitMap[BBIC_HF_TRX_MAX_DIE_NUM]; /* 该参数供HIRF使用 */
} BBIC_CAL_M2M_CFG_STRU;

/*
 * hirf每个天线的beam cfg，当前antUintCtrl全开
 */
typedef struct {
    UINT8                           beamIndex;
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 antType;                             /* 天线类型 */
    UINT8                           antUnitCtrl;                         /* 0-全开，1-Map;M2M校准为:1； */
    UINT8                           rsv;
    UINT8                           antUnitMap[BBIC_HF_TRX_MAX_DIE_NUM]; /* 该参数供HIRF使用 */
} BBIC_CAL_RfdebugM2mCfg;

/*
 * Description: HF RX AGC STEP配置结构
 */
typedef struct {
    BBIC_CAL_HF_RX_AGC_GAIN_CONFIG_UNION unAgcGainCfg; /* AGC配置模式 */
    BBIC_CAL_M2M_CFG_STRU                stM2MCfg;     /* M2M校准配置 */
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
    UINT8                           ucChsState;    /* < 1-- 通道交叉, 0--通道不交叉 */
    UINT8                           ucBandNum;     /* < 1 or 2 */
    BBIC_CAL_RF_DEBUG_HF_RX_BAND_INFO_STRU astBandInfo[BBIC_HFCAL_HIRF_MAX_BAND_NUM];
} BBIC_CAL_RF_DEBUG_HF_RX_REQ_PARA_STRU;

/*
 * Description: HF RX Rssi
 */
typedef struct {
    INT16  hwAnaRssi;
    UINT16 uwWbRssiValidCnt;
    INT16  ahwWbRssi[BBIC_HFCAL_NCP_SYMBOL_NUM]; /* < 按照uhwBeamSwitchMap对应的bit位存放 */
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
    UINT32 uwIfApcGainCode; /* < Hi6370配Code */
    UINT32 uwHfApcIndex;    /* < Hi6P01配Index */
    INT32  dbbGain0;
    INT32  dbbGain1; /* *< 校准时无效 */
} HF_TX_REG_CTRL_STRU;

typedef struct {
    INT16  ifTxPower; /* 中频增益 */
    INT16  rsv;
    UINT32 hfApcGainCode; /* 高频控制字 */
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
    UINT8                           lockTrimEn;  /* 锁定状态,1:锁定使用trimIndex，0:由rfdsp配置 */
    UINT8                           trimIndex;   /* 实际使用的trimidx:[0,15] */
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
    UINT8                           ucChsState;  /* < 1-- 通道交叉, 0--通道不交叉 */
    UINT8                           ucBandNum;   /* < 1 or 2 */
    BBIC_CAL_RF_DEBUG_HF_TX_BAND_INFO_STRU astBandInfo[BBIC_HFCAL_HIRF_MAX_BAND_NUM];
} BBIC_CAL_RF_DEBUG_HF_TX_REQ_PARA_STRU;

/*
 * Description: HF Hi6P01 TEMP REQ
 */
typedef struct {
    BAND_ENUM_UINT16 enBand;                               /* < Band No */
    UINT8            hffeStatus;                           /* 0-只有Hi6370的温度，1/2-Hi6370+6P01的温度 */
    UINT8            ucChsState;                           /* < 1-- 通道交叉, 0--通道不交叉 */
    UINT8            ucChanNum;                            /* < 1R/2R: 2, 4R: 4 */
    UINT8            ucChanMap;                            /* < 1R: 0x1/0x2, 2R: 0x3, 4R: 0xF */
    UINT8            aucMasState[RFHAL_HFCAL_MAX_MAS_NUM]; /* *< 0: AIP 1/3, 1: AIP 2/4,只在hffeStatus非0时有效 */
     /* *< 天线类型boardside/endfire，只在hffeStatus非0时有效 */
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
    UINT8                           ucChsState; /* < 1-- 通道交叉, 0--通道不交叉 */
    UINT8                           ucChanNum;  /* < 1R/2R: 2 */
    UINT8                           ucChanMap;  /* < 1R: 0x1/0x2, 2R: 0x3 */
    UINT8                           ucMasState; /* < 0: AIP 1/3, 1: AIP 2/4 */
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 enAntType;
    UINT8                           ucBeamIndex; /* < 校准采用垂直方向 */
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
    UINT8                           ucChsState; /* < 1-- 通道交叉, 0--通道不交叉 */
    UINT8                           ucChanNum;  /* < 1R/2R: 2 */
    UINT8                           ucChanMap;  /* < 1R: 0x1/0x2, 2R: 0x3 */
    UINT8                           ucMasState; /* < 0: AIP 1/3, 1: AIP 2/4 */
    BBIC_CAL_HF_ANT_TYPE_ENUM_UINT8 enAntType;
    UINT8                           ucBeamIndex; /* < 校准采用垂直方向 */
    UINT8                           lockTrimEn;  /* 锁定状态,1:锁定使用trimIndex，0:由rfdsp配置 */
    UINT8                           trimIndex;   /* 实际使用的trimidx:[0,15] */
    UINT16                          rsv;
} BBIC_CAL_HF_TRX_PATH_CONFIG_STRU;

typedef struct {
    UINT16                             uhwTriggerMode;   /* < 触发方式, 0 - 表示RX触发, 1 - 表示TX触发 */
    INT16                              hwRxTriggerLevel; /* < RX触发方式时下行信号的强度，单位0.1dBm */
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
     * cfg,n=usPatternConfigNum,和装备约定从bit0开始取值,
     *  并且是连续取值 BBIC_CAL_HF_RX_AGC_STEP_CONFIG_STRU   astAgcStepCfg[n]; AGC Gain
     * Cfg
     */
    UINT8 aucData[4];
} BBIC_CAL_HF_RX_START_REQ_PARA_STRU;

/*
 * Description: HF RX Rssi
 */
typedef struct {
    INT16 ahwAnaRssi[2]; /* < 1R默认取[0] */
    INT16 ahwWbRssi[2];  /* < 1R默认取[0] */
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
    BBA_CAL_HFTX_CALTYPE_ENUM_UINT8 enM2mCtrl;       /* < 0-Tx校准，1-M2M基础功率校准，2-M2M相位校准 */
    SIGNAL_TYPE_ENUM_UINT16         enSignalType;    /* < 信号源类型 */
    MODU_TYPE_ENUM_UINT16           enModuType;      /* < 调制类型 */
    UINT16                          uhwPathNum;      /* < Path Config num */
    UINT16                          uhwFreqNum;      /* < Freq Config num */
    UINT16                          uhwPatternNum;   /* < Pattern Config num */
    UINT16                          uhwStepNum;      /* < Step Config num */
    /*
     * Data Segment, ausData, format:
     *  BBIC_CAL_HF_TRX_PATH_CONFIG_STRU astPathConfig[n];   Any Path cfg, n=usPathConfigNum
     *  BBIC_CAL_TX_FREQ_CONFIG_STRU astFreqConfig[n];      Any Freq cfg, n=usFreqConfigNum
     *  UINT32                       aulTxPatternConfig[n]; Total Pattern Cfg,n=ceil(usPatternConfigNum / 32
     * ),和装备约定从bit0开始取值,并且是连续取值 HF_TX_STEP_CFG_STRU          astStepData[n];        Total Step Data Cfg
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
    RAT_MODE_ENUM_UINT16  enRatMode;   /* 模式 */
    BAND_ENUM_UINT16      enBand;      /* 频段 */
    UINT32                uwFreqInfo;  /* 频率,从Path NV项中获取,单位100KHZ */
    BANDWIDTH_ENUM_UINT16 enBandWidth; /* 校准带宽 */
    UINT16                uhwRxPathNum;
    UINT16                auhwRxPathIdx[2];
} BBIC_CAL_HF_RX_DCOC_CONFIG_STRU;

/*
 * Description: Rx DCOC Cal Req
 */
typedef struct {
    UINT16                          uhwBandNum; /* RX DC校准Band个数 */
    UINT16                          uhwRsv;
     /* < 该数组按照最大来定义，实际使用时根据uhwBandNum来动态使用 */
    BBIC_CAL_HF_RX_DCOC_CONFIG_STRU astCalList[BBIC_HF_MAX_BAND_NUM];
} BBIC_CAL_HF_RX_DCOC_START_REQ_PARA_STRU;

/*
 * Description: 每个BAND的RX DCOC上报结果
 */
typedef struct {
    UINT32                  uwErrorCode;
    UINT32                  uwValidCnt; /* < 2: 2R, 4: 4R */
    BBIC_CAL_DC_RESULT_STRU astRxDcInd[BBIC_HFCAL_MAX_ANT_NUM][BBIC_HFCAL_RX_MAX_VGA_NUM];
} BBIC_CAL_HF_RX_DCOC_BAND_STRU;

/*
 * Description: 多个PATH的RX DC上报结果
 */
typedef struct {
    UINT32                        uwErrorCode;
    UINT16                        uhwBandNum; /* Band有效个数 */
    UINT16                        uhwRsv;
    /* < 该数组按照最大来定义，实际使用时根据uhwBandNum来动态使用 */
    BBIC_CAL_HF_RX_DCOC_BAND_STRU astCalInd[BBIC_HF_MAX_BAND_NUM];
} BBIC_CAL_HF_RX_DCOC_RESULT_IND_PARA_STRU;

/*
 * Description: 温度获取接口
 */
typedef struct {
    BBIC_TEMP_CHANNEL_TYPE_ENUM_UINT16 enChannelType;
    INT16                              hwChannelNum;
} BBIC_CAL_TEMP_QRY_REQ_PARA_STRU;

/*
 * Description: 温度获取上报接口
 */
typedef struct {
    UINT32                             uwErrorCode;
    BBIC_TEMP_CHANNEL_TYPE_ENUM_UINT16 enChannelType;
    INT16                              hwChannelNum;
    INT32                              wTemperature;
} BBIC_CAL_TEMP_QRY_IND_PARA_STRU;

/*
 * Description: PLL状态获取接口
 */
typedef struct {
    RAT_MODE_ENUM_UINT16  enRatMode; /* Rat模式 */
    MODU_TYPE_ENUM_UINT16 enModType; /* 调制模式 GSM使用 */
    UINT16                uhwBand;   /* Band */
    UINT16                uhwRsv;
} BBIC_CAL_PLL_QRY_REQ_PARA_STRU;

/*
 * Description: PLL状态获取上报接口
 */
typedef struct {
    UINT32 uwErrorCode;
    UINT32 uwRxPllStatus;
    UINT32 uwTxPllStatus;
} BBIC_CAL_PLL_QRY_IND_PARA_STRU;

/*
 * Description: DPDT配置接口
 */
typedef struct {
    RAT_MODE_ENUM_UINT16           enRatMode;
    BBIC_DPDT_OPERTYPE_ENUM_UINT16 enOperType; /* 配置DPDT状态还是获取DPDT状态, 0--表示配置DPDT状态,1--获取DPDT状态 */
    UINT32                         uwValue;    /* 目前只用了低8bit，低4bit表示TAS/MAS状态,高4bit表示HALL状态,
其中低4BIT含义如下:
0: TAS-直通  MAS-直通
1: TAS-交叉  MAS-直通
2: TAS-直通  MAS-交叉
3: TAS-交叉  MAS-交叉 */
    UINT16 uhwModemWorkType;                   /* 业务还是侦听,0--表示业务，1--侦听 */
    UINT16 uhwRsv;
} BBIC_CAL_DPDT_REQ_PARA_STRU;

/*
 * Description: DPDT配置上报接口
 */
typedef struct {
    UINT32                         uwErrorCode;
    BBIC_DPDT_OPERTYPE_ENUM_UINT16 unOperType;
    UINT16                         uhwRsv;
    UINT32                         uwValue;
} BBIC_CAL_DPDT_IND_PARA_STRU;

/*
 * Description: TRX TAS配置的具体参数
 */
typedef struct {
    UINT16 ratMode;
    UINT16 band;
    UINT32 trxTasValue;
} BBIC_CAL_SetTrxTasReqParaStru;

/*
 * Description: TRX TAS配置结果上报接口
 */
typedef struct {
    UINT32 errorCode;
} BBIC_CAL_SetTrxTasCnfParaStru;

/*
 * Description: PLL状态获取结果上报消息结构体
 */
typedef struct {
    BBIC_CAL_DCXO_SET_ENUM_UINT16 enSetType;
    VOS_UINT16                    usBand;
    UINT32                        txArfcn; /* 上行频点号 */
} BBIC_CAL_DCXO_REQ_PARA_STRU;

/*
 * desc: dcxo下行校准消息参数
 */
typedef struct {
    RAT_MODE_ENUM_UINT16                    ratMode;               /* Rat Mode */
    BAND_ENUM_UINT16                        bandNo;                /* Band No. */
    UINT32                                  rxFreqInfo;            /* Rx频点,单位KHZ */

    UINT16                                  txPathIndex;           /* Tx Path Index */
    UINT16                                  dlPathIndex;           /* 下行Path Index */
    UINT16                                  rxAntMap;              /* 下行天线配置map,Rx采数按该map选取配置物理天线 */
    INT16                                   rxSigIor;              /* 仪表配置的天线口功率,所有制式按1/8单位下发 */
    TX_POWER_CFG_UNION                      pwrCfg;                /**< Selector(enPowerParaType) Power config */
    TX_PA_VCC_CAL_CONFIG_STRU               paVccCfg;              /* pa vcc配置 */
    RX_AGC_GAIN_INDEX_STRU                  rxAgcIndex;            /* 配置仪器IOR对应的RX AGC GAIN Index, 从工具下发*/
} BBIC_CAL_DcxoSelfCalPara;

/*
 * desc: dcxo下行校准结果参数
 */
typedef struct {
    UINT32                              errorCode;           /* DCXO校准错误码 */
    UINT16                              c2Fix;               /* C2校准结果 */
    UINT16                              c1Fix;               /* C1校准结果 */
    INT32                               calTemp;             /* C1&C2校准的温度,单位0.001 */
    INT32                               initFreqInfo;        /* C1&C2校准后频率误差,单位HZ */
    BBIC_CAL_FLT_FORMAT_E15_T32_STRU    aValue[4];           /* A0A1校准结果,如果A2A3系数不校准,则上报默认NV项值
                                                               [0]:A0校准系数,
                                                               [1]:A1校准系数,
                                                               [2]:A2校准系数,
                                                               [3]:A3校准系数  */
    UINT32                              a0A1Enable;          /* A0A1校准使能 */
    INT32                               refXoTemp;           /* A0A1参考温度 */
    INT32                               beforeTemperatureUp; /* A0A1校准前温度 */
    INT32                               afterTemperatureUp; /* A0A1校准后温度 */
} BBIC_CAL_DcxoSelfCalRslt;

/*
 * Description: 高频FDIQ单个Band的配置信息结构体
 */
typedef struct {
    RAT_MODE_ENUM_UINT16 enRatMode; /* 模式 */
    BAND_ENUM_UINT16     enBand;    /* 频段 */
    UINT8                chsState;  /* 1-- 通道交叉, 0--通道不交叉 */
    UINT8                portNum;   /* 端口数量 */
    UINT8                portMap;   /* *< 1R: 0x1/0x2, 2R: 0x3 */
    UINT8                rsv;
    UINT32               uwRsv[2];
} BBIC_CAL_HF_SELFCAL_BAND_CONFIG_STRU;

/* 装备重定义rx adc结构，当前仅与mmw分支对齐 */
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
    UINT16 bandNum; /* 有效band个数 */
    UINT16 rsv;
    /* 支持变长，数组个数按实际填写，保证下发和上报消息不超过16KB */
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
    /* 支持变长，数组个数按实际填写，保证下发和上报消息不超过16KB */
    BBIC_CAL_RficHfRxAdcPortCalRst hfRxAdcValue[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
} BBIC_CAL_RficHfRxAdcCalIndPara;

/*
 * Description: 高频FDIQ校准请求参数结构体
 */
typedef struct {
    UINT16 uhwBandNum; /* 有效band个数 */
    UINT16 uwRsv;
    /* 支持变长，数组个数按实际填写，保证下发和上报消息不超过16KB */
    BBIC_CAL_HF_SELFCAL_BAND_CONFIG_STRU astBand[BBIC_HF_MAX_BAND_NUM];
} BBIC_CAL_HF_SELFCAL_FDIQ_REQ_PARA_STRU;

/*
 * 结构说明: IQ 子结构体
 */
typedef struct {
    INT16 shwI; /* I路 */
    INT16 shwQ; /* Q路 */
} BBIC_CAL_HF_COMM_IQ_UNIT_STRU;

/*
 * 结构说明: FDIQ参数的产线校准结果
 */
typedef struct {
    BBIC_CAL_HF_COMM_IQ_UNIT_STRU astFdiqCalResultTap[RFHAL_HFCAL_FDIQ_CAL_TAP_NUM]; /* FDIQ Cal Result Tap */
} BBIC_CAL_HF_FDIQ_CAL_RESULT_TAP_STRU;

/*
 * 结构说明: FDIQ参数的产线校准结果
 */
typedef struct {
    /* RX FDIQ Cal Result VGA */
    BBIC_CAL_HF_FDIQ_CAL_RESULT_TAP_STRU astRxFdiqCalResultVga[RFHAL_HFCAL_FDIQ_CAL_VGA_NUM];
} BBIC_CAL_HF_FDIQ_CAL_RESULT_VGA_STRU;

/*
 * 结构说明: RX FDIQ参数的产线校准结果
 */
typedef struct {
     /* RX FDIQ Cal Result VGA */
    BBIC_CAL_HF_FDIQ_CAL_RESULT_VGA_STRU astRxFdiqCalResultBw[RFHAL_HFCAL_TRX_BANDWIDTH_NUM];
} BBIC_CAL_HF_RX_FDIQ_CAL_RESULT_STRU;

/*
 * 结构说明: TX FDIQ参数的产线校准结果
 */
typedef struct {
     /* RX FDIQ Cal Result VGA */
    BBIC_CAL_HF_FDIQ_CAL_RESULT_TAP_STRU astTxFdiqCalResultBw[RFHAL_HFCAL_TRX_BANDWIDTH_NUM];
} BBIC_CAL_HF_TX_FDIQ_CAL_RESULT_STRU;

/*
 * 结构说明: TRX FDIQ参数的产线校准结果
 */
typedef struct {
    BBIC_CAL_HF_RX_FDIQ_CAL_RESULT_STRU stRxFdiqCalResult; /* RX FDIQ Cal Result */
    BBIC_CAL_HF_TX_FDIQ_CAL_RESULT_STRU stTxFdiqCalResult; /* TX FDIQ Cal Result */
} BBIC_CAL_HF_TRX_FDIQ_CAL_RESULT_STRU;

/*
 * Description: FDIQ状态获取结果上报消息结构体
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
 * Description: FDIQ状态获取结果上报消息结构体
 */
typedef struct {
    UINT32                            uwErrorCode;
    UINT16                            afeChanNum;
    UINT16                            uhwRsv;
    BBIC_CAL_HF_SELFCAL_IND_PORT_STRU astData[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
} BBIC_CAL_HF_SELFCAL_IF_IND_PARA_STRU;

/*
 * Description: FIIQ状态获取结果上报消息结构体
 */
typedef struct {
    UINT32                  ulErrorCode;
    UINT32                  ulRsv1;
    UINT16                  usPortIndex;
    UINT16                  usRsv2;
    BBIC_CAL_IQ_RESULT_STRU stRxFiiqInd;
} BBIC_CAL_HF_RX_FIIQ_IND_PORT_STRU;

/*
 * Description: FIIQ状态获取结果上报消息结构体
 */
typedef struct {
    UINT32                            ulErrorCode;
    UINT16                            usPortNum;
    UINT16                            usRsv;
    BBIC_CAL_HF_RX_FIIQ_IND_PORT_STRU astData[RFHAL_HFCAL_TRX_MAX_ANT_NUM];
} BBIC_CAL_HF_RX_FIIQ_RESULT_IND_PARA_STRU;

typedef struct {
    RAT_MODE_ENUM_UINT16            enRatMode;   /* 模式 */
    BAND_ENUM_UINT16                enBand;      /* 频段 */
    UINT32                          ulFreqInfo;  /* 频点，工具配置 */
    BANDWIDTH_ENUM_UINT16           enBandWidth; /* 校准带宽 */
    UINT8                           ucChsState;  /* 1-通道交叉，0-不交叉 */
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
    UINT8                       ucTxEnable;     /* 1--Tx enable, 0--Tx Disable,对应FTXON的参数<switch> */
    UINT8                       ucIsSingleTone; /* 是否是单音，VOS_TRUE:表示单音， VOS_FALSE: 表示调制 */
    UINT8                       ucTxPaMode;     /* PA Mode, 对应^PFA命令中的参数<level> */
    NR_SCS_TYPE_COMM_ENUM_UINT8 enScsType;      /* 子载波间隔，对应^FCHAN 命令中的<对应^FCHAN 命令中的<band_width> */
    UINT16                      usMrxEanble;    /* Mrx Enable, 1--Enable, 0--Disable,需要测度FPOWDET,默认为enable, */
    /* Mimo配置,目前仅在MT使用:1 - 1T/1R, 2 - 2T/2R, 4 - 4R, 8 - 8R， 对应^TSELRF中的参数<mimo_type> */
    UINT16 usMimoType;
    UINT16                usAntMap; /* 表示第几根天线，若是单天线，则默认写1,对应^TSELRF中的参数<group> */
    /* 调制波形，对应^FWAVE命令中的<type>，单音时，若是GSM，则填GMSK，若是EDGE，则是8PSK */
    MODU_TYPE_ENUM_UINT16 enModType;
    MODEM_ID_ENUM_UINT16       enModemId;       /* Modem Id, 目前默认为modem0 */
    RAT_MODE_ENUM_UINT16       enRatMode;       /* Rat Mode, 对应^FCHAN 命令中的<mode> */
    BAND_ENUM_UINT16           enBand;          /* Band No., 对应^FCHAN 命令中的<band> */
    BANDWIDTH_ENUM_UINT16      enBandWith;      /* BandWidth, 对应^FCHAN 命令中的<band_width> */
    UINT32                     ulFreqInfo;      /* Rx/Tx的频率，通过^FCHAN 命令中的<channel>转换过来 */
    POWER_CTRL_MODE_ENUM_UINT8 enPowerCtrlMode; /* < Power Ctrl Mode */

    UINT8                      rbCfgEnable;     /* 1--RB config enable, 0--RB config disable,对应XXX<XXX> */
    UINT16                     rbNumCfg;        /* Config RB number,对应XXX<XXX> */
    UINT16                     rbStartCfg;      /* Config RB start point,对应XXX<XXX> */
    UINT8                      ucRsv[2];        /* 预留位，对齐 */
    TX_POWER_CFG_UNION         unPowerPara;
} BBIC_CAL_MT_TX_REQ_PARA;

typedef struct {
    UINT8                       ucTxEnable;     /* 1--Tx enable, 0--Tx Disable,对应FTXON的参数<switch> */
    UINT8                       ucIsSingleTone; /* 是否是单音，VOS_TRUE:表示单音， VOS_FALSE: 表示调制 */
    UINT8                       ucTxPaMode;     /* PA Mode, 对应^PFA命令中的参数<level> */
    NR_SCS_TYPE_COMM_ENUM_UINT8 enScsType;      /* 子载波间隔，对应^FCHAN 命令中的<对应^FCHAN 命令中的<band_width> */
    UINT16                      usMrxEanble;    /* Mrx Enable, 1--Enable, 0--Disable,需要测度FPOWDET,默认为enable, */
    /* Mimo配置,目前仅在MT使用:1 - 1T/1R, 2 - 2T/2R, 4 - 4R, 8 - 8R， 对应^TSELRF中的参数<mimo_type> */
    UINT16 usMimoType;
    UINT16                usAntMap; /* 表示第几根天线，若是单天线，则默认写1,对应^TSELRF中的参数<group> */
    /* 调制波形，对应^FWAVE命令中的<type>，单音时，若是GSM，则填GMSK，若是EDGE，则是8PSK */
    MODU_TYPE_ENUM_UINT16 enModType;
    MODEM_ID_ENUM_UINT16       enModemId;       /* Modem Id, 目前默认为modem0 */
    RAT_MODE_ENUM_UINT16       enRatMode;       /* Rat Mode, 对应^FCHAN 命令中的<mode> */
    BAND_ENUM_UINT16           enBand;          /* Band No., 对应^FCHAN 命令中的<band> */
    BANDWIDTH_ENUM_UINT16      enBandWith;      /* BandWidth, 对应^FCHAN 命令中的<band_width> */
    UINT32                     ulFreqInfo;      /* Rx/Tx的频率，通过^FCHAN 命令中的<channel>转换过来 */
    POWER_CTRL_MODE_ENUM_UINT8 enPowerCtrlMode; /* < Power Ctrl Mode */

    UINT8                      ucRsv[3];        /* 预留位，对齐 */
    TX_POWER_CFG_UNION         unPowerPara;
} BBIC_CAL_DCXO_MT_TX_REQ_PARA;

typedef struct {
    UINT32 errorCode;    /* 错误码 */
    UINT32 mrxCorrValue; /* MRX线性值 */
    INT16  antPower;     /* 天线口对应的功率值，单位GUC 0.1db，L/NR: 1/8db */
    INT16  rsv;          /* 四字节对齐 */
} BBIC_CAL_MT_TX_PD_IND_PARA;


typedef struct {
    UINT8                 ucRxEnable; /* 1--Rx enable, 0--Rx Disable */
    UINT8                 ucRev;
    UINT16                uhwAgcGainIndex; /* 对应^FAGCGAIN命令的<level> */
    MODEM_ID_ENUM_UINT16  enModemId;       /* Modem Id, 目前默认为modem0 */
    RAT_MODE_ENUM_UINT16  enRatMode;       /* Rat Mode, 对应^FCHAN 命令中的<mode> */
    BAND_ENUM_UINT16      enBand;          /* Band No., 对应^FCHAN 命令中的<band> */
    BANDWIDTH_ENUM_UINT16 enBandWith;      /* BandWidth, 对应^FCHAN 命令中的<band_width> */
    /* Mimo配置,目前仅在MT使用:1 - 1T/1R, 2 - 2T/2R, 4 - 4R, 8 - 8R， 对应^TSELRF中的参数<mimo_type> */
    UINT16 usMimoType;
    UINT16 usAntMap;   /* 表示第几根天线，若是单天线，则默认写1,对应^TSELRF中的参数<group> */
    UINT32 dlFreqInfo; /* Rx/Tx的频率，通过^FCHAN 命令中的<channel>转换过来 */
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

