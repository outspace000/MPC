/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2019. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __APP_LMM_INTERFACE_H__
#define __APP_LMM_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "app_nas_comm.h"
#include "app_rrc_interface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#define APP_MAX_PLMN_NUM 37
#define APP_MAX_UEID_BUF_SIZE 10
#define APP_MS_NET_CAP_MAX_SIZE 9
/* add begin */
#define APP_MM_MAX_EQU_PLMN_NUM 16 /* ????????EPlmn???????? */
#define APP_MM_MAX_PLMN_NUM 64     /* PLMN???????????? */
#define APP_MM_MAX_TA_NUM 64       /* TA ???????????? */
/* add end */

#define APP_MM_CN_NAME_MAX_LEN 255 /* ?????????????????? */

/* DT begin */
#define APP_EMM_IMSI_MAX_LEN 15
/* DT end */

/* APP->MM ??????????????3???????????? APP->MM */
#define APP_MM_COMM_MSG_ID_HEADER PS_MSG_ID_APP_TO_EMM_BASE

/* MM->APP ??????????????3???????????? MM->APP */
#define MM_APP_COMM_MSG_ID_HEADER PS_MSG_ID_EMM_TO_APP_BASE

/* MM->APP ??????????????3???????????? MM->APP */
#define MM_APP_KEY_EVT_MSG_ID_HEADER PS_OMT_KEY_EVT_REPORT_IND

/* APP->MM ??????????????3???????????? APP->MM */
#define APP_MM_TP_MSG_ID_HEADER OM_PS_TRANSPARENT_CMD_REQ

/* MM->APP ??????????????3???????????? MM->APP */
#define MM_APP_TP_MSG_ID_HEADER OM_PS_TRANSPARENT_CMD_CNF

/* MM->APP ??????????????3???????????? MM->APP */
#define MM_APP_AIR_MSG_ID_HEADER PS_OMT_AIR_MSG_REPORT_IND

/* ????????: APP??MM???????? */
enum APP_MM_MsgType {
    /* ???????? ??????????????  0x30 ~ 0x4F */
    ID_APP_MM_CMD_INQ_START = 0x30 + APP_MM_COMM_MSG_ID_HEADER,

    ID_APP_MM_INQ_UE_MODE_REQ = 0x44 + APP_MM_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqUeModeReq */
    ID_APP_MM_INQ_UE_MODE_CNF = 0x44 + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqUeModeCnf */
    ID_APP_MM_INQ_LTE_CS_REQ  = 0x45 + APP_MM_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqLteCsReq */
    ID_APP_MM_INQ_LTE_CS_CNF  = 0x45 + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqLteCsCnf */

    ID_APP_MM_CMD_INQ_END = 0x4F + APP_MM_COMM_MSG_ID_HEADER,

    /* V7R2-DT GUTI IMSI EMM_STATE  2014/03/20  start */
    /* DT begin */
    ID_APP_MM_INQ_LTE_GUTI_REQ = 0x46 + APP_MM_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqLteGutiReq */
    ID_APP_MM_INQ_LTE_GUTI_CNF = 0x46 + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqLteGutiCnf */
    ID_APP_MM_INQ_LTE_GUTI_IND = 0x47 + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqLteGutiInd */

    ID_APP_MM_INQ_IMSI_REQ = 0x47 + APP_MM_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqImsiReq */
    ID_APP_MM_INQ_IMSI_CNF = 0x48 + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqImsiCnf */
    ID_APP_MM_INQ_IMSI_IND = 0x49 + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqImsiInd */

    ID_APP_MM_INQ_EMM_STATE_REQ = 0x48 + APP_MM_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqEmmStateReq */
    ID_APP_MM_INQ_EMM_STATE_CNF = 0x4a + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqEmmStateCnf */
    ID_APP_MM_INQ_EMM_STATE_IND = 0x4b + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_InqEmmStateInd */
    /* DT end */
    /* V7R2-DT GUTI IMSI EMM_STATE   2014/03/20  end */

    /* add for ue cap display, 2017-02-03, begin */
    ID_APP_MM_UE_CAP_INFO_REQ = 0x4c + APP_MM_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_UeCapInfoReq */
    ID_MM_APP_UE_CAP_INFO_CNF = 0x4c + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice MM_APP_UeCapInfoCnf */
    /* add for ue cap display, 2017-02-03, end */

    /* ???????? ??????????  0x50 ~ 0x8F */
    /* Added for DT report, 2018-11-21, begin */
    ID_APP_MM_REG_STAT_REQ = 0x5c + APP_MM_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice ID_APP_MM_REG_STAT_REQ_STRU */
    ID_APP_MM_REG_STAT_CNF = 0x5c + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice ID_APP_MM_REG_STAT_CNF_STRU */
    /* Added for DT report, 2018-11-21, end */
    ID_APP_MM_REG_STAT_IND = 0x5D + MM_APP_COMM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_MM_RegStatInd */

    ID_APP_MM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 APP_MM_MsgTypeUint32;

/* ????????: EMM?????? */
enum APP_EMM_MainState {
    /* =================== EMM???????? =================== */
    APP_EMM_MS_NULL       = 0x0000, /* ??????           */
    APP_EMM_MS_DEREG      = 0x0001, /* DETACH????       */
    APP_EMM_MS_REG_INIT   = 0x0002, /* ATTACH?????????? */
    APP_EMM_MS_REG        = 0x0003, /* ATTACH????       */
    APP_EMM_MS_DEREG_INIT = 0x0004, /* DETACH?????????? */
    APP_EMM_MS_TAU_INIT   = 0x0005, /* TAU??????????    */
    APP_EMM_MS_SER_INIT   = 0x0006, /* SERVICE?????????? */
    APP_EMM_MS_STATE_BUTT
};
typedef VOS_UINT16 APP_EMM_MainStateUint16;

/* ????????: EMM?????? */
enum APP_EMM_SubState {
    /* =================== EMM???????? =================== */
    APP_EMM_SS_NULL = 0x0000, /* ???????? */
    /* ========== APP_EMM_MS_DEREG?????????? ============== */
    APP_EMM_SS_DEREG_NORMAL_SERVICE    = 0x0001, /* ?????????????????? */
    APP_EMM_SS_DEREG_LIMITED_SERVICE   = 0x0002, /* ?????????????????? */
    APP_EMM_SS_DEREG_ATTEMPT_TO_ATTACH = 0x0003, /* ??????????????ATTCH???? */
    APP_EMM_SS_DEREG_PLMN_SEARCH       = 0x0004, /* ?????????????? */
    APP_EMM_SS_DEREG_NO_IMSI           = 0x0005, /* ???????????????? */
    APP_EMM_SS_DEREG_ATTACH_NEEDED     = 0x0006, /* ??????????????ATTACH???? */
    APP_EMM_SS_DEREG_NO_CELL_AVAILABLE = 0x0007, /* ?????????????????????? */

    /* ========== APP_EMM_MS_REG?????????? ================ */
    APP_EMM_SS_REG_NORMAL_SERVICE                 = 0x0011, /* ???????????????? */
    APP_EMM_SS_REG_ATTEMPTING_TO_UPDATE           = 0x0012, /* ????????????TA???????? */
    APP_EMM_SS_REG_LIMITED_SERVICE                = 0x0013, /* ???????????????? */
    APP_EMM_SS_REG_PLMN_SEARCH                    = 0x0014, /* ???????????? */
    APP_EMM_SS_REG_WAIT_ACCESS_GRANT_IND          = 0x0015, /* ????????TA???????? */
    APP_EMM_SS_REG_NO_CELL_AVAILABLE              = 0x0016, /* ???????????????????? */
    APP_EMM_SS_REG_ATTEMPT_TO_UPDATE_MM           = 0x0017, /* ??????????????????EPS?????????? */
    APP_EMM_SS_REG_IMSI_DETACH_WAIT_CN_DETACH_CNF = 0x0018, /* IMSI DETACH???????????????? */
    APP_EMM_SS_REG_IMSI_DETACH_WAIT_RRC_REL_IND   = 0x0019, /* IMSI DETACH???????????????? */
    APP_EMM_SS_BUTT
};
typedef VOS_UINT16 APP_EMM_SubStateUint16;

/* ????????: EMM UPDATE???? */
enum APP_EMM_UpdateState {
    APP_EMM_US_EU1_UPDATED             = 0x00, /* ????????       */
    APP_EMM_US_EU2_NOT_UPDATED         = 0x01, /* ??????????     */
    APP_EMM_US_EU3_ROAMING_NOT_ALLOWED = 0x02, /* ?????????????? */

    APP_EMM_US_BUTT
};
typedef VOS_UINT32 APP_EMM_UpdateStateUint32;

/* ????????: EMM???????? */
enum APP_EMM_RegState {
    APP_EMM_RS_NULL                = 0x00, /* ?????? */
    APP_EMM_RS_L1_UPDATED          = 0x01, /* ???????? */
    APP_EMM_RS_L2_IDLE_NO_IMSI     = 0x02, /* ?????????? */
    APP_EMM_RS_L3_ROMING_NOT_ALLOW = 0x03, /* ?????????????? */
    APP_EMM_RS_L4_NOT_UPDATED      = 0x04, /* ?????????? */
    APP_EMM_RS_BUTT
};
typedef VOS_UINT32 APP_EMM_RegStateUint32;

/* ????????: ???????? */
enum APP_EMM_SelMode {
    APP_EMM_PLMN_SEL_AUTO   = 0x00, /* ???????????????? */
    APP_EMM_PLMN_SEL_MANUAL = 0x01, /* ???????????????? */
    APP_EMM_PLMN_SEL_BUTT
};
typedef VOS_UINT32 APP_EMM_SelModeUint32;

/* ????????: PLMN lock???? */
enum APP_MM_LockPlmnType {
    APP_MM_LOCK_PLMN_TYPE_LOCK   = 0x00,
    APP_MM_LOCK_PLMN_TYPE_UNLOCK = 0x01,
    APP_MM_LOCK_PLMN_TYPE_BUTT
};
typedef VOS_UINT32 APP_MM_LockPlmnTypeUint32;

/* ????????: ???????? */
enum APP_EMM_SrvState {
    APP_EMM_SRV_STATUS_NO_SRV           = 0x00, /* ?????????? */
    APP_EMM_SRV_STATUS_LIMITED          = 0x01, /* ???????????? */
    APP_EMM_SRV_STATUS_SRV              = 0x02, /* ???????? */
    APP_EMM_SRV_STATUS_LIMITED_REGIONAL = 0x03, /* ???????????????? */
    APP_EMM_SRV_STATUS_BUTT
};
typedef VOS_UINT32 APP_EMM_SrvStateUint32;

/* ????????: ???????? */
enum APP_MM_ReportMode {
    APP_MM_RM_ONE_TIME = 0x00, /* ???????? */
    APP_MM_RM_AUTO     = 0x01, /* ???????? */
    APP_MM_RM_PERIOD   = 0x02, /* ???????? */
    APP_MM_RM_BUTT
};
typedef VOS_UINT32 APP_MM_ReportModeUint32;

/* DT begin */
/* ????????: NAS???????????????????? */
enum NAS_DT_PrtStauts {
    NAS_DT_RPT_STOP,  /* ???? */
    NAS_DT_RPT_START, /* ???? */
    NAS_DT_RPT_BUTT
};
typedef VOS_UINT32 NAS_DT_RptStatusUint32;

/* ????????: NAS???????????????????????? */
enum NAS_DT_ReportItem {
    NAS_DT_REPORT_TYPE_GUTI,
    NAS_DT_REPORT_TYPE_IMSI,
    NAS_DT_REPORT_TYPE_EMM_STATE,
    /* Added for DT report, 2018-11-21, begin */
    NAS_DT_REPORT_TYPE_EMM_REG_STATE,
    /* Added for DT report, 2018-11-21, end */
    NAS_DT_REPORT_TYPE_BUTT
};
typedef VOS_UINT32 NAS_DT_ReportItemUint32;

/* ????????: NAS?????????????????????????????????? */
typedef struct {
    HTIMER     rptTimer;  /* ?????????????? */
    VOS_UINT32 rptPeriod; /* ???????? */
} NAS_DT_RptTimer;

/* ????????: NAS???????????????????????? */
typedef struct {
    NAS_DT_ReportItemUint32 dtRptItem; /* ?????????????? */
    NAS_DT_RptStatusUint32  rptStatus; /* ???????????? */
    APP_MM_ReportModeUint32 rptType;   /* ???????? */
    NAS_DT_RptTimer         rptTimer;  /* ?????????????????? */
} APP_MM_DtReportCtrl;
/* DT end */

/* ????????: ???????? */
enum APP_PH_RaMode {
    APP_PH_RAT_WCDMA    = 0x00,
    APP_PH_RAT_GSM_GPRS = 0x01,
    APP_PH_RAT_LTE_FDD  = 0x02,
    APP_PH_RAT_LTE_TDD  = 0x03,

    APP_PH_RAT_TYPE_BUTT
};
typedef VOS_UINT32 APP_PH_RaModeUint32;

/* ????????: PLMN???????? */
enum APP_PLMN_ReselModeType {
    APP_PLMN_RESELECTION_AUTO   = 0x00, /* ???????? */
    APP_PLMN_RESELECTION_MANUAL = 0x01, /* ???????? */

    APP_PLMN_RESEL_MODE_TYPE_BUTT
};
typedef VOS_UINT32 APP_PLMN_ReselModeTypeUint32;

/* ????????: PLMN???? */
enum APP_PLMN_StatusFlag {
    APP_PLMN_STATUS_UNKNOWN   = 0x00,
    APP_PLMN_STATUS_AVAILABLE = 0x01,
    APP_PLMN_STATUS_CURRENT   = 0x02,
    APP_PLMN_STATUS_FORBIDDEN = 0x03,

    APP_PLMN_STATUS_FLAG_BUTT
};
typedef VOS_UINT32 APP_PLMN_StatusFlagUint32;

/* ????????: ???????? */
enum APP_PHONE_ServiceStatus {
    APP_NORMAL_SERVICE       = 0x00, /* ????????????   */
    APP_LIMITED_SERVICE      = 0x01, /* ????????????   */
    APP_ATTEMPTING_TO_UPDATE = 0x02, /* ??????????     */
    APP_NO_IMSI              = 0x03, /* ??????IMSI???? */
    APP_NO_SERVICE           = 0x04, /* ??????????     */
    APP_DETACHED             = 0x05, /* ??????????     */
    APP_DISABLE              = 0x06, /* ?????????????? */
    APP_DETACH_FAIL          = 0x07, /* ?????????????? */

    APP_PHONE_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 APP_PHONE_ServiceStatusUint32;

/* ????????: ATTACH TYPE */
enum APP_MM_AttachType {
    APP_MM_ATTACH_TYPE_PS    = 0x01,
    APP_MM_ATTACH_TYPE_PS_CS = 0x02,

    APP_MM_ATTACH_RST_BUTT
};
typedef VOS_UINT32 APP_MM_AttachTypeUint32;

/* ????????: DETACH TYPE */
enum APP_MM_DetachType {
    APP_MM_DETACH_TYPE_PS    = 0x01,
    APP_MM_DETACH_TYPE_CS    = 0x02,
    APP_MM_DETACH_TYPE_PS_CS = 0x03,
    APP_MM_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 APP_MM_DetachTypeUint32;

enum APP_EMM_SmcCtrl {
    APP_EMM_SMC_OPEN  = 0,
    APP_EMM_SMC_CLOSE = 1,

    APP_EMM_SMC_CTRL_BUTT
};
typedef VOS_UINT8 APP_EMM_SmcCtrlUint8;

enum APP_REG_Stat {
    APP_REG_STAT_NOT_REG_AND_NOT_SRCH_OPERATOR = 0x00,
    APP_REG_STAT_REG_HPLMN,
    APP_REG_STAT_NOT_REG_AND_SRCH_OPERATOR,
    APP_REG_STAT_REG_DENIED,
    APP_REG_STAT_UNKNOWN,
    APP_REG_STAT_REG_ROAMING,
    APP_REG_STAT_BUTT
};
typedef VOS_UINT32 APP_REG_StatUint32;

enum APP_MM_ServiceDomain {
    APP_MM_SERVICE_DOMAIN_NULL = 0x00,
    APP_MM_SERVICE_DOMAIN_PS,
    APP_MM_SERVICE_DOMAIN_CS,
    APP_MM_SERVICE_DOMAIN_PS_CS,
    APP_MM_SERVICE_DOMAIN_BUTT
};
typedef VOS_UINT32 APP_MM_ServiceDomainUint32;

enum APP_MM_DetachEntity {
    APP_MM_DETACH_ENTITY_ME = 0x01,
    APP_MM_DETACH_ENTITY_NW = 0x02,
    APP_MM_DETACH_ENTITY_BUTT
};
typedef VOS_UINT32 APP_MM_DetachEntityUint32;

enum APP_MM_PlmnType {
    APP_MM_PLMN_TYPE_RPLMN = 0x01,
    APP_MM_PLMN_TYPE_EPLMN,
    APP_MM_PLMN_TYPE_FPLMN,
    APP_MM_PLMN_TYPE_UPLMN,
    APP_MM_PLMN_TYPE_OPLMN,
    APP_MM_PLMN_TYPE_BUTT
};
typedef VOS_UINT32 APP_MM_PlmnTypeUint32;

enum APP_MM_SetType {
    APP_MM_SET_TYPE_SETTING = 0x00,
    APP_MM_SET_TYPE_DELETE,
    APP_MM_SET_TYPE_BUTT
};
typedef VOS_UINT32 APP_MM_SetTypeUint32;

enum APP_MM_DaylightSaveTime {
    APP_MM_DAYLIGHT_NO_ADJUST = 0,
    APP_MM_DAYLIGHT_1_HOUR_ADJUST,
    APP_MM_DAYLIGHT_2_HOUR_ADJUST,
    APP_MM_DAYLIGHT_BUTT
};
typedef VOS_UINT32 APP_MM_DaylightSaveTimeUint32;

enum APP_MM_Timezone {
    APP_MM_TIMEZONE_POSITIVE = 0,
    APP_MM_TIMEZONE_NAGETIVE,
    APP_MM_TIMEZONE_BUTT
};
typedef VOS_UINT8 APP_MM_TimezoneUint8;

/* add for ue cap display, 2017-02-03, begin */
/*
 * ????????: HIDS????LNAS??IMSA????UE??????????,????LNAS??IMSA??????????????????,
 *           ????????????
 */
enum APP_MM_UeCapInfoRslt {
    APP_MM_UE_CAP_INFO_FAIL = 0,
    APP_MM_UE_CAP_INFO_SUCC = 1,
    APP_MM_UE_CAP_INFO_BUTT
};
typedef VOS_UINT32 APP_MM_UeCapInfoRsltUint32;
/* add for ue cap display, 2017-02-03, end */

/*
 * APP_MM_MSG_ID_UINT32????4????:
 *   ????????                                      ????????
 * -----------------------------------------------------------
 * | BYTE1??4?? + 0000 |  BYTE2    |   BYTE3    |    BYTE4   |
 * -----------------------------------------------------------
 * 0000????????????????|  ???????? |  ??????????| ??????0-255
 * -----------------------------------------------------------
 * 0001??L2 LOG        |           |            |
 * -----------------------------------------------------------
 * 0010??????????      |           |            |
 * -----------------------------------------------------------
 * 0011??????????      |           |            |
 * -----------------------------------------------------------
 * 0100??????????????  |           |            |
 * -----------------------------------------------------------
 * 0101??????????      |           |            | ????????
 * -----------------------------------------------------------
 */
typedef VOS_UINT32 APP_MM_MSG_ID_UINT32;

typedef struct {
    APP_PlmnId                plmnId;     /* PLMN ID  */
    APP_PLMN_StatusFlagUint32 plmnStatus; /* PLMN???? */
    APP_PH_RaModeUint32       accessMode; /* ???????? */
} APP_PLMN_Info;

typedef struct {
    VOS_UINT32    plmnNum;
    APP_PLMN_Info plmnInfo[APP_MAX_PLMN_NUM];
} APP_PLMN_InfoList;

/* ????????:APP_GUTI_HEAD_STRU?????????? */
typedef struct {
    VOS_UINT8 lenth;
    VOS_UINT8 oeToi;
    VOS_UINT8 rsv[2];
} APP_GUTI_Head;

/* ????????:APP_MME_GROUPID_STRU?????????? */
typedef struct {
    VOS_UINT8 groupId;
    VOS_UINT8 groupIdCnt;
    VOS_UINT8 rsv[2];
} APP_MME_Groupid;

/* ????????:APP_MME_CODE_STRU?????????? */
typedef struct {
    VOS_UINT8 mmeCode;
    VOS_UINT8 rsv[3];
} APP_MME_Code;

/* ????????:APP_MTMSI_STRU?????????? */
typedef struct {
    VOS_UINT8 mtmsi;
    VOS_UINT8 mtmsiCnt1;
    VOS_UINT8 mtmsiCnt2;
    VOS_UINT8 mtmsiCnt3;
} APP_Mtmsi;

/* ????????:APP_GUTI_STRU?????????? */
typedef struct {
    APP_GUTI_Head   gutiHead;
    APP_PlmnId      plmn;
    APP_MME_Groupid mmeGroupId;
    APP_MME_Code    mmeCode;
    APP_Mtmsi       mtmsi;
} APP_Guti;

/*
 * ????????: 24.008 10.5.6.13
 *           MBMS Service ID (octet 3, 4 and 5)
 *           In the MBMS Service ID field bit 8 of octet 3 is the most
 *           significant bit and bit 1 of octet 5 the least significant bit.
 *           The coding of the MBMS Service ID is the responsibility of each
 *           administration. Coding using full hexadecimal representation may
 *           be used. The MBMS Service ID consists of 3 octets.
 */
typedef struct {
    VOS_UINT32 mbmsSerId;
} APP_MBMSSER_Id;

/* ????????:APP_TMGI_STRU?????????? */
typedef struct {
    VOS_UINT32 opPlmn : 1; /* 1: VALID; 0: INVALID */
    VOS_UINT32 opSpare : 31;

    APP_MBMSSER_Id mbmsSer;
    APP_PlmnId     plmnId;
} APP_TMGI;

/* ????????:APP_TMGI_MBMS_HEAD_STRU?????????? */
typedef struct {
    VOS_UINT8 lenth;
    VOS_UINT8 oeTi;
    VOS_UINT8 rsv[2];
} APP_TMGI_MbmsHead;

/* ????????:APP_TMGI_MBMS_STRU?????????? */
typedef struct {
    VOS_UINT32 opMbmsSesId : 1; /* 1: VALID; 0: INVALID */
    VOS_UINT32 opSpare : 31;

    APP_TMGI_MbmsHead msidHead;
    APP_TMGI          tmgi;
    VOS_UINT8         mbmsSesId;
    VOS_UINT8         rsv[3];
} APP_TMGI_Mbms;

/* ????????:APP_UEID_STRU?????????? */
typedef struct {
    VOS_UINT32 opImsi : 1; /* 1: VALID; 0: INVALID */
    VOS_UINT32 opImei : 1;
    VOS_UINT32 opImeisv : 1;
    VOS_UINT32 opTmsi : 1;
    VOS_UINT32 opPtmsi : 1;
    VOS_UINT32 opGuti : 1;
    VOS_UINT32 opTmgiMbms : 1; /* 1: VALID; 0: INVALID */
    VOS_UINT32 opRsv : 25;

    VOS_UINT8 imsi[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8 reserved1[2];
    VOS_UINT8 imei[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8 reserved2[2];
    VOS_UINT8 imeisv[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8 reserved3[2];
    VOS_UINT8 tmsi[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8 reserved4[2];
    VOS_UINT8 ptmsi[APP_MAX_UEID_BUF_SIZE];
    VOS_UINT8 reserved5[2];

    APP_Guti      guti;
    APP_TMGI_Mbms tmgiMbms;
} APP_UEID;

/* ????????:APP_LAC_STRU?????????? */
typedef struct {
    VOS_UINT8 lac;
    VOS_UINT8 lacCnt;
    VOS_UINT8 rsv[2];
} APP_LAC;

/* ????????:APP_RAC_STRU?????????? */
typedef struct {
    VOS_UINT8 rac;
    VOS_UINT8 rsv[3];
} APP_RAC;

/* ????????:APP_TAC_STRU?????????? */
typedef struct {
    VOS_UINT8 tac;
    VOS_UINT8 tacCnt;
    VOS_UINT8 rsv[2];
} APP_TAC;

/* ????????:APP_NETWORK_ID_STRU?????????? */
typedef struct {
    VOS_UINT32 opPlmnId : 1; /* 1: VALID; 0: INVALID */
    VOS_UINT32 opLac : 1;    /* 1: VALID; 0: INVALID */
    VOS_UINT32 opRac : 1;    /* 1: VALID; 0: INVALID */
    VOS_UINT32 opTac : 1;    /* 1: VALID; 0: INVALID */
    VOS_UINT32 opCellId : 1;
    VOS_UINT32 opRsv : 27;

    APP_PlmnId plmnId;
    APP_LAC    lac;
    APP_RAC    rac;
    APP_TAC    tac;
    VOS_UINT32 cellId; /* Cell Identity */
} APP_NETWORK_Id;

/* ????????:24.008 840 10.5.1.5 */
typedef struct {
    VOS_UINT8 value;
    VOS_UINT8 rsv[3];
} APP_MS_Classmark1;

/*
 * ????????:24.008 840 10.5.1.6
 *           ????????????BIT??????????????
 */
typedef struct {
    VOS_UINT8 lenLvLen;
    VOS_UINT8 classMark[3];
} APP_MS_Classmark2;

/* ????????:24.008 840 10.5.1.7 */
typedef struct {
    VOS_UINT8 lenLvLen;
    VOS_UINT8 value[35];
} APP_MS_Classmark3;

/*
 * ????????:24.008 840 10.5.1.6
 *         0   EPS encryption algorithm *** not supported
 *         1   EPS encryption algorithm *** supported
 *         #define NAS_MM_ALGORITHM_NOT_SUPPORT    0
 *         #define NAS_MM_ALGORITHM_SUPPORT        1
 */
typedef struct {
    VOS_UINT32 opClassMark1 : 1;
    VOS_UINT32 opClassMark2 : 1;
    VOS_UINT32 opClassMark3 : 1;

    VOS_UINT32 opRsv : 29;

    APP_MS_Classmark1 classMark1;
    APP_MS_Classmark2 classMark2;
    APP_MS_Classmark3 classMark3;
} APP_MS_Classmark;

/*
 * ????????:23.401-800 9.9.3.34
 *         0   EPS encryption algorithm *** not supported
 *         1   EPS encryption algorithm *** supported
 *         #define NAS_MM_ALGORITHM_NOT_SUPPORT    0
 *         #define NAS_MM_ALGORITHM_SUPPORT        1
 *         ????????????BIT??????????????
 */
typedef struct {
    VOS_UINT8 ueNetCapLen;
    VOS_UINT8 ueNetCap[NAS_MM_MAX_UE_NET_CAP_LEN];
    VOS_UINT8 rsv[2];
} APP_UE_NetCap;

/*
 * ????????:24.008 10.5.5.12
 *     aucMsNetCap??????????????????????/????????????:
 *     --------------------------------------------------------------
 *     (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
 *     --------------------------------------------------------------
 *         Length of MS network capability contents, UNIT is byte      octet 0
 *     --------------------------------------------------------------
 *         MS network capability value                                 octet 1-8
 *     --------------------------------------------------------------
 */
typedef struct {
    VOS_UINT8 msNetCapLen;
    /* ??????????????????????????aucMsNetCap[0]??????????????GEA1 bits???????????????? */
    VOS_UINT8 msNetCap[NAS_MM_MAX_MS_NET_CAP_LEN];
    VOS_UINT8 rsv[3];
} APP_MS_NetCap;

typedef struct {
    VOS_UINT32 plmnNum;
    APP_PlmnId plmnId[APP_MM_MAX_PLMN_NUM];
} APP_MM_PlmnList;

/* add begin */
typedef struct {
    VOS_UINT32 plmnNum;
    APP_PlmnId plmnId[APP_MM_MAX_EQU_PLMN_NUM];
} APP_EMM_EplmnList;

typedef struct {
    APP_PlmnId plmnId;
    APP_TAC    tac;
} APP_TA;

typedef struct {
    VOS_UINT32 taNum; /* TA??????    */
    APP_TA     ta[APP_MM_MAX_TA_NUM];
} APP_TA_List;

typedef struct {
    VOS_UINT32 plmnNum;
    APP_PlmnId plmnId[APP_MM_MAX_PLMN_NUM];
} APP_EMM_PlmnList;

typedef struct {
    APP_EMM_MainStateUint16   mainState;   /* MM?????? */
    APP_EMM_SubStateUint16    subState;    /* MM?????? */
    APP_EMM_UpdateStateUint32 emmUpState;  /* EMM update???? */
    APP_EMM_RegStateUint32    regState;    /* ???????? */
    APP_EMM_SrvStateUint32    mmcSrvStat;  /* EMM???????? */
    APP_EMM_SelModeUint32     plmnSelMode; /* ???????? */
    APP_EMM_EplmnList         eplmnList;   /* EPLMN List */
    APP_PlmnId                rplmn;       /* RPlmn */
    APP_TA_List               taiList;     /* TaiList */
    APP_TA                    lastTa;      /* Last Ta */
    APP_EMM_PlmnList          fplmnList;   /* Forbiden Plmn */
    APP_TA_List               forbTaList;  /* Forbiden Ta */
    APP_Guti                  guti;        /* GUTI */
} APP_EMM_Info;

typedef struct {
    APP_MM_TimezoneUint8 posNegTimeZone;
    VOS_UINT8            timeZone;
    VOS_UINT8            rsv[2];
} APP_MM_CnTimezone;

typedef struct {
    APP_MM_CnTimezone timeZone;
    VOS_UINT8         year;
    VOS_UINT8         month;
    VOS_UINT8         day;
    VOS_UINT8         hour;
    VOS_UINT8         minute;
    VOS_UINT8         second;
    VOS_UINT8         rsv[2];
} APP_MM_CnTimezoneUnitime;

typedef struct {
    VOS_UINT8 msgLen; /* ??????????TextString?????? */
    VOS_UINT8 codingScheme;
    VOS_UINT8 addCi;
    VOS_UINT8 numOfSpareInLastByte;
    VOS_UINT8 msg[APP_MM_CN_NAME_MAX_LEN];
    VOS_UINT8 rsv;
} APP_MM_CnNetworkName;
/* add end */
/*
 * ????????:
 *     ucSplitPgCode:???????? [0,98]
 *     ucPsDrxLen:????????(0,6,7,8,9),????0:????UE??????DRX Cycle Len
 *     ucSplitOnCcch:????????0 ???? 1
 *     ucNonDrxTimer:????????[0,7]
 */
typedef struct {
    VOS_UINT8 splitPgCode; /* SPLIT PG CYCLE CODE */
    VOS_UINT8 psDrxLen;    /* DRX length         */
    VOS_UINT8 splitOnCcch; /* SPLIT on CCCH      */
    VOS_UINT8 nonDrxTimer; /* non-DRX timer      */
} APP_DRX;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
} APP_MM_StartReq;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt;
} APP_MM_StartCnf;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
} APP_MM_StopReq;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt;
} APP_MM_StopCnf;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32              opId;
    APP_MM_AttachTypeUint32 attachType; /* ???????? */
} APP_MM_AttachReq;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER

    VOS_UINT32 opId;
    VOS_UINT32 rslt;
} APP_MM_AttachCnf;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32              opId;
    VOS_UINT32              rslt;
    APP_MM_AttachTypeUint32 attachType; /* ????????       */
} APP_MM_AttachInd;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32              opId;
    APP_MM_DetachTypeUint32 detachType;
} APP_MM_DetachReq;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt;
} APP_MM_DetachCnf;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32                opId;
    APP_MM_DetachEntityUint32 detEntityType;
} APP_MM_DetachInd;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER

    VOS_UINT32                 opId;
    APP_REG_StatUint32         regStat;
    APP_MM_ServiceDomainUint32 srvDomain;
    APP_PH_RaModeUint32        accessMode; /* ???????? */
    APP_PlmnId                 plmnId;     /* PLMN ID  */
    APP_TAC                    tac;
    VOS_UINT32                 cellId;
} APP_MM_RegStatInd;

/* ========== ??????????????  ???????? ========== */

typedef struct {
    VOS_UINT8 bitOpAttach;
    VOS_UINT8 bitOpRsv[3];

    VOS_UINT8 attachAtmNum;
    VOS_UINT8 rsv[3];
} APP_MM_OptAttempNum;

/* ========== ??????????????  ???????? ======================================== */

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */

    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt;
} APP_MM_SetCmdCnf;

/* ========== ??????????????     ???????? ========== */

typedef VOS_UINT32 DT_CMD_Uint32;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */

    APP_MSG_HEADER
    VOS_UINT32 opId;

    DT_CmdUint8 cmd;
    VOS_UINT8         rsv[3];
    VOS_UINT32        rptPeriod;
} APP_MM_InqCmdReq;

typedef APP_MM_InqCmdReq APP_MM_InqUeModeReq;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32                    opId;
    VOS_UINT32                    rslt;               /* 0??????1???? */
    NAS_LMM_UeOperationModeUint32 currentUeMode;      /* ????UE???? */
    VOS_UINT32                    supportModeCnt;     /* UE???????????????????? */
    NAS_LMM_UeOperationModeUint32 supportModeList[4]; /* UE?????????????? */
} APP_MM_InqUeModeCnf;

typedef APP_MM_InqCmdReq APP_MM_InqLteCsReq;

typedef struct {
    VOS_UINT8 smsOverSgs;
    VOS_UINT8 smsOverIms;
    VOS_UINT8 csfb;
    VOS_UINT8 srvcc;
    VOS_UINT8 volga;
    VOS_UINT8 rsv[3];
} APP_MM_LteCsInfo;

typedef struct {
    VOS_MSG_HEADER
    VOS_UINT32 msgId;
    APP_MSG_HEADER
    VOS_UINT32       opId;
    VOS_UINT32       rslt; /* 0??????1???? */
    APP_MM_LteCsInfo ltecsInfo;
} APP_MM_InqLteCsCnf;

/* DT begin */
typedef APP_MM_InqCmdReq APP_MM_InqLteGutiReq;

/* V7R2-DT ,2014/4/23,CNF ????????????????IND????, begin */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt; /* 0??????1???? */
} APP_MM_InqLteGutiCnf;
/* V7R2-DT ,2014/4/23,CNF ????????????????IND????, end */

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    APP_Guti   guti; /* GUTI???? */
} APP_MM_InqLteGutiInd;

typedef APP_MM_InqCmdReq APP_MM_InqImsiReq;

typedef struct {
    VOS_UINT8 imsiLen;                    /* IMSI???? */
    VOS_UINT8 imsi[APP_EMM_IMSI_MAX_LEN]; /* IMSI???? */
} NAS_OM_ImsiInfo;

/* V7R2-DT ,2014/4/25, begin */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt; /* 0??????1???? */
} APP_MM_InqImsiCnf;
/* V7R2-DT ,2014/4/25, end */

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32      opId;
    NAS_OM_ImsiInfo imsi; /* IMSI???? */
} APP_MM_InqImsiInd;

typedef APP_MM_InqCmdReq APP_MM_InqEmmStateReq;

typedef struct {
    APP_EMM_MainStateUint16 mainState; /* EMM?????? */
    APP_EMM_SubStateUint16  subState;  /* EMM?????? */
    VOS_UINT16              staTid;    /* ?????????? */
    VOS_UINT8               rsv[2];
} NAS_OM_EmmState;

/* V7R2-DT ,2014/4/23,CNF ????????????????IND????, begin */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt; /* 0??????1???? */
} APP_MM_InqEmmStateCnf;
/* V7R2-DT ,2014/4/23, CNF ????????????????IND????,end */

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32      opId;
    NAS_OM_EmmState emmState; /* EMM???????? */
} APP_MM_InqEmmStateInd;

/* DT end */
/* Added for DT report, 2018-11-21, begin */
typedef APP_MM_InqCmdReq APP_MM_InqEmmReqStateReq;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt; /* 0??????1???? */
} APP_MM_InqEmmRegStateCnf;
/* Added for DT report, 2018-11-21, end */

typedef struct {
    APP_MM_MsgTypeUint32 msgId; /* _H2ASN_MsgChoice_Export APP_MM_MsgTypeUint32  */
    VOS_UINT8            msg[4];
    /* _H2ASN_MsgChoice_When_Comment          APP_MM_MSG_TYPE_ENUM_UINT32 */
} APP_MM_InterfaceMsgData;
/* _H2ASN_Length UINT32 */

typedef struct {
    VOS_MSG_HEADER
    APP_MM_InterfaceMsgData stMsgData;
} APP_MM_InterfaceMsg;

/* add for ue cap display, 2017-02-03, begin */
/* ????????: HIDS????LNAS??IMSA????UE???????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT8  rsv[32]; /* ???? */
} APP_MM_UeCapInfoReq;

/* ????????: LNAS????UE???????????????? */
typedef struct {
    VOS_UINT8                     ueNetCap[NAS_MM_MAX_UE_NET_CAP_LEN]; /* UE NETWORK CAPABILITY */
    VOS_UINT8                     rsv[35];                             /* ????,????4????????    */
    NAS_EMM_UsageSettingUint32    usageSetting;                        /* UE CENTER             */
    NAS_LMM_VoiceDomainUint32     voiceDomain;                         /* VOICE DOMAIN          */
    NAS_LMM_CsServiceUint32       csService;                           /* CS SERVICE            */
    NAS_LMM_UeOperationModeUint32 lteUeMode;                           /* CS/PS MODE            */
} LNAS_APP_UeCapInfo;

/* ????????: IMSA????UE?????????? */
typedef struct {
    VOS_UINT8 lteImsSupportFlag;         /**< LTE IMS??????,  1 :??????0 :?????? */
    VOS_UINT8 voiceCallOnImsSupportFlag; /**< IMS??????????,  1 :??????0 :?????? */
    VOS_UINT8 videoCallOnImsSupportFlag; /**< IMS??????????,  1 :??????0 :?????? */
    VOS_UINT8 smsOnImsSupportFlag;       /**< IMS??????????,  1 :??????0 :?????? */
    VOS_UINT8 srvccOnImsSupportFlag;     /**< IMS Srvcc??????,1 :??????0 :?????? */
    VOS_UINT8 amrWbSupportFlag;          /**< AMR WB??????,   1 :??????0 :?????? */
    VOS_UINT8 ir92ComplianceFlag;        /**< IR.92????????,  1 :??????0 :?????? */
    VOS_UINT8 rsv[33];                   /**< ????,????4????????                 */
} IMSA_APP_UeCapInfo;

/* ????????: ????HIDS????UE????????????????--????LNAS??IMSA??UE???? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32         opId;
    VOS_UINT32         opLnasUeCap : 1; /* ????LNAS UE??????????????????, 1:????????; 0:???????? */
    VOS_UINT32         opImsaUeCap : 1; /* ????IMSA UE??????????????????, 1:????????; 0:???????? */
    VOS_UINT32         opRsv : 30;
    LNAS_APP_UeCapInfo lnasUeCapInfo; /* LNAS????UE???????? */
    IMSA_APP_UeCapInfo imsaUeCapInfo; /* IMSA????HIDS??????UE???? */
} MM_APP_UeCapInfoCnf;
/* add for ue cap display, 2017-02-03, end */

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of app_lmm_interface.h */
