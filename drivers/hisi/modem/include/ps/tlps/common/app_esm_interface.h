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

#ifndef __APP_ESM_INTERFACE_H__
#define __APP_ESM_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "app_nas_comm.h"
#include "app_rrc_interface.h"
#include "nas_comm_packet_ser.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/* IP?????????????? */
#define APP_MAX_IPV4_ADDR_LEN 4
#define APP_MAX_IPV6_ADDR_LEN 16
#define APP_ESM_PCSCF_ADDR_MAX_NUM 8

/* Added 2016-06-20,Begin */
#define APP_MAX_IPV6_PREFIX_LEN 8
/* Added 2016-06-20,End */

#define APP_ESM_MAX_IPV6_PREFIX_NUM 6
#define APP_ESM_IPV6_ADDR_LEN 16

#define APP_ESM_MAX_LENGTH_OF_APN 100

#define APP_MAX_APN_LEN 99
#define APP_ESM_MAX_EPSB_NUM 11 /* ?????????? */
#define APP_ESM_MAX_ACCESS_NUM_LEN 32

/* ??????at????????AT^AUTHDATA??????????????????????99 */
#define APP_ESM_MAX_USER_NAME_LEN 99
#define APP_ESM_MAX_PASSWORD_LEN 99

#define APP_ESM_MAX_SDF_PF_NUM 16

/* APP->SM Command??????3???????????? APP->SM */
#define APP_ESM_MSG_ID_HEADER PS_MSG_ID_APP_TO_ESM_BASE

/* SM->APP Command??????3???????????? SM->APP */
#define ESM_APP_MSG_ID_HEADER PS_MSG_ID_ESM_TO_APP_BASE

#define APP_ESM_PPP_CHAP_CHALLNGE_LEN 16
#define APP_ESM_PPP_CHAP_CHALLNGE_NAME_LEN 16
#define APP_ESM_PPP_CHAP_RESPONSE_LEN 16

#define APP_ESM_PPP_MAX_USERNAME_LEN 99
#define APP_ESM_PPP_MAX_PASSWORD_LEN 99

#define APP_ESM_TFT_MAX_PF_NUM 16

/* DT begin */
#define APP_ESM_DT_REPORT_STATUS_OPEN 1
#define APP_ESM_DT_REPORT_STATUS_CLOSE 0
/* DT end */

/* moded for verizon band13 pco requirement 2017-03-25, begin */
#define APP_ESM_MAX_CUSTOM_PCO_CONTAINER_NUM 3
#define APP_ESM_MAX_CUSTOM_PCO_CONTAINER_CONTENT_LEN 53
/* moded for verizon band13 pco requirement 2017-03-25, end */
/* added for Band13 R1 PHASE1, 2017-10-20, begin */
#define APP_ESM_MAX_VZW_APN_INFO_NUM 8
/* added for Band13 R1 PHASE1, 2017-10-20, end */
/* added for R1 DATA DEVICE PHASE1, 2017-12-13, begin */
#define APP_ESM_MAX_IPV4_EPDG_NUM 2
#define APP_ESM_MAX_IPV6_EPDG_NUM 2
/* added for R1 DATA DEVICE PHASE1, 2017-12-13, end */

/* ????????: APP??SM???????? */
enum APP_ESM_MsgType {
    /* ???????????? */
    ID_APP_ESM_SET_TFT_REQ = 0x01 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetTftReq */
    ID_APP_ESM_SET_TFT_CNF = 0x02 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetTftCnf */

    ID_APP_ESM_SET_QOS_REQ = 0x03 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetQosReq */
    ID_APP_ESM_SET_QOS_CNF = 0x04 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetQosCnf */

    ID_APP_ESM_SET_EPS_QOS_REQ = 0x05 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetEpsQosReq */
    ID_APP_ESM_SET_EPS_QOS_CNF = 0x06 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetEpsQosCnf */

    ID_APP_ESM_SET_APN_REQ = 0x07 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetApnReq */
    ID_APP_ESM_SET_APN_CNF = 0x08 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetApnCnf */

    ID_APP_ESM_SET_PCO_REQ = 0x09 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetPcoReq */
    ID_APP_ESM_SET_PCO_CNF = 0x0A + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetPcoCnf */

    ID_APP_ESM_SET_PDN_TYPE_REQ = 0x0B + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetPdnTypeReq */
    ID_APP_ESM_SET_PDN_TYPE_CNF = 0x0C + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetPdnTypeCnf */

    ID_APP_ESM_SET_BEARER_TYPE_REQ = 0x0D + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetBearerTypeReq */
    ID_APP_ESM_SET_BEARER_TYPE_CNF = ESM_APP_MSG_ID_HEADER + 0x0E, /* _H2ASN_MsgChoice  APP_ESM_SetBearerTypeCnf */

    ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ = 0x0F + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_SetPdpManagerTypeReq */
    ID_APP_ESM_SET_PDP_MANAGER_TYPE_CNF = 0x10 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_SetPdpManagerTypeCnf */

    ID_APP_ESM_SET_GW_AUTH_REQ = 0x11 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetGwAuthReq */
    ID_APP_ESM_SET_GW_AUTH_CNF = 0x11 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetGwAuthCnf */
    /* modify begin */
    ID_APP_ESM_IPV6_INFO_NOTIFY = 0x12 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_Ipv6InfoNotify */

    ID_APP_ESM_PROCEDURE_ABORT_NOTIFY = 0x13 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_ProcedureAbortNotify */
    /* modify end */

    /* begin 2013-05-29 Modify L4A */
    ID_APP_ESM_NDISCONN_REQ = 0x14 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_NdisconnReq */
    ID_APP_ESM_NDISCONN_CNF = 0x12 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_NdisconnCnf */

    ID_APP_ESM_SET_CGDCONT_REQ = 0x15 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetCgdcontReq */
    ID_APP_ESM_SET_CGDCONT_CNF = 0x13 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_SetCgdcontCnf */
    /* end 2013-05-29 Modify L4A */
    /* added for Band13 R1 PHASE1, 2017-10-20, begin */
    ID_APP_ESM_APN_ENABLE_INFO_CHANGE_NTF = 0x16 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_ApnEnableInfoChangeNtf */
    /* added for Band13 R1 PHASE1, 2017-10-20, end */
    /* Added for R1 e911, 2017-12-6, begin */
    ID_APP_ESM_SET_APN_THROT_INFO_REQ = 0x17 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_SetApnThrotInfoReq */
    ID_APP_ESM_SET_APN_THROT_INFO_CNF = 0x14 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_SetApnThrotInfoCnf */
    /* Added for R1 e911, 2017-12-6, end */

    ID_APP_ESM_SET_ROAMING_PDN_TYPE_REQ = 0x18 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_SetRoamingPdnTypeReq */
    ID_APP_ESM_SET_ROAMING_PDN_TYPE_CNF = 0x15 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_SetRoamingPdnTypeCnf */

    /* ???????????? */
    ID_APP_ESM_INQ_TFT_REQ = 0x31 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqTftReq */
    ID_APP_ESM_INQ_TFT_CNF = 0x32 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqTftCnf */

    ID_APP_ESM_INQ_QOS_REQ = 0x33 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqQosReq */
    ID_APP_ESM_INQ_QOS_CNF = 0x34 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqQosCnf */

    ID_APP_ESM_INQ_EPS_QOS_REQ = 0x35 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqEpsQosReq */
    ID_APP_ESM_INQ_EPS_QOS_CNF = 0x36 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqEpsQosCnf */

    ID_APP_ESM_INQ_APN_REQ = 0x37 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqApnReq */
    ID_APP_ESM_INQ_APN_CNF = 0x38 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqApnCnf */

    ID_APP_ESM_INQ_PCO_REQ = 0x39 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqPcoReq */
    ID_APP_ESM_INQ_PCO_CNF = 0x3A + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqPcoCnf */

    ID_APP_ESM_INQ_PDN_TYPE_REQ = 0x3B + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqPdnTypeReq */
    ID_APP_ESM_INQ_PDN_TYPE_CNF = 0x3C + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqPdnTypeCnf */

    ID_APP_ESM_INQ_BEARER_TYPE_REQ = 0x3D + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqBearerTypeReq */
    ID_APP_ESM_INQ_BEARER_TYPE_CNF = ESM_APP_MSG_ID_HEADER + 0x3E, /* _H2ASN_MsgChoice  APP_ESM_InqBearerTypeCnf */

    ID_APP_ESM_INQ_PDP_MANAGER_TYPE_REQ = 0x3F + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_InqPdpManagerTypeReq */
    ID_APP_ESM_INQ_PDP_MANAGER_TYPE_CNF = 0x40 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_InqPdpManagerTypeCnf */

    ID_APP_ESM_INQ_BEAER_QOS_REQ = 0x41 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqBeaerQosReq */
    ID_APP_ESM_INQ_BEAER_QOS_CNF = 0x42 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqBeaerQosCnf */
    ID_APP_ESM_INQ_BEAER_QOS_IND = 0x43 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqBeaerQosInd */

    ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ = 0x44 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_InqDynamicPdpContReq */
    ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF = 0x45 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_InqDynamicPdpContCnf */

    ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ = 0x46 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_InqDynamicEpsQosReq */
    ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF = 0x47 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_InqDynamicEpsQosCnf */

    ID_APP_ESM_INQ_DYNAMIC_TFT_REQ = 0x48 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqDynamicTftReq */
    ID_APP_ESM_INQ_DYNAMIC_TFT_CNF = 0x49 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqDynamicTftCnf */

    ID_APP_ESM_INQ_GW_AUTH_REQ = 0x4A + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqGwAuthReq */
    ID_APP_ESM_INQ_GW_AUTH_CNF = 0x4A + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqGwAuthCnf */

    /* V7R2-DT PDP   2014/03/21  start */
    /* DT begin */
    ID_APP_ESM_DT_INQ_PDP_INFO_REQ = 0x4B + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqPdpInfoReq */
    ID_APP_ESM_DT_INQ_PDP_INFO_CNF = 0x4B + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqPdpInfoCnf */
    ID_APP_ESM_DT_INQ_PDP_INFO_IND = 0x4C + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_InqPdpInfoInd */
    /* DT end */
    /* V7R2-DT PDP   2014/03/21  end */

    ID_ESM_DSM_NOTIFICATION_IND = 0x4D + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice ESM_DSM_NotificationInd */
    ID_ESM_DSM_REG_CID_IND      = 0x4E + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice ESM_DSM_RegCidInd */
    /* ???????????????????????????????? */
    ID_APP_ESM_PDP_SETUP_REQ = 0x61 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpSetupReq */
    ID_APP_ESM_PDP_SETUP_CNF = 0x62 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpSetupCnf */
    ID_APP_ESM_PDP_SETUP_IND = 0x63 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpSetupInd */

    ID_APP_ESM_PDP_MODIFY_REQ = 0x64 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpModifyReq */
    ID_APP_ESM_PDP_MODIFY_CNF = 0x65 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpModifyCnf */
    ID_APP_ESM_PDP_MODIFY_IND = 0x66 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpModifyInd */

    ID_APP_ESM_PDP_RELEASE_REQ = 0x67 + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpReleaseReq */
    ID_APP_ESM_PDP_RELEASE_CNF = 0x68 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpReleaseCnf */
    ID_APP_ESM_PDP_RELEASE_IND = 0x69 + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpReleaseInd */

    ID_APP_ESM_PDP_MANAGER_IND = 0x6A + ESM_APP_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpManagerInd */
    ID_APP_ESM_PDP_MANAGER_RSP = 0x6B + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice  APP_ESM_PdpManagerRsp */

    ID_APP_ESM_NR_HANDOVER_TO_LTE_IND = 0x6C + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_NrHandoverToLteInd */
    /* Added for HO ATTACH, 2018-12-15 begin */
    ID_APP_ESM_SYNC_BEARER_INFO_NTF = 0x6D + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APP_ESM_SyncBearerInfoNotify */
    /* Added for HO ATTACH, 2018-12-15 end */

    ID_APS_ESM_LOCAL_RELEASE_NTF = 0x6E + APP_ESM_MSG_ID_HEADER, /* _H2ASN_MsgChoice APS_ESM_LocalReleaseNotify */

    ID_APP_ESM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_MsgTypeUint32;

/* ????????: ???????????????? */
enum APP_ESM_ParaSet {
    APP_ESM_PARA_SETTING = 0x00,
    APP_ESM_PARA_DELETE  = 0x01,
    APP_ESM_PARA_BUTT
};
typedef VOS_UINT32 APP_ESM_ParaSetUint32;

/* ????????: ???????????????? */
enum APP_ESM_ParaSetResult {
    APP_ESM_PARA_SET_SUCCESS = 0x00,
    APP_ESM_PARA_SET_FAIL    = 0x01,
    APP_ESM_PARA_SET_BUTT
};
typedef VOS_UINT32 APP_ESM_ParaSetResultUint32;

/* ????????: ???????????? */
enum APP_ESM_BearerState {
    APP_ESM_BEARER_STATE_INACTIVE  = 0x00,
    APP_ESM_BEARER_STATE_ACTIVATED = 0x01,
    APP_ESM_BEARER_STATE_BUTT
};
typedef VOS_UINT32 APP_ESM_BearerStateUint32;

/*
 * ????????  : SM????????
 */
typedef VOS_UINT32 APP_ESM_CauseUint32;

/* ????????: ???????????? */
enum APP_ESM_BearerType {
    APP_ESM_BEARER_TYPE_DEFAULT   = 0x00,
    APP_ESM_BEARER_TYPE_DEDICATED = 0x01,
    APP_ESM_BEARER_TYPE_EMERGENCY = 0x02,
    APP_ESM_BEARER_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_BearerTypeUint32;

/* ????????: ???????????????? */
enum APP_ESM_BearerModify {
    APP_ESM_BEARER_MODIFY_TFT     = 0x00,
    APP_ESM_BEARER_MODIFY_QOS     = 0x01,
    APP_ESM_BEARER_MODIFY_TFT_QOS = 0x02,
    APP_ESM_BEARER_MODIFY_BUTT
};
typedef VOS_UINT32 APP_ESM_BearerModifyUint32;

/* ????????: ???????????????? */
enum APP_ESM_BearerActType {
    APP_ESM_BEARER_ACT_TYPE_ACTIVE = 0x00,
    APP_ESM_BEARER_ACT_TYPE_MODIFY = 0x01,
    APP_ESM_BEARER_ACT_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_BearerActTypeUint32;

/* ????????: ???????????????? */
enum APP_ESM_BearerActResult {
    APP_ESM_BEARER_ACT_ACCEPT = 0x00,
    APP_ESM_BEARER_ACT_REJ    = 0x01,
    APP_ESM_BEARER_ACT_BUTT
};
typedef VOS_UINT32 APP_ESM_BearerActResultUint32;

/* ????????: ???????????????? */
enum APP_ESM_AnswerMode {
    APP_ESM_ANSWER_MODE_AUTO = 0x00,
    APP_ESM_ANSWER_MODE_MANI = 0x01,
    APP_ESM_ANSWER_MODE_BUTT
};
typedef VOS_UINT32 APP_ESM_AnswerModeUint32;

/* ????????: ???????????????? */
enum APP_ESM_AnswerResult {
    APP_ESM_ANSWER_ACCEPT = 0x00,
    APP_ESM_ANSWER_REJ    = 0x01,
    APP_ESM_ANSWER_RESULT_BUTT
};
typedef VOS_UINT32 APP_ESM_AnswerResultUint32;

/* ????????: PDN???????? */
enum APP_ESM_PdnType {
    APP_ESM_PDN_TYPE_IPV4      = 0x01, /* ????????24301 9.9.4.10???? */
    APP_ESM_PDN_TYPE_IPV6      = 0x02,
    APP_ESM_PDN_TYPE_IPV4_IPV6 = 0x03,
    APP_ESM_PDN_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_PdnTypeUint32;

/* Modify for CL multimode 2014-01-09 begin */
/* ????????: PDN???????????? 24008 10.5.6.17 */
enum APP_ESM_PdnRequestType {
    APP_ESM_PDN_REQUEST_TYPE_INITIAL  = 0x01, /* ????????????PDN???? */
    APP_ESM_PDN_REQUEST_TYPE_HANDOVER = 0x02, /* ????non-3GPP????????PDN???? */
    APP_ESM_PDN_REQUEST_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_PdnRequestTypeUint32;
/* Modify for CL multimode 2014-01-09 end */

/* ????????: CID???????? */
enum APP_ESM_CidType {
    APP_ESM_CID_TYPE_DEFAULT   = 0x00,
    APP_ESM_CID_TYPE_DEDICATED = 0x01,
    APP_ESM_CID_TYPE_EMERGENCY = 0x02,
    APP_ESM_CID_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_CidTypeUint32;

enum APP_ESM_TransferDirection {
    APP_ESM_TRANSFER_DIRECTION_PRE_REL7_TFT_FILTER = 0x00,
    APP_ESM_TRANSFER_DIRECTION_DOWNLINK            = 0x01,
    APP_ESM_TRANSFER_DIRECTION_UPLINK              = 0x02,
    APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK     = 0x03,
    APP_ESM_TRANSFER_DIRECTION_BUTT
};
typedef VOS_UINT8 APP_ESM_TransferDirectionUint8;

enum APP_ESM_BearerOperateType {
    APP_ESM_BEARER_OPERATE_TYPE_DEF_ACT  = 0x00,
    APP_ESM_BEARER_OPERATE_TYPE_DEDI_ACT = 0x01,
    APP_ESM_BEARER_OPERATE_TYPE_MODIFY   = 0x02,
    APP_ESM_BEARER_OPERATE_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_BearerOperateTypeUint32;

enum APP_ESM_Ipv4AddrAllocType {
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_NAS_SIGNALING = 0x00,
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_DHCP          = 0x01,

    APP_ESM_IPV4_ADDR_ALLOC_TYPE_BUTT
};
typedef VOS_UINT32 APP_ESM_Ipv4AddrAllocTypeUint32;

enum APP_ESM_PdpSetupType {
    APP_ESM_PDP_SETUP_TYPE_NORMAL = 0x00,
    APP_ESM_PDP_SETUP_TYPE_PPP    = 0x01,

    APP_ESM_PDP_SETUP_TYPE_BUTT = 0xFF
};
typedef VOS_UINT32 APP_ESM_PdpSetupTypeUint32;

/* Added for DATA RETRY PHASEIII, 2016-6-23, begin */
/* ????EAB??????????APP???????????????? */
enum APP_ESM_BearerPrio {
    APP_ESM_BEARER_PRIO_NORMAL = 0x00,
    APP_ESM_BEARER_PRIO_LOW    = 0x01,

    APP_ESM_BEARER_PRIO_BUTT
};
typedef VOS_UINT32 APP_ESM_BearerPrioUint32;
/* Added for DATA RETRY PHASEIII, 2016-6-23, end */

/*
 * ????????: Authentication Type
 */
enum APP_ESM_AuthType {
    APP_ESM_AUTH_TYPE_NONE = 0x00,
    APP_ESM_AUTH_TYPE_PAP  = 0x01,
    APP_ESM_AUTH_TYPE_CHAP = 0x02,

    APP_ESM_AUTH_TYPE_BUTT = 0xFF
};
typedef VOS_UINT8 APP_ESM_AuthTypeUint8;

enum APP_ESM_BearerManageType {
    APP_ESM_BEARER_MANAGE_TYPE_ACCEPT = 0, /* ???? */
    APP_ESM_BEARER_MANAGE_TYPE_REJ,        /* ???? */

    APP_ESM_BEARER_MANANGE_TYPE_BUTT
};
typedef VOS_UINT8 APP_ESM_BearerManageTypeUint8;

enum APP_ESM_BearerManageMode {
    APP_ESM_BEARER_MANAGE_MODE_AUTO = 0, /* ???? */
    APP_ESM_BEARER_MANAGE_MODE_MANUAL,   /* ???? */

    APP_ESM_BEARER_MANAGE_MODE_BUTT
};
typedef VOS_UINT8 APP_ESM_BearerManageModeUint8;

/* DT begin */
/* ????????: ???????????????????? */
enum NAS_ESM_DtBearerType {
    NAS_ESM_DT_BEARER_TYPE_DEFAULT = 0, /* ???????? */
    NAS_ESM_DT_BEARER_TYPE_DEDICATED,   /* ???????? */
    /* V7R2-DT ,2014/5/6, begin */
    NAS_ESM_DT_BEARER_TYPE_EMERGENCY, /* ???????? */
    /* V7R2-DT ,2014/5/6, end */

    NAS_ESM_DT_BEARER_TYPE_BUTT
}; /* ?????????? */
typedef VOS_UINT8 NAS_ESM_DtBearerTypeUint8;
/* DT end */

/* ims begin */
enum APP_ESM_PcscfDiscovery {
    APP_ESM_PCSCF_DISCOVERY_NOT_INFLUENCED  = 0x00,
    APP_ESM_PCSCF_DISCOVERY_THROUGH_NAS_SIG = 0x01,
    APP_ESM_PCSCF_DISCOVERY_THROUGH_DHCP    = 0x02,

    APP_ESM_PCSCF_DISCOVERY_BUTT
};
typedef VOS_UINT32 APP_ESM_PcscfDiscoveryUint32;

enum APP_ESM_ImsCnSigFlag {
    APP_ESM_PDP_NOT_FOR_IMS_CN_SIG_ONLY = 0x00,
    APP_ESM_PDP_FOR_IMS_CN_SIG_ONLY     = 0x01,

    APP_ESM_IMS_CN_SIG_FLAG_BUTT
};
typedef VOS_UINT32 APP_ESM_ImsCnSigFlagUint32;
/* ims end */

/* modify for 2014-05-09 begin */
enum APP_ESM_PdpEmcInd {
    APP_ESM_PDP_NOT_FOR_EMC = 0x00,
    APP_ESM_PDP_FOR_EMC     = 0x01,

    APP_ESM_PDP_EMC_IND_BUTT
};
typedef VOS_UINT32 APP_ESM_PdpEmcIndUint32;
/* modify for 2014-05-09 end */

/* Added for DATA RETRY PHASEI, 2016-03-21, Begin */
/* ????????: PDP???????? */
enum APP_ESM_PdpReleaseCause {
    APP_ESM_PDP_RELEASE_CAUSE_NORMAL               = 0,
    APP_ESM_PDP_RELEASE_CAUSE_IPV6_ADDR_ALLOC_FAIL = 1,
    /* Added for DATA RETRY PHASEIV, 2016-7-25, begin */
    APP_ESM_PDP_RELEASE_CAUSE_IPV6_ADDR_TIME_OUT = 2,
    /* Added for DATA RETRY PHASEIV, 2016-7-25, end */
    APP_ESM_PDP_RELEASE_CAUSE_PCSCF_ADDR_ALLOC_FAIL = 3,
    /* added for Band13 R1 PHASE1, 2017-10-20, begin */
    /* del reattach type */
    /* added for Band13 R1 PHASE1, 2017-10-20, end */

    /* Added for DCM DATA OFF, 2017-10-28, begin */
    APP_ESM_PDP_RELEASE_CAUSE_DATA_OFF = 4,
    /* Added for DCM DATA OFF, 2017-10-28, end */
    /* Added for 2018-1-8, begin */
    APP_ESM_PDP_RELEASE_CAUSE_CELLULAR2W_HO = 5,
    /* Added for 2018-1-8, end */

    APP_ESM_PDP_RELEASE_CAUSE_BUTT
};
typedef VOS_UINT8 APP_ESM_PdpReleaseCauseUint8;
/* Added for DATA RETRY PHASEI, 2016-03-21, End */

/* Added for DATA RETRY PHASEIV, 2016-7-25, begin */
/* added for Band13 R1 PHASE1, 2017-10-20, begin */
/* ????????: ??????????APN ???? */
enum APP_ESM_ApnType {
    APP_ESM_APN_TYPE_INVALID = 0x00,
    APP_ESM_APN_TYPE_CLASS1  = 0x01,
    APP_ESM_APN_TYPE_CLASS2  = 0x02,
    APP_ESM_APN_TYPE_CLASS3  = 0x03,
    APP_ESM_APN_TYPE_CLASS4  = 0x04,
    APP_ESM_APN_TYPE_CLASS5  = 0x05,
    APP_ESM_APN_TYPE_CLASS6  = 0x06,
    APP_ESM_APN_TYPE_CLASS7  = 0x07,
    APP_ESM_APN_TYPE_CLASS8  = 0x08,

    APP_ESM_APN_TYPE_BUTT
};
typedef VOS_UINT8 APP_ESM_ApnTypeUint8;
/* added for Band13 R1 PHASE1, 2017-10-20, end */
/* Added for DATA RETRY PHASEIV, 2016-7-25, begin */

/* ????????: SRVCC???????? */
enum ESM_DSM_NotificationIndType {
    ESM_DSM_NOTIFICATION_IND_SRVCC_HO_CANCELLED = 0,

    ESM_DSM_NOTIFICATION_IND_BUTT
};
typedef VOS_UINT32 ESM_DSM_NotificationIndTypeUint32;

/*
 * ????????: BEARER CONTROL MODE????
 */
enum APP_ESM_Bcm {
    APP_ESM_BCM_MS_ONLY = 0x01,
    APP_ESM_BCM_MS_NW   = 0x02,

    APP_ESM_BCM_BUTT
};
typedef VOS_UINT8 APP_ESM_BcmUint8;

/* ????????: ???????????? */
enum APP_ESM_HandoverResult {
    APP_ESM_HANDOVER_RESULT_SUCC = 0x00,
    APP_ESM_HANDOVER_RESULT_FAIL = 0x01,
    APP_ESM_HANDOVER_RESULT_BUTT
};
typedef VOS_UINT32 APP_ESM_HandoverResultUint32;

/* ????????: ???????????????? */
enum APS_ESM_LocalRelCause {
    /* ???????????????? */
    APS_ESM_LOCAL_REL_CAUSE_DEACT_TIMEOUT,
    /*
     * LTE/NR/EHRPD????????????????????????????1X/HRPD????????????????
     * LTE/NR????????????????????????????GU(??TI??)????????????????
     * GU????????????????????????????NR????????????????
     */
    APS_ESM_LOCAL_REL_CAUSE_MODE_CHANGE,
    /* ?????????????????? */
    APS_ESM_LOCAL_REL_CAUSE_DEDICATED_BEARER,
    /* ESM????APS?????????? */
    APS_ESM_LOCAL_REL_CAUSE_PARA_INVALID,
    /* APS????????????????????IDN?????????????????????? */
    APS_ESM_LOCAL_REL_CAUSE_APS_INTER_DEACT,
    /* APS????EHSM??????????????EHSM??????ESM????APS????ESM?????????? */
    APS_ESM_LOCAL_REL_CAUSE_EHSM_DEACT,

    APS_ESM_LOCAL_REL_CAUSE_BUTT
};
typedef VOS_UINT32 APS_ESM_LocalRelCauseUint32;

/* ???????????????? */
/* Added for DATA RETRY PHASEIV, 2016-7-25, begin */

/* Added for 5G Iteration 5, 2018-1-22, begin */
/*
 * ??????: ESM_DSM_NotificationInd
 * ????????: SRVCC????????
 */
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT32                        msgId;
    ESM_DSM_NotificationIndTypeUint32 notificationIndicator;
} ESM_DSM_NotificationInd;

/*
 * ????????: ESM -> DSM
 *           ??????????????SDF????CID??????DSM
 */
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT32 msgId;
    VOS_UINT32 regCid;
} ESM_DSM_RegCidInd;

/* moded for Band13 R1 PHASE1, 2017-10-16, begin */
/* ????????: ????APN???????? */
typedef struct {
    VOS_UINT32           cid;         /* CID [0,11] */
    APP_ESM_ApnTypeUint8 apnType;     /* apn class */
    VOS_UINT8            disableFlag; /* apn disable flag */
    VOS_UINT8            reserved[2];
    VOS_UINT32           inactivityTimerValue; /* Inactivity Timer Value in second */
} APP_ESM_ApnClassInfo;
/* moded for Band13 R1 PHASE1, 2017-10-16, end */
/* Added for DATA RETRY PHASEIV, 2016-7-25, end */

/* ????????: ?????????????????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;    /* ???????????? */
    VOS_UINT32 cid;     /* ????????????:0~31   */
    VOS_UINT32 setRslt; /* ????????????:0:????,1:????   */
} APP_ESM_ParaSetCnf;

/* begin for r11 2014-09-18 */
/* ????????: TFT  ???? */
typedef struct {
    VOS_UINT32 opRmtIpv4AddrAndMask : 1;
    VOS_UINT32 opRmtIpv6AddrAndMask : 1;
    VOS_UINT32 opProtocolId : 1;
    VOS_UINT32 opSingleLocalPort : 1;
    VOS_UINT32 opLocalPortRange : 1;
    VOS_UINT32 opSingleRemotePort : 1;
    VOS_UINT32 opRemotePortRange : 1;
    VOS_UINT32 opSecuParaIndex : 1;
    VOS_UINT32 opTypeOfService : 1;
    VOS_UINT32 opFlowLabelType : 1;
    /* begin for r11 2014-09-18 */
    VOS_UINT32 opLocalIpv4AddrAndMask : 1;
    VOS_UINT32 opLocalIpv6AddrAndMask : 1;
    /* end for r11 2014-09-18 */
    VOS_UINT32 opSpare : 20;

    VOS_UINT8                      packetFilterId;
    VOS_UINT8                      nwPacketFilterId;
    APP_ESM_TransferDirectionUint8 direction;
    VOS_UINT8                      precedence; /* packet filter evaluation precedence */

    VOS_UINT32 secuParaIndex; /* SPI */
    VOS_UINT16 singleLcPort;
    VOS_UINT16 lcPortHighLimit;
    VOS_UINT16 lcPortLowLimit;
    VOS_UINT16 singleRmtPort;
    VOS_UINT16 rmtPortHighLimit;
    VOS_UINT16 rmtPortLowLimit;
    VOS_UINT8  protocolId;    /* ?????? */
    VOS_UINT8  typeOfService; /* TOS */

    VOS_UINT8 typeOfServiceMask; /* TOS Mask */
    VOS_UINT8 reserved[1];

    VOS_UINT8 rmtIpv4Address[APP_MAX_IPV4_ADDR_LEN];
    /*
     * ucSourceIpAddress[0]??IP????????????
     * ucSourceIpAddress[3]??????????
     */
    VOS_UINT8 rmtIpv4Mask[APP_MAX_IPV4_ADDR_LEN];
    /*
     * ucSourceIpMask[0]??IP???????????? ,
     * ucSourceIpMask[3]??????????
     */
    VOS_UINT8 rmtIpv6Address[APP_MAX_IPV6_ADDR_LEN];
    /*
     * ucRmtIpv6Address[0]??IPv6????????????????
     * ucRmtIpv6Address[7]??IPv6????????????????
     */
    VOS_UINT8 rmtIpv6Mask[APP_MAX_IPV6_ADDR_LEN];
    /*
     * ucRmtIpv6Mask[0]??????????
     * ucRmtIpv6Mask[7]??????????
     */

    VOS_UINT32 flowLabelType; /* FlowLabelType */
    /* begin for r11 2014-09-18 */
    VOS_UINT8 localIpv4Addr[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 localIpv4Mask[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 localIpv6Addr[APP_MAX_IPV6_ADDR_LEN];
    VOS_UINT8 localIpv6Prefix;
    VOS_UINT8 reserved2[3];
    /* end for r11 2014-09-18 */
} APP_ESM_TftInfo;
/* end for r11 2014-09-18 */

/* ????????: TFT  ???????? */
typedef struct {
    VOS_MSG_HEADER               /* _H2ASN_Skip */
    VOS_UINT32            msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32            opId;       /* ???????????? */
    VOS_UINT32            cid;        /* ????????????:0~31       */
    APP_ESM_ParaSetUint32 setType;    /* ????????:0:????,1:???? */
    APP_ESM_TftInfo       appTftInfo; /* TFT???? */
} APP_ESM_SetTftReq;

typedef APP_ESM_ParaSetCnf APP_ESM_SetTftCnf;

/* ????????: QOS  ???? */
typedef struct {
    VOS_UINT8 delayClass;
    VOS_UINT8 reliabClass;
    VOS_UINT8 peakThrough;
    VOS_UINT8 precedenceClass;
    VOS_UINT8 meanThrough;
    VOS_UINT8 trafficClass;
    VOS_UINT8 deliverOrder;
    VOS_UINT8 deliverOfErrSdu;
    VOS_UINT8 maximSduSize;
    VOS_UINT8 maxBitRateForUp;
    VOS_UINT8 maxBitRateForDown;
    VOS_UINT8 residualBer;
    VOS_UINT8 sduErrRatio;
    VOS_UINT8 transDelay;
    VOS_UINT8 traffHandlPrior;
    VOS_UINT8 guarantBitRateForUp;
    VOS_UINT8 guarantBitRateForDown;
    VOS_UINT8 srcStatisticsDescriptor;
    VOS_UINT8 signallingIndication;
    VOS_UINT8 maxBitRateForDownExt;
    VOS_UINT8 guarantBitRateForDownExt;
    VOS_UINT8 maxBitRateForUpExt;
    VOS_UINT8 guarantBitRateForUpExt;
    /* begin for r11 2014-09-02 */
    VOS_UINT8 maxBitRateForDownExt2;
    VOS_UINT8 guarantBitRateForDownExt2;
    VOS_UINT8 maxBitRateForUpExt2;
    VOS_UINT8 guarantBitRateForUpExt2;
    /* end for r11 2014-09-02 */

    VOS_UINT8 reserved[1];
} APP_ESM_QosInfo;

/* ????????: QOS  ???????? */
typedef struct {
    VOS_MSG_HEADER               /* _H2ASN_Skip */
    VOS_UINT32            msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32            opId;
    VOS_UINT32            cid;        /* ????????????:0~31       */
    APP_ESM_ParaSetUint32 setType;    /* ????????:0:????,1:???? */
    APP_ESM_QosInfo       appQoSInfo; /* APP_ESM_QosInfo???????? */
} APP_ESM_SetQosReq;

typedef APP_ESM_ParaSetCnf APP_ESM_SetQosCnf;

/* ????????: EPS_QOS  ???? */
typedef struct {
    VOS_UINT8  qci;
    VOS_UINT8  rsv[3];
    VOS_UINT32 ulMaxRate;  /* ??????kbps */
    VOS_UINT32 dlMaxRate;  /* ??????kbps */
    VOS_UINT32 ulGMaxRate; /* ??????kbps */
    VOS_UINT32 dlGMaxRate; /* ??????kbps */
} APP_ESM_EpsQosInfo;

typedef struct {
    VOS_UINT32         epsbId;
    APP_ESM_EpsQosInfo qos;
} APP_EPS_Qos;

/* ????????: SDF QOS  ???????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    APP_ESM_ParaSetUint32 setType; /* 0:SET;1:DEL */
    APP_ESM_EpsQosInfo    sdfQosInfo;
} APP_ESM_SetEpsQosReq;

typedef APP_ESM_ParaSetCnf APP_ESM_SetEpsQosCnf;

/* ????????: APN  ???? */
typedef struct {
    VOS_UINT8 apnLen;
    VOS_UINT8 apnName[APP_MAX_APN_LEN];
} APP_ESM_ApnInfo;

/*
 * ????????: ????TS 24.008 section 10.5.6.1 APN??????????(??????)
 */
typedef struct {
    VOS_UINT8 length;      /* APN????    */
    VOS_UINT8 reserved[3]; /* ?????????? */
    VOS_UINT8 value[APP_ESM_MAX_LENGTH_OF_APN];
} APP_ESM_Apn;

/* ????????: APN  ???????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    APP_ESM_ParaSetUint32 setType; /* 0:SET;1:DEL */
    APP_ESM_ApnInfo       apnInfo;
} APP_ESM_SetApnReq;

typedef APP_ESM_ParaSetCnf APP_ESM_SetApnCnf;

/* Added for R1 e911, 2017-12-6, begin */
/* ????????: APN  ???????? */
typedef struct {
    APP_ESM_ApnInfo apnInfo;

    VOS_UINT32 waitTime;        /* ??PDN??????????????waittime????????????PDN??????????????:s */
    VOS_UINT32 pdnMaxConnTime;  /* ????????????????????????PDN??????????????????????????????????:s */
    VOS_UINT32 pdnMaxConnCount; /* ??????????????????????????????????????PDN?????????????? */

    VOS_UINT8            cid;
    APP_ESM_ApnTypeUint8 apnClassType;
    VOS_UINT8            rsv[2];
} APP_ESM_ExcessivePdnCtrlPara;

/* ????????: APN  ???????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER

    APP_ESM_ExcessivePdnCtrlPara excessivePdnCtrlPara;
} APP_ESM_SetApnThrotInfoReq;

/* ????????: APN  ???????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER

    VOS_UINT32 rslt;
} APP_ESM_SetApnThrotInfoCnf;

/* Added for R1 e911, 2017-12-6, end */
/* ????????: APN AMBR ???? */
typedef struct {
    VOS_UINT32 dlApnAmbr; /* ??????????,????KBPS */
    VOS_UINT32 ulApnAmbr; /* ??????????,????KBPS */
} APP_ESM_ApnAmbrInfo;

/* ????????: PCO  ???? */
typedef struct {
    VOS_UINT32 opApl : 1;
    VOS_UINT32 opCpol : 1;
    VOS_UINT32 opPcscfAddReq : 1;
    VOS_UINT32 opImcnFlag : 1;
    VOS_UINT32 opDnsAddrReq : 1;
    VOS_UINT32 opMsBearCtrlId : 1;
    VOS_UINT32 opPrefBearCtrlMode : 1;

    VOS_UINT32 opSpare : 25;

    VOS_UINT8  configProtocol;
    VOS_UINT8  bearMode; /* container identifier??Preferred Bearer Control Mode???????? */
    VOS_UINT8  reserved[2];
    VOS_UINT16 aplCid;  /* Additional parameters list??container identifier */
    VOS_UINT16 cpolPid; /* Configuration protocol options list??protocol identifier */
    VOS_UINT8  pppPacket[248];
} APP_ESM_PcoInfo;

/* ????????: PCO ???????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId; /* ???????????? */
    VOS_UINT32 cid;  /* ????????????:0~31       */

    APP_ESM_ParaSetUint32 setType;    /* ????????:0:????,1:???? */
    APP_ESM_PcoInfo       appPcoInfo; /* PCO???? */
} APP_ESM_SetPcoReq;

typedef APP_ESM_ParaSetCnf APP_ESM_SetPcoCnf;

/* ????????: PDN_TYPE ???????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32 opIpv4AddrAllocType : 1;
    VOS_UINT32 opSpare : 31;

    APP_ESM_ParaSetUint32           setType; /* 0:SET;1:DEL */
    APP_ESM_PdnTypeUint32           pdnType; /* 1:IPV4,2:IPV6,3:BOTH */
    APP_ESM_Ipv4AddrAllocTypeUint32 ipv4AddrAllocType;
} APP_ESM_SetPdnTypeReq;
typedef APP_ESM_ParaSetCnf APP_ESM_SetPdnTypeCnf;

/* ????????: BEARER_TYPE  ???????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32 opLinkdCid : 1;
    VOS_UINT32 opSpare : 31;

    APP_ESM_ParaSetUint32 setType;
    APP_ESM_CidTypeUint32 bearCidType;

    VOS_UINT32 linkdCid;
} APP_ESM_SetBearerTypeReq;

typedef APP_ESM_ParaSetCnf APP_ESM_SetBearerTypeCnf;

/* ????????: ????APP???????????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;

    APP_ESM_ParaSetUint32      setType;
    APP_ESM_AnswerModeUint32   ansMode; /* APP????????:0:????,1:???? */
    APP_ESM_AnswerResultUint32 ansType; /* APP????????:0:????,1:????,???????????????????? */
} APP_ESM_SetPdpManagerTypeReq;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 setRslt;
} APP_ESM_SetPdpManagerTypeCnf;

/* ????????: ???????????????????? */
typedef struct {
    APP_ESM_AuthTypeUint8 gwAuthType;

    VOS_UINT8 accNumLen;
    VOS_UINT8 rsv1[2];
    VOS_UINT8 accessNum[APP_ESM_MAX_ACCESS_NUM_LEN]; /* ?????????????????????? */
    VOS_UINT8 userNameLen;
    VOS_UINT8 rsv2[3];
    VOS_UINT8 userName[APP_ESM_MAX_USER_NAME_LEN + 1];
    VOS_UINT8 pwdLen;
    VOS_UINT8 rsv3[3];
    VOS_UINT8 pwd[APP_ESM_MAX_PASSWORD_LEN + 1];
} APP_ESM_GwAuthInfo;

/* ????????: APP??ESM ??????SDF?????????????? */
typedef struct {
    VOS_UINT32 opPdnType : 1;
    VOS_UINT32 opApn : 1;
    VOS_UINT32 opSdfQos : 1;
    VOS_UINT32 opLinkdCid : 1;
    VOS_UINT32 opIpv4AddrAllocType : 1;
    VOS_UINT32 opGwAuthInfo : 1;
    /* ims begin */
    VOS_UINT32 opPcscfDiscovery : 1;
    VOS_UINT32 opImsCnSignalFlag : 1;
    VOS_UINT32 opRoamPdnTypeFlag : 1;
    VOS_UINT32 opSpare : 23;
    /* ims end */

    APP_ESM_PdnTypeUint32           pdnType;
    APP_ESM_PdnTypeUint32           roamPdnType;
    APP_ESM_Ipv4AddrAllocTypeUint32 ipv4AddrAllocType;
    APP_ESM_BearerTypeUint32        bearerCntxtType; /* SM???????????????????? */

    VOS_UINT32 cid;      /* ??????????ID */
    VOS_UINT32 linkdCid; /* ????CID */

    VOS_UINT32         pfNum;
    APP_ESM_EpsQosInfo sdfQosInfo;
    APP_ESM_ApnInfo    apnInfo;
    APP_ESM_GwAuthInfo gwAuthInfo;
    APP_ESM_TftInfo    cntxtTftInfo[APP_ESM_MAX_SDF_PF_NUM];
    /* ims begin */
    APP_ESM_PcscfDiscoveryUint32 pcscfDiscovery;
    APP_ESM_ImsCnSigFlagUint32   imsCnSignalFlag;
    /* ims end */
} APP_ESM_SdfPara;

/*lint -save -e959*/
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    APP_ESM_ParaSetUint32 setType;
    APP_ESM_GwAuthInfo    gwAuthInfo;
} APP_ESM_SetGwAuthReq;
/*lint -restore*/

typedef APP_ESM_ParaSetCnf APP_ESM_SetGwAuthCnf;

/* ???????????????? */
/* ????????: ???????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
} APP_ESM_InqParaReq;

typedef APP_ESM_InqParaReq APP_ESM_InqTftReq;

/* ????????: ????????:TFT */
typedef struct {
    VOS_MSG_HEADER         /* _H2ASN_Skip */
    VOS_UINT32      msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32      opId;
    VOS_UINT32      cid;
    VOS_UINT32      rslt;
    VOS_UINT32      pfNum; /* ??????PF?? */
    APP_ESM_TftInfo pfInfo[APP_ESM_TFT_MAX_PF_NUM];
} APP_ESM_InqTftCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqQosReq;

/* ????????: ????????:QOS */
typedef struct {
    VOS_MSG_HEADER         /* _H2ASN_Skip */
    VOS_UINT32      msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32      opId;
    VOS_UINT32      cid;
    VOS_UINT32      rslt;
    APP_ESM_QosInfo stAppQoSInfo; /* APP_ESM_QosInfo???????? */
} APP_ESM_InqQosCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqPcoReq;

/* ????????: ????????:PCO */
typedef struct {
    VOS_MSG_HEADER         /* _H2ASN_Skip */
    VOS_UINT32      msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32      opId;
    VOS_UINT32      cid;
    VOS_UINT32      rslt;
    APP_ESM_PcoInfo appPcoInfo; /* PCO???? */
} APP_ESM_InqPcoCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqBearerTypeReq;

/* ????????: ????????:BEARER_TYPE */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 opLinkdCid : 1;
    VOS_UINT32 opSpare : 31;

    VOS_UINT32            rslt;
    APP_ESM_CidTypeUint32 bearCidType;
    VOS_UINT32            linkdCid; /* ??????????CID */
} APP_ESM_InqBearerTypeCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqPdnTypeReq;

/* ????????: ????????:PDN_TYPE */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32 opIpv4AddrAllocType : 1;
    VOS_UINT32 opSpare : 31;

    VOS_UINT32                      rslt;
    APP_ESM_PdnTypeUint32           pdnType; /* 1:IPV4,2:IPV6,3:BOTH */
    APP_ESM_Ipv4AddrAllocTypeUint32 ipv4AddrAllocType;
} APP_ESM_InqPdnTypeCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqApnReq;

/* ????????: ????????:APN */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32      rslt;
    APP_ESM_ApnInfo apnInfo;
} APP_ESM_InqApnCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqEpsQosReq;

/* ????????: ????????:SDF QOS */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 rslt;

    APP_ESM_EpsQosInfo sdfQosInfo;
} APP_ESM_InqEpsQosCnf;

/* ????????: ????????:BEARER_MANAGER_TYPE */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
} APP_ESM_InqPdpManagerTypeReq;

/* ????????: ????????:BEARER_MANAGER_TYPE */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;

    VOS_UINT32                 rslt;
    APP_ESM_AnswerModeUint32   ansMode; /* APP????????:0:????,1:???? */
    APP_ESM_AnswerResultUint32 ansType; /* APP????????:0:????,1:????,???????????????????? */
} APP_ESM_InqPdpManagerTypeCnf;

/* ????????: ????????:BEARER_QOS */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */

    APP_MSG_HEADER
    VOS_UINT32 epsbId;
} APP_ESM_InqBeaerQosReq;

/* ????????: ????????:BEARER_QOS */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */

    APP_MSG_HEADER
    VOS_UINT32                 epsbIdNum;
    APP_EPS_Qos                qosInfo[APP_ESM_MAX_EPSB_NUM];
    APP_ESM_AnswerResultUint32 ansType;
} APP_ESM_InqBeaerQosCnf;

typedef struct {
    VOS_MSG_HEADER            /* _H2ASN_Skip */
    VOS_UINT32         msgId; /* _H2ASN_Skip */

    APP_MSG_HEADER
    VOS_UINT32         epsbId;
    APP_ESM_EpsQosInfo qosInfo;
} APP_ESM_InqBeaerQosInd;

typedef APP_ESM_InqParaReq APP_ESM_InqDynamicPdpContReq;

/* ????????: IP???????????? */
typedef struct {
    VOS_UINT8 ipType;
    VOS_UINT8 reserved[3];
    VOS_UINT8 ipv4Addr[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 ipv6Addr[APP_MAX_IPV6_ADDR_LEN];
} APP_ESM_IpAddr;

/* ????????: ????????:????PDP?????????? */
typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
        VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32 opPdnAddr : 1;
    VOS_UINT32 opApn : 1;
    VOS_UINT32 opLinkCid : 1;
    VOS_UINT32 opDnsPrim : 1;
    VOS_UINT32 opDnsSec : 1;
    VOS_UINT32 opPcscfPrim : 1;
    VOS_UINT32 opPcscfSec : 1;
    VOS_UINT32 opGateWayAddrInfo : 1;
    /* ims begin */
    VOS_UINT32 opImsCnSignalFlag : 1;
    /* ims end */
    /* Modified for IPV4 MTU, 2016-11-15, Begin */
    VOS_UINT32 opIpv4Mtu : 1;
    VOS_UINT32 opSpare : 22;
    /* Modified for IPV4 MTU, 2016-11-15, End */

    VOS_UINT32      rslt;
    VOS_UINT32      epsbId;
    APP_ESM_IpAddr  pdnAddrInfo;
    APP_ESM_IpAddr  subnetMask;
    APP_ESM_IpAddr  gateWayAddrInfo;
    APP_ESM_IpAddr  dnsPrimAddrInfo;   /* ??DNS???? */
    APP_ESM_IpAddr  dnsSecAddrInfo;    /* ??DNS???? */
    APP_ESM_IpAddr  pcscfPrimAddrInfo; /* ??P-CSCF???? */
    APP_ESM_IpAddr  pcscfSecAddrInfo;  /* ??P-CSCF???? */
    APP_ESM_ApnInfo apnInfo;
    VOS_UINT32      linkCid;
    /* ims begin */
    APP_ESM_ImsCnSigFlagUint32 imsCnSignalFlag;
    /* ims end */
    /* Added for IPV4 MTU, 2016-11-15, Begin */
    VOS_UINT16 ipv4Mtu;
    VOS_UINT8  reserved[2];
    /* Added for IPV4 MTU, 2016-11-15, End */
} APP_ESM_InqDynamicPdpContCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqDynamicEpsQosReq;

/* ????????: ????????:????EPS QoS???? */
typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
        VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32         rslt;
    APP_ESM_EpsQosInfo sdfQosInfo;
} APP_ESM_InqDynamicEpsQosCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqDynamicTftReq;

/* ????????: ????????:????TFT???? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32      rslt;
    VOS_UINT32      pfNum; /* ??????PF?? */
    APP_ESM_TftInfo pfInfo[APP_ESM_TFT_MAX_PF_NUM];
} APP_ESM_InqDynamicTftCnf;

typedef APP_ESM_InqParaReq APP_ESM_InqGwAuthReq;

/* ????????: ????????:???????????? */
/*lint -save -e959*/
typedef struct {
    VOS_MSG_HEADER            /* _H2ASN_Skip */
    VOS_UINT32         msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32         opId;
    VOS_UINT32         cid;
    VOS_UINT32         rslt;
    APP_ESM_GwAuthInfo gwAuthInfo;
} APP_ESM_InqGwAuthCnf;
/*lint -restore*/

/* ?????????????????? */
/*
 * ????????: The struct contains the parameter of CHAP.
 *           challengeLen     - Length of username
 *           achallenge       - Array of challenge
 *           challengeNameLen - Length of challenge name
 *           challengeName    - Array of challenge name
 *           responseLen      - Length of response
 *           response         - Array of response
 *           responseNameLen  - Length of response name (username)
 *           responseName     - Array of response name (username)
 */
typedef struct {
    VOS_UINT32 challengeLen;
    VOS_UINT8  challenge[APP_ESM_PPP_CHAP_CHALLNGE_LEN];
    VOS_UINT32 challengeNameLen;
    VOS_UINT8  challengeName[APP_ESM_PPP_CHAP_CHALLNGE_NAME_LEN];
    VOS_UINT32 responseLen;
    VOS_UINT8  response[APP_ESM_PPP_CHAP_RESPONSE_LEN];
    VOS_UINT8  responseNameLen;
    VOS_UINT8  responseName[APP_ESM_PPP_MAX_USERNAME_LEN];
} APP_ESM_ChapParam;

/*
 * ????????: The struct contains the parameter of PAP.
 *           usernameLen - Length of username
 *           username    - Array of username
 *           passwordLen - Length of password
 *           password    - Array of password
 */
typedef struct {
    VOS_UINT8 usernameLen;
    VOS_UINT8 username[APP_ESM_PPP_MAX_USERNAME_LEN];
    VOS_UINT8 passwordLen;
    VOS_UINT8 password[APP_ESM_PPP_MAX_PASSWORD_LEN];
} APP_ESM_PapParam;

/*
 * ????????: The struct contains the authentication information.
 *           authType  - Auth Type (NONE/PAP/CHAP)
 *           chapParam - Parameters of CHAP
 *           papParam  - Parameters of PAP
 */
typedef struct {
    APP_ESM_AuthTypeUint8 authType;
    VOS_UINT8             authId;
    VOS_UINT8             rsv[2];
    union {
        APP_ESM_ChapParam chapParam;
        APP_ESM_PapParam  papParam;
    } unAuthParam;
} APP_ESM_AuthInfo;

/*
 * ????????: The struct contains the IPCP information.
 *           primDns  - Primary DNS address
 *           secDns   - Secondary DNS address
 *           primNbns - Primary NBNS address
 *           secNbns  - Secondary NBNS address
 */
typedef struct {
    VOS_UINT32 opIpAddr : 1;
    VOS_UINT32 opPrimDns : 1;
    VOS_UINT32 opSecDns : 1;
    VOS_UINT32 opPrimNbns : 1;
    VOS_UINT32 opSecNbns : 1;
    VOS_UINT32 opSpare : 27;

    VOS_UINT8 ipAddr[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 primDns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 secDns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 primNbns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 secNbns[APP_MAX_IPV4_ADDR_LEN];
} APP_ESM_IpcpInfo;

/*
 * ????????: The struct contains the PPP information.
 *           authInfo - Authentication information
 *           ipcpInfo - IPCP information
 */
typedef struct {
    APP_ESM_AuthInfo authInfo; /* PPP???????????? */
    APP_ESM_IpcpInfo ipcpInfo; /* PPP????IPCP??????ESM?????? */
} APP_ESM_PppInfo;

typedef struct {
    VOS_UINT32                epsbId;
    NAS_ESM_DtBearerTypeUint8 bearerType; /* ???????? */
    VOS_UINT8                 rsv[3];
    APP_ESM_ApnInfo           apn;        /* APN???? */
    APP_ESM_IpAddr            ipAddr;     /* UE IP???????? */
    APP_ESM_EpsQosInfo        sdfQosInfo; /* QoS???? */
} NAS_OM_EpsbInfo;

typedef struct {
    VOS_UINT32      actEpsbNum; /* ?????????????? */
    NAS_OM_EpsbInfo epsbInfo[APP_ESM_MAX_EPSB_NUM];
} NAS_OM_ActPdpInfo;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */

    APP_MSG_HEADER
    VOS_UINT32 opId;

    DT_CmdUint8 cmd;
    VOS_UINT8   rsv[3];
    VOS_UINT32  rptPeriod;
} APP_ESM_DtInqCmdReq;

typedef APP_ESM_DtInqCmdReq APP_ESM_InqPdpInfoReq;

/* V7R2-DT ,2014/4/24, CNF ????????????????IND????,begin */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 rslt;
} APP_ESM_InqPdpInfoCnf;
/* V7R2-DT ,2014/4/24, CNF ????????????????IND????,end */

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;

    NAS_OM_ActPdpInfo actPdpInfo;
} APP_ESM_InqPdpInfoInd;
/* DT end */

/* ?????????????????? */

/* moded for verizon band13 pco requirement 2017-03-25, begin */
/*
 * ????????: PCO????????????24008-10.5.6.3
 *           PCO-FF00H????????:
 *           Container Identifier     -FF00H(2 bytes)
 *           Container Content Length -MAX 50 octets(1 bytes)
 *           Container Content Format -MCCMNC(VZW-311480, 3 octets),
 *                                     ACTION(value:0-5;  6-255:reserved)
 *           4????????
 * ????????: ESM -> APS
 */
typedef struct {
    VOS_UINT16 containerId;
    VOS_UINT8  contentLen;
    VOS_UINT8  contents[APP_ESM_MAX_CUSTOM_PCO_CONTAINER_CONTENT_LEN];
} APP_ESM_CustomPcoContainer;

/*
 * ????????: PCO??????????????????????PCO????????????24008-10.5.6.3??
 *           ??VERIZON????????,????????????????????????????
 *           ????????????3??????????????FF00H
 * ????????: ESM -> APS
 */
typedef struct {
    VOS_UINT32                 containerNum;
    APP_ESM_CustomPcoContainer containerList[APP_ESM_MAX_CUSTOM_PCO_CONTAINER_NUM];
} APP_ESM_CustomPcoInfo;
/* moded for verizon band13 pco requirement 2017-03-25, end */

/* added for R1 DATA DEVICE PHASE1, 2017-12-13, begin */
typedef struct {
    VOS_UINT8 ipv4Addr[APP_MAX_IPV4_ADDR_LEN];
} APP_ESM_Ipv4Epdg;

typedef struct {
    VOS_UINT8 ipv6Addr[APP_MAX_IPV6_ADDR_LEN];
} APP_ESM_Ipv6Epdg;

/*
 * ????????: R1????EPDG????????
 * ????????: ESM -> TAF
 */
typedef struct {
    VOS_UINT16       ipv4EpdgNum;
    VOS_UINT16       ipv6EpdgNum;
    APP_ESM_Ipv4Epdg ipv4EpdgList[APP_ESM_MAX_IPV4_EPDG_NUM];
    APP_ESM_Ipv6Epdg ipv6EpdgList[APP_ESM_MAX_IPV6_EPDG_NUM];
} APP_ESM_EpdgInfo;
/* added for R1 DATA DEVICE PHASE1, 2017-12-13, end */

/* ????????: APP???????????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId; /* ?????????????? */

    APP_ESM_PdpSetupTypeUint32 setupType; /* ????PDP????????PPP???????? */

    VOS_UINT32      cid; /* ??????????????????:0~31 */
    VOS_UINT8       pduSessionId;
    VOS_UINT8       rsv[3];
    APP_ESM_PppInfo pppInfo; /* PPP???????????? */
    /* Added for DATA RETRY PHASEIII 2016-06-21 start */
    APP_ESM_BearerPrioUint32 bearerPrio; /* NAS signalling low priority???? */
    /* Added for DATA RETRY PHASEIII 2016-06-21 end */
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */
} APP_ESM_PdpSetupReq;


typedef struct {
    VOS_UINT8 plmnId[3];
    VOS_UINT8 rsv;
} APP_ESM_PlmnId;

/*
 * ????????: ESM??APS??????S_NSSAI??????,????24.501 9.10.2.6
 *           ??5G??????????????????PLMN ID
 * ????????:
 *  1.??    ??: 2018??08??16??
 *    ????????: ????????
 */
typedef struct {
    PS_S_NSSAI_STRU snssai;
    APP_ESM_PlmnId  plmnId;
} APP_ESM_SNssai;

/* ????????: ???????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32 opLinkCid : 1;
    VOS_UINT32 opBearerState : 1;
    VOS_UINT32 opBearerType : 1;
    VOS_UINT32 opPdnAddr : 1;
    VOS_UINT32 opRabId : 1;
    VOS_UINT32 opApn : 1;
    VOS_UINT32 opSdfQos : 1;
    VOS_UINT32 opDnsPrim : 1;
    VOS_UINT32 opDnsSec : 1;
    VOS_UINT32 opPcscfPrim : 1;
    VOS_UINT32 opPcscfSec : 1;
    VOS_UINT32 opGateWayAddrInfo : 1;
    /* added for verizon band13 pco requirement 2017-03-25, begin */
    VOS_UINT32 opCustomPco : 1; /* ????VERRIZON??????????,??FF00H??????APS??,????FF00H?????????????? 1:???? 0:?????? */
    /* added for verizon band13 pco requirement 2017-03-25, end */
    /* moded for R1 DATA DEVICE PHASE1, 2017-12-13, begin */
    VOS_UINT32 opEpdgInfo : 1; /* ????R1??????????,??EPDG??????????APS??,????????????????IMSA?? 1:???? 0:?????? */
    /* moded for R1 DATA DEVICE PHASE1, 2017-12-13, end */
    VOS_UINT32 opSscMode : 1;
    VOS_UINT32 opSnssai : 1;
    VOS_UINT32 opSessionAmbr : 1;
    VOS_UINT32 opSpare : 15;

    VOS_UINT32 rslt; /* ????????????;????????:????????3.1 */
    VOS_UINT32 linkCid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */

    APP_ESM_BearerStateUint32 bearerState; /* ????????????:0~1 */
    APP_ESM_BearerTypeUint32  bearerType;  /* ???????? */
    APP_ESM_IpAddr            pdnAddrInfo;
    APP_ESM_IpAddr            subnetMask;
    APP_ESM_IpAddr            gateWayAddrInfo;   /* ???????? */
    APP_ESM_IpAddr            dnsPrimAddrInfo;   /* ??DNS???? */
    APP_ESM_IpAddr            dnsSecAddrInfo;    /* ??DNS???? */
    APP_ESM_IpAddr            pcscfPrimAddrInfo; /* ??P-CSCF???? */
    APP_ESM_IpAddr            pcscfSecAddrInfo;  /* ??P-CSCF???? */
    VOS_UINT32                rabId;             /* ??????????????????????????????????????ulEpsBid */
    APP_ESM_ApnInfo           apnInfo;
    APP_ESM_EpsQosInfo        sdfQosInfo;

    /* add for active pdp timer expire, 2016-10-20, begin */
    VOS_UINT8 expiredCount; /* ?????????????????? */
    /* add for active pdp timer expire, 2016-10-20, end */
    PS_SSC_ModeUint8 sscMode; /* 24501-9.10.4.12 */
    VOS_UINT8        pduSessionId;
    VOS_UINT8        reserve;
    /* added for verizon band13 pco requirement 2017-03-25, begin */
    APP_ESM_CustomPcoInfo customPcoInfo;
    /* added for verizon band13 pco requirement 2017-03-25, end */
    /* added for R1 DATA DEVICE PHASE1, 2017-12-13, begin */
    APP_ESM_EpdgInfo epdgInfo;
    /* added for R1 DATA DEVICE PHASE1, 2017-12-13, end */

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    /* TODO:??????????NR???????????????????????????? */
    APP_ESM_SNssai     snssaiInfo;     /* 5G S-NASSAI */
    PS_PDU_SessionAmbr pduSessionAmbr; /* 5G SESSION AMBR */

    PS_EPS_MapQosFlowList mapQosFlowList;
    PS_EPS_MapQosRuleList mapQosRuleList;
#endif
} APP_ESM_PdpSetupCnf;

typedef APP_ESM_PdpSetupCnf APP_ESM_PdpSetupInd;

/* ????????: APP???????????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId; /* ?????????????? */
    VOS_UINT32 cid;  /* ??????????????????:0~31 */
    /* Added for DATA RETRY PHASEIII, 2016-6-23, begin */
    APP_ESM_BearerPrioUint32 bearerPrio; /* NAS signalling priority???? */
    /* Added for DATA RETRY PHASEIII, 2016-6-23, end */
    /* add for PS CALL ID,2018-05-22,begin */
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */
    /* add for PS CALL ID,2018-05-22,end */
} APP_ESM_PdpModifyReq;

typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */

    APP_ESM_BearerModifyUint32 bearerModifyType;

    VOS_UINT32 opBearerState : 1;
    VOS_UINT32 opBearerType : 1;
    VOS_UINT32 opRabId : 1;
    VOS_UINT32 opSdfQos : 1;
    /* added for verizon band13 pco requirement 2017-03-25, begin */
    VOS_UINT32 opCustomPco : 1; /* ????VERRIZON??????????,??FF00H??????APS??,????FF00H?????????????? 1:???? 0:?????? */
    /* added for verizon band13 pco requirement 2017-03-25, end */
    VOS_UINT32 opSpare : 27;

    VOS_UINT32 rslt; /* ????????????;????????:????????3.1 */

    APP_ESM_BearerStateUint32 bearerState; /* ????????????:0~1 */
    APP_ESM_BearerTypeUint32  bearerType;  /* ???????? */

    VOS_UINT32 rabId; /* ??????????????????????????????????????ulEpsBid */

    APP_ESM_EpsQosInfo sdfQosInfo;

    /* added for verizon band13 pco requirement 2017-03-25, begin */
    APP_ESM_CustomPcoInfo customPcoInfo;
    /* added for verizon band13 pco requirement 2017-03-25, end */
} APP_ESM_PdpModifyCnf;

typedef APP_ESM_PdpModifyCnf APP_ESM_PdpModifyInd;

/* ????????: APP???????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */

    /* Added for DATA RETRY PHASEI, 2016-03-21, Begin */
    APP_ESM_PdpReleaseCauseUint8 cause;     /* ???????? */
    VOS_UINT8                    detachInd; /* ????????????DETACH??VOS_TRUE????VOS_FALS?? */
    VOS_UINT8                    rsv[2];    /* ???? */
    /* Added for DATA RETRY PHASEI, 2016-03-21, End */
} APP_ESM_PdpReleaseReq;

/* ????????: ???????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */

    VOS_UINT32 opLinkCid : 1;
    VOS_UINT32 opPdnAddr : 1;
    /* added for verizon band13 pco requirement 2017-03-25, begin */
    VOS_UINT32 opCustomPco : 1; /* ????VERRIZON??????????,??FF00H??????APS??,????FF00H?????????????? 1:???? 0:?????? */
    /* added for verizon band13 pco requirement 2017-03-25, end */
    VOS_UINT32 opSpare : 29;

    VOS_UINT32 rslt;

    VOS_UINT32     linkCid;
    APP_ESM_IpAddr pdnAddrInfo;

    /* add for VIA CL MT-DETACH make CID mod problem begin */
    /* ??APP????RELEASE IND??(RELEASE CNF????);    */
    VOS_UINT32 epsbId;
    /* add for VIA CL MT-DETACH make CID mod problem end */

    /* added for verizon band13 pco requirement 2017-03-25, begin */
    APP_ESM_CustomPcoInfo customPcoInfo;
    /* added for verizon band13 pco requirement 2017-03-25, end */
    VOS_UINT8 pduSessionId;
    /* fix pclint, add begin, 2018-11-06 */
    VOS_UINT8 reserved[3];
    /* fix pclint, add end, 2018-11-06 */
} APP_ESM_PdpReleaseCnf;

typedef APP_ESM_PdpReleaseCnf APP_ESM_PdpReleaseInd;

/* ????????: ????????????APP???? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31????????????????TAF_APS_GetUnusedPsCallId()???????? */
    VOS_UINT32 opLinkCid : 1;
    VOS_UINT32 opModifyTpye : 1;
    VOS_UINT32 opSpare : 30;
    VOS_UINT32 linkCid;

    APP_ESM_BearerOperateTypeUint32 operateType;
    APP_ESM_BearerModifyUint32      bearerModifyType;
} APP_ESM_PdpManagerInd;

/* ????????: APP???????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */

    APP_ESM_BearerActResultUint32 setupRslt; /* ????????:0:??????????????????,1:???????? */
} APP_ESM_PdpManagerRsp;

/*
 * ????????  : APS-->ESM IPv6 Prefix????
 */
/* APS????????????, IPV6???? */
typedef struct {
    VOS_UINT8 prefixLen;
    VOS_UINT8 reserved[3];

    VOS_UINT8 prefix[APP_ESM_IPV6_ADDR_LEN];
} APP_ESM_Ipv6Prefix;

/* ????????: APS-->ESM IPv6 Notify */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32         opId;
    VOS_UINT8          epsbId;
    VOS_UINT8          ipv6PrefixNum;
    VOS_UINT8          reserved[2];
    APP_ESM_Ipv6Prefix ipv6PrefixArray[APP_ESM_MAX_IPV6_PREFIX_NUM];
} APP_ESM_Ipv6InfoNotify;

/* modify begin */
/* ????????: APS-->ESM ???????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */
} APP_ESM_ProcedureAbortNotify;
/* modify end */

/* by begin 2013-05-29 Modify L4A */

/* ims begin */
/* ????????: APS-->ESM ???????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */

    VOS_UINT8 pduSessionId;
    VOS_UINT8 rsv[3];

    VOS_UINT32 opPdnType : 1;
    VOS_UINT32 opApn : 1;
    VOS_UINT32 opGwAuth : 1;
    /* modify 2014-05-09 begin */
    VOS_UINT32 opIpv4AddrAlloc : 1;  /* Ipv4AddrAlloc */
    VOS_UINT32 opPcscfDiscovery : 1; /* P-CSCF discovery */
    VOS_UINT32 opImCnSignalFlg : 1;  /* IM CN Signalling Flag */
    VOS_UINT32 opSpare : 26;
    /* modify 2014-05-09 end */

    APP_ESM_ApnInfo       apnInfo;
    APP_ESM_PdnTypeUint32 pdnType;
    APP_ESM_GwAuthInfo    gwAuthInfo;
    /* Modify for CL multimode 2014-02-14 begin */
    APP_ESM_PdnRequestTypeUint32 pdnReqestType;
    /* Modify for CL multimode 2014-02-14 end */
    /* 2014-05-09 begin */
    APP_ESM_PdpEmcIndUint32         emergencyInd;
    APP_ESM_Ipv4AddrAllocTypeUint32 ipv4AddrAlloc;
    APP_ESM_PcscfDiscoveryUint32    pcscfDiscovery;
    APP_ESM_ImsCnSigFlagUint32      imCnSignalFlg;
    /* 2014-05-09 end */
    /* Added for DATA RETRY PHASEIII, 2016-6-23, begin */
    APP_ESM_BearerPrioUint32 bearerPrio;
    /* Added for DATA RETRY PHASEIII, 2016-6-23, end */
} APP_ESM_NdisconnReq;
/* ims end */

/* ????????: ????APS-->ESM ???????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;
    VOS_UINT32 psCallId; /* ????????ID??????:0~31 */

    VOS_UINT32 opBearerState : 1;
    VOS_UINT32 opBearerType : 1;
    VOS_UINT32 opPdnAddr : 1;
    VOS_UINT32 opRabId : 1;
    VOS_UINT32 opApn : 1;
    VOS_UINT32 opSdfQos : 1;
    VOS_UINT32 opDnsPrim : 1;
    VOS_UINT32 opDnsSec : 1;
    VOS_UINT32 opPcscfPrim : 1;
    VOS_UINT32 opPcscfSec : 1;
    VOS_UINT32 opGateWayAddrInfo : 1;
    /* added for verizon band13 pco requirement 2017-03-25, begin */
    VOS_UINT32 opCustomPco : 1; /* ????VERRIZON??????????,??FF00H??????APS??,????FF00H?????????????? 1:???? 0:?????? */
    /* added for verizon band13 pco requirement 2017-03-25, end */
    /* moded for R1 DATA DEVICE PHASE1, 2017-12-13, begin */
    VOS_UINT32 opEpdgInfo : 1; /* ????R1??????????,??EPDG??????????APS??,??????????????IMSA?? 1:???? 0:?????? */
    /* moded for R1 DATA DEVICE PHASE1, 2017-12-13, end */
    VOS_UINT32 opSscMode : 1;
    VOS_UINT32 opSnssai : 1;
    VOS_UINT32 opSessionAmbr : 1;
    VOS_UINT32 opSpare : 16;

    VOS_UINT32 rslt; /* ????????:????????3.1 */

    APP_ESM_BearerStateUint32 bearerState; /* ????????????:0~1 */
    APP_ESM_BearerTypeUint32  bearerType;  /* ???????? */

    APP_ESM_IpAddr     pdnAddrInfo;
    APP_ESM_IpAddr     subnetMask;
    APP_ESM_IpAddr     gateWayAddrInfo;
    APP_ESM_IpAddr     dnsPrimAddrInfo;   /* ??DNS???? */
    APP_ESM_IpAddr     dnsSecAddrInfo;    /* ??DNS???? */
    APP_ESM_IpAddr     pcscfPrimAddrInfo; /* ??P-CSCF???? */
    APP_ESM_IpAddr     pcscfSecAddrInfo;  /* ??P-CSCF???? */
    VOS_UINT32         rabId;             /* ??????????????????????????????????ulEpsbId */
    APP_ESM_ApnInfo    apnInfo;
    APP_ESM_EpsQosInfo sdfQosInfo;

    /* add for active pdp timer expire, 2016-10-20, begin */
    VOS_UINT8 expiredCount; /* ?????????????????? */
    /* add for active pdp timer expire, 2016-10-20, end */
    PS_SSC_ModeUint8 sscMode; /* 24501-9.10.4.12 */
    VOS_UINT8        pduSessionId;
    VOS_UINT8        reserve;
    /* added for verizon band13 pco requirement 2017-03-25, begin */
    APP_ESM_CustomPcoInfo customPcoInfo;
    /* added for verizon band13 pco requirement 2017-03-25, end */
    /* added for R1 DATA DEVICE PHASE1, 2017-12-13, begin */
    APP_ESM_EpdgInfo epdgInfo;
    /* added for R1 DATA DEVICE PHASE1, 2017-12-13, end */

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    /* TODO:??????????NR???????????????????????????? */
    APP_ESM_SNssai     snssaiInfo;     /* 5G S-NASSAI */
    PS_PDU_SessionAmbr pduSessionAmbr; /* 5G SESSION AMBR */

    PS_EPS_MapQosFlowList mapQosFlowList;
    PS_EPS_MapQosRuleList mapQosRuleList;
#endif
} APP_ESM_NdisconnCnf;

/* ????????: CGDCONTAT?????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32 opBearType : 1;
    VOS_UINT32 opPdnType : 1;
    VOS_UINT32 opApn : 1;

    VOS_UINT32 opIpv4AddrAllocType : 1;
    /* ims begin */
    VOS_UINT32 opPcscfDiscovery : 1;
    VOS_UINT32 opImsCnSignalFlag : 1;
    /* ims end */
    VOS_UINT32 opSpare : 26;

    APP_ESM_ParaSetUint32           setType; /* 0:SET;1:DEL */
    APP_ESM_CidTypeUint32           bearCidType;
    APP_ESM_ApnInfo                 apnInfo;
    APP_ESM_PdnTypeUint32           pdnType;
    APP_ESM_Ipv4AddrAllocTypeUint32 ipv4AddrAllocType;
    /* ims begin */
    APP_ESM_PcscfDiscoveryUint32 pcscfDiscovery;
    APP_ESM_ImsCnSigFlagUint32   imsCnSignalFlag;
    /* ims end */
} APP_ESM_SetCgdcontReq;

/* ????????: ????CGDCONTAT?????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;
    VOS_UINT32 cid;

    VOS_UINT32 rslt;
} APP_ESM_SetCgdcontCnf;
/* end 2013-05-29 Modify L4A */

/* added for Band13 R1 PHASE1, 2017-10-16, begin */
/* ????????: APN enable?????????????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    APP_MSG_HEADER
    VOS_UINT32 opId;

    VOS_UINT32           cid;        /* CID [0,11] */
    APP_ESM_ApnTypeUint8 apnType;    /* apn class */
    VOS_UINT8            enableFlag; /* apn enable flag */
    VOS_UINT8            reserved[2];
} APP_ESM_ApnEnableInfoChangeNtf;
/* added for Band13 R1 PHASE1, 2017-10-16, end */

/* ????????: PDP???????????????? */
typedef struct {
    APP_ESM_BearerManageModeUint8 mode;        /* ???????????? */
    APP_ESM_BearerManageTypeUint8 type;        /* ???????????? */
    VOS_UINT8                     reserve1[2]; /* ???????????????? */
} APP_ESM_PdpManageInfo;

/* Added for DCM DATA OFF, 2017-11-11, begin */
/* ????????: ???????????????????? */
typedef struct {
    VOS_UINT8 dataSwitch;     /* ???????????????? */
    VOS_UINT8 dataRoamSwitch; /* ???????????????????? */

    VOS_UINT8 resv[2];
} APP_ESM_DataSwitchInfo;
/* Added for DCM DATA OFF, 2017-11-11, end */

typedef struct {
    APP_ESM_MsgTypeUint32 msgId; /* _H2ASN_MsgChoice_Export APP_ESM_MsgTypeUint32  */
    VOS_UINT8             msg[4];
    /* _H2ASN_MsgChoice_When_Comment          APP_ESM_MSG_TYPE_ENUM_UINT32 */
} APP_ESM_InterfaceMsgData;
/* _H2ASN_Length UINT32 */

typedef struct {
    VOS_MSG_HEADER
    APP_ESM_InterfaceMsgData stMsgData;
} APP_ESM_InterfaceMsg;

/*
 * ????????: CID????PF??????
 */
typedef struct {
    VOS_UINT32      cid;
    APP_ESM_TftInfo pf;
} APP_ESM_CidPf;
/*
 * ????????: TFT????
 */
typedef struct {
    VOS_UINT32    pfNum;
    APP_ESM_CidPf cidPf[PS_MAX_PF_NUM_IN_TFT];
} APP_ESM_Tft;

/*
 * ????????: Transaction ID ????
 */
typedef struct {
    VOS_UINT8 tiFlag;
    VOS_UINT8 tiValue;

    VOS_UINT8 reserved[2];
} APP_ESM_TransactionId;


typedef struct {
    VOS_UINT8 pcscfAddr[APP_MAX_IPV4_ADDR_LEN];
} APP_ESM_Ipv4Pcscf;


typedef struct {
    VOS_UINT8 pcscfAddr[APP_MAX_IPV6_ADDR_LEN];
} APP_ESM_Ipv6Pcscf;


typedef struct {
    VOS_UINT8 ipv4PcscfAddrNum; /* IPV4??P-CSCF??????????????????[0,8] */
    VOS_UINT8 rsv[3];           /* ???? */

    APP_ESM_Ipv4Pcscf ipv4PcscfAddrList[APP_ESM_PCSCF_ADDR_MAX_NUM];
} APP_ESM_Ipv4PcscfList;


typedef struct {
    VOS_UINT8 ipv6PcscfAddrNum; /* IPV6??P-CSCF??????????????????[0,8] */
    VOS_UINT8 rsv[3];           /* ???? */

    APP_ESM_Ipv6Pcscf ipv6PcscfAddrList[APP_ESM_PCSCF_ADDR_MAX_NUM];
} APP_ESM_Ipv6PcscfList;

/*
 * ????????: priDns   - Primary DNS server Address
 *           secDns   - Secondary DNS server Address
 *           gateWay  - Peer IP address
 *           priNbns  - Primary WINS DNS address
 *           secNbns  - Seocndary WINS DNS address
 *           priPcscf - Primary P-CSCF address
 *           secPcscf - Seocndary P-CSCF address
 *           gateWay[0]????????????????gateWay[3]??????????????
 *           priNbns[0]????????????????priNbns[3]??????????????
 *           secNbns[0]????????????????secNbns[3]??????????????
 */
typedef struct {
    VOS_UINT32 opPriDns : 1;
    VOS_UINT32 opSecDns : 1;
    VOS_UINT32 opGateWay : 1;
    VOS_UINT32 opPriNbns : 1;
    VOS_UINT32 opSecNbns : 1;
    VOS_UINT32 opIpv4Mtu : 1;
    VOS_UINT32 opSpare : 26;

    VOS_UINT8 priDns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 secDns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 gateWay[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 priNbns[APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8 secNbns[APP_MAX_IPV4_ADDR_LEN];

    APP_ESM_Ipv4PcscfList ipv4PcscfList;

    VOS_UINT16 ipv4Mtu;
    VOS_UINT8  reserved[2];
} APP_ESM_PcoIpv4Item;

/*
 * ????????: priDns   - Primary DNS server Address
 *           secDns   - Secondary DNS server Address
 *           priPcscf - Primary P-CSCF address
 *           secPcscf - Seocndary P-CSCF address
 *           priDns[0]????????????????priDns[15]??????????????
 *           secDns[0]????????????????secDns[15]??????????????
 */
typedef struct {
    VOS_UINT32 opPriDns : 1;
    VOS_UINT32 opSecDns : 1;
    VOS_UINT32 opSpare : 30;

    VOS_UINT8 priDns[APP_MAX_IPV6_ADDR_LEN];
    VOS_UINT8 secDns[APP_MAX_IPV6_ADDR_LEN];

    APP_ESM_Ipv6PcscfList ipv6PcscfList;
} APP_ESM_PcoIpv6Item;

/*
 * ????????: ESM -> APS
 *           EPS Bearer??????????(Activate, Modify, Deactivate), ????EPS??????????
 *           ??????TI, ????????????????????. ????????????????TI, SM??????????????
 *           linked EPS bearer identity (if available) ?????? linked TI;
 *           PDN address and APN of the default EPS bearer context??????PDP address and APN of the default PDP context;
 *           TFT of the default EPS bearer context?????? the TFT of the default PDP context;
 *           TFTs of the dedicated EPS bearer contexts ??????TFTs of the secondary PDP contexts;
 *           ????????????SM_ESM_PDP_OPT_MODIFY????OP????0????????????????????OP????1??????????????????
 *           ??????????TFT??????????bitOpPf????1??ulPfNum????0??
 *           ????????DNS??NBNS,P-CSCF??????????????????OP??????1??????????????????0??
 *           ucLlcSapi??ucRadioPriority??ucPacketFlowId????????????????GU????SM????
 */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */

    VOS_UINT32 opLinkedEpsbId : 1;
    VOS_UINT32 opEpsQos : 1;
    VOS_UINT32 opTft : 1;
    VOS_UINT32 opApn : 1;
    VOS_UINT32 opApnAmbr : 1;
    VOS_UINT32 opTransId : 1;
    VOS_UINT32 opNegQos : 1;
    VOS_UINT32 opLlcSapi : 1;
    VOS_UINT32 opRadioPriority : 1;
    VOS_UINT32 opPacketFlowId : 1;
    VOS_UINT32 opBcm : 1;
    VOS_UINT32 opEmcInd : 1;
    VOS_UINT32 opImCnSigalFlag : 1;
    VOS_UINT32 opErrorCode : 1;
    VOS_UINT32 opCustomPco : 1; /* ????VERRIZON??????????,??FF00H??????APS??,????FF00H?????????????? 1:???? 0:?????? */
    /* Added for no n26, 2019-1-17, begin */
    VOS_UINT32 opSnssai : 1;
    /* Added for no n26, 2019-1-17, end */

    VOS_UINT32 opSpare : 16;

    APP_ESM_HandoverResultUint32 result;
    VOS_UINT32                   epsbId;
    VOS_UINT32                   bitCid;
    VOS_UINT32                   linkedEpsbId; /* ??????????????EPS????ID */

    VOS_UINT8        psCallId;
    VOS_UINT8        pduSessionId;
    PS_SSC_ModeUint8 sscMode; /* ??????SSC MODE1??????????24501-9.10.4.12 */
    VOS_UINT8        rsv[1];

    APP_ESM_IpAddr      pdnAddr;
    PS_EPS_ApnAmbr      epsApnAmbr;
    APP_ESM_EpsQosInfo  epsQos;
    APP_ESM_Tft         tft;
    APP_ESM_Apn         apn;
    APP_ESM_QosInfo     negQos;
    APP_ESM_PcoIpv4Item pcoIpv4Item;
    APP_ESM_PcoIpv6Item pcoIpv6Item;

    VOS_UINT8             llcSapi;
    VOS_UINT8             radioPriority;
    VOS_UINT8             packetFlowId;
    APP_ESM_BcmUint8      bcm;
    APP_ESM_TransactionId transId;

    APP_ESM_PdpEmcIndUint32    emergencyInd;
    APP_ESM_ImsCnSigFlagUint32 imCnSignalFlag;

    VOS_UINT32            errorCode; /* ????????????????????SM???????? */
    APP_ESM_CustomPcoInfo customPcoInfo;
    APP_ESM_SNssai        snssaiInfo; /* 5G S-NASSAI */
} APP_ESM_NrHandoverToLteInd;

/* Added for HO ATTACH, 2018-12-15 begin */
/* ????????: APS -> ESM ???????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
} APP_ESM_SyncBearerInfoNotify;
/* Added for HO ATTACH, 2018-12-15 end */

/* ????????: ????PDN IP???????????? */
typedef struct {
    VOS_MSG_HEADER               /* _H2ASN_Skip */
    VOS_UINT32            msgId; /* _H2ASN_Skip */
    VOS_UINT8             cid;
    VOS_UINT8             rsv[3];
    APP_ESM_ParaSetUint32 setType; /* 0:SET;1:DEL */
    APP_ESM_PdnTypeUint32 pdpType;
} APP_ESM_SetRoamingPdnTypeReq;

/* ????????: ????PDN IP???????????? */
typedef struct {
    VOS_MSG_HEADER    /* _H2ASN_Skip */
    VOS_UINT32 msgId; /* _H2ASN_Skip */
    VOS_UINT32 rslt;
} APP_ESM_SetRoamingPdnTypeCnf;

/* ????????: APS -> ESM ?????????????? */
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT32 msgId;
    APS_ESM_LocalRelCauseUint32 cause;
    VOS_UINT8  pduSessionId;
    VOS_UINT8  psCallId;
    VOS_UINT8  epsbid;
    VOS_UINT8  rsv;
} APS_ESM_LocalReleaseNotify;

extern VOS_UINT32 APP_GetSdfParaByModemId(MODEM_ID_ENUM_UINT16 modemId, VOS_UINT32* sdfNum,
                                          APP_ESM_SdfPara* sdfPara);
extern VOS_UINT32 APP_GetPdpManageInfoByModemId(MODEM_ID_ENUM_UINT16   modemId,
                                                APP_ESM_PdpManageInfo* pdpManageInfo);
extern VOS_UINT32 APP_GetCidImsSuppFlagByModemId(MODEM_ID_ENUM_UINT16 modemId, VOS_UINT8 cid,
                                                 VOS_UINT8* imsSuppFlag);
/* added for Band13 R1 PHASE1, 2017-10-16, begin */

extern VOS_UINT32 APP_ESM_GetAllApnClassInfo(MODEM_ID_ENUM_UINT16 modemId, VOS_UINT32* apnNum,
                                             APP_ESM_ApnClassInfo* apnClassInfo);
/* added for Band13 R1 PHASE1, 2017-10-16, end */

/* Added for DCM DATA OFF, 2017-11-1, begin */
extern VOS_UINT32 APP_GetDataSwitchInfoByModemId(MODEM_ID_ENUM_UINT16    modemId,
                                                 APP_ESM_DataSwitchInfo* dataSwitchInfo);
/* Added for DCM DATA OFF, 2017-11-1, end */

extern VOS_UINT32 APP_AllocPsCallIdByModemId(MODEM_ID_ENUM_UINT16 modemId, VOS_UINT8* psCallId);

extern VOS_UINT32 APP_AllocPduSessionIdByModemId(MODEM_ID_ENUM_UINT16 modemId, VOS_UINT8* pduSessionId);

extern VOS_VOID APP_FreePduSessionIdByModemId(MODEM_ID_ENUM_UINT16 modemId, VOS_UINT8 pduSessionId);

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

#endif /* end of app_esm_interface.h */
