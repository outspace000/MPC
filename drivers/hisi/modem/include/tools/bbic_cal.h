
#ifndef BBIC_CAL_H
#define BBIC_CAL_H

#include "bbic_cal_shared.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#pragma pack(push, 4)

#define BBIC_CAL_COMM_STRU_BEGIN

/*
 * Description: Msg header struct, only with stComponentID
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
} BBIC_CAL_MSG_HDR_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    UINT16                     uhwBusiness;
    UINT16                     uhwRsv;
} BBIC_CAL_BU_TYPE_STRU;

/*
 * Description: Msg header struct, only with stComponentID
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT8                  aucPara[4];
} BBIC_CAL_MSG_BLOCK_STRU;

/*
 * Description: Msg cnf struct
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_MSG_CNF_PARA_STRU stPara;
} BBIC_CAL_MSG_CNF_STRU;

#define BBIC_CAL_SELF_STRU_BEGIN

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU                stComponentID;
    BBIC_CAL_COMM_SELFCAL_START_REQ_PARA_STRU stPara;
} BBIC_CAL_COMM_SELFCAL_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU                 stComponentID;
    BBIC_CAL_COMM_SELFCAL_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_COMM_SELFCAL_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    BBIC_CAL_RX_IQ_START_REQ_PARA_STRU stPara;
} BBIC_CAL_RX_IQ_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RX_FIIQ_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_RX_FIIQ_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RX_FDIQ_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_RX_FDIQ_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_TX_FILTER_START_REQ_PARA_STRU stPara;
} BBIC_CAL_TX_FILTER_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU              stComponentID;
    BBIC_CAL_TX_FILTER_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_TX_FILTER_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    BBIC_CAL_TX_IQ_START_REQ_PARA_STRU stPara;
} BBIC_CAL_TX_IQ_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_TX_IQ_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_TX_IQ_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    BBIC_CAL_TX_LO_START_REQ_PARA_STRU stPara;
} BBIC_CAL_TX_LO_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_TX_LO_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_TX_LO_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    BBIC_CAL_IP2_START_REQ_PARA_STRU stPara;
} BBIC_CAL_IP2_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU        stComponentID;
    BBIC_CAL_IP2_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_IP2_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_MRX_DCOC_START_REQ_PARA_STRU stPara;
} BBIC_CAL_MRX_DCOC_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_MRX_DCOC_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_MRX_DCOC_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU           stComponentID;
    BBIC_CAL_RX_DCOC_START_REQ_PARA_STRU stPara;
} BBIC_CAL_RX_DCOC_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RX_DCOC_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_RX_DCOC_RESULT_IND_STRU;

#define BBIC_CAL_TRX_STRU_BEGIN

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU      stComponentID;
    BBIC_CAL_RX_START_REQ_PARA_STRU stPara;
} BBIC_CAL_RX_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    BBIC_CAL_RX_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_RX_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU      stComponentID;
    BBIC_CAL_TX_START_REQ_PARA_STRU stPara;
} BBIC_CAL_TX_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    BBIC_CAL_TX_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_TX_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    BBIC_CAL_VCC_START_REQ_PARA_STRU stPara;
} BBIC_CAL_PA_VCC_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU           stComponentID;
    BBIC_CAL_PA_VCC_IND_RESULT_PARA_STRU stPara;
} BBIC_CAL_PA_VCC_RESULT_IND_STRU;

/*
 * Description: ????Path??????Mrx coor????Pa ????????VCC??????????????????????????????????????IQ??????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_PA_VCC_MRXCOOR_IND_PARA_STRU stPara;
} BBIC_CAL_PA_VCC_PATH_MRXCOOR_IND_STRU;

/*
 * Description: ??????????????????????????????Path????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU           stComponentID;
    BBIC_CAL_PA_VC_SAMPLES_IND_PARA_STRU stPara;
} BBIC_CAL_PA_VCC_EXTRACT_SAMPLES_IND_STRU;

/*
 * Description: ????Apt/Apt Dpd/Et/Et Dpd compress, ????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_PA_VCC_COMPRESS_REQ_PARA_STRU stPara;
} BBIC_CAL_PA_VCC_COMPRESS_START_REQ_STRU;

typedef BBIC_CAL_MSG_CNF_STRU BBIC_CAL_PA_VCC_COMPRESS_CNF_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU           stComponentID;
    BBIC_CAL_PA_GAIN_DELTA_REQ_PARA_STRU stPara;
} BBIC_CAL_PA_GAIN_DELTA_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU           stComponentID;
    BBIC_CAL_PA_GAIN_DELTA_IND_PARA_STRU stPara;
} BBIC_CAL_PA_GAIN_DELTA_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    BBIC_CAL_DPD_START_REQ_PARA_STRU stPara;
} BBIC_CAL_DPD_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU        stComponentID;
    BBIC_CAL_DPD_IND_RESULT_PARA_STRU stPara;
} BBIC_CAL_DPD_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_ET_DELAY_START_REQ_PARA_STRU stPara;
} BBIC_CAL_ET_DELAY_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU               stComponentID;
    BBIC_CAL_ET_DELAY_K_IND_RESULT_PARA_STRU stPara;
} BBIC_CAL_ET_DELAY_K_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_ET_DELAY_IND_RESULT_PARA_STRU stPara;
} BBIC_CAL_ET_DELAY_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU   stComponentID;
    BBIC_CAL_GE_TX_REQ_PARA_STRU stPara;
} BBIC_CAL_GE_TX_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU   stComponentID;
    BBIC_CAL_GE_TX_IND_PARA_STRU stPara;
} BBIC_CAL_GE_TX_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 uwErrorCode;
    VOS_UINT16                 uhwPathNum; /* < ??????Path???? */
    VOS_UINT16                 uhwRsv;
} BBIC_CAL_GE_TX_COMM_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_GE_RAMP_REQ_PARA_STRU stPara;
} BBIC_CAL_GETX_RAMP_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_GE_RAMP_IND_PARA_STRU stPara;
} BBIC_CAL_GETX_RAMP_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
} BBIC_CAL_TRX_START_STEP_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU           stComponentID;
    BBIC_CAL_GE_RF_SETTING_REQ_PARA_STRU stPara;
} BBIC_CAL_GE_TX_RFSETTING_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU           stComponentID;
    BBIC_CAL_GE_RF_SETTING_IND_PARA_STRU stPara;
} BBIC_CAL_GE_TX_RFSETTING_RESULT_IND_STRU;

#define BBIC_CAL_RF_DEBUG_TRX_STRU_BEGIN
/*
 * Description: ????RFDEUG TX??????????????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_RF_DEBUG_TX_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_TX_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    BBIC_CAL_RF_DEBUG_TX_CNF_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_TX_CNF_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_RF_DEBUG_RX_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_RX_REQ_STRU;
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    BBIC_CAL_RF_DEBUG_RX_CNF_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_RX_CNF_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    BBIC_CAL_RF_DEBUG_G_TX_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_GSM_TX_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU                stComponentID;
    BBIC_CAL_RF_DEBUG_TX_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_TX_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU              stComponentID;
    BBIC_CAL_RF_DEBUG_GTX_MRX_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_GTX_MRX_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU      stComponentID;
    BBIC_CAL_RF_DEBUG_TRX_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_TRX_REQ_STRU;
typedef BBIC_CAL_RF_DEBUG_TRX_REQ_STRU BBIC_CAL_RF_DEBUG_RM_REQ_STRU;

/*
 * Description: RFDEUG??????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
} BBIC_CAL_RF_DEBUG_INIT_REQ_STRU;

/*
 * Description: RM notify????????,??????????CNF??RM??????????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
} BBIC_CAL_RF_DEBUG_RM_NOTIFY_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    BBIC_CAL_RF_DEBUG_RM_CNF_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_RM_CNF_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    UINT32                     modemId;
} BBIC_CAL_RF_DEBUG_RSSI_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU                 stComponentID;
    BBIC_CAL_RF_DEBUG_RX_RSSI_REPORT_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_RX_RSSI_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    /* Need to nothing */
} BBIC_CAL_RF_DEBUG_RX_EVM_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_RF_DEBUG_RX_EVM_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_RX_EVM_IND_STRU;

#define BBIC_CAL_RF_DEBUG_SELF_STRU_BEGIN

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    UINT8                      aucPara[4];
} BBIC_CAL_RF_DEBUG_SELF_UNIFORM_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_DEBUG_DCXO_CFIX_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_DCXO_CFIX_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    /* Need to nothing */
} BBIC_CAL_RF_DEBUG_DCXO_FE_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU                  stComponentID;
    BBIC_CAL_RF_DEBUG_DCXO_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_DCXO_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_RF_DEBUG_IP2_REQ_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_IP2_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU                 stComponentID;
    BBIC_CAL_RF_DEBUG_IP2_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_IP2_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU              stComponentID;
    BBIC_CAL_RF_DEBUG_RX_DCOC_REQ_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_RX_DCOC_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU              stComponentID;
    BBIC_CAL_RF_DEBUG_RX_DCOC_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_RX_DCOC_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU               stComponentID;
    BBIC_CAL_RF_DEBUG_MRX_DCOC_REQ_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_MRX_DCOC_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU               stComponentID;
    BBIC_CAL_RF_DEBUG_MRX_DCOC_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_MRX_DCOC_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_DEBUG_TX_IQ_REQ_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_TX_IQ_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_DEBUG_TX_IQ_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_TX_IQ_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_DEBUG_TX_LO_REQ_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_TX_LO_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_DEBUG_TX_LO_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_TX_LO_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU      stComponentID;
    BBIC_CAL_READ_REG_DATA_REQ_STRU stPara;
} BBIC_CAL_RF_DEBUG_READ_REG_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU      stComponentID;
    VOS_UINT32                      uwResult;
    BBIC_CAL_READ_REG_DATA_IND_STRU stPara;
} BBIC_CAL_RF_DEBUG_READ_REG_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    BBIC_CAL_WRITE_REG_DATA_REQ_STRU stPara;
} BBIC_CAL_RF_DEBUG_WRITE_REG_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 uwResult;
} BBIC_CAL_RF_DEBUG_WRITE_REG_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    BBIC_CAL_READ_MIPI_DATA_REQ_STRU stPara;
} BBIC_CAL_RF_DEBUG_READ_MIPI_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU       stComponentID;
    VOS_UINT32                       uwResult;
    BBIC_CAL_READ_MIPI_DATA_IND_STRU stPara;
} BBIC_CAL_RF_DEBUG_READ_MIPI_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU        stComponentID;
    BBIC_CAL_WRITE_MIPI_DATA_REQ_STRU stPara;
} BBIC_CAL_RF_DEBUG_WRITE_MIPI_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 uwResult;
} BBIC_CAL_RF_DEBUG_WRITE_MIPI_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 uwResult;
} BBIC_CAL_RF_DEBUG_WRITE_MIPI_REQ_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 uwResult;
} BBIC_CAL_RF_DEBUG_REGISTER_CNF_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 uwResult;
    VOS_UINT8                  aucPara[4];
} BBIC_CAL_RF_DEBUG_REGISTER_IND_STRU;

#define BBIC_CAL_MT_BEGIN
/*
 * ????????: AT ????BBIC??RX REQ????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_MT_RX_REQ_PARA    stMtRxPara;
} AT_BBIC_CAL_MT_RX_REQ;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    /* Need to nothing */
} AT_BBIC_CAL_MT_RX_RSSI_REQ;


typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU   stComponentID;
    BBIC_CAL_MT_RX_RSSI_IND_PARA mtRxIndPara;
} BBIC_CAL_AT_MT_RX_RSSI_IND;


typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 ulErrCode; /* 0????????????0???????? */
} BBIC_CAL_AT_MT_TRX_CNF;


typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_MT_TX_REQ_PARA    stMtTxPara;
} AT_BBIC_CAL_MT_TX_REQ;


typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_DCXO_MT_TX_REQ_PARA   stDcxoTxPara;
} BBIC_CAL_DCXO_TX_REQ;


typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 ulErrCode; /* 0????????????0???????? */
} BBIC_CAL_AT_MT_TX_CNF;


typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_MT_TX_PD_IND_PARA mtTxIndPara;
} BBIC_CAL_AT_MT_TX_PD_IND;

#define BBIC_CAL_CBT_STRU_BEGIN

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    RAT_MODE_ENUM_UINT16               uhwRatMode;
    BBA_CAL_RELOAD_NV_TYPE_ENUM_UINT16 rficType;
} BBIC_CAL_RELOAD_NV_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 uwErrorCode;
} BBIC_CAL_RELOAD_NV_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU      stComponentID;
    BBIC_CAL_NV_RESET_REQ_PARA_STRU stPara;
} BBIC_CAL_NV_RESET_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 uwErrorCode;
} BBIC_CAL_NV_RESET_CNF_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU componentID;
    UINT32                     count;
    UINT16                     data[0]; /* ????????nv??????????nvid,len,data???? */
} BBICCAL_WriteNvReqStru;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU componentID;
    UINT32                     errorCode; /* ???????????? */
    UINT32                     errorNvId; /* ??????????????NVID */
} BBICCAL_WriteNvCnfStru;

#define BBIC_CAL_PHY_STRU_BEGIN

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_WPHY_CONFIG_PARA_STRU stPara;
} BBIC_CAL_WPHY_CONFIG_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_CPHY_CONFIG_PARA_STRU stPara;
} BBIC_CAL_CDMA_CONFIG_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_LPHY_CONFIG_PARA_STRU stPara;
} BBIC_CAL_LTE_CONFIG_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    BBIC_CAL_NB_RSSI_PARA_STRU stPara;
} BBIC_CAL_NB_RSSI_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_NB_RSSI_IND_PARA_STRU stPara;
} BBIC_CAL_NB_RSSI_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_RFIC_SELFCAL_REQ_PARA_STRU stPara;
} BBIC_CAL_RFIC_SELFCAL_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_RFIC_SELFCAL_IND_PARA_STRU stPara;
} BBIC_CAL_RFIC_SELFCAL_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     componentId;
    BBIC_CAL_RficHfRxAdcCalReqPara rxAdcPara;
} BBIC_CAL_RficHfRxAdcSelfCalReq;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     componentId;
    BBIC_CAL_RficHfRxAdcCalIndPara rxAdcInd;
} BBIC_CAL_RficHfRxAdcSelfCalInd;

#define BBIC_CAL_RF_DEBUG_HF_TRX_STRU_BEGIN

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_DEBUG_HF_RX_REQ_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_HF_RX_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    /* Need to nothing */
} BBIC_CAL_RF_DEBUG_HF_RSSI_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU                 stComponentID;
    BBIC_CAL_RF_DEBUG_HF_RX_RSSI_IND_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_HF_RX_RSSI_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_DEBUG_HF_TX_REQ_PARA_STRU stPara;
} BBIC_CAL_RF_DEBUG_HF_TX_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_HF_ANA_TEMP_REQ_PARA_STRU stPara;
} BBIC_CAL_RF_HF_ANA_TEMP_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_RF_HF_ANA_TEMP_IND_PARA_STRU stPara;
} BBIC_CAL_RF_HF_ANA_TEMP_IND_STRU;

#define BBIC_CAL_HF_TRX_STRU_BEGIN

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    BBIC_CAL_HF_RX_START_REQ_PARA_STRU stPara;
} BBIC_CAL_HF_RX_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_HF_RX_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_HF_RX_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU         stComponentID;
    BBIC_CAL_HF_TX_START_REQ_PARA_STRU stPara;
} BBIC_CAL_HF_TX_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU          stComponentID;
    BBIC_CAL_HF_TX_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_HF_TX_RESULT_IND_STRU;

#define BBIC_CAL_HF_SELF_STRU_BEGIN

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU              stComponentID;
    BBIC_CAL_HF_RX_DCOC_START_REQ_PARA_STRU stPara;
} BBIC_CAL_HF_RX_DCOC_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU               stComponentID;
    BBIC_CAL_HF_RX_DCOC_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_HF_RX_DCOC_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU      stComponentID;
    BBIC_CAL_TEMP_QRY_REQ_PARA_STRU stPara;
} BBIC_CAL_TEMP_QRY_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU      stComponentID;
    BBIC_CAL_TEMP_QRY_IND_PARA_STRU stPara;
} BBIC_CAL_TEMP_QRY_IND_STRU;

/*
 * Description: PLL??????????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_PLL_QRY_REQ_PARA_STRU stPara;
} BBIC_CAL_PLL_QRY_REQ_STRU;

/*
 * Description: PLL??????????????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU     stComponentID;
    BBIC_CAL_PLL_QRY_IND_PARA_STRU stPara;
} BBIC_CAL_PLL_QRY_IND_STRU;

/*
 * Description: DPDT??????????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU  stComponentID;
    BBIC_CAL_DPDT_REQ_PARA_STRU stPara;
} BBIC_CAL_DPDT_REQ_STRU;

/*
 * Description: DPDT??????????????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU  stComponentID;
    BBIC_CAL_DPDT_IND_PARA_STRU stPara;
} BBIC_CAL_DPDT_IND_STRU;

/*
 * Description: TRX TAS????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU    componentId;
    BBIC_CAL_SetTrxTasReqParaStru data;
} BBIC_CAL_SetTrxTasReqStru;

/*
 * Description: TRX TAS????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU    componentId;
    BBIC_CAL_SetTrxTasCnfParaStru data;
} BBIC_CAL_SetTrxTasCnfStru;

/*
 * Description: PLL??????????????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU  stComponentID;
    BBIC_CAL_DCXO_REQ_PARA_STRU stPara;
} BBIC_CAL_DCXO_REQ_STRU;

/*
 * Description: PLL??????????????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU stComponentID;
    VOS_UINT32                 ulErrorCode;
} BBIC_CAL_DCXO_IND_STRU;

/*
 * desc : dcxo pc req msg
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU componentId;
    BBIC_CAL_DcxoSelfCalPara dcxoPara;
} BBIC_CAL_DcxoSelfCalReq;

/*
 * desc : DCXO ind pc msg
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU componentId;
    BBIC_CAL_DcxoSelfCalRslt dcxoInd;
} BBIC_CAL_DcxoSelfCalInd;


/*
 * desc : DCXO dcoc req msg
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU componentId;
    BBIC_CAL_DcxoSelfCalDcocReqPara dcocPara;
} BBIC_CAL_DcxoDcocCalReq;

/*
 * desc: DCXO dcoc confirm msg
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU componentId;
    UINT32 errCode;
} BBIC_CAL_DcxoDcocCalCfm;

/*
 * Description: ????FDIQ??????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_HF_SELFCAL_FDIQ_REQ_PARA_STRU stPara;
} BBIC_CAL_HF_SELFCAL_FDIQ_REQ_STRU;

/*
 * Description: ????FDIQ??????????????????
 */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU           stComponentID;
    BBIC_CAL_HF_SELFCAL_IF_IND_PARA_STRU stPara;
} BBIC_CAL_HF_TRX_FDIQ_RESULT_IND_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU              stComponentID;
    BBIC_CAL_HF_RX_FIIQ_START_REQ_PARA_STRU stPara;
} BBIC_CAL_HF_RX_FIIQ_START_REQ_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU               stComponentID;
    BBIC_CAL_HF_RX_FIIQ_RESULT_IND_PARA_STRU stPara;
} BBIC_CAL_HF_RX_FIIQ_RESULT_IND_STRU;

/* For Hids */
typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU            stComponentID;
    BBIC_CAL_DPD_START_REQ_PARA_HIDS_STRU stPara;
} BBIC_CAL_DPD_START_REQ_HIDS_STRU;

typedef struct {
    VOS_MSG_HEADER
    BBIC_CAL_COMPONENT_ID_STRU             stComponentID;
    BBIC_CAL_DPD_IND_RESULT_PARA_HIDS_STRU stPara;
} BBIC_CAL_DPD_RESULT_IND_HIDS_STRU;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

