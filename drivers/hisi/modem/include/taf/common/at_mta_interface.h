/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
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

#ifndef __AT_MTA_INTERFACE_H__
#define __AT_MTA_INTERFACE_H__

#include "PsTypeDef.h"
#include "at_mn_interface.h"
#include "mta_comm_interface.h"
#include "nv_stru_sys.h"
#include "nv_stru_gucnas.h"

#include "AtParse.h"
#include "nas_comm_packet_ser.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef WIN32
#pragma warning(disable : 4200) /* zero-sized array in struct/union */
#endif

#pragma pack(4)

#define MTA_CPOS_XML_MAX_LEN (1024)   /* MTA????AT??????XML???????????? */
#define MTA_CPOSR_XML_MAX_LEN (1024)  /* MTA??AT??????XML??????????????1024 */
#define MTA_SIMLOCK_PASSWORD_LEN (16) /* ?????????????????????? */
#define MTA_MAX_EPDU_NAME_LEN (32)    /* EPDU??????????Name?????? */
#define MTA_MAX_EPDU_BODY_LEN (500)   /* EPDU???????? */

#define MTA_CLIENTID_BROADCAST (0xFFFF)
#define MTA_INVALID_TAB_INDEX (0x00)

#define AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM (10)   /* autotest???????????????????? */
#define MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM (20)  /* autotest???????????????????? */
#define MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM (8) /* ?????????????????????????? */
#define MTA_AT_WRR_MAX_MEANRPT_NUM (10)         /* ?????????????????????????? */

#define MTA_AT_WRR_MAX_NCELL_NUM (8)

#define AT_MTA_GAS_AUTOTEST_MAX_PARA_NUM (10)
#define MTA_AT_GAS_AUTOTEST_MAX_RSULT_NUM (20) /* autotest???????????????????? */

#define AT_MTA_RPT_CFG_MAX_SIZE (8)

#define AT_MTA_HANDLEDECT_MIN_TYPE (0)
#define AT_MTA_HANDLEDECT_MAX_TYPE (4)

#define AT_RSA_CIPHERTEXT_LEN (256)

#define AT_MTA_INTEREST_FREQ_MAX_NUM (0x05)
#define AT_MTA_MBMS_AVL_SERVICE_MAX_NUM (0x10)
#define AT_MTA_ISMCOEX_BANDWIDTH_NUM (0x06)

#define AT_MTA_MEID_DATA_LEN (7)

#define MTA_AT_EFRUIMID_OCTET_LEN_EIGHT (8)
#define MTA_AT_EFRUIMID_OCTET_LEN_FIVE (5)

#define MTA_AT_UIMID_OCTET_LEN (4)

#define AT_MTA_GPS_XO_COEF_NUM (4)

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
#define MTA_FREQLOCK_MAX_MODE (4)
#endif

#define MTA_AT_MAX_BESTFREQ_GROUPNUM (8)

#define MTA_AT_MAX_DIE_ID_LEN (32)

#define MTA_AT_MAX_RFFE_DIE_ID_LEN (16)
#define MTA_AT_MAX_RFFE_DIE_ID_COUNT (4)
#define MTA_AT_RFFE_DIE_ID_VALID (1)

#define MTA_PMU_MAX_DIE_SN_LEN (20)

#define AT_MAX_RS_INFO_NUM (32) /* LRRC????RS???????? */
#define AT_RS_INFO_MULTI (100)  /* LRRC??RSRP??RSRQ??????100????????MTA */

#define AT_MTA_PSEUCELL_PLMN_LEN_FIVE (5)
#define AT_MTA_PSEUCELL_PLMN_LEN_SIX (6)
#define AT_MTA_PSEUCELL_LAC_LEN (4)
#define AT_MTA_PSEUCELL_CELLID_LEN (8)
#define AT_MTA_PLMN_MCC_LEN (3)
#define AT_MTA_PLMN_MNC_LEN_TWO (2)
#define AT_MTA_PLMN_MNC_LEN_THREE (3)

#define MTA_AT_PESN_NV_DATA_LEN (4)
#define MTA_AT_MEID_NV_DATA_LEN_NEW (7)

#define AT_MTA_EPDU_NAME_LENGTH_MAX (32)
#define AT_MTA_EPDU_CONTENT_LENGTH_MAX (250)
#define AT_MTA_EPDU_CONTENT_STRING_LEN_MAX (500)

#define AT_MTA_MAX_BAND_NUM (8)     /* ????????8??Band */
#define AT_MTA_BAND_INFO_OFFSET (3) /* band?????????????? */
#define AT_MTA_MAX_SUB_BAND_NUM (4) /* ????Band??????????????4????BAND */
#define AT_MTA_BAND_INFO_LEN (72)   /* ????Band?????????????? */
#define MTA_AT_CA_MAX_CELL_NUM (8)
#define MTA_AT_UTC_MAX_LENGTH (21)

#define MTA_AT_BOOSTER_IND_MAX_NUM (248)    /* Booster????????????LRRC??MTA????248???????? */
#define MTA_AT_BOOSTER_QRY_CNF_MAX_NUM (40) /* Booster???????????????????????????? */
#define MTA_AT_UE_CAP_INFO_IND_MAX_LEN 2400 /* UE????????????LRRC??MTA????2400???????? */

#define MTA_AT_EPS_NETWORK_BYTE (2)

#define MTA_AT_MAX_STATEII_LEVEL_ITEM 4

#define AT_MTA_VERSION_INFO_LEN (10) /* ?????????????????????????????? */

#define UCOM_NV_DCXO_SAMPLE_H_MAX_NUM (40)

#define AT_MTA_UECAP_MAX_NR_BAND_NUM (32)

#define AT_MTA_NRRCCAP_PARA_MAX_NUM (10)

#define MTA_AT_MAX_CC_NUMBER (4)
#define MTA_AT_MAX_CODE_NUMBER (2)
#define MTA_AT_INVALID_MCS_VALUE (0xFF)

#define MTA_AT_MAX_ALLOWED_AND_CFG_NSSAI_PLMN_NUM 16

#define AT_MTA_LTE_SUPPORT_OVERHEATING_PARA_NUM 7
#define AT_MTA_NR_SUPPORT_OVERHEATING_PARA_NUM 13
#define AT_MTA_NOT_SUPPORT_OVERHEATING_PARA_NUM 2
#define MTA_AT_MAX_LADN_DNN_NUM 8

#define MTA_AT_MAX_NR_NCELL_RPT_NUM 4
#define MTA_AT_MAX_NR_NCELL_BEAM_RPT_NUM 4
#define MTA_AT_MAX_NR_SSB_BEAM_NUM 8
#define MTA_AT_NR_RSRP_INVALID_VALUE 0x7FFF
#define MTA_AT_NR_SSBID_INVALID_VALUE 0xFF

#if (FEATURE_LTEV == FEATURE_ON)
#define MTA_AT_LTEV_BAND_MAX_NUM 64
#endif

#if (FEATURE_UE_MODE_NR == FEATURE_ON)
#define MTA_NRPHY_MAX_PARA_NUM 15
#endif

enum AT_MTA_MsgType {
    /* ???????? */ /* ????ID */ /* ????, ????ASN */
    /* AT????MTA?????? */
    ID_AT_MTA_CPOS_SET_REQ      = 0x0000, /* _H2ASN_MsgChoice AT_MTA_CposReq        */
    ID_AT_MTA_CGPSCLOCK_SET_REQ = 0x0001, /* _H2ASN_MsgChoice AT_MTA_CgpsclockReq   */
    ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ = 0x0003, /* _H2ASN_MsgChoice AT_MTA_SimlockunlockReq */

    ID_AT_MTA_QRY_NMR_REQ = 0x0004, /* _H2ASN_MsgChoice AT_MTA_QryNmrReq */

    /* _H2ASN_MsgChoice AT_MTA_ReselOffsetCfgSetNtf */
    ID_AT_MTA_RESEL_OFFSET_CFG_SET_NTF = 0x0005,
    ID_AT_MTA_WRR_AUTOTEST_QRY_REQ     = 0x0006, /* _H2ASN_MsgChoice AT_MTA_WrrAutotestQryPara */
    ID_AT_MTA_WRR_CELLINFO_QRY_REQ     = 0x0007, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_WRR_MEANRPT_QRY_REQ      = 0x0008, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_WRR_FREQLOCK_SET_REQ     = 0x0009, /* _H2ASN_MsgChoice MTA_AT_WrrFreqlockCtrl     */
    ID_AT_MTA_WRR_RRC_VERSION_SET_REQ  = 0x000A, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_WRR_CELLSRH_SET_REQ      = 0x000B, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_WRR_FREQLOCK_QRY_REQ     = 0x000C, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ  = 0x000D, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_WRR_CELLSRH_QRY_REQ      = 0x000E, /* _H2ASN_MsgChoice AT_MTA_Reserve */

    ID_AT_MTA_BODY_SAR_SET_REQ        = 0x000F, /* _H2ASN_MsgChoice AT_MTA_BodySarSetReq */
    ID_AT_MTA_CURC_SET_NOTIFY         = 0x0010, /* _H2ASN_MsgChoice AT_MTA_CurcSetNotify */
    ID_AT_MTA_CURC_QRY_REQ            = 0x0011, /* _H2ASN_MsgChoice AT_MTA_CurcQryReq */
    ID_AT_MTA_UNSOLICITED_RPT_SET_REQ = 0x0012, /* _H2ASN_MsgChoice AT_MTA_UnsolicitedRptSetReq */
    ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ = 0x0013, /* _H2ASN_MsgChoice AT_MTA_UnsolicitedRptQryReq */

    ID_AT_MTA_IMEI_VERIFY_QRY_REQ   = 0x0014, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_CGSN_QRY_REQ          = 0x0015, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_NCELL_MONITOR_SET_REQ = 0x0016, /* _H2ASN_MsgChoice AT_MTA_NcellMonitorSetReq */
    ID_AT_MTA_NCELL_MONITOR_QRY_REQ = 0x0017, /* _H2ASN_MsgChoice AT_MTA_Reserve */

    ID_AT_MTA_REFCLKFREQ_SET_REQ = 0x0018, /* _H2ASN_MsgChoice AT_MTA_RefclkfreqSetReq */
    ID_AT_MTA_REFCLKFREQ_QRY_REQ = 0x0019, /* _H2ASN_MsgChoice AT_MTA_Reserve */

    ID_AT_MTA_HANDLEDECT_SET_REQ = 0x001A, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_HANDLEDECT_QRY_REQ = 0x001B, /* _H2ASN_MsgChoice AT_MTA_Reserve */

    ID_AT_MTA_ECID_SET_REQ = 0x001C, /* _H2ASN_MsgChoice AT_MTA_EcidSetReq */

    ID_AT_MTA_MIPICLK_QRY_REQ = 0x001D, /* _H2ASN_MsgChoice AT_MTA_Reserve */

    ID_AT_MTA_SET_DPDTTEST_FLAG_REQ = 0x001E, /* _H2ASN_MsgChoice AT_MTA_SetDpdttestFlagReq */
    ID_AT_MTA_SET_DPDT_VALUE_REQ    = 0x001F, /* _H2ASN_MsgChoice AT_MTA_SetDpdtValueReq */
    ID_AT_MTA_QRY_DPDT_VALUE_REQ    = 0x0020, /* _H2ASN_MsgChoice AT_MTA_QryDpdtValueReq */

    ID_AT_MTA_RRC_PROTECT_PS_REQ = 0x0021,
    ID_AT_MTA_PHY_INIT_REQ       = 0x0022,

    ID_AT_MTA_SET_JAM_DETECT_REQ = 0x0023, /* _H2ASN_MsgChoice AT_MTA_SetJamDetectReq */

    ID_AT_MTA_SET_FREQ_LOCK_REQ = 0x0024, /* _H2ASN_MsgChoice AT_MTA_SetFreqLockReq */

    ID_AT_MTA_SET_GSM_FREQLOCK_REQ = 0x0025, /* _H2ASN_MsgChoice AT_MTA_SetGsmFreqlockReq */
    ID_AT_MTA_SET_FEMCTRL_REQ      = 0x0026,

    ID_AT_MTA_NVWRSECCTRL_SET_REQ = 0x0027,

    /* _H2ASN_MsgChoice AT_MTA_MbmsServiceOptionSetReq */
    ID_AT_MTA_MBMS_SERVICE_OPTION_SET_REQ = 0x0028,
    ID_AT_MTA_MBMS_PREFERENCE_SET_REQ     = 0x0029, /* _H2ASN_MsgChoice AT_MTA_MbmsPreferenceSetReq */
    ID_AT_MTA_SIB16_NETWORK_TIME_QRY_REQ  = 0x002A, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_BSSI_SIGNAL_LEVEL_QRY_REQ   = 0x002B, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_NETWORK_INFO_QRY_REQ        = 0x002C, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_EMBMS_STATUS_QRY_REQ        = 0x002D, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    /* _H2ASN_MsgChoice AT_MTA_MbmsUnsolicitedCfgSetReq */
    ID_AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ = 0x002E,
    /* _H2ASN_MsgChoice AT_MTA_LowPowerConsumptionSetReq */
    ID_AT_MTA_LTE_LOW_POWER_SET_REQ = 0x002F,
    /* _H2ASN_MsgChoice AT_MTA_MbmsInterestlistSetReq */
    ID_AT_MTA_INTEREST_LIST_SET_REQ = 0x0030,
    /* _H2ASN_MsgChoice AT_MTA_MbmsServiceStateSetReq */
    ID_AT_MTA_MBMS_SERVICE_STATE_SET_REQ    = 0x0031,
    ID_AT_MTA_MBMS_AVL_SERVICE_LIST_QRY_REQ = 0x0032, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_LTE_WIFI_COEX_SET_REQ         = 0x0033, /* _H2ASN_MsgChoice AT_MTA_LteWifiCoexSetReq */
    ID_AT_MTA_LTE_WIFI_COEX_QRY_REQ         = 0x0034, /* _H2ASN_MsgChoice AT_MTA_Reserve */

    ID_AT_MTA_SET_FR_REQ = 0x0035,

    ID_AT_MTA_MEID_SET_REQ = 0x0036, /* _H2ASN_MsgChoice AT_MTA_MeidSetReq */
    ID_AT_MTA_MEID_QRY_REQ = 0x0037,

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
    ID_AT_MTA_SET_M2M_FREQLOCK_REQ = 0x0038, /* _H2ASN_MsgChoice AT_MTA_SetM2MFreqlockReq */
    ID_AT_MTA_QRY_M2M_FREQLOCK_REQ = 0x0039, /* _H2ASN_MsgChoice AT_MTA_Reserve */
#endif

    ID_AT_MTA_TRANSMODE_QRY_REQ = 0x0044,

    ID_AT_MTA_UE_CENTER_SET_REQ = 0x0045, /* _H2ASN_MsgChoice AT_MTA_SetUeCenterReq */
    ID_AT_MTA_UE_CENTER_QRY_REQ = 0x0046,

    ID_AT_MTA_SET_NETMON_SCELL_REQ = 0x0047,
    ID_AT_MTA_SET_NETMON_NCELL_REQ = 0x0048,

    ID_AT_MTA_RFICSSIRD_QRY_REQ = 0x0049,

    ID_AT_MTA_ANQUERY_QRY_REQ = 0x004A,
    ID_AT_MTA_CSNR_QRY_REQ    = 0x004B,
    ID_AT_MTA_CSQLVL_QRY_REQ  = 0x004C,

    ID_AT_MTA_EVDO_SYS_EVENT_SET_REQ = 0x004d, /* _H2ASN_MsgChoice AT_MTA_EvdoSysEventSetReq */
    ID_AT_MTA_EVDO_SIG_MASK_SET_REQ  = 0x004e, /* _H2ASN_MsgChoice AT_MTA_EvdoSigMaskSetReq */

    /* _H2ASN_MsgChoice AT_MTA_SetXcposrReq */
    ID_AT_MTA_XCPOSR_SET_REQ = 0x004F,
    /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_XCPOSR_QRY_REQ = 0x0050,
    /* _H2ASN_MsgChoice AT_MTA_SetXcposrrptReq */
    ID_AT_MTA_XCPOSRRPT_SET_REQ = 0x0051,
    /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_XCPOSRRPT_QRY_REQ      = 0x0052,
    ID_AT_MTA_CLEAR_HISTORY_FREQ_REQ = 0x0053, /* _H2ASN_MsgChoice AT_MTA_ClearHistoryFreqReq */

    /* _H2ASN_MsgChoice AT_MTA_SetSensorReq */
    ID_AT_MTA_SET_SENSOR_REQ = 0x0054,
    /* _H2ASN_MsgChoice AT_MTA_SetScreenReq */
    ID_AT_MTA_SET_SCREEN_REQ = 0x0055,
    /* _H2ASN_MsgChoice MTA_AT_FratIgnitionQryCnf */
    ID_AT_MTA_FRAT_IGNITION_QRY_REQ = 0x0056,
    /* _H2ASN_MsgChoice MTA_AT_FratIgnitionSetCnf */
    ID_AT_MTA_FRAT_IGNITION_SET_REQ = 0x0057,

    ID_AT_MTA_MODEM_TIME_SET_REQ = 0x0058,

    ID_AT_MTA_RX_TEST_MODE_SET_REQ = 0x0059,

    ID_AT_MTA_SLAVE_SET_REQ = 0x005A,

    ID_AT_MTA_BESTFREQ_SET_REQ = 0x005B, /* AT_MTA_BestfreqSetReq */
    ID_AT_MTA_BESTFREQ_QRY_REQ = 0x005C,

    ID_AT_MTA_RFIC_DIE_ID_QRY_REQ = 0x005D,

    ID_AT_MTA_CRRCONN_SET_REQ     = 0x005E,
    ID_AT_MTA_CRRCONN_QRY_REQ     = 0x005F,
    ID_AT_MTA_VTRLQUALRPT_SET_REQ = 0x0060,

    ID_AT_MTA_PMU_DIE_SN_QRY_REQ = 0x0061,

    ID_AT_MTA_MODEM_CAP_UPDATE_REQ = 0x0062,

    ID_AT_MTA_TAS_CFG_REQ = 0x0063,
    ID_AT_MTA_TAS_QRY_REQ = 0x0064,

    ID_AT_MTA_MIPI_WREX_REQ = 0x0065,
    ID_AT_MTA_MIPI_RDEX_REQ = 0x0066,

    ID_AT_MTA_RS_INFO_QRY_REQ = 0x0067,

    ID_AT_MTA_PHY_COM_CFG_SET_REQ = 0x0068,

    ID_AT_MTA_ERRCCAP_CFG_SET_REQ = 0x0069,
    ID_AT_MTA_ERRCCAP_QRY_SET_REQ = 0x006A,

    ID_AT_MTA_QRY_GSM_FREQLOCK_REQ  = 0x006B,
    ID_AT_MTA_DEL_CELLENTITY_REQ    = 0x006C,
    ID_AT_MTA_PSEUCELL_INFO_SET_REQ = 0x006D,

    ID_AT_MTA_POWER_DET_QRY_REQ = 0x006E, /* _H2ASN_MsgChoice AT_MTA_Reserve */

    ID_AT_MTA_MIPIREAD_SET_REQ = 0x006F,

    ID_AT_MTA_NO_CARD_MODE_SET_REQ = 0x0070,
    ID_AT_MTA_NO_CARD_MODE_QRY_REQ = 0x0071,

    /* _H2ASN_MsgChoice AT_MTA_ChrAlarmRlatCfgSetReq */
    ID_AT_MTA_CHRALARMRLAT_CFG_SET_REQ = 0x0072,

    ID_AT_MTA_ECC_CFG_SET_REQ = 0x0073,

    ID_AT_MTA_EPDU_SET_REQ = 0x0074,

    ID_AT_MTA_LTE_CA_CELL_RPT_CFG_SET_REQ = 0x0075,
    ID_AT_MTA_LTE_CA_CELL_RPT_CFG_QRY_REQ = 0x0076,
    ID_AT_MTA_LTE_CA_CFG_SET_REQ          = 0x0077,
    ID_AT_MTA_LTE_CA_CELLEX_QRY_REQ       = 0x0078,

    ID_AT_MTA_FINE_TIME_SET_REQ = 0x0079,
    /* _H2ASN_MsgChoice AT_MTA_GasAutotestQryPara    */
    ID_AT_MTA_GAS_AUTOTEST_QRY_REQ = 0x0080,

    ID_AT_MTA_COMM_BOOSTER_SET_REQ = 0x0081, /* _H2ASN_MsgChoice AT_MTA_CommBoosterSetReq */
    ID_AT_MTA_COMM_BOOSTER_QRY_REQ = 0x0082, /* _H2ASN_MsgChoice AT_MTA_CommBoosterQueryReq */

    ID_AT_MTA_NVLOAD_SET_REQ = 0x0083,

    ID_AT_MTA_SMS_DOMAIN_SET_REQ = 0x0084,
    ID_AT_MTA_SMS_DOMAIN_QRY_REQ = 0x0085,
    /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_AT_MTA_EPS_NETWORK_QRY_REQ = 0x0086,

    ID_AT_MTA_SET_SAMPLE_REQ = 0x0087,

    ID_AT_MTA_GPS_LOCSET_SET_REQ = 0x0088,

    ID_AT_MTA_CCLK_QRY_REQ = 0x0089,

    ID_AT_MTA_GAME_MODE_SET_REQ = 0x008A, /* _H2ASN_MsgChoice AT_MTA_COMM_GAME_MODE_SET_STRU */

    ID_AT_MTA_PSEUDBTS_SET_REQ = 0x008B,

    ID_AT_MTA_SUBCLFSPARAM_SET_REQ = 0x008C,
    ID_AT_MTA_SUBCLFSPARAM_QRY_REQ = 0x008D,

    ID_AT_MTA_NV_REFRESH_SET_REQ = 0x008E, /* _H2ASN_MsgChoice AT_MTA_NvRefreshSetReq */

#if (FEATURE_ON == FEATURE_PHONE_ENG_AT_CMD)
    ID_AT_MTA_SLT_TEST_SET_REQ = 0X008F,
#endif

    ID_AT_MTA_CDMA_MODEM_CAP_SET_REQ = 0x0090,

    ID_AT_MTA_CDMA_CAP_RESUME_SET_REQ = 0x0091,

    ID_AT_MTA_PHYMIPIWRITE_SET_REQ = 0x0092,

    ID_AT_MTA_FORCESYNC_SET_REQ = 0x0093,

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_LENDC_QRY_REQ       = 0x0094,
    ID_AT_MTA_NR_FREQLOCK_SET_REQ = 0x0095,
    ID_AT_MTA_NR_FREQLOCK_QRY_REQ = 0x0096,
#endif

    ID_AT_MTA_SET_LTEPWRDISS_REQ = 0x0097,

    ID_AT_MTA_GNSS_NTY = 0x0098,

    ID_AT_MTA_SFEATURE_QRY_REQ     = 0x0099,
    ID_AT_MTA_LOW_PWR_MODE_SET_REQ = 0x009A,
    ID_AT_MTA_LL2_COM_CFG_SET_REQ  = 0x009D,
    ID_AT_MTA_LL2_COM_CFG_QRY_REQ  = 0x009E,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_NL2_COM_CFG_SET_REQ = 0x009F,
    ID_AT_MTA_NL2_COM_CFG_QRY_REQ = 0x00A0,

    ID_AT_MTA_NRRCCAP_CFG_SET_REQ = 0x00A1,
    ID_AT_MTA_NRRCCAP_QRY_REQ     = 0x00A2,
    ID_AT_MTA_NRPWRCTRL_SET_REQ   = 0x00A3,
#endif

    ID_AT_MTA_SARREDUCTION_NTF = 0x00A4,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_SET_TRX_TAS_REQ          = 0x00A5,
    ID_AT_MTA_QRY_TRX_TAS_REQ          = 0x00A6,
    ID_AT_MTA_MULTI_PMU_DIE_ID_SET_REQ = 0x00A7,
    ID_AT_MTA_5G_OPTION_CFG_REQ        = 0X00A8,
    ID_AT_MTA_5G_OPTION_QRY_REQ        = 0X00A9,

    ID_AT_MTA_5G_NSSAI_SET_REQ = 0x00AA,
    ID_AT_MTA_5G_NSSAI_QRY_REQ = 0x00AB,
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_SET_NETMON_SSCELL_REQ = 0x00AE,
#endif

    ID_AT_MTA_RFFE_DIE_ID_QRY_REQ       = 0x00AF,
    ID_AT_MTA_OVERHEATING_CFG_SET_REQ   = 0x00B0,
    ID_AT_MTA_OVERHEATING_CFG_QRY_REQ   = 0x00B1,
    ID_AT_MTA_LRRC_UE_CAP_PARAM_SET_REQ = 0x00B2,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_NRRC_UE_CAP_PARAM_SET_REQ = 0x00B3,
#endif
    ID_AT_MTA_UART_TEST_REQ = 0x00B4,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_SET_LADN_RPT_REQ          = 0x00B5,
    ID_AT_MTA_QRY_LADN_INFO_REQ         = 0x00B6,
    ID_AT_MTA_NPDCP_SLEEP_THRES_CFG_REQ = 0x00B7,
    ID_AT_MTA_NR_SSB_ID_QRY_REQ         = 0x00B8,
    ID_AT_MTA_NR_NW_CAP_INFO_RPT_CFG_SET_REQ = 0x00BD,
#endif
    ID_AT_MTA_NV_REFRESH_RSP = 0x2002, /* ????AT->MTA??????????ID_MTA_NV_REFRESH_RSP???????? */

    /* MTA????AT?????? */
    ID_MTA_AT_CPOS_SET_CNF          = 0x1000, /* _H2ASN_MsgChoice MTA_AT_CposCnf        */
    ID_MTA_AT_CGPSCLOCK_SET_CNF     = 0x1001, /* _H2ASN_MsgChoice MTA_AT_CgpsclockCnf   */
    ID_MTA_AT_CPOSR_IND             = 0x1002, /* _H2ASN_MsgChoice MTA_AT_CposrInd       */
    ID_MTA_AT_XCPOSRRPT_IND         = 0x1003, /* _H2ASN_MsgChoice MTA_AT_XcposrrptInd   */
    ID_MTA_AT_APSEC_SET_CNF         = 0x1004, /* _H2ASN_MsgChoice MTA_AT_APSEC_CNF_STRU       */
    ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF = 0x1005, /* _H2ASN_MsgChoice MTA_AT_SimlockunlockCnf */

    ID_MTA_AT_QRY_NMR_CNF = 0x1006, /* _H2ASN_MsgChoice MTA_AT_QryNmrCnf */

    /* _H2ASN_MsgChoice MTA_AT_WrrAutotestQryCnf       */
    ID_MTA_AT_WRR_AUTOTEST_QRY_CNF = 0x1007,
    /* _H2ASN_MsgChoice MTA_AT_WrrCellinfoQryCnf       */
    ID_MTA_AT_WRR_CELLINFO_QRY_CNF = 0x1008,
    /* _H2ASN_MsgChoice MTA_AT_WrrMeanrptQryCnf        */
    ID_MTA_AT_WRR_MEANRPT_QRY_CNF = 0x1009,
    /* _H2ASN_MsgChoice MTA_AT_WrrFreqlockSetCnf       */
    ID_MTA_AT_WRR_FREQLOCK_SET_CNF = 0x100A,
    /* _H2ASN_MsgChoice MTA_AT_WrrRrcVersionSetCnf    */
    ID_MTA_AT_WRR_RRC_VERSION_SET_CNF = 0x100B,
    /* _H2ASN_MsgChoice MTA_AT_WrrCellsrhSetCnf        */
    ID_MTA_AT_WRR_CELLSRH_SET_CNF = 0x100C,
    /* _H2ASN_MsgChoice MTA_AT_WrrFreqlockQryCnf       */
    ID_MTA_AT_WRR_FREQLOCK_QRY_CNF = 0x100D,
    /* _H2ASN_MsgChoice MTA_AT_WrrRrcVersionQryCnf    */
    ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF = 0x100E,
    /* _H2ASN_MsgChoice MTA_AT_WrrCellsrhQryCnf        */
    ID_MTA_AT_WRR_CELLSRH_QRY_CNF = 0x100F,

    ID_MTA_AT_BODY_SAR_SET_CNF = 0x1010, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */

    ID_MTA_AT_CURC_QRY_CNF            = 0x1011, /* _H2ASN_MsgChoice MTA_AT_CurcQryCnf */
    ID_MTA_AT_UNSOLICITED_RPT_SET_CNF = 0x1012, /* _H2ASN_MsgChoice MTA_AT_UnsolicitedRptSetCnf */
    ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF = 0x1013, /* _H2ASN_MsgChoice MTA_AT_UnsolicitedRptQryCnf */

    ID_MTA_AT_IMEI_VERIFY_QRY_CNF   = 0x1014, /* _H2ASN_MsgChoice AT_MTA_Reserve */
    ID_MTA_AT_CGSN_QRY_CNF          = 0x1015, /* _H2ASN_MsgChoice MTA_AT_CgsnQryCnf */
    ID_MTA_AT_NCELL_MONITOR_SET_CNF = 0x1016, /* _H2ASN_MsgChoice MTA_AT_ResultCnf        */
    /* _H2ASN_MsgChoice MTA_AT_NcellMonitorQryCnf        */
    ID_MTA_AT_NCELL_MONITOR_QRY_CNF = 0x1017,
    /* _H2ASN_MsgChoice MTA_AT_NcellMonitorInd        */
    ID_MTA_AT_NCELL_MONITOR_IND = 0x1018,

    ID_MTA_AT_REFCLKFREQ_SET_CNF = 0x1019, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_REFCLKFREQ_QRY_CNF = 0x101A, /* _H2ASN_MsgChoice MTA_AT_RefclkfreqQryCnf */
    ID_MTA_AT_REFCLKFREQ_IND     = 0x101B, /* _H2ASN_MsgChoice MTA_AT_RefclkfreqInd */

    ID_MTA_AT_HANDLEDECT_SET_CNF = 0x101C, /* _H2ASN_MsgChoice MTA_AT_HandledectSetCnf */
    ID_MTA_AT_HANDLEDECT_QRY_CNF = 0x101D, /* _H2ASN_MsgChoice MTA_AT_HandledectQryCnf */

    ID_MTA_AT_PS_TRANSFER_IND = 0x101E, /* _H2ASN_MsgChoice MTA_AT_PsTransferInd */

    ID_MTA_AT_ECID_SET_CNF = 0x101F, /* _H2ASN_MsgChoice MTA_AT_EcidSetCnf */

    ID_MTA_AT_MIPICLK_QRY_CNF  = 0x1020, /* _H2ASN_MsgChoice MTA_AT_RfLcdMipiclkCnf */
    ID_MTA_AT_MIPICLK_INFO_IND = 0x1021, /* _H2ASN_MsgChoice MTA_AT_RfLcdMipiclkInd */

    ID_MTA_AT_SET_DPDTTEST_FLAG_CNF = 0x1022, /* _H2ASN_MsgChoice MTA_AT_SetDpdttestFlagCnf */
    ID_MTA_AT_SET_DPDT_VALUE_CNF    = 0x1023, /* _H2ASN_MsgChoice MTA_AT_SetDpdtValueCnf */
    ID_MTA_AT_QRY_DPDT_VALUE_CNF    = 0x1024, /* _H2ASN_MsgChoice MTA_AT_QryDpdtValueCnf */

    ID_MTA_AT_RRC_PROTECT_PS_CNF = 0x1025,
    ID_MTA_AT_PHY_INIT_CNF       = 0x1026,

    ID_MTA_AT_SET_JAM_DETECT_CNF = 0x1027, /* _H2ASN_MsgChoice MTA_AT_SetJamDetectCnf */
    ID_MTA_AT_JAM_DETECT_IND     = 0x1028, /* _H2ASN_MsgChoice MTA_AT_JamDetectInd */

    ID_MTA_AT_SET_FREQ_LOCK_CNF = 0x1029, /* _H2ASN_MsgChoice MTA_AT_SetFreqLockCnf */

    ID_MTA_AT_SET_GSM_FREQLOCK_CNF = 0x102A, /* _H2ASN_MsgChoice MTA_AT_SetGsmFreqlockCnf */

    ID_AT_MTA_SET_FEMCTRL_CNF = 0x102B,

    ID_MTA_AT_XPASS_INFO_IND = 0x102C,

    ID_MTA_AT_NVWRSECCTRL_SET_CNF = 0x102D,

    ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF = 0x102E, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_MBMS_PREFERENCE_SET_CNF     = 0x102F, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    /* _H2ASN_MsgChoice MTA_AT_MbmsSib16NetworkTimeQryCnf */
    ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF = 0x1030,
    /* _H2ASN_MsgChoice MTA_AT_MbmsBssiSignalLevelQryCnf */
    ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF = 0x1031,
    /* _H2ASN_MsgChoice MTA_AT_MbmsNetworkInfoQryCnf */
    ID_MTA_AT_NETWORK_INFO_QRY_CNF         = 0x1032,
    ID_MTA_AT_EMBMS_STATUS_QRY_CNF         = 0x1033, /* _H2ASN_MsgChoice MTA_AT_EmbmsStatusQryCnf */
    ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF = 0x1034, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_MBMS_SERVICE_EVENT_IND       = 0x1035, /* _H2ASN_MsgChoice MTA_AT_MbmsServiceEventInd */
    ID_MTA_AT_LTE_LOW_POWER_SET_CNF        = 0x1036, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_INTEREST_LIST_SET_CNF        = 0x1037, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF   = 0x1038, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    /* _H2ASN_MsgChoice MTA_AT_MbmsAvlServiceListQryCnf */
    ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF = 0x1039,
    ID_MTA_AT_LTE_WIFI_COEX_SET_CNF         = 0x103A, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF         = 0x103B, /* _H2ASN_MsgChoice MTA_AT_LteWifiCoexQryCnf */

    ID_MTA_AT_SET_FR_CNF = 0x103C,

    ID_MTA_AT_MEID_SET_CNF = 0x103d, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */

    ID_MTA_AT_RFICSSIRD_QRY_CNF = 0x103e,

    ID_MTA_AT_MEID_QRY_CNF = 0x103f, /* _H2ASN_MsgChoice MTA_AT_MeidQryCnf */

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)
    ID_MTA_AT_SET_M2M_FREQLOCK_CNF = 0x1040, /* _H2ASN_MsgChoice AT_MTA_SET_M2M_FREQLOCK_CNF_STRU */
    ID_MTA_AT_QRY_M2M_FREQLOCK_CNF = 0x1041, /* _H2ASN_MsgChoice MTA_AT_QRY_FREQLOCK_CNF_STRU */
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_LENDC_QRY_CNF       = 0x1042,
    ID_MTA_AT_LENDC_INFO_IND      = 0x1043,
    ID_MTA_AT_NR_FREQLOCK_SET_CNF = 0x1044,
    ID_MTA_AT_NR_FREQLOCK_QRY_CNF = 0x1045,
#endif

    ID_MTA_AT_TRANSMODE_QRY_CNF = 0x1052,

    ID_MTA_AT_UE_CENTER_SET_CNF = 0x1053,
    ID_MTA_AT_UE_CENTER_QRY_CNF = 0x1054, /* _H2ASN_MsgChoice MTA_AT_QryUeCenterCnf */

    ID_MTA_AT_SET_NETMON_SCELL_CNF = 0x1055, /* _H2ASN_MsgChoice MTA_AT_NetmonCellInfo */
    ID_MTA_AT_SET_NETMON_NCELL_CNF = 0x1056, /* _H2ASN_MsgChoice MTA_AT_NetmonCellInfo */

    ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ = 0x1057, /* _H2ASN_MsgChoice AT_MTA_QryAfcClkFreqXocoefReq */
    ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF = 0x1058, /* _H2ASN_MsgChoice MTA_AT_QryAfcClkFreqXocoefCnf */
    ID_MTA_AT_ANQUERY_QRY_CNF             = 0x1059, /* _H2ASN_MsgChoice MTA_AT_AntennaInfoQryCnf */
    ID_MTA_AT_CSNR_QRY_CNF                = 0x105A, /* _H2ASN_MsgChoice MTA_AT_CsnrQryCnf */
    ID_MTA_AT_CSQLVL_QRY_CNF              = 0x105B, /* _H2ASN_MsgChoice MTA_AT_CsqlvlQryCnf */

    ID_MTA_AT_EVDO_SYS_EVENT_CNF       = 0x105c, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_EVDO_SIG_MASK_CNF        = 0x105d, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_EVDO_REVA_RLINK_INFO_IND = 0x105e,
    ID_MTA_AT_EVDO_SIG_EXEVENT_IND     = 0x105f,

    /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_XCPOSR_SET_CNF = 0x1060,
    /* _H2ASN_MsgChoice MTA_AT_QryXcposrCnf */
    ID_MTA_AT_XCPOSR_QRY_CNF = 0x1061,
    /* _H2ASN_MsgChoice MTA_AT_ResultCnf */
    ID_MTA_AT_XCPOSRRPT_SET_CNF = 0x1062,
    /* _H2ASN_MsgChoice MTA_AT_QryXcposrrptCnf */
    ID_MTA_AT_XCPOSRRPT_QRY_CNF      = 0x1063,
    ID_MTA_AT_CLEAR_HISTORY_FREQ_CNF = 0x1064, /* _H2ASN_MsgChoice MTA_AT_ResultCnf */

    ID_MTA_AT_SET_SENSOR_CNF = 0x1065, /* _H2ASN_MsgChoice MTA_AT_SetSensorCnf */
    ID_MTA_AT_SET_SCREEN_CNF = 0x1066, /* _H2ASN_MsgChoice MTA_AT_SetScreenCnf */
    /* _H2ASN_MsgChoice MTA_AT_FratIgnitionQryCnf */
    ID_MTA_AT_FRAT_IGNITION_QRY_CNF = 0x1067,
    /* _H2ASN_MsgChoice MTA_AT_FratIgnitionSetCnf */
    ID_MTA_AT_FRAT_IGNITION_SET_CNF = 0x1068,

    ID_MTA_AT_SET_MODEM_TIME_CNF = 0x1069,

    ID_MTA_AT_RX_TEST_MODE_SET_CNF = 0x106A,

    ID_MTA_AT_AFC_CLK_UNLOCK_CAUSE_IND = 0x106B,

    ID_MTA_AT_SIB16_TIME_UPDATE_IND = 0x106C,

    ID_MTA_AT_SLAVE_SET_CNF = 0x106D,

    ID_MTA_AT_BESTFREQ_SET_CNF = 0x106E,
    /* _H2ASN_MsgChoice MTA_AT_BEST_FREQ_CASE_STRU */
    ID_MTA_AT_BEST_FREQ_INFO_IND = 0x106F,
    ID_MTA_AT_BESTFREQ_QRY_CNF   = 0x1070,

    ID_MTA_AT_RFIC_DIE_ID_QRY_CNF = 0x1071,

    ID_MTA_AT_CRRCONN_SET_CNF     = 0x1072,
    ID_MTA_AT_CRRCONN_QRY_CNF     = 0x1073,
    ID_MTA_AT_CRRCONN_STATUS_IND  = 0x1074,
    ID_MTA_AT_VTRLQUALRPT_SET_CNF = 0x1075,
    ID_MTA_AT_RL_QUALITY_INFO_IND = 0x1076,
    ID_MTA_AT_VIDEO_DIAG_INFO_RPT = 0x1077,

    ID_MTA_AT_PMU_DIE_SN_QRY_CNF = 0x1078,

    ID_MTA_AT_MODEM_CAP_UPDATE_CNF = 0x1079,

    /* _H2ASN_MsgChoice MTA_AT_LteCategoryInfoInd */
    ID_MTA_AT_LTE_CATEGORY_INFO_IND = 0x107A,

    ID_MTA_AT_TAS_TEST_CFG_CNF = 0x1080,
    ID_MTA_AT_TAS_TEST_QRY_CNF = 0x1081,

    ID_MTA_AT_ACCESS_STRATUM_REL_IND = 0x1082,

    ID_MTA_AT_MIPI_WREX_CNF = 0x1083,
    ID_MTA_AT_MIPI_RDEX_CNF = 0x1084,

    ID_MTA_AT_RS_INFO_QRY_CNF = 0x1085,

    ID_MTA_AT_PHY_COM_CFG_SET_CNF = 0x1086,

    ID_MTA_AT_ERRCCAP_CFG_SET_CNF = 0x1087,
    ID_MTA_AT_ERRCCAP_QRY_SET_CNF = 0x1088,

    /* _H2ASN_MsgChoice MTA_AT_QryGsmFreqlockCnf */
    ID_MTA_AT_QRY_GSM_FREQLOCK_CNF = 0x1089,
    ID_MTA_AT_DEL_CELLENTITY_CNF   = 0x108A,

    ID_MTA_AT_POWER_DET_QRY_CNF = 0x108B,

    ID_MTA_AT_PSEUCELL_INFO_SET_CNF = 0x108C,

    ID_MTA_AT_MIPIREAD_SET_CNF = 0x108D,

    ID_MTA_AT_NO_CARD_MODE_SET_CNF = 0x108E,
    ID_MTA_AT_NO_CARD_MODE_QRY_CNF = 0x108F,

    ID_MTA_AT_CHRALARMRLAT_CFG_SET_CNF = 0x1090,

    ID_MTA_AT_ECC_CFG_SET_CNF = 0x1091,
    ID_MTA_AT_ECC_STATUS_IND  = 0x1092,

    ID_MTA_AT_EPDU_SET_CNF   = 0x1093,
    ID_MTA_AT_EPDUR_DATA_IND = 0x1094,

    ID_MTA_AT_LTE_CA_CFG_SET_CNF     = 0x1095,
    ID_MTA_AT_LTE_CA_CELLEX_QRY_CNF  = 0x1096,
    ID_MTA_AT_LTE_CA_CELLEX_INFO_NTF = 0x1097,

    ID_MTA_AT_LTE_CA_CELL_RPT_CFG_SET_CNF = 0x1098,
    ID_MTA_AT_LTE_CA_CELL_RPT_CFG_QRY_CNF = 0x1099,

    ID_MTA_AT_FINE_TIME_SET_CNF = 0x109A,
    ID_MTA_AT_SIB_FINE_TIME_NTF = 0x109B,
    ID_MTA_AT_LPP_FINE_TIME_NTF = 0x109C,

    ID_MTA_AT_PHY_COMM_ACK_IND = 0x109D,

    /* _H2ASN_MsgChoice MTA_AT_GasAutotestQryCnf */
    ID_MTA_AT_GAS_AUTOTEST_QRY_CNF = 0x109E,

    ID_MTA_AT_COMM_BOOSTER_SET_CNF   = 0x109F, /* _H2ASN_MsgChoice MTA_AT_CommBoosterSetCnf */
    ID_MTA_AT_COMM_BOOSTER_IND       = 0x10A0, /* _H2ASN_MsgChoice MTA_AT_CommBoosterInd */
    ID_MTA_AT_COMM_BOOSTER_QUERY_CNF = 0x10A1, /* _H2ASN_MsgChoice MTA_AT_CommBoosterQueryCnf */

    ID_MTA_AT_NVLOAD_SET_CNF = 0x10A2,

    ID_MTA_AT_SMS_DOMAIN_SET_CNF = 0x10A3, /* _H2ASN_MsgChoice MTA_AT_SmsDomainSetCnf */
    ID_MTA_AT_SMS_DOMAIN_QRY_CNF = 0x10A4, /* _H2ASN_MsgChoice MTA_AT_SmsDomainQryCnf */

    /* _H2ASN_MsgChoice MTA_AT_EpsNetworkQryCnf */
    ID_MTA_AT_EPS_NETWORK_QRY_CNF = 0x10A5,
    /* _H2ASN_MsgChoice MTA_AT_EPS_NETWORK_INFO_IND_STRU */
    ID_MTA_AT_EPS_NETWORK_INFO_IND = 0x10A6,

    ID_MTA_AT_SET_SAMPLE_CNF = 0x10A7,

    ID_MTA_AT_GPS_LOCSET_SET_CNF = 0x10A8,

    ID_MTA_AT_CCLK_QRY_CNF = 0x10A9,

    ID_MTA_AT_TEMP_PROTECT_IND = 0x10AA,

    ID_AT_MTA_GAME_MODE_SET_CNF = 0x10AB, /* _H2ASN_MsgChoice MTA_AT_GameModeSetCfn */

    ID_MTA_AT_PSEUDBTS_SET_CNF = 0x10AC,

    ID_MTA_AT_SUBCLFSPARAM_SET_CNF = 0X10AD,
    ID_MTA_AT_SUBCLFSPARAM_QRY_CNF = 0X10AE,

    ID_MTA_AT_NV_REFRESH_SET_CNF = 0x10AF, /* _H2ASN_MsgChoice MTA_AT_NvRefreshSetCnf */

#if (FEATURE_ON == FEATURE_PHONE_ENG_AT_CMD)
    ID_AT_MTA_SLT_TEST_SET_CNF = 0x10B0,
#endif

    ID_MTA_AT_CDMA_MODEM_CAP_SET_CNF = 0x10B1,

    ID_MTA_AT_CDMA_CAP_RESUME_SET_CNF = 0x10B2,

    ID_MTA_AT_PHYMIPIWRITE_SET_CNF = 0x10B3,

    ID_MTA_AT_SFEATURE_QRY_CNF     = 0x10B4,
    ID_MTA_AT_LOW_PWR_MODE_SET_CNF = 0x10B5,

    ID_MTA_AT_LL2_COM_CFG_SET_CNF = 0x10B8,
    ID_MTA_AT_LL2_COM_CFG_QRY_CNF = 0x10B9,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_NL2_COM_CFG_SET_CNF = 0x10BA,
    ID_MTA_AT_NL2_COM_CFG_QRY_CNF = 0x10BB,

    ID_MTA_AT_NRRCCAP_CFG_SET_CNF        = 0x10BC,
    ID_MTA_AT_NRRCCAP_QRY_CNF            = 0x10BD,
    ID_MTA_AT_NRPWRCTRL_SET_CNF          = 0x10BE,
    ID_MTA_AT_NPDCP_SLEEP_TRHRES_CFG_CNF = 0x10BF,
    ID_MTA_AT_NR_NW_CAP_INFO_REPORT_IND      = 0x10C4,
    ID_MTA_AT_NR_NW_CAP_INFO_RPT_CFG_SET_CNF = 0x10C5,
#endif

    ID_AT_MTA_QRY_JAM_DETECT_REQ = 0x1100,
    ID_MTA_AT_QRY_JAM_DETECT_CNF = 0x1101,

    ID_MTA_AT_PSEUD_BTS_IDENT_IND = 0x1102,

    ID_MTA_AT_FORCESYNC_SET_CNF = 0X1103,

    ID_AT_MTA_SET_LTEPWRDISS_CNF = 0X1104,

    ID_AT_MTA_DCXO_SAMPLE_QRY_REQ = 0X1105,
    ID_MTA_AT_DCXO_SAMPLE_QRY_CNF = 0X1106,

    ID_AT_MTA_MCS_SET_REQ     = 0X1107,
    ID_MTA_AT_MCS_SET_CNF     = 0X1108,
    ID_AT_MTA_TXPOWER_QRY_REQ = 0X1109,
    ID_MTA_AT_TXPOWER_QRY_CNF = 0X110A,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_AT_MTA_NTXPOWER_QRY_REQ = 0X110B,
    ID_MTA_AT_NTXPOWER_QRY_CNF = 0X110C,
#endif
    ID_AT_MTA_HFREQINFO_QRY_REQ = 0X110D,
    ID_MTA_AT_HFREQINFO_QRY_CNF = 0X110E,
    ID_MTA_AT_HFREQINFO_IND     = 0X110F,

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_SET_TRX_TAS_CNF = 0X1110,
    ID_MTA_AT_QRY_TRX_TAS_CNF = 0X1111,

#endif

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_5G_OPTION_SET_CNF = 0X1112,
    ID_MTA_AT_5G_OPTION_QRY_CNF = 0X1113,
    ID_MTA_AT_5G_NSSAI_SET_CNF  = 0X1114,
    ID_MTA_AT_5G_NSSAI_QRY_CNF  = 0X1115,
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_SET_NETMON_SSCELL_CNF = 0x1118,
#endif
    ID_MTA_AT_RFFE_DIE_ID_QRY_CNF       = 0x1119,
    ID_MTA_AT_OVERHEATING_CFG_SET_CNF   = 0x111A,
    ID_MTA_AT_OVERHEATING_CFG_QRY_CNF   = 0x111B,
    ID_MTA_AT_LRRC_UE_CAP_PARA_INFO_NTF = 0x111C,
    ID_MTA_AT_LRRC_UE_CAP_PARA_SET_CNF  = 0x111D,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_NRRC_UE_CAP_PARA_SET_CNF  = 0x111E,
    ID_MTA_AT_NRRC_UE_CAP_PARA_INFO_NTF = 0x111F,
#endif

    ID_MTA_AT_UART_TEST_CNF      = 0x1120,
    ID_MTA_AT_UART_TEST_RSLT_IND = 0X1121,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_SET_LADN_RPT_CNF  = 0x1122,
    ID_MTA_AT_QRY_LADN_INFO_CNF = 0x1123,
    ID_MTA_AT_LADN_INFO_IND     = 0x1124,
#endif
    ID_MTA_AT_HSRCELLINFO_IND = 0x1125,
#if (FEATURE_ON == FEATURE_UE_MODE_NR)
    ID_MTA_AT_NR_SSB_ID_QRY_CNF = 0x1126,
#endif

#if (FEATURE_LTEV_WL == FEATURE_ON)
    ID_MTA_AT_FILE_WRITE_CNF = 0x1130,
    ID_MTA_AT_FILE_READ_CNF  = 0x1131,
    ID_AT_MTA_FILE_WRITE_REQ = 0x1132,
    ID_AT_MTA_FILE_READ_REQ  = 0x1133,
#endif
    ID_AT_MTA_LTE_CONN_RECOVERY_NTF = 0x1134,

#if (FEATURE_UE_MODE_NR == FEATURE_ON)
    ID_AT_MTA_NRPHY_COM_CFG_SET_REQ = 0x1135,
    ID_MTA_AT_NRPHY_COM_CFG_SET_CNF = 0x1136,
#endif
    /* ???????????? */
    ID_AT_MTA_MSG_TYPE_BUTT

};
typedef VOS_UINT32 AT_MTA_MsgTypeUint32;


enum AT_SetSltTestType {
    AT_SET_SGMII_TEST      = 1, /* SGMII???????????????? */
    AT_SET_RGMII_TEST      = 2, /* RGMII???????????????? */
    AT_SET_PCIE_TEST       = 3, /* PCIe????PHY???????????? */
    AT_SET_SPI_TEST        = 4, /* SPI master??slave???????????? */
    AT_SET_SDCARD_TEST     = 5, /* MMC0??????SD?????????? */
    AT_SET_L2CACHE_TEST    = 6, /* L2CACHE???? */
    AT_SET_HIFI_TEST       = 7, /* HIFI???? */
    AT_SET_SLT_SERDES_TEST = 8, /* SERDES ???? */
    AT_SET_SLT_ALINK_TEST  = 9, /* alink ???? */
    AT_SET_SLT_TEST_BUTT
};
typedef VOS_UINT8 AT_SetSltTestTypeUint8;


enum MTA_AT_Result {
    /* ??AT???????????????????? */
    MTA_AT_RESULT_NO_ERROR = 0x000000, /* ???????????? */
    MTA_AT_RESULT_ERROR,               /* ???????????? */
    MTA_AT_RESULT_INCORRECT_PARAMETERS,
    MTA_AT_RESULT_OPTION_TIMEOUT,
    MTA_AT_RESULT_OPERATION_NOT_ALLOWED, /* ?????????????? */
    MTA_AT_RESULT_FUNC_DISABLE,          /* ???????????????? */
    /* ????????AT?????????????? */

    /* ?????????????????? */
    MTA_AT_RESULT_DEVICE_ERROR_BASE = 0x100000,
    MTA_AT_RESULT_DEVICE_SEC_IDENTIFY_FAIL,         /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL,        /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_DK_INCORRECT,          /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_UNLOCK_KEY_INCORRECT,  /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_LEN_ERROR,   /* ?????????????? */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_VALUE_ERROR, /* ???????????? */
    MTA_AT_RESULT_DEVICE_SEC_PH_PHYNUM_TYPE_ERROR,  /* ?????????????? */
    MTA_AT_RESULT_DEVICE_SEC_RSA_ENCRYPT_FAIL,      /* RSA???????? */
    MTA_AT_RESULT_DEVICE_SEC_RSA_DECRYPT_FAIL,      /* RSA???????? */
    MTA_AT_RESULT_DEVICE_SEC_GET_RAND_NUMBER_FAIL,  /* ??????????????(crypto_rand) */
    MTA_AT_RESULT_DEVICE_SEC_WRITE_HUK_FAIL,        /* HUK???????? */
    MTA_AT_RESULT_DEVICE_SEC_FLASH_ERROR,           /* Flash???? */
    MTA_AT_RESULT_DEVICE_SEC_NV_ERROR,              /* NV???????? */
    MTA_AT_RESULT_DEVICE_SEC_OTHER_ERROR,           /* ???????? */

    /* ?????????????????? */
    MTA_AT_RESULT_PRICMD_ERROR_BASE = 0x200000,

    MTA_AT_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_ResultUint32;


enum MTA_AT_ResultType {
    MTA_AT_RESULT_TYPE_NULL = 0x00,
    MTA_AT_RESULT_TYPE_LTE  = 0x01,
    MTA_AT_RESULT_TYPE_NR   = 0x02,
    MTA_AT_RESULT_TYPE_DC   = 0x03,
    MTA_AT_RESULT_TYPE_BUTT
};
typedef VOS_UINT8 MTA_AT_ResultTypeUint8;

enum MTA_AT_Cgpsclock {
    MTA_AT_CGPSCLOCK_STOP = 0,
    MTA_AT_CGPSCLOCK_START,
    MTA_AT_CGPSCLOCK_BUTT
};
typedef VOS_UINT32 MTA_AT_CgpsclockUint32;


enum MTA_AT_CposOperateType {
    MTA_AT_CPOS_SEND = 0,
    MTA_AT_CPOS_CANCEL,
    MTA_AT_CPOS_BUTT
};
typedef VOS_UINT32 MTA_AT_CposOperateTypeUint32;


enum AT_MTA_PersCategory {
    AT_MTA_PERS_CATEGORY_NETWORK          = 0x00, /* Category: ???? */
    AT_MTA_PERS_CATEGORY_NETWORK_SUBSET   = 0x01, /* Category: ?????? */
    AT_MTA_PERS_CATEGORY_SERVICE_PROVIDER = 0x02, /* Category: ??SP */
    AT_MTA_PERS_CATEGORY_CORPORATE        = 0x03, /* Category: ?????? */
    AT_MTA_PERS_CATEGORY_SIM_USIM         = 0x04, /* Category: ??(U)SIM?? */

    AT_MTA_PERS_CATEGORY_BUTT
};
typedef VOS_UINT8 AT_MTA_PersCategoryUint8;


enum AT_MTA_RptGeneralCtrlType {
    AT_MTA_RPT_GENERAL_CONTROL_NO_REPORT = 0x00, /* ?????????????????? */
    AT_MTA_RPT_GENERAL_CONTROL_REPORT    = 0x01, /* ?????????????????? */
    AT_MTA_RPT_GENERAL_CONTROL_CUSTOM    = 0x02, /* ??BIT???????????????????????? */

    AT_MTA_RPT_GENERAL_CONTROL_BUTT
};
typedef VOS_UINT8 AT_MTA_RptGeneralCtrlTypeUint8;


enum AT_MTA_RptSetType {
    AT_MTA_SET_MODE_RPT_TYPE = 0, /* Category: ???????????????????????? */
    AT_MTA_SET_SRVST_RPT_TYPE,
    AT_MTA_SET_RSSI_RPT_TYPE,
    AT_MTA_SET_TIME_RPT_TYPE,
    AT_MTA_SET_CTZR_RPT_TYPE,
    AT_MTA_SET_SIMST_RPT_TYPE,
    AT_MTA_SET_CREG_RPT_TYPE,
    AT_MTA_SET_CGREG_RPT_TYPE,
    AT_MTA_SET_CEREG_RPT_TYPE,
    AT_MTA_SET_CSID_RPT_TYPE,
    AT_MTA_SET_CLOCINFO_RPT_TYPE,
    AT_MTA_SET_MTREATTACH_RPT_TYPE,
    AT_MTA_SET_CENFS_RPT_TYPE,
    AT_MTA_SET_C5GREG_RPT_TYPE,

    AT_MTA_SET_LENDC_RPT_TYPE,

    AT_MTA_SET_RRCSTAT_RPT_TYPE,
    AT_MTA_SET_HFREQINFO_RPT_TYPE,

    AT_MTA_SET_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RptSetTypeUint32;


enum AT_MTA_RptQryType {
    AT_MTA_QRY_TIME_RPT_TYPE = 0,
    AT_MTA_QRY_CTZR_RPT_TYPE,
    AT_MTA_QRY_CSSN_RPT_TYPE,
    AT_MTA_QRY_CUSD_RPT_TYPE,
    AT_MTA_QRY_RPT_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RptQryTypeUint32;


enum AT_MTA_CmdRptFlg {
    AT_MTA_CMD_RPT_FLG_OFF = 0, /* AT?????????????? */
    AT_MTA_CMD_RPT_FLG_ON,      /* AT???????????? */
    AT_MTA_CMD_RPT_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_CmdRptFlgUint8;

enum AT_MTA_ClearFreqFlg {
    AT_MTA_CLEAR_FREQ_FLG_NOT_CSG_HISTORY_FREQ = 0, /* ??????CSG???????? */
    AT_MTA_CLEAR_FREQ_FLG_CSG_HISTORY_FREQ,         /* ????CSG???????? */
    AT_MTA_CLEAR_FREQ_FLG_ALL_FREQ,                 /* ???????????????? */
    AT_MTA_CLEAR_FREQ_FLG_BUTT
};
typedef VOS_UINT8 AT_MTA_ClearFreqFlgUint8;


enum AT_MTA_CmdRatmode {
    AT_MTA_CMD_RATMODE_GSM = 0,
    AT_MTA_CMD_RATMODE_WCDMA,
    AT_MTA_CMD_RATMODE_LTE,
    AT_MTA_CMD_RATMODE_TD,
    AT_MTA_CMD_RATMODE_CDMA,
    AT_MTA_CMD_RATMODE_NR,
    AT_MTA_CMD_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_CmdRatmodeUint8;


enum AT_MTA_CmdSignaling {
    AT_MTA_CMD_SIGNALING_MODE    = 0, /* ???????? */
    AT_MTA_CMD_NONSIGNALING_MODE = 1, /* ?????????? */

    AT_MTA_CMD_NONSIGNALING_BUTT
};
typedef VOS_UINT8 AT_MTA_CmdSignalingUint8;


enum AT_MTA_TrxTasCmd {
    AT_MTA_TRX_TAS_CMD_CLOSE_ALGORITHM = 0, /* ???????? */
    AT_MTA_TRX_TAS_CMD_SET_PARA        = 1, /* ???????? */
    AT_MTA_TRX_TAS_CMD_OPEN_ALGORITHM  = 2, /* ???????? */

    AT_MTA_TRX_TAS_CMD_BUTT
};
typedef VOS_UINT8 AT_MTA_TrxTasCmdUint8;


enum MTA_AT_JamResult {
    MTA_AT_JAM_RESULT_JAM_DISAPPEARED = 0x00, /* ?????????????? */
    MTA_AT_JAM_RESULT_JAM_DISCOVERED,         /* ???????? */

    MTA_AT_JAM_RESULT_BUTT
};
typedef VOS_UINT32 MTA_AT_JamResultUint32;


enum AT_MTA_FreqlockRatmode {
    AT_MTA_FREQLOCK_RATMODE_GSM = 0x01,
    AT_MTA_FREQLOCK_RATMODE_WCDMA,
    AT_MTA_FREQLOCK_RATMODE_LTE,
    AT_MTA_FREQLOCK_RATMODE_CDMA1X,
    AT_MTA_FREQLOCK_RATMODE_TD,
    AT_MTA_FREQLOCK_RATMODE_WIMAX,
    AT_MTA_FREQLOCK_RATMODE_EVDO,

    AT_MTA_FREQLOCK_RATMODE_BUTT
};
typedef VOS_UINT8 AT_MTA_FreqlockRatmodeUint8;


enum AT_MTA_GsmBand {
    AT_MTA_GSM_BAND_850 = 0x00,
    AT_MTA_GSM_BAND_900,
    AT_MTA_GSM_BAND_1800,
    AT_MTA_GSM_BAND_1900,

    AT_MTA_GSM_BAND_BUTT
};
typedef VOS_UINT16 AT_MTA_GsmBandUint16;


enum AT_MTA_Cfg {
    AT_MTA_CFG_DISABLE = 0,
    AT_MTA_CFG_ENABLE  = 1,
    AT_MTA_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_CfgUint8;


enum AT_MTA_MbmsServiceStateSet {
    AT_MTA_MBMS_SERVICE_STATE_SET_ACTIVE       = 0,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE     = 1,
    AT_MTA_MBMS_SERVICE_STATE_SET_DEACTIVE_ALL = 2,
    AT_MTA_MBMS_SERVICE_STATE_SET_BUTT
};
typedef VOS_UINT8 AT_MTA_MbmsServiceStateSetUint8;


enum AT_MTA_MbmsCastMode {
    AT_MTA_MBMS_CAST_MODE_UNICAST   = 0,
    AT_MTA_MBMS_CAST_MODE_MULTICAST = 1,
    AT_MTA_MBMS_CAST_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_MbmsCastModeUint8;


enum MTA_AT_EmbmsFuntionalityStatus {
    MTA_AT_EMBMS_FUNTIONALITY_OFF = 0,
    MTA_AT_EMBMS_FUNTIONALITY_ON  = 1,
    MTA_AT_EMBMS_FUNTIONALITY_STATUS_BUTT
};
typedef VOS_UINT8 MTA_AT_EmbmsFuntionalityStatusUint8;


enum MTA_AT_MbmsServiceEvent {
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_CHANGE    = 0,
    MTA_AT_MBMS_SERVICE_EVENT_NO_SERVICE        = 1,
    MTA_AT_MBMS_SERVICE_EVENT_ONLY_UNICAST      = 2,
    MTA_AT_MBMS_SERVICE_EVENT_SERVICE_AVAILABLE = 3,
    MTA_AT_MBMS_SERVICE_EVENT_BUTT
};
typedef VOS_UINT8 MTA_AT_MbmsServiceEventUint8;


enum AT_MTA_CoexBwType {
    AT_MTA_COEX_BAND_WIDTH_6RB   = 0, /* ????1.4M */
    AT_MTA_COEX_BAND_WIDTH_15RB  = 1, /* ????3M */
    AT_MTA_COEX_BAND_WIDTH_25RB  = 2, /* ????5M */
    AT_MTA_COEX_BAND_WIDTH_50RB  = 3, /* ????10M */
    AT_MTA_COEX_BAND_WIDTH_75RB  = 4, /* ????15M */
    AT_MTA_COEX_BAND_WIDTH_100RB = 5, /* ????20M */
    AT_MTA_COEX_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 AT_MTA_CoexBwTypeUint16;


enum AT_MTA_CoexCfg {
    AT_MTA_COEX_CFG_DISABLE = 0,
    AT_MTA_COEX_CFG_ENABLE  = 1,
    AT_MTA_COEX_CFG_BUTT
};
typedef VOS_UINT16 AT_MTA_CoexCfgUint16;


enum AT_MTA_LteLowPower {
    AT_MTA_LTE_LOW_POWER_NORMAL = 0,
    AT_MTA_LTE_LOW_POWER_LOW    = 1,
    AT_MTA_LTE_LOW_POWER_BUTT
};
typedef VOS_UINT8 AT_MTA_LteLowPowerUint8;


enum AT_MTA_MbmsPriority {
    AT_MTA_MBMS_PRIORITY_UNICAST = 0,
    AT_MTA_MBMS_PRIORITY_MBMS    = 1,
    AT_MTA_MBMS_PRIORITY_BUTT
};
typedef VOS_UINT8 AT_MTA_MbmsPriorityUint8;

enum AT_MTA_UeCenterType {
    AT_MTA_UE_CENTER_VOICE_CENTRIC = 0,
    AT_MTA_UE_CENTER_DATA_CENTRIC  = 1,
    AT_MTA_UE_CENTER_BUTT
};
typedef VOS_UINT32 AT_MTA_UeCenterTypeUint32;


enum AT_MTA_BodySarState {
    AT_MTA_BODY_SAR_OFF = 0, /* Body SAR???????? */
    AT_MTA_BODY_SAR_ON,      /* Body SAR???????? */
    AT_MTA_BODY_SAR_STATE_BUTT
};
typedef VOS_UINT16 AT_MTA_BodySarStateUint16;


enum MTA_AT_RefclockStatus {
    MTA_AT_REFCLOCK_UNLOCKED = 0, /* GPS?????????????????????? */
    MTA_AT_REFCLOCK_LOCKED,       /* GPS???????????????????? */
    MTA_AT_REFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 MTA_AT_RefclockStatusUint16;


enum MTA_AT_GphyXpassMode {
    MTA_AT_GPHY_XPASS_MODE_DISABLE = 0, /* ??XPASS?????????????? */
    MTA_AT_GPHY_XPASS_MODE_ENABLE,      /* XPASS?????????????? */
    MTA_AT_GPHY_XPASS_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_GphyXpassModeUint16;


enum MTA_AT_WphyHighwayMode {
    MTA_AT_WPHY_HIGHWAY_MODE_DISABLE = 0, /* W?????????? */
    MTA_AT_WPHY_HIGHWAY_MODE_ENABLE,      /* W???????? */
    MTA_AT_WPHY_HIGHWAY_MODE_BUTT
};
typedef VOS_UINT16 MTA_AT_WphyHighwayModeUint16;


enum MTA_AT_NetmonGsmState {
    MTA_AT_NETMON_GSM_STATE_INIT            = 0,
    MTA_AT_NETMON_GSM_STATTE_WAIT_CELL_INFO = 1,
    MTA_AT_NETMON_GSM_STATTE_WAIT_TA        = 2,
    MTA_AT_NETMON_GSM_STATTE_BUTT
};

typedef VOS_UINT32 MTA_AT_NetmonGsmStateUint32;



enum MTA_AT_NetmonCellInfoRat {
    MTA_AT_NETMON_CELL_INFO_GSM       = 0,
    MTA_AT_NETMON_CELL_INFO_UTRAN_FDD = 1,
    MTA_AT_NETMON_CELL_INFO_UTRAN_TDD = 2,
    MTA_AT_NETMON_CELL_INFO_LTE       = 3,
    MTA_AT_NETMON_CELL_INFO_NR        = 4,
    MTA_AT_NETMON_CELL_INFO_RAT_BUTT
};
typedef VOS_UINT32 MTA_AT_NetmonCellInfoRatUint32;



enum MTA_TAF_CTZR_TYPE {
    MTA_TAF_CTZR_OFF  = 0x00, /* CTZR?????? */
    MTA_TAF_CTZR_CTZV = 0x01, /* CTZR:CTZV */
    MTA_TAF_CTZR_CTZE = 0x02, /* CTZR:CTZE */
    MTA_TAF_CTZR_BUTT
};
typedef VOS_UINT32 MTA_TAF_CtzrTypeUint32;


enum AT_MTA_AfcClkStatus {
    AT_MTA_AFC_CLK_UNLOCKED = 0, /* AFC UNLOCKED */
    AT_MTA_AFC_CLK_LOCKED,       /* AFC LOCKED */

    AT_MTA_AFC_CLK_STATUS_BUTT
};
typedef VOS_UINT32 AT_MTA_AfcClkStatusUint32;


enum AT_MTA_XcposrCfg {
    AT_MTA_XCPOSR_CFG_DISABLE = 0, /* ?????????????? */
    AT_MTA_XCPOSR_CFG_ENABLE,      /* ???????????? */
    AT_MTA_XCPOSR_CFG_BUTT
};
typedef VOS_UINT8 AT_MTA_XcposrCfgUnit8;


enum AT_MTA_FratIgnition {
    AT_MTA_FRAT_IGNITION_STATT_OFF = 0, /* ?????????????? */
    AT_MTA_FRAT_IGNITION_STATT_ON,      /* ???????????? */
    AT_MTA_FRAT_IGNITION_STATT_BUTT
};
typedef VOS_UINT8 AT_MTA_FratIgnitionUnit8;


enum MTA_AT_AfcClkUnlockCause {
    MTA_AT_AFC_CLK_UNLOCK_CAUSE_SLEEP,

    MTA_AT_AFC_CLK_UNLOCK_CAUSE_BUTT
};
typedef VOS_UINT16 MTA_AT_AfcClkUnlockCauseUint16;


enum MTA_AT_ModemId {
    MTA_AT_MODEM_ID_0 = 0,
    MTA_AT_MODEM_ID_1,
    MTA_AT_MODEM_ID_2,

    MTA_AT_MODEM_ID_BUTT
};
typedef VOS_UINT8 MTA_AT_ModemIdUint8;


enum MTA_AT_RatMode {
    MTA_AT_RAT_MODE_GSM     = 0,
    MTA_AT_RAT_MODE_WCDMA   = 1,
    MTA_AT_RAT_MODE_LTE     = 2,
    MTA_AT_RAT_MODE_TDSCDMA = 3,
    MTA_AT_RAT_MODE_CDMA_1X = 4,
    MTA_AT_RAT_MODE_HRPD    = 5,
    MTA_AT_RAT_MODE_NR      = 6,
    MTA_AT_RAT_MODE_BUTT
};
typedef VOS_UINT8 MTA_AT_RatModeUint8;


enum AT_MTA_RatModeEnum {
    AT_MTA_RAT_MODE_LTE = 0,
    AT_MTA_RAT_MODE_NR  = 1,
    AT_MTA_RAT_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_RatModeUint8;


enum MTA_AT_DayLightSavingInd {
    MTA_AT_NO_ADJUST = 0,
    MTA_AT_ONE_HOUR  = 1,
    MTA_AT_TWO_HOUR  = 2,
    MTA_AT_HOUR_BUTT
};
typedef VOS_UINT8 MTA_AT_DayLightSavingIndUint8;


enum MTA_AT_TimeType {
    MTA_AT_LOCAL_TIME     = 1,
    MTA_AT_GPS_TIME       = 2,
    MTA_AT_LOCAL_GPS_TIME = 3,
    MTA_AT_TIME_BUTT
};
typedef VOS_UINT8 MTA_AT_TimeTypeUint8;


enum AT_MTA_ModemCapUpdateType {
    AT_MTA_MODEM_CAP_UPDATE_TYPE_CDMA_MODEM_SWITCH = 0x00U, /* AT^CDMAMODEMSWITCH?????????????????? */
    AT_MTA_MODEM_CAP_UPDATE_TYPE_ACTIVE_MODEM      = 0x01U, /* AT^ACTIVEMODEM?????????????????? */

    AT_MTA_MODEM_CAP_UPDATE_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_ModemCapUpdateTypeUint8;


enum AT_MTA_RsInfoType {
    AT_MTA_RSRP_TYPE = 0,
    AT_MTA_RSRQ_TYPE = 1,
    AT_MTA_RS_INFO_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_RsInfoTypeUint32;


enum AT_MTA_PseucellNotifyType {
    AT_MTA_PSEUCELL_NOTIFY_TYPE_BY_MESSAGE = 0,
    AT_MTA_PSEUCELL_NOTIFY_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_PseucellNotifyTypeUint8;


enum AT_MTA_SysMode {
    AT_MTA_SYS_MODE_GSM     = 1,
    AT_MTA_SYS_MODE_1X      = 2,
    AT_MTA_SYS_MODE_WCDMA   = 3,
    AT_MTA_SYS_MODE_TDSCDMA = 4,
    AT_MTA_SYS_MODE_WIMAX   = 5,
    AT_MTA_SYS_MODE_LTE     = 6,
    AT_MTA_SYS_MODE_HRPD    = 7,
    AT_MTA_SYS_MODE_BUTT
};
typedef VOS_UINT32 AT_MTA_SysModeUint32;


enum AT_MTA_ChrAlarmRlatOp {
    AT_MTA_CHR_ALARM_RLAT_OP_READ  = 0,
    AT_MTA_CHR_ALARM_RLAT_OP_WRITE = 1,

    AT_MTA_CHR_ALARM_RLAT_OP_BUTT
};
typedef VOS_UINT32 AT_MTA_ChrAlarmRlatOpUint32;


enum MTA_AT_BandWidth {
    MTA_AT_BAND_WIDTH_1DOT4M = 0, /* ??????1.4MHz */
    MTA_AT_BAND_WIDTH_3M,         /* ??????3MHz */
    MTA_AT_BAND_WIDTH_5M,         /* ??????5MHz */
    MTA_AT_BAND_WIDTH_10M,        /* ??????10MHz */
    MTA_AT_BAND_WIDTH_15M,        /* ??????15MHz */
    MTA_AT_BAND_WIDTH_20M,        /* ??????20MHz */
    MTA_AT_BAND_WIDTH_BUTT
};
typedef VOS_UINT8 MTA_AT_BandWidthUint8;


enum MTA_AT_FineTimeRat {
    MTA_AT_FINE_TIME_RAT_GSM      = 0,
    MTA_AT_FINE_TIME_RAT_WCDMA    = 1,
    MTA_AT_FINE_TIME_RAT_LTE      = 2,
    MTA_AT_FINE_TIME_RAT_TDS_CDMA = 3,
    MTA_AT_FINE_TIME_RAT_CDMA_1X  = 4,
    MTA_AT_FINE_TIME_RAT_HRPD     = 5,
    MTA_AT_FINE_TIME_RAT_NR       = 6,
    MTA_AT_FINE_TIME_RAT_BUTT
};
typedef VOS_UINT8 MTA_AT_FineTimeRatUint8;

/*
 * ????????:
 * ASN.1????:
 * ????????: ??????????????
 */
enum MTA_AT_ProtocolState {
    MTA_AT_PROTOCOL_STATE_IDLE      = 0,
    MTA_AT_PROTOCOL_STATE_CONNECTED = 1,
    MTA_AT_PROTOCOL_STATE_INACTIVE  = 2,

    MTA_AT_PROTOCOL_STATE_BUTT
};
typedef VOS_UINT8 MTA_AT_ProtocolStateUint8;

/*
 * ????????:
 * ASN.1????:
 * ????????: FINETIME PARA
 */
enum AT_MTA_FinetimePara {
    AT_MTA_FINETIME_PARA_0 = 0,
    AT_MTA_FINETIME_PARA_1 = 1,
    AT_MTA_FINETIME_PARA_2 = 2,

    AT_MTA_FINETIME_PARA_BUTT
};
typedef VOS_UINT8 AT_MTA_FinetimeParaUint8;


enum AT_MTA_OverHeatingSetEnum {
    AT_MTA_OVERHEATING_SET  = 0,
    AT_MTA_OVERHEATING_QUIT = 1,

    AT_MTA_OVERHEATING_PARA_BUTT
};
typedef VOS_UINT8 AT_MTA_OoverheatingParaUint8;


enum TAF_MTA_NvCarrierOptResult {
    TAF_MTA_NV_CARRIER_OPT_NO_ERROR                 = 0x00000000,
    TAF_MTA_NV_CARRIER_OPT_INVALID_PARA             = 0x10100002, /* ?????????? */
    TAF_MTA_NV_CARRIER_OPT_NOT_FIND_FILE            = 0x10100006, /* ?????????? */
    TAF_MTA_NV_CARRIER_OPT_NOT_FIND_NV              = 0x10100016, /* ????????NV */
    TAF_MTA_NV_CARRIER_OPT_WRITE_NV_TIMEOUT         = 0x10100035, /* ??NV????,(??????????????????????) */
    TAF_MTA_NV_CARRIER_OPT_WRITE_NV_NOT_SUPPORT_ERR = 0x10100037, /* ?????????? */
    TAF_MTA_NV_CARRIER_OPT_MODEM_ID_ERROR           = 0x10100039, /* modem id ???????? */

    TAF_MTA_NV_CARRIER_OPT_BUTT
};
typedef VOS_UINT32 TAF_MTA_NvCarrierOptResultUint32;


enum AT_MTA_SmsDomain {
    AT_MTA_SMS_DOMAIN_NOT_USE_SMS_OVER_IP = 0, /* *< not to use SMS over ip */
    /* *< prefer to use SMS over ip, CS/PS SMS as secondary */
    AT_MTA_SMS_DOMAIN_PREFER_TO_USE_SMS_OVER_IP = 1,

    AT_MTA_SMS_DOMAIN_BUTT
};
typedef VOS_UINT8 AT_MTA_SmsDomainUint8;


enum MTA_AT_TimeInfoRptOpt {
    MTA_AT_TIME_INFO_RPT_OPT_MMINFO    = 0, /* ^TIME???? */
    MTA_AT_TIME_INFO_RPT_OPT_SIB16TIME = 1, /* ^SIB16TIME???? */
    MTA_AT_TIME_INFO_RPT_OPT_BUTT
};
typedef VOS_UINT8 MTA_AT_TimeInfoRptOptUint8;


enum AT_MTA_NvRefreshReason {
    AT_MTA_NV_REFRESH_USIM_DEPENDENT = 0, /* ???????? */
    AT_MTA_NV_REFRESH_BUTT
};
typedef VOS_UINT8 AT_MTA_NvRefreshReasonUint8;


enum AT_MTA_JamDetectMode {
    AT_MTA_JAM_DETECT_MODE_STOP   = 0, /* ???????????? */
    AT_MTA_JAM_DETECT_MODE_START  = 1, /* ???????????? */
    AT_MTA_JAM_DETECT_MODE_UPDATE = 2, /* ???????????????? */
    AT_MTA_JAM_DETECT_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_JamDetectModeUint8;


enum AT_MTA_DcxoSampleType {
    AT_MTA_DCXO_SAMPLE_H        = 0, /* ?????? */
    AT_MTA_DCXO_SAMPLE_M        = 1, /* ?????? */
    AT_MTA_DCXO_SAMPLE_L        = 2, /* ?????? */
    AT_MTA_DCXO_SAMPLE_INITFREQ = 3, /* ???????????? */
    AT_MTA_DCXO_SAMPLE_BUTT
};
typedef VOS_UINT16 AT_MTA_DcxoSampleTypeUint16;


enum MTA_AT_DcxoSampleResult {
    MTA_AT_DCXO_SAMPLE_RESULT_NO_ERROR       = 0, /* ???????? */
    MTA_AT_DCXO_SAMPLE_RESULT_ERROR          = 1, /* ???????? */
    MTA_AT_DCXO_SAMPLE_RESULT_PARA_ERROR     = 2, /* ???????? */
    MTA_AT_DCXO_SAMPLE_RESULT_OPTION_TIMEOUT = 3, /* ?????????? */
    MTA_AT_DCXO_SAMPLE_RESULT_BUTT
};
typedef VOS_UINT16 MTA_AT_DcxoSampleResultUint16;


enum AT_MTA_LowPwrModeRat {
    AT_MTA_LOW_PWR_MODE_RAT_LTE = 0, /* LTE */
    AT_MTA_LOW_PWR_MODE_RAT_NR  = 1, /* NR */

    AT_MTA_LOW_PWR_MODE_RAT_BUTT
};
typedef VOS_UINT8 AT_MTA_LowPwrModeRatUint8;


enum MTA_AT_UlMode {
    MTA_AT_UL_MODE_NULL = 0, /* ???????????? */
    MTA_AT_UL_MODE_UL_ONLY,  /* ??????????UL???? */
    MTA_AT_UL_MODE_SUL_ONLY, /* ??????????SUL???? */
    MTA_AT_UL_MODE_BOTH,     /* ?????????????????? */
    MTA_AT_UL_MODE_BUTT
};
typedef VOS_UINT32 MTA_AT_UlModeUint32;


enum MTA_AT_IndexTable {
    /* 3GPP TS38.214 5.1.3.1 3???? */
    MTA_AT_INDEX_TABLE_ONE = 0,
    MTA_AT_INDEX_TABLE_TWO,
    MTA_AT_INDEX_TABLE_THREE,
    /* 3GPP TS38.214 6.1.4.1 2???? */
    MTA_AT_INDEX_TABLE_FOUR,
    MTA_AT_INDEX_TABLE_FIVE,
    MTA_AT_INDEX_TABLE_BUTT
};
typedef VOS_UINT8 MTA_AT_IndexTableUint8;


enum MTA_AT_NrScsTypeComm {
    MTA_AT_NR_SCS_TYPE_COMM_15  = 0x00,
    MTA_AT_NR_SCS_TYPE_COMM_30  = 0x01,
    MTA_AT_NR_SCS_TYPE_COMM_60  = 0x02,
    MTA_AT_NR_SCS_TYPE_COMM_120 = 0x03,
    MTA_AT_NR_SCS_TYPE_COMM_240 = 0x04,
    MTA_AT_NR_SCS_TYPE_COMM_BUTT
};
typedef VOS_UINT8 MTA_AT_NrScsTypeCommUint8;


enum AT_MTA_NssaiQryType {
    AT_MTA_NSSAI_QRY_DEF_CFG_NSSAI_ONLY    = 0x00, /* ??????default config nssai */
    AT_MTA_NSSAI_QRY_DEF_CFG_AND_REJ_NSSAI = 0x01, /* ????default config nssai && reject nssai */
    /* ????default config nssai && reject nssai && Cfg nssai */
    AT_MTA_NSSAI_QRY_DEF_CFG_AND_REJ_AND_CFG_NSSAI = 0x02,
    /* ????default config nssai && reject nssai && Cfg nssai && Allowed nssai */
    AT_MTA_NSSAI_QRY_DEF_CFG_AND_REJ_AND_CFG_AND_ALLOWED_NSSAI = 0x03,

    AT_MTA_NSSAI_QRY_PREFER_NSSAI = 0x04, /* ????prefer nssai */

    AT_MTA_NSSAI_QRY_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_NssaiQryTypeUint32;


enum AT_MTA_NssaiSetType {
    AT_MTA_NSSAI_SET_PREFER_NSSAI  = 0x00, /* ????prefer nssai???? */
    AT_MTA_NSSAI_SET_DEF_CFG_NSSAI = 0x01, /* ????default config nssai */

    AT_MTA_NSSAI_SET_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_NssaiSetTypeUint32;


enum MTA_AT_NetmonMeasRsType {
    MTA_AT_NETMON_MEAS_RS_TYPE_SSB = 0,
    MTA_AT_NETMON_MEAS_RS_TYPE_CSI_RS,
    MTA_AT_NETMON_MEAS_RS_TYPE_BUTT
};
typedef VOS_UINT8 MTA_AT_NetmonMeasRsTypeUint8;


enum MTA_AT_UartTestRslt {
    MTA_AT_UART_TEST_RSLT_SUCCESS      = 0x0000, /* ???????????? */
    MTA_AT_UART_TEST_RSLT_DATA_ERROR   = 0x0001,
    MTA_AT_UART_TEST_RSLT_ICC_NOT_OPEN = 0x0002,
    MTA_AT_UART_TEST_RSLT_TIME_OUT     = 0x0003,

    MTA_AT_UART_TEST_RSLT_BUTT
};
typedef VOS_UINT32 MTA_AT_UartTestRsltUint32;


enum MTA_AT_HsrcellInfoRat {
    MTA_AT_HSRCELLINFO_RAT_GSM     = 0,
    MTA_AT_HSRCELLINFO_RAT_WCDMA   = 1,
    MTA_AT_HSRCELLINFO_RAT_LTE     = 2,
    MTA_AT_HSRCELLINFO_RAT_TD_CDMA = 3,
    MTA_AT_HSRCELLINFO_RAT_1X      = 4,
    MTA_AT_HSRCELLINFO_RAT_NR      = 5,
    MTA_AT_HSRCELLINFO_RAT_UNKNOWN = 6,

    MTA_AT_HSRCELLINFO_RAT_BUTT
};
typedef VOS_UINT8 MTA_AT_HsrcellInfoRatUint8;

/*
 * 5 ??????????
 * *s
 */


typedef struct {
    VOS_MSG_HEADER
    VOS_UINT32 msgId; /* ?????? */
    AT_APPCTRL appCtrl;
    VOS_UINT8  content[4]; /* ???????? */
} AT_MTA_Msg;


typedef struct {
    MTA_AT_CposOperateTypeUint32 cposOpType;
    VOS_UINT32                   xmlLength;
    VOS_CHAR                     xmlText[MTA_CPOS_XML_MAX_LEN];
} AT_MTA_CposReq;


typedef struct {
    AT_MTA_LowPwrModeRatUint8 rat;
    VOS_UINT8                 rcv[3];
} AT_MTA_LowPwrModeReq;


typedef struct {
    VOS_UINT32 result;
} MTA_AT_LowPwrModeCnf;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????? */
} MTA_AT_CposCnf;


typedef struct {
    /* AT??MTA??????XML??????????????1024???????????????????????????????????????????? */
    VOS_CHAR  xmlText[MTA_CPOSR_XML_MAX_LEN + 1];
    VOS_UINT8 rsv[3];
} MTA_AT_CposrInd;

typedef struct {
    VOS_UINT16 transactionId;
    VOS_UINT8  msgBodyType;
    VOS_UINT8  commonIeValidFlg;
    VOS_UINT8  endFlg;
    VOS_UINT8  id;
    VOS_UINT8  reserved;
    VOS_UINT8  nameLength;
    VOS_UINT8  name[MTA_MAX_EPDU_NAME_LEN]; /* ????????????'\0' */
    VOS_UINT8  total;
    VOS_UINT8  index;
    VOS_UINT16 dataLength;
    VOS_UINT8  data[MTA_MAX_EPDU_BODY_LEN];
} MTA_AT_EpduDataInd;

typedef struct {
    VOS_UINT32 clearFlg;
} MTA_AT_XcposrrptInd;


typedef struct {
    MTA_AT_CgpsclockUint32 gpsClockState; /* RF????GPS???????? */
} AT_MTA_CgpsclockReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????? */

    MTA_AT_ModemIdUint8 modemId;
    MTA_AT_RatModeUint8 ratMode;

    VOS_UINT8 reserved[2];
} MTA_AT_CgpsclockCnf;


typedef struct {
    AT_MTA_PersCategoryUint8 category;
    VOS_UINT8                reserved[3];
    VOS_UINT8                password[MTA_SIMLOCK_PASSWORD_LEN];
} AT_MTA_SimlockunlockReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????? */
} MTA_AT_SimlockunlockCnf;


typedef struct {
    VOS_UINT8 ratType;
    VOS_UINT8 reserve[3]; /* ???????????? */
} AT_MTA_QryNmrReq;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT8           totalIndex;
    VOS_UINT8           currIndex;
    VOS_UINT16          nmrLen;     /* NMR???????? */
    VOS_UINT8           nmrData[4]; /* NMR?????????? */
} MTA_AT_QryNmrCnf;


typedef struct {
    VOS_UINT8 offsetFlg;  /* 0:??????1:???? */
    VOS_UINT8 reserve[3]; /* ???????????? */
} AT_MTA_ReselOffsetCfgSetNtf;


typedef struct {
    VOS_UINT8  cmd;
    VOS_UINT8  paraNum;
    VOS_UINT16 reserve;
    VOS_UINT32 para[AT_MTA_WRR_AUTOTEST_MAX_PARA_NUM];
} AT_MTA_WrrAutotestQryPara;


typedef struct {
    VOS_UINT8  cmd;
    VOS_UINT8  paraNum;
    VOS_UINT16 reserve;
    VOS_UINT32 para[AT_MTA_GAS_AUTOTEST_MAX_PARA_NUM];
} AT_MTA_GasAutotestQryPara;


typedef struct {
    VOS_UINT32 rsltNum;
    VOS_UINT32 rslt[MTA_AT_WRR_AUTOTEST_MAX_RSULT_NUM];
} MTA_AT_WrrAutotestQryRslt;


typedef struct {
    VOS_UINT32                result;
    MTA_AT_WrrAutotestQryRslt wrrAutoTestRslt;
} MTA_AT_WrrAutotestQryCnf;


typedef struct {
    VOS_UINT32 rsltNum;
    VOS_UINT32 rslt[MTA_AT_GAS_AUTOTEST_MAX_RSULT_NUM];
} MTA_AT_GasAutotestQryRslt;


typedef struct {
    VOS_UINT32                result;
    MTA_AT_GasAutotestQryRslt grrAutoTestRslt;
} MTA_AT_GasAutotestQryCnf;


typedef struct {
    VOS_UINT16 cellFreq;
    VOS_UINT16 primaryScramCode;
    VOS_INT16  cpichRscp;
    VOS_INT16  cpichEcN0;

} MTA_AT_WrrCellinfo;


typedef struct {
    VOS_UINT32         cellNum;
    MTA_AT_WrrCellinfo wCellInfo[MTA_AT_WRR_MAX_NCELL_NUM]; /* ????????W 8???????????? */

} MTA_AT_WrrCellinfoRslt;

typedef struct {
    VOS_UINT32             result;
    MTA_AT_WrrCellinfoRslt wrrCellInfo;
} MTA_AT_WrrCellinfoQryCnf;


typedef struct {
    VOS_UINT16 eventId; /* ?????????????? */
    VOS_UINT16 cellNum;
    VOS_UINT16 primaryScramCode[MTA_AT_WRR_ONE_MEANRPT_MAX_CELL_NUM];
} MTA_AT_WrrMeanrpt;


typedef struct {
    VOS_UINT32        rptNum;
    MTA_AT_WrrMeanrpt meanRptInfo[MTA_AT_WRR_MAX_MEANRPT_NUM];
} MTA_AT_WrrMeanrptRslt;


typedef struct {
    VOS_UINT32            result;
    MTA_AT_WrrMeanrptRslt meanRptRslt;
} MTA_AT_WrrMeanrptQryCnf;


typedef struct {
    VOS_INT16 cpichRscp;
    VOS_INT16 cpichEcNo;
} MTA_AT_AntennaQryCnf;


typedef struct {
    VOS_UINT8  freqLockEnable;
    VOS_UINT8  reserved[1];
    VOS_UINT16 lockedFreq;
} MTA_AT_WrrFreqlockCtrl;


typedef struct {
    VOS_UINT32 result;
} MTA_AT_WrrFreqlockSetCnf;


typedef struct {
    VOS_UINT32             result;
    MTA_AT_WrrFreqlockCtrl freqLockInfo;
} MTA_AT_WrrFreqlockQryCnf;


typedef struct {
    VOS_UINT32 result;
} MTA_AT_WrrRrcVersionSetCnf;


typedef struct {
    VOS_UINT32 result;
    VOS_UINT8  rrcVersion;
    VOS_UINT8  reserved[3];
} MTA_AT_WrrRrcVersionQryCnf;


typedef struct {
    VOS_UINT32 result;
} MTA_AT_WrrCellsrhSetCnf;


typedef struct {
    VOS_UINT32 result;
    VOS_UINT8  cellSearchType;
    VOS_UINT8  reserve[3];
} MTA_AT_WrrCellsrhQryCnf;


typedef struct {
    VOS_INT16  cpichRscp;
    VOS_INT16  cpichEcNo;
    VOS_UINT32 cellId;
    VOS_UINT8  rssi; /* Rssi, GU?????? */
    VOS_UINT8  reserve[3];

} AT_MTA_Anquery2G3GPara;


typedef struct {
    VOS_INT16 rsrp; /* ??????(-141,-44), 99?????? */
    VOS_INT16 rsrq; /* ??????(-40, -6) , 99?????? */
    VOS_INT16 rssi; /* Rssi, LTE?????? */
    VOS_UINT8 reserve[2];
} AT_MTA_Anquery4GPara;


typedef struct {
    VOS_UINT8 serviceSysMode; /* ???????????? */
    VOS_UINT8 reserve[3];
    union {
        AT_MTA_Anquery2G3GPara st2G3GCellSignInfo; /* Rssi, GU?????? */
        AT_MTA_Anquery4GPara   st4GCellSignInfo;   /* Rssi, LTE?????? */
    } u;
} AT_MTA_AnqueryPara;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????? */
    AT_MTA_AnqueryPara  antennaInfo;
} MTA_AT_AntennaInfoQryCnf;


typedef struct {
    VOS_INT16 cpichRscp;
    VOS_INT16 cpichEcNo;
} AT_MTA_CsnrPara;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????? */
    AT_MTA_CsnrPara     csnrPara;
} MTA_AT_CsnrQryCnf;

/*
 * ????????: CSQLVL??????????????????????
 *           ????RSCP ??????RSCP ????????
 */
typedef struct {
    VOS_UINT16 rscp;  /* RSCP ???? */
    VOS_UINT16 level; /* RSCP ???????? */
} AT_MTA_CsqlvlPara;


typedef struct {
    VOS_UINT8 rssilv; /* CSQLVLEX???????????????????? */
    /* ????????????????????????????BER????????99 */
    VOS_UINT8 ber;
} AT_MTA_CsqlvlextPara;


typedef struct {
    MTA_AT_ResultUint32  result; /* ???????? */
    AT_MTA_CsqlvlPara    csqLvlPara;
    AT_MTA_CsqlvlextPara csqLvlExtPara;
    VOS_UINT8            reserved[2];
} MTA_AT_CsqlvlQryCnf;


typedef struct {
    MTA_AT_ResultUint32      result;            /* ???????? */
    AT_MTA_FratIgnitionUnit8 fratIgnitionState; /* IgnitionState */
    VOS_UINT8                reserved[3];
} MTA_AT_FratIgnitionQryCnf;


typedef struct {
    AT_MTA_FratIgnitionUnit8 fratIgnitionState; /* IgnitionState */
    VOS_UINT8                reserved[3];
} AT_MTA_FratIgnitionSetReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????? */
} MTA_AT_FratIgnitionSetCnf;


typedef struct {
    AT_MTA_BodySarStateUint16 state;       /* Body SAR???? */
    VOS_UINT16                rsv;         /* ?????? */
    MTA_BodySarPara           bodySarPara; /* Body SAR???????????? */
} AT_MTA_BodySarSetReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????? */
} MTA_AT_ResultCnf;


typedef struct {
    VOS_UINT8 reserved[4]; /* ?????? */
} AT_MTA_Reserve;


typedef struct {
    /* ??????????+CSSI?????????????? 0:??????;1:???? */
    VOS_UINT8 cssiRptFlg;
    /* ??????????+CSSU?????????????? 0:??????;1:???? */
    VOS_UINT8 cssuRptFlg;
} AT_MTA_CssnRptFlg;


typedef struct {
    /* ??????????????0:????????????????????1:????????????????????2:????RptCfg??????????????bit?????????????? */
    AT_MTA_RptGeneralCtrlTypeUint8 curcRptType;
    VOS_UINT8                      reserve[3]; /* ???????? */
    /* 64bit???????????? */
    VOS_UINT8 rptCfg[AT_MTA_RPT_CFG_MAX_SIZE];
} AT_MTA_CurcSetNotify;


typedef struct {
    VOS_UINT8 reserve[4];
} AT_MTA_CurcQryReq;


typedef struct {
    AT_MTA_RptSetTypeUint32 reqType; /* ???????? */

    union {
        /* mode???????????????? 0:????????1:???? */
        VOS_UINT8 modeRptFlg;
        VOS_UINT8 srvstRptFlg;  /* service status???????????????? */
        VOS_UINT8 rssiRptFlg;   /* rssi???????????????? */
        VOS_UINT8 timeRptFlg;   /* time???????????????? */
        VOS_UINT8 ctzrRptFlg;   /* ctzr???????????????? */
        VOS_UINT8 dsFlowRptFlg; /* ???????????????????? */
        VOS_UINT8 simstRptFlg;  /* sim?????????????????????? */
        VOS_UINT8 cregRptFlg;   /* cs?????????????????????????? */
        VOS_UINT8 cgregRptFlg;  /* ps?????????????????????????? */
        VOS_UINT8 ceregRptFlg;  /* L???????????????????????? */
        VOS_UINT8 csidRptFlg;     /* CSID???????????????? */
        VOS_UINT8 clocinfoRptFlg; /* CLOCINFO???????????????? */
        VOS_UINT8 mtReattachRptFlg; /* MTREATTACH???????????????? */
        /* ^CENFS???????????????? 0:????????1:???? */
        VOS_UINT8 cenfsRptFlg;
        VOS_UINT8 c5gregRptFlg; /* NR???????????????????????? */

        VOS_UINT8 lendcRptFlg;

        VOS_UINT8 rrcStatRptFlg;
        VOS_UINT8 hfreqInfoRptFlg;
    } u;

    VOS_UINT8 reserve[3];

} AT_MTA_UnsolicitedRptSetReq;


typedef struct {
    AT_MTA_RptQryTypeUint32 reqType;
} AT_MTA_UnsolicitedRptQryReq;


typedef struct {
    VOS_UINT8 gameMode;
    VOS_UINT8 rsv[3];
} AT_MTA_CommGameModeSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_GameModeSetCfn;


typedef struct {
    ModemIdUint16           sourceModemId;
    ModemIdUint16           destinationModemId;
    PLATAFORM_RatCapability sourceModemPlatform;
    PLATAFORM_RatCapability destinationModemPlatform;
} AT_MTA_CdmaModemCapSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_CdmaModemCapSetCnf;


typedef struct {
    ModemIdUint16           cdmaModemId; /* cdma??????????modem id */
    VOS_UINT8               rsv[2];
    PLATAFORM_RatCapability modem0Platform;
    PLATAFORM_RatCapability modem1Platform;
} AT_MTA_CdmaCapResumeSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_CdmaCapResumeSetCnf;


typedef struct {
    VOS_UINT16 pidIndex;
    VOS_UINT8  rsv[2];
    VOS_UINT32 len; /* ?????????????? */
    VOS_UINT8  date[AT_CMD_COMM_BOOSTER_BS_MAX_LENGTH];
} AT_MTA_CommBoosterSetReq;


typedef struct {
    VOS_UINT16 pidIndex;
    VOS_UINT8  rsv[2];
    VOS_UINT32 len; /* ?????????????? */
    VOS_UINT8  date[AT_CMD_COMM_BOOSTER_BS_MAX_LENGTH];
} AT_MTA_CommBoosterQueryReq;


typedef struct {
    VOS_UINT8  internalResultFlag; /* ???????????? */
    VOS_UINT8  externalResultFlag; /* ???????????? */
    VOS_UINT8  rsv[2];             /* ?????? */
    VOS_UINT32 result;             /* ???? */
} MTA_AT_CommBoosterSetCnf;


typedef struct {
    VOS_UINT8  result;
    VOS_UINT8  rsv[3];
    VOS_UINT32 len; /* ?????????????? */
    VOS_UINT8  date[MTA_AT_BOOSTER_QRY_CNF_MAX_NUM];
} MTA_AT_CommBoosterQueryCnf;


typedef struct {
    TAF_MTA_NvCarrierOptResultUint32 result;
} MTA_AT_SetNvloadCnf;


typedef struct {
    VOS_UINT32 pidIndex;
    VOS_UINT32 len;
    /* Booster??????????????????TLV???????????????????? */
    VOS_UINT8 boosterIndData[MTA_AT_BOOSTER_IND_MAX_NUM];
} MTA_AT_CommBoosterInd;


typedef struct {
    VOS_UINT32 reqType;
} AT_MTA_NvloadSetReq;


typedef struct {
    VOS_UINT16 reqType;
    /* ????????(????????????????????????????????)??"11111"???????????? */
    VOS_UINT16 tempRange;
    VOS_INT16  ppmOffset;  /* ?????????? */
    VOS_INT16  timeOffset; /* ?????????? */

} AT_MTA_SetSampleReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetSampleCnf;



typedef struct {
    VOS_UINT8 pseudRat; /* ?????????? 1.GSM  2.WCDMA  3.LTE */
    /* ???????? 1.??????????????????  2.?????????????????? */
    VOS_UINT8 pseudBtsQryType;
    VOS_UINT8 rsv[2];

} AT_MTA_SetPseudbtsReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* NO_ERROR:??????????:???? */
    /* ???????? 1.??????????????????  2.?????????????????? */
    VOS_UINT8 pseudBtsIdentType;
    VOS_UINT8 rsv[3];

    union {
        VOS_UINT32 pseudBtsIdentTimes; /* ???????? */
        VOS_UINT8  pseudBtsIdentCap;   /* ???????? */
    } u;
} MTA_AT_PseudBtsSetCnf;



typedef struct {
    /* AT??????CLFS????????????4?????????????????????????????????????????? */
    VOS_UINT16 clfsGroupNum;
    VOS_UINT16 dataLength;  /* aucClfsData???? */
    VOS_UINT8  clfsData[4]; /* CLFS???????????? */
} AT_MTA_ParaInfo;



typedef struct {
    VOS_UINT8 activeFlg;                          /* 0:??????????1:???????? */
    VOS_UINT8 seq;                                /* ?????? */
    VOS_UINT8 type;                               /* 0:????????GSM?????????????? */
    VOS_UINT8 versionId[AT_MTA_VERSION_INFO_LEN]; /* ??????????????xx.xx.xxx */
    VOS_UINT8 rsv[3];
    /* ??????????????????????????0~99999??????99999????99.999%???? */
    VOS_UINT32      probaRate;
    AT_MTA_ParaInfo paraInfo;
} AT_MTA_SetSubclfsparamReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SubclfsparamSetCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT8           versionId[AT_MTA_VERSION_INFO_LEN]; /* ?????? */
    VOS_UINT8           rsv[2];
} MTA_AT_SubclfsparamQryCnf;


typedef struct {
    VOS_UINT8 switchFlag;
    VOS_UINT8 reserve[3];
} AT_MTA_NcellMonitorSetReq;


typedef struct {
    AT_MTA_ClearFreqFlgUint8 mode;
    VOS_UINT8                reserved[3];
} AT_MTA_ClearHistoryFreqReq;


typedef struct {
    MTA_AT_ResultUint32 result;
    /* ??????????????0:????????????????????1:????????????????????2:????ReportCfg??????????????bit?????????????? */
    AT_MTA_RptGeneralCtrlTypeUint8 curcRptType;
    VOS_UINT8                      reserve[3];
    VOS_UINT8                      rptCfg[AT_MTA_RPT_CFG_MAX_SIZE]; /* ???????????? */
} MTA_AT_CurcQryCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_UnsolicitedRptSetCnf;


typedef struct {
    MTA_AT_ResultUint32     result;
    AT_MTA_RptQryTypeUint32 reqType;

    union {
        VOS_UINT8              timeRptFlg; /* time???????????????? */
        MTA_TAF_CtzrTypeUint32 ctzrRptFlg; /* ctzr???????????????? */
        AT_MTA_CssnRptFlg      cssnRptFlg; /* cssn?????????????????????? */
        VOS_UINT8              cusdRptFlg; /* cusd?????????????????????? */
    } u;

} MTA_AT_UnsolicitedRptQryCnf;


typedef struct {
    VOS_UINT8 imei[NV_ITEM_IMEI_SIZE]; /* IMEI???? */
} MTA_AT_CgsnQryCnf;

typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT8           switchFlag;
    VOS_UINT8           ncellState;
    VOS_UINT8           reserved[2];
} MTA_AT_NcellMonitorQryCnf;


typedef struct {
    VOS_UINT8 ncellState;
    VOS_UINT8 reserved[3];
} MTA_AT_NcellMonitorInd;


typedef struct {
    AT_MTA_CmdRptFlgUint8 rptFlg;       /* ???????????????? */
    VOS_UINT8             reserved1[3]; /* ?????? */
} AT_MTA_RefclkfreqSetReq;


typedef struct {
    MTA_AT_ResultUint32         result;
    VOS_UINT32                  freq;         /* GPS??????????????????????Hz */
    VOS_UINT32                  precision;    /* ????GPS????????????????????ppb */
    MTA_AT_RefclockStatusUint16 status;       /* ???????????????? */
    VOS_UINT8                   reserved1[2]; /* ?????? */
} MTA_AT_RefclkfreqQryCnf;


typedef struct {
    VOS_UINT16 channelNo; /* ?????????? */
    VOS_UINT16 rficReg;
} AT_MTA_RficssirdReq;


typedef struct {
    VOS_UINT32 regValue; /* ???????????????? */
} MTA_AT_RficssirdCnf;


typedef struct {
    VOS_UINT32                  freq;         /* GPS??????????????????????Hz */
    VOS_UINT32                  precision;    /* ????GPS????????????????????ppb */
    MTA_AT_RefclockStatusUint16 status;       /* ???????????????? */
    VOS_UINT8                   reserved1[2]; /* ?????? */
} MTA_AT_RefclkfreqInd;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????? */
} MTA_AT_HandledectSetCnf;


typedef struct {
    VOS_UINT16          handle; /* ?????????? */
    VOS_UINT16          reserved1[1];
    MTA_AT_ResultUint32 result; /* ???????? */
} MTA_AT_HandledectQryCnf;


typedef struct {
    VOS_UINT8 cause;        /* PS???????????? */
    VOS_UINT8 reserved1[3]; /* ?????? */
} MTA_AT_PsTransferInd;


typedef struct {
    VOS_UINT16 mipiClk;      /* ????????MIPICLK?? */
    VOS_UINT8  reserved1[2]; /* ?????? */
} MTA_AT_RfLcdMipiclkInd;


typedef struct {
    MTA_AT_UartTestRsltUint32 uartTestRslt;
} MTA_AT_UartTestRsltInd;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_UartTestCnf;


typedef struct {
    VOS_UINT16 mipiClk; /* ????????MIPICLK?? */
    VOS_UINT16 result;
} MTA_AT_RfLcdMipiclkCnf;


typedef struct {
    VOS_UINT32 version; /* ?????????? */
} AT_MTA_EcidSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT8           cellInfoStr[4]; /* ???????????????????? */
} MTA_AT_EcidSetCnf;


typedef struct {
    PS_BOOL_ENUM_UINT8 psProtectFlg;
    VOS_UINT8          reserve[3]; /* ???????????? */
} AT_MTA_RrcProtectPsReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ??????AT?????? */
} MTA_AT_RrcProtectPsCnf;


typedef struct {
    VOS_UINT8 reserve[4]; /* ???????????? */
} AT_MTA_PhyInitReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ??????AT?????? */
} MTA_AT_PhyInitCnf;


typedef struct {
    AT_MTA_CmdRatmodeUint8 ratMode;
    VOS_UINT8              flag;
    VOS_UINT8              reserved[2];
} AT_MTA_SetDpdttestFlagReq;


typedef struct {
    AT_MTA_CmdRatmodeUint8 ratMode;
    VOS_UINT8              reserved[3];
    VOS_UINT32             dpdtValue;
} AT_MTA_SetDpdtValueReq;


typedef struct {
    AT_MTA_CmdRatmodeUint8 ratMode;
    VOS_UINT8              reserved[3];
} AT_MTA_QryDpdtValueReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetDpdttestFlagCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetDpdtValueCnf;


typedef struct {
    VOS_UINT32          dpdtValue;
    MTA_AT_ResultUint32 result;
} MTA_AT_QryDpdtValueCnf;


typedef struct {
    AT_MTA_CmdRatmodeUint8   ratMode;
    AT_MTA_TrxTasCmdUint8    cmd;
    AT_MTA_CmdSignalingUint8 mode;
    VOS_UINT8                reserved;
    VOS_UINT32               trxTasValue;
} AT_MTA_SetTrxTasReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetTrxTasCnf;


typedef struct {
    AT_MTA_CmdRatmodeUint8   ratMode;
    AT_MTA_CmdSignalingUint8 mode;
    VOS_UINT8                reserved[2];
} AT_MTA_QryTrxTasReq;


typedef struct {
    MTA_AT_ResultUint32    result;
    AT_MTA_CmdRatmodeUint8 ratMode;
    VOS_UINT8              reserved[3];
    VOS_UINT32             trxTasValue;
} MTA_AT_QryTrxTasCnf;


typedef struct {
    /* ??????????????????????????????????:[0,70] */
    VOS_UINT8 threshold;
    /* ????????????????????????????????:[0,255] */
    VOS_UINT8 freqNum;
    VOS_UINT8 reserved[2];
} AT_MTA_GsmJamDetect;


typedef struct {
    /* ????RSSI??????????????????????????????????????[0,70]????????????????70???? */
    VOS_UINT8 rssiSrhThreshold;
    /* ????RSSI????????????????????????????????????BAND??????????????????????????????????????[0,100] */
    VOS_UINT8 rssiSrhFreqPercent;
    /* ????PSCH??????????????????????????????????????????:[0,65535] */
    VOS_UINT16 pschSrhThreshold;
    /* ????PSCH????????????????????????????????????BAND????????????????????????????????????:[0,100] */
    VOS_UINT8 pschSrhFreqPercent;
    VOS_UINT8 reserved[3];
} AT_MTA_WcdmaJamDetect;


typedef struct {
    /* ????RSSI??????????????????????????????????????[0,70]????????????????70???? */
    VOS_INT16 rssiThresh;
    /* ????PSS Ratio????????????????????????????????????????:[0,100] */
    VOS_UINT16 pssratioThresh;
    /* ????RSSI????????????????????????????????????BAND??????????????????????????????????????[0,100] */
    VOS_UINT8 rssiPercent;
    /* ????PSS Ratio??????????????????????????????????????????????????????????:[0,100] */
    VOS_UINT8 pssratioPercent;
    VOS_UINT8 reserved[2];
} AT_MTA_LteJamDetect;


typedef union {
    AT_MTA_GsmJamDetect   gsmPara;
    AT_MTA_WcdmaJamDetect wcdmaPara;
    AT_MTA_LteJamDetect   ltePara;
} AT_MTA_JamDetectUnion;


typedef struct {
    VOS_UINT8              mode; /* ???????????????? */
    VOS_UINT8              reserved[2];
    AT_MTA_CmdRatmodeUint8 rat;       /* ???????? */
    AT_MTA_JamDetectUnion  unJamPara; /* ???????????????? */
} AT_MTA_SetJamDetectReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetJamDetectCnf;


typedef struct {
    VOS_UINT8             gsmJamMode;   /* GSM???????????????????????? */
    VOS_UINT8             wcdmaJamMode; /* WCDMA???????????????????????? */
    VOS_UINT8             lteJamMode;   /* LTE???????????????????????? */
    VOS_UINT8             reserved;
    AT_MTA_GsmJamDetect   gsmPara;
    AT_MTA_WcdmaJamDetect wcdmaPara;
    AT_MTA_LteJamDetect   ltePara;
} MTA_AT_QryJamDetectCnf;


typedef struct {
    AT_MTA_CmdRatmodeUint8 rat;
    VOS_UINT8              reserved[3];
    MTA_AT_JamResultUint32 jamResult;
} MTA_AT_JamDetectInd;


typedef struct {
    VOS_UINT8                   enableFlg; /* 1:??????????????0:???????? */
    AT_MTA_FreqlockRatmodeUint8 ratMode;
    AT_MTA_GsmBandUint16        band;
    VOS_UINT32                  lockedFreq;
} AT_MTA_SetFreqLockReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetFreqLockCnf;


typedef struct {
    PS_BOOL_ENUM_UINT8   enableFlag;  /* PS_TRUE:??????PS_FALSE:?????? */
    VOS_UINT8            reserved[3]; /* ?????? */
    VOS_UINT16           freq;        /* ?????? */
    AT_MTA_GsmBandUint16 band;        /* GSM???? */
} AT_MTA_SetGsmFreqlockReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetGsmFreqlockCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    /* PS_TRUE: ??????????????,PS_FALSE: ???????????????? */
    PS_BOOL_ENUM_UINT8   lockFlg;
    VOS_UINT8            reserved[3]; /* ?????? */
    VOS_UINT16           freq;        /* ?????????? */
    AT_MTA_GsmBandUint16 band;        /* GSM???? */
} MTA_AT_QryGsmFreqlockCnf;


typedef struct {
    VOS_UINT32 result;
} MTA_AT_DelCellentityCnf;

#if (FEATURE_ON == FEATURE_PROBE_FREQLOCK)

enum AT_FREQLOCK_WType {
    AT_MTA_WCDMA_FREQLOCK_CMD_FREQ_ONLY = 8, /* ????CWAS???????? */
    AT_MTA_WCDMA_FREQLOCK_CMD_COMBINED  = 9, /* ????CWAS????+???????? */
    AT_MTA_WCDMA_FREQLOCK_CMD_BUTT
};
typedef VOS_UINT8 AT_MTA_WcdmaFreqlockCmdUint8;


enum AT_MTA_M2MFreqlockType {
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_ONLY     = 1, /* ????ONLY???? */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_FREQ_COMBINED = 2, /* ????+??????/????/????????ID */
    AT_MTA_M2M_FREQLOCK_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 AT_MTA_M2MFreqlockTypeUint8;


typedef struct {
    VOS_UINT16           freq;    /* ?????? */
    AT_MTA_GsmBandUint16 band;    /* GSM???? */
    VOS_UINT32           reserve; /* 8????????-???????? */
} AT_MTA_M2MGsmFreqlockPara;


typedef struct {
    AT_MTA_M2MFreqlockTypeUint8 freqType;    /* ???????? */
    VOS_UINT8                   reserved[3]; /* ?????? */
    VOS_UINT16                  freq;        /* ?????? */
    VOS_UINT16                  psc;         /* WCDMA?????? */
} AT_MTA_M2MWcdmaFreqlockPara;


typedef struct {
    AT_MTA_M2MFreqlockTypeUint8 freqType;    /* ???????? */
    VOS_UINT8                   reserved[3]; /* ?????? */
    VOS_UINT16                  freq;        /* ?????? */
    VOS_UINT16                  sc;          /* TD-SCDMA???? */
} AT_MTA_M2MTdscdmaFreqlockPara;


typedef struct {
    VOS_UINT32                  freq;     /* ?????? */
    VOS_UINT16                  pci;      /* LTE????????ID */
    AT_MTA_M2MFreqlockTypeUint8 freqType; /* ???????? */
    VOS_UINT8                   reserved; /* ?????? */
} AT_MTA_M2MLteFreqlockPara;


enum AT_FreqlockFlagType {
    AT_MTA_M2M_FREQLOCK_MODE_GSM     = 1, /* GSM???? */
    AT_MTA_M2M_FREQLOCK_MODE_WCDMA   = 2, /* WCDMA???? */
    AT_MTA_M2M_FREQLOCK_MODE_TDSCDMA = 3, /* TD-SCDMA???? */
    AT_MTA_M2M_FREQLOCK_MODE_LTE     = 4, /* LTE???? */
    AT_MTA_M2M_FREQLOCK_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_M2MFreqlockModeUint8;


enum AT_MTA_M2MFreqlockFlagType {
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_OFF = 0, /* ???????? */
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_ON  = 1, /* ???????? */
    AT_MTA_M2M_FREQLOCK_FLAG_TYPE_BUTT
};
typedef VOS_UINT8 AT_MTA_M2MFreqlockFlagUint8;


typedef struct {
    AT_MTA_M2MFreqlockFlagUint8   enableFlag;  /* ???????? */
    AT_MTA_M2MFreqlockModeUint8   mode;        /* ???????? */
    VOS_UINT8                     reserved[6]; /* ???? */
    AT_MTA_M2MGsmFreqlockPara     gFreqPara;   /* G?????????????? */
    AT_MTA_M2MWcdmaFreqlockPara   wFreqPara;   /* W?????????????? */
    AT_MTA_M2MTdscdmaFreqlockPara tdFreqPara;  /* TD?????????????? */
    AT_MTA_M2MLteFreqlockPara     lFreqPara;   /* L?????????????? */
} AT_MTA_SetM2MFreqlockReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetM2MFreqlockCnf;


typedef struct {
    VOS_UINT8                     freqState[MTA_FREQLOCK_MAX_MODE]; /* GUTL?????????????? */
    AT_MTA_M2MGsmFreqlockPara     gFreqLockInfo;                    /* GSM???????????????? */
    AT_MTA_M2MWcdmaFreqlockPara   wFreqLockInfo;                    /* WCDMA???????????????? */
    AT_MTA_M2MTdscdmaFreqlockPara tFreqLockInfo;                    /* TD-SCDMA???????????????? */
    AT_MTA_M2MLteFreqlockPara     lFreqLockInfo;                    /* LTE???????????????? */
} MTA_AT_QryM2MFreqlockCnf;
#endif


typedef struct {
    MTA_AT_GphyXpassModeUint16   gphyXpassMode;
    VOS_UINT16                   resev1;
    MTA_AT_WphyHighwayModeUint16 wphyXpassMode;
    VOS_UINT16                   resev2;
} MTA_AT_XpassInfoInd;

typedef struct {
    VOS_UINT32 ctrlType;
    VOS_UINT32 para1;
    VOS_UINT32 para2;
    VOS_UINT32 para3;
} AT_MTA_SetFemctrlReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetFemctrlCnf;


typedef struct {
    VOS_UINT8 secType;   /* ???????????? */
    VOS_UINT8 secStrFlg; /* ???????????????????? */
    VOS_UINT8 reserved[2];
    VOS_UINT8 secString[AT_RSA_CIPHERTEXT_LEN]; /* ???????????? */
} AT_MTA_NvwrsecctrlSetReq;


typedef struct {
    PS_BOOL_ENUM_UINT8 actFrFlag; /* ????FR??????0:??????  1:???? */
    VOS_UINT8          rsv[3];    /* ?????? */
} AT_MTA_SetFrReq;


typedef struct {
    MTA_AT_ResultUint32 rslt; /* FR?????????? */
} MTA_AT_SetFrCnf;


typedef struct {
    VOS_UINT16 year;
    VOS_UINT8  month;
    VOS_UINT8  day;
    VOS_UINT8  hour;
    VOS_UINT8  minute;
    VOS_UINT8  second;
    VOS_INT8   timeZone;
} MTA_AT_Time;


typedef struct {
    VOS_UINT8   dst;
    VOS_UINT8   ieFlg;
    VOS_INT8    localTimeZone;
    VOS_UINT8   rsv;
    VOS_UINT8   curcRptCfg[8];
    VOS_UINT8   unsolicitedRptCfg[8];
    MTA_AT_Time universalTimeandLocalTimeZone;
} TAF_AT_CommTime;


typedef struct {
    MTA_AT_TimeInfoRptOptUint8 rptOptType;
    VOS_UINT8                  reserve[3];
    TAF_AT_CommTime            commTimeInfo;
} MTA_AT_Sib16TimeUpdate;


enum MTA_AT_AccessStratumRel {
    MTA_AT_ACCESS_STRATUM_REL8       = 0,
    MTA_AT_ACCESS_STRATUM_REL9       = 1,
    MTA_AT_ACCESS_STRATUM_REL10      = 2,
    MTA_AT_ACCESS_STRATUM_REL11      = 3,
    MTA_AT_ACCESS_STRATUM_REL12      = 4,
    MTA_AT_ACCESS_STRATUM_REL13      = 5,
    MTA_AT_ACCESS_STRATUM_REL14      = 6,
    MTA_AT_ACCESS_STRATUM_REL_SPARE1 = 7
};
typedef VOS_UINT8 MTA_AT_AccessStratumRelUint8;


typedef struct {
    MTA_AT_AccessStratumRelUint8 accessStratumRel; /* ????AT???????????????? */
    VOS_UINT8                    rsv[3];
} MTA_AT_AccessStratumRelInd;


typedef struct {
    /* ??????CC TM1????TRUE??????????????????; ?????????? ??????????FALSE(????????????????????????0). */
    VOS_UINT8 validflag;
    VOS_UINT8 rxAntNum; /* UE????????????2????4?? */
    /* ???????? ?????? ucTmMode=0(????????????1)?????????????????????????? */
    VOS_UINT8 tmMode;
    VOS_UINT8  reserved;
    VOS_UINT32 corrQR1Data0011; /* ????????6???????????????????????????? */
    VOS_UINT32 corrQR1Data01Iq;
    VOS_UINT32 corrQR2Data0011; /* ??4?????????? */
    VOS_UINT32 corrQR2Data01Iq; /* ??4?????????? */
    VOS_UINT32 corrQR3Data0011; /* ??4?????????? */
    VOS_UINT32 corrQR3Data01Iq; /* ??4?????????? */
    VOS_INT16 rsrpR0; /* ???? 0 rsrp?? ???? dB */
    VOS_INT16 rsrpR1; /* ???? 1 rsrp?? ???? dB */
    VOS_INT16 rsrpR2; /* ???? 2 rsrp?? ???? dB???? 4???????? */
    VOS_INT16 rsrpR3; /* ???? 3 rsrp?? ???? dB???? 4???????? */
    VOS_INT16 rssiR0; /* ???? 0 rssi?? ???? dB */
    VOS_INT16 rssiR1; /* ???? 1 rssi?? ???? dB */
    VOS_INT16 rssiR2; /* ???? 2 rssi?? ???? dB???? 4???????? */
    VOS_INT16 rssiR3; /* ???? 3 rssi?? ???? dB???? 4???????? */
    VOS_INT16 rsv[8];
} MTA_AT_EccStatusInd;


typedef struct {
    VOS_UINT32 eccEnable;
    VOS_UINT32 rptPeriod;
} AT_MTA_SetEccCfgReq;


typedef MTA_AT_ResultCnf MTA_AT_SET_ECC_CFG_CNF_STRU;

typedef MTA_AT_ResultCnf MTA_AT_LENDC_CNF_STRU;


typedef struct {
    /* ????????????????endc????: 0:????????1:???? */
    VOS_UINT8 endcAvaliableFlag;
    /* ????????ENDC??????????: 0:??ENDC??????1:ENDC???????????? */
    VOS_UINT8 nrPscellFlag;
    /* PLMN LIST????????PLMN????ENDC????, true??????PLMN????ENDC????, false????????PLMN????endc???? */
    VOS_UINT8 endcPlmnAvaliableFlag;
    /* ??????????????endc??????true??????????????endc??????false??????????????????endc???? */
    VOS_UINT8 endcEpcRestrictedFlag;
} MTA_AT_LendcInfo;


typedef struct {
    MTA_AT_ResultUint32 rslt; /* ???? */
    /* ????/????^LENDC??????????0:????  1:???? */
    VOS_UINT32       reportFlag;
    MTA_AT_LendcInfo lendcInfo;
} MTA_AT_LendcQryCnf;


typedef struct {
    MTA_AT_LendcInfo lendcInfo;
} MTA_AT_LendcInfoInd;

/*
 * ????????:
 * ASN.1????:
 * ????????: NRRC????????
 */
enum MTA_AT_FreqlockType {
    MTA_AT_FREQLOCK_TYPE_LOCK_NONE = 0,
    MTA_AT_FREQLOCK_TYPE_LOCK_FREQ = 1,
    MTA_AT_FREQLOCK_TYPE_LOCK_CELL = 2,
    MTA_AT_FREQLOCK_TYPE_LOCK_BAND = 3,

    MTA_AT_FREQLOCK_TYPE_LOCK_BUTT
};
typedef VOS_UINT8 MTA_AT_FreqlockTypeUint8;

/*
 * ????????:
 * ASN.1????:
 * ????????: NRRC SCS Type COMM
 */
enum MTA_AT_ScsTypeComm {
    MTA_AT_SCS_TYPE_COMM_15  = 0x00,
    MTA_AT_SCS_TYPE_COMM_30  = 0x01,
    MTA_AT_SCS_TYPE_COMM_60  = 0x02,
    MTA_AT_SCS_TYPE_COMM_120 = 0x03,
    MTA_AT_SCS_TYPE_COMM_240 = 0x04,

    MTA_AT_SCS_TYPE_COMM_BUTT
};
typedef VOS_UINT8 MTA_AT_ScsTypeCommUint8;

typedef MTA_AT_ResultCnf MTA_AT_NRRC_FREQLOCK_SET_CNF_STRU;


typedef struct {
    MTA_AT_FreqlockTypeUint8 freqType;
    MTA_AT_ScsTypeCommUint8  scsType;
    VOS_UINT16               reserved;
    VOS_UINT16               band;
    VOS_UINT16               phyCellId;
    VOS_UINT32               nrArfcn;
} AT_MTA_SetNrfreqlockReq;


typedef struct {
    MTA_AT_ResultUint32      result;
    MTA_AT_FreqlockTypeUint8 freqType;
    MTA_AT_ScsTypeCommUint8  scsType;
    VOS_UINT16               reserved;
    VOS_UINT16               band;
    VOS_UINT16               phyCellId;
    VOS_UINT32               nrArfcn;
} MTA_AT_NrrcFreqlockQryCnf;


typedef struct {
    AT_MTA_CfgUint8 cfg;         /* 0:????????1:???? */
    VOS_UINT8       reserved[3]; /* ?????? */
} AT_MTA_MbmsServiceOptionSetReq;


typedef struct {
    VOS_UINT32 mcc; /* MCC, 3 bytes */
    VOS_UINT32 mnc; /* MNC, 2 or 3 bytes */
} AT_MTA_PlmnId;


typedef struct {
    VOS_UINT32    mbmsSerId; /* Service ID */
    AT_MTA_PlmnId plmnId;    /* PLMN ID */
} AT_MTA_MbmsTmgi;


typedef struct {
    AT_MTA_MbmsServiceStateSetUint8 stateSet;    /* ???????? */
    VOS_UINT8                       reserved[3]; /* ?????? */
    VOS_UINT32                      areaId;      /* Area ID */
    AT_MTA_MbmsTmgi                 tmgi;        /* TMGI */
} AT_MTA_MbmsServiceStateSetReq;


typedef struct {
    AT_MTA_MbmsCastModeUint8 castMode;    /* 0:????,1:???? */
    VOS_UINT8                reserved[3]; /* ?????? */
} AT_MTA_MbmsPreferenceSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT32          utc[2]; /* (0..549755813887) */
} MTA_AT_MbmsSib16NetworkTimeQryCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    /* BSSI????????,0xFF:????BSSI???????????? */
    VOS_UINT8 bssiLevel;
    VOS_UINT8 reserved[3]; /* ?????? */
} MTA_AT_MbmsBssiSignalLevelQryCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT32          cellId; /* ????ID */
} MTA_AT_MbmsNetworkInfoQryCnf;


typedef struct {
    MTA_AT_ResultUint32                 result;
    MTA_AT_EmbmsFuntionalityStatusUint8 status;      /* ???????? */
    VOS_UINT8                           reserved[3]; /* ?????? */
} MTA_AT_EmbmsStatusQryCnf;


typedef struct {
    AT_MTA_CfgUint8 cfg;         /* 0:????,1:???? */
    VOS_UINT8       reserved[3]; /* ?????? */
} AT_MTA_MbmsUnsolicitedCfgSetReq;


typedef struct {
    MTA_AT_MbmsServiceEventUint8 event;       /* ???????? */
    VOS_UINT8                    reserved[3]; /* ?????? */
} MTA_AT_MbmsServiceEventInd;


typedef struct {
    /* 0: Normal;1: Low Power Consumption */
    AT_MTA_LteLowPowerUint8 lteLowPowerFlg;
    VOS_UINT8               reserved[3]; /* ?????? */
} AT_MTA_LowPowerConsumptionSetReq;


typedef struct {
    VOS_UINT32 freqList[AT_MTA_INTEREST_FREQ_MAX_NUM]; /* ???????? */
    /* VOS_FALSE: ????????;VOS_TRUE: MBMS???? */
    AT_MTA_MbmsPriorityUint8 mbmsPriority;
    VOS_UINT8                reserved[3]; /* ?????? */
} AT_MTA_MbmsInterestlistSetReq;


typedef struct {
    VOS_UINT32      opSessionId : 1;
    VOS_UINT32      spare : 31;
    VOS_UINT32      areaId;    /* Area ID */
    AT_MTA_MbmsTmgi tmgi;      /* TMGI */
    VOS_UINT32      sessionId; /* Session ID */
} MTA_AT_MbmsAvlService;


typedef struct {
    MTA_AT_ResultUint32 result;
    /* ??????????,0:???????????????? */
    VOS_UINT32            avlServiceNum;
    MTA_AT_MbmsAvlService avlServices[AT_MTA_MBMS_AVL_SERVICE_MAX_NUM]; /* ???????????? */
} MTA_AT_MbmsAvlServiceListQryCnf;


typedef struct {
    AT_MTA_CoexBwTypeUint16 coexBwType;
    AT_MTA_CoexCfgUint16    cfg;
    VOS_UINT16              txBegin;
    VOS_UINT16              txEnd;
    VOS_INT16               txPower;
    VOS_UINT16              rxBegin;
    VOS_UINT16              rxEnd;
    VOS_UINT8               reserved[2]; /* ?????? */
} AT_MTA_CoexPara;


typedef struct {
    VOS_UINT16      coexParaNum;
    VOS_UINT16      coexParaSize;
    AT_MTA_CoexPara coexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} AT_MTA_LteWifiCoexSetReq;


typedef struct {
    AT_MTA_CoexPara coexPara[AT_MTA_ISMCOEX_BANDWIDTH_NUM];
} MTA_AT_LteWifiCoexQryCnf;


typedef struct {
    VOS_UINT8 meid[AT_MTA_MEID_DATA_LEN];
    VOS_UINT8 rsv[1];
} AT_MTA_MeidSetReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????? */
    VOS_UINT8           efruimid[MTA_AT_EFRUIMID_OCTET_LEN_EIGHT];
    VOS_UINT8           meId[MTA_AT_MEID_NV_DATA_LEN_NEW + 1]; /* Data */
    VOS_UINT8           pEsn[MTA_AT_PESN_NV_DATA_LEN];         /* Data */
    VOS_UINT32          meIdReadRst;
    VOS_UINT32          pEsnReadRst;
} MTA_AT_MeidQryCnf;


typedef struct {
    MTA_AT_ResultUint32 result;      /* ???????????? */
    VOS_UINT8           transMode;   /* ???????? */
    VOS_UINT8           reserved[3]; /* ?????? */
} MTA_AT_TransmodeQryCnf;


typedef struct {
    AT_MTA_UeCenterTypeUint32 ueCenter; /* UE???? */
} AT_MTA_SetUeCenterReq;

#if (FEATURE_ON == FEATURE_UE_MODE_NR)

enum AT_MTA_NrDcMode {
    AT_MTA_NR_DC_MODE_NONE           = 0x00, /* ???????????? */
    AT_MTA_NR_DC_MODE_ENDC_ONLY      = 0x01, /* ??????ENDC */
    AT_MTA_NR_DC_MODE_NEDC_ONLY      = 0x02, /* ??????NEDC */
    AT_MTA_NR_DC_MODE_ENDC_NEDC_BOTH = 0x03, /* ENDC??NEDC?????? */
    AT_MTA_NR_DC_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_NrDcModeUint8;

enum AT_MTA_5GcAccessMode {
    AT_MTA_5GC_ACCESS_MODE_NOT_ALLOW  = 0x00, /* ??????????5gc */
    AT_MTA_5GC_ACCESS_MODE_NR_ONLY    = 0x01, /* ??????NR????5gc */
    AT_MTA_5GC_ACCESS_MODE_LTE_ONLY   = 0x02, /* ??????LTE????5gc */
    AT_MTA_5GC_ACCESS_MODE_NR_AND_LTE = 0x03, /* ????LTE??NR??????5gc */
    AT_MTA_5GC_ACCESS_MODE_BUTT
};
typedef VOS_UINT8 AT_MTA_5GcAccessModeUint8;


typedef struct {
    /* 0:??????NR????????SA??????1:????NR????????SA???? */
    VOS_UINT8                 nrSaSupportFlag;
    AT_MTA_NrDcModeUint8      nrDcMode;        /* NR??DC???????? */
    AT_MTA_5GcAccessModeUint8 en5gcAccessMode; /* ????????5gc?????? */
    VOS_UINT8                 rsv;
} AT_MTA_Set5GOptionReq;


typedef struct {
    MTA_AT_ResultUint32 rslt;
} MTA_AT_Set5GOptionCnf;


typedef struct {
    MTA_AT_ResultUint32 rslt;
    /* 0:??????NR????????SA??????1:????NR????????SA???? */
    VOS_UINT8                 nrSaSupportFlag;
    AT_MTA_NrDcModeUint8      nrDcMode;        /* NR??DC???????? */
    AT_MTA_5GcAccessModeUint8 en5gcAccessMode; /* ????????5gc?????? */
    VOS_UINT8                 rsv;
} MTA_AT_Qry5GOptionCnf;
#endif


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????? */
} MTA_AT_SetUeCenterCnf;


typedef struct {
    MTA_AT_ResultUint32       result;   /* ???????????? */
    AT_MTA_UeCenterTypeUint32 ueCenter; /* UE???? */
} MTA_AT_QryUeCenterCnf;


typedef struct {
    VOS_UINT32            opTa : 1;
    VOS_UINT32            opSpare : 31;
    VOS_UINT16            ta;
    VOS_UINT8             reserved[2];
    VOS_UINT32            mcc;    /* ?????????? */
    VOS_UINT32            mnc;    /* ?????????? */
    VOS_UINT32            cellId; /* ????ID */
    VOS_UINT32            arfcn;  /* ?????????? */
    VOS_UINT16            lac;    /* ???????? */
    VOS_INT16             rssi;   /* Receiving signal strength in dbm */
    MTA_RRC_GsmBandUint16 band;   /* GSM????(0-3) */
    VOS_UINT8             bsic;   /* ?????????? */
    /* IDLE????????PS????????????,????????????????????????????[0,7] ,??????99 */
    VOS_UINT8 rxQuality;
} MTA_AT_NetmonGsmScellInfo;


typedef struct {
    VOS_UINT32                 opCellId : 1;
    VOS_UINT32                 opLac : 1;
    VOS_UINT32                 opSpare : 30;
    VOS_UINT32                 mcc;    /* ?????????? */
    VOS_UINT32                 mnc;    /* ?????????? */
    VOS_UINT32                 cellId; /* ????ID */
    VOS_UINT32                 arfcn;  /* ???? */
    VOS_UINT16                 lac;    /* ???????? */
    VOS_UINT8                  reserved[2];
    MTA_NETMON_UtranTypeUint32 cellMeasTypeChoice; /* NETMON????????????:FDD,TDD */
    union {
        MTA_NETMON_UtranScellInfoFdd cellMeasResultsFdd; /* FDD */
        MTA_NETMON_UtranScellInfoTdd cellMeasResultsTdd; /* TDD */
    } u;
} MTA_AT_NetmonUtranScellInfo;


typedef struct {
    VOS_UINT32                mcc;                 /* ?????????? */
    VOS_UINT32                mnc;                 /* ?????????? */
    VOS_UINT32                cellIdentityHighBit; /* Cell Identity??32?? */
    VOS_UINT32                cellIdentityLowBit;  /* Cell Identity??32?? */
    VOS_UINT32                phyCellId;           /* ????????ID */
    VOS_UINT32                arfcn;               /* ???? */
    VOS_UINT32                tac;
    VOS_INT16                 rsrp;
    VOS_INT16                 rsrq;
    VOS_INT16                 sinr;
    MTA_AT_NrScsTypeCommUint8 nrScsType;
    VOS_UINT8                 reserved;
} MTA_AT_NetmonNrScellInfo;


typedef union {
    MTA_AT_NetmonGsmScellInfo   gsmSCellInfo;   /* GSM???????????? */
    MTA_AT_NetmonUtranScellInfo utranSCellInfo; /* WCDMA???????????? */
    MTA_NETMON_EutranScellInfo  lteSCellInfo;   /* LTE???????????? */
    MTA_AT_NetmonNrScellInfo    nrSCellInfo;    /* NR???????????? */
} MTA_AT_NetMonScellInfo;


typedef struct {
    VOS_UINT32            opBsic : 1;
    VOS_UINT32            opCellId : 1;
    VOS_UINT32            opLac : 1;
    VOS_UINT32            opSpare : 29;
    VOS_UINT32            cellId; /* ????ID */
    VOS_UINT32            afrcn;  /* ???? */
    VOS_UINT16            lac;    /* ???????? */
    VOS_INT16             rssi;   /* ??????RSSI */
    MTA_RRC_GsmBandUint16 band;   /* band 0-3 */
    VOS_UINT8             bsic;   /* ?????????? */
    VOS_UINT8             reserved;
} MTA_AT_NetmonGsmNcellInfo;


typedef struct {
    VOS_UINT32 arfcn; /* ???? */
    VOS_UINT16 psc;   /* ?????? */
    VOS_INT16  ecN0;  /* ECN0 */
    VOS_INT16  rscp;  /* RSCP */
    VOS_UINT8  reserved[2];
} MTA_AT_NetmonUtranNcellInfoFdd;


typedef struct {
    VOS_UINT32 arfcn;  /* ???? */
    VOS_UINT16 sc;     /* ???? */
    VOS_UINT16 syncId; /* ?????????? */
    VOS_INT16  rscp;   /* RSCP */
    VOS_UINT8  reserved[2];
} MTA_AT_NetmonUtranNcellInfoTdd;


typedef struct {
    VOS_UINT32 phyCellId; /* ????????ID */
    VOS_UINT32 arfcn;     /* ???? */
    VOS_INT16  rsrp;      /* RSRP???????????????? */
    VOS_INT16  rsrq;      /* RSRQ???????????????? */
    VOS_INT16  sinr;
    VOS_UINT8  reserved[2];
} MTA_AT_NetmonNrNcellInfo;


typedef struct {
    /* GSM ???????? */
    VOS_UINT8 gsmNCellCnt;
    /* WCDMA ???????? */
    VOS_UINT8 utranNCellCnt;
    /* LTE ???????? */
    VOS_UINT8 lteNCellCnt;
    /* NR ???????? */
    VOS_UINT8 nrNCellCnt;
    /* GSM ???????????? */
    MTA_AT_NetmonGsmNcellInfo gsmNCellInfo[NETMON_MAX_GSM_NCELL_NUM];
    /* NETMON????????????:FDD,TDD */
    MTA_NETMON_UtranTypeUint32 cellMeasTypeChoice;
    union {
        /* FDD???????????? */
        MTA_AT_NetmonUtranNcellInfoFdd fddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM];
        /* TDD???????????? */
        MTA_AT_NetmonUtranNcellInfoTdd tddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM];
    } u;
    /* LTE ???????????? */
    MTA_NETMON_LteNcellInfo lteNCellInfo[NETMON_MAX_LTE_NCELL_NUM];
    /* NR ???????????? */
    MTA_AT_NetmonNrNcellInfo nrNCellInfo[NETMON_MAX_NR_NCELL_NUM];
} MTA_AT_NetmonNcellInfo;


typedef struct {
    VOS_UINT32                   arfcn;
    VOS_UINT32                   phyCellId;
    VOS_INT16                    rsrp;
    VOS_INT16                    rsrq;
    VOS_INT16                    sinr;
    MTA_AT_NetmonMeasRsTypeUint8 measRsType;
    VOS_UINT8                    rsv;
} MTA_AT_NetmonNrCcInfo;


typedef struct {
    VOS_UINT32            componentCarrierNum;                        /* ???????? */
    MTA_AT_NetmonNrCcInfo componentCarrierInfo[NETMON_MAX_NR_CC_NUM]; /* ???????? */
} MTA_AT_NetmonNrSscellInfo;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????????? */
    /* 0:??????????????1:??????????2:???????????????? */
    MTA_NetMonCellTypeUint32       cellType;
    MTA_AT_NetmonCellInfoRatUint32 ratType; /* ?????????????????????? */
    union {
        MTA_AT_NetmonNcellInfo    nCellInfo; /* ???????? */
        MTA_AT_NetMonScellInfo    unSCellInfo;
        MTA_AT_NetmonNrSscellInfo secSrvCellInfo; /* ?????????????? */
    } u;
} MTA_AT_NetmonCellInfo;


typedef struct {
    VOS_UINT32 reserveValue;
} AT_MTA_QryAfcClkFreqXocoefReq;


typedef struct {
    MTA_AT_ResultUint32 result;

    AT_MTA_AfcClkStatusUint32 status;
    VOS_INT32                 deviation; /* ???? */

    /* ???????? */
    VOS_INT16 coeffStartTemp;
    VOS_INT16 coeffEndTemp;

    /* ?????????? */
    VOS_UINT32 coeffMantissa[AT_MTA_GPS_XO_COEF_NUM]; /* a0,a1,a2,a3???? */
    VOS_UINT16 coeffExponent[AT_MTA_GPS_XO_COEF_NUM]; /* a0,a1,a2,a3???? */

    MTA_AT_ModemIdUint8 modemId;
    MTA_AT_RatModeUint8 ratMode;
    VOS_UINT8           reserved[2];
} MTA_AT_QryAfcClkFreqXocoefCnf;


typedef struct {
    VOS_UINT32 doSysEvent;
} AT_MTA_EvdoSysEventSetReq;


typedef struct {
    VOS_UINT32 doSigMask;
} AT_MTA_EvdoSigMaskSetReq;


typedef struct {
    VOS_UINT32 paraLen;
    VOS_UINT8  content[4];
} MTA_AT_EvdoRevaRlinkInfoInd;


typedef struct {
    VOS_UINT32 paraLen;
    VOS_UINT8  content[4];
} MTA_AT_EvdoSigExeventInd;


typedef struct {
    /* GPS?????????????????????????????????????????????????? */
    AT_MTA_XcposrCfgUnit8 xcposrEnableCfg;
    VOS_UINT8             reserved[3];
} AT_MTA_SetXcposrReq;


typedef struct {
    MTA_AT_ResultUint32   result; /* ???????????? */
    AT_MTA_XcposrCfgUnit8 xcposrEnableCfg;
    VOS_UINT8             reserved[3];
} MTA_AT_QryXcposrCnf;


typedef struct {
    /* +XCPOSRRPT?????????????????????????????????????????????? */
    VOS_UINT8 xcposrRptFlg;
    VOS_UINT8 reserved[3];
} AT_MTA_SetXcposrrptReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????? */
    VOS_UINT8           xcposrRptFlg;
    VOS_UINT8           reserved[3];
} MTA_AT_QryXcposrrptCnf;


typedef struct {
    VOS_UINT32 sensorStat; /* Sensor Hub ???? */
} AT_MTA_SetSensorReq;

typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetSensorCnf;


typedef struct {
    VOS_UINT8 screenStat; /* Screen ???? */
    VOS_UINT8 reserved[3];
} AT_MTA_SetScreenReq;

typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetScreenCnf;


typedef struct {
    AT_MTA_CfgUint8 cfg;         /* 0:????,1:???? */
    VOS_UINT8       reserved[3]; /* ?????? */
} AT_MTA_SetRxtestmodeReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????? */
} MTA_AT_SetRxtestmodeCnf;

typedef struct {
    VOS_UINT16 cause;
    VOS_UINT16 reserved; /* ?????? */
} MTA_AT_AfcClkUnlockInd;


typedef struct {
    VOS_UINT8 groupId;  /* ?????? */
    VOS_UINT8 deviceId; /* ?????? */
    VOS_UINT8 caseId;   /* ???????????????? */
    VOS_UINT8 mode;     /* ???????????? */
} MTA_AT_DeviceFreq;


typedef struct {
    VOS_UINT8         rptDeviceNum;                                 /* ???????????????????? */
    VOS_UINT8         reserved[3];                                  /* ?????? */
    MTA_AT_DeviceFreq deviceFreqList[MTA_AT_MAX_BESTFREQ_GROUPNUM]; /* 8?????????????????? */
} MTA_AT_BestFreqCaseInd;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????????? */
    VOS_UINT8           activeDeviceNum;
    VOS_UINT8           reserved[3];
    MTA_AT_DeviceFreq   deviceInfoList[MTA_AT_MAX_BESTFREQ_GROUPNUM];
} MTA_AT_BestfreqQryCnf;


typedef struct {
    VOS_UINT32 ratType; /* 0-GSM 1-WCDMA */
} AT_MTA_SlaveSetReq;

typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT16          rfic0DieIdValid; /* 1-?????? 0-?????? */
    VOS_UINT16          rfic1DieIdValid;
    VOS_UINT16          rfic2DieIdValid;
    VOS_UINT16          rfic3DieIdValid;
    VOS_UINT16          rfic0DieId[MTA_AT_MAX_DIE_ID_LEN];
    VOS_UINT16          rfic1DieId[MTA_AT_MAX_DIE_ID_LEN];
    VOS_UINT16          rfic2DieId[MTA_AT_MAX_DIE_ID_LEN];
    VOS_UINT16          rfic3DieId[MTA_AT_MAX_DIE_ID_LEN];
} MTA_AT_RficDieIdReqCnf;


typedef struct {
    VOS_UINT16 dataValid;
    VOS_UINT16 reserved;
    VOS_UINT8  rffeDieId[MTA_AT_MAX_RFFE_DIE_ID_LEN];
} MTA_AT_RffeDieIdValue;


typedef struct {
    MTA_AT_ResultUint32   result;                                  /* ???????? */
    MTA_AT_RffeDieIdValue dieIdData[MTA_AT_MAX_RFFE_DIE_ID_COUNT]; /* DieId???? */
} MTA_AT_RffeDieIdReqCnf;


typedef struct {
    VOS_UINT16 cmdType;   /* ???????? */
    VOS_UINT16 ratBitmap; /* ??????rat????????bitmap */
    VOS_UINT32 para1;     /* ????????1 */
    VOS_UINT32 para2;     /* ????????2 */
    VOS_UINT32 para3;     /* ????????3 */
} AT_MTA_PhyComCfgSetReq;

#if (FEATURE_UE_MODE_NR == FEATURE_ON)

typedef struct {
    VOS_UINT16 cmdType;   /* ???????? */
    VOS_UINT16 paraNum;   /* ???????? */
    VOS_UINT32 paraList[MTA_NRPHY_MAX_PARA_NUM];     /* ???????? */
} AT_MTA_NrphyComCfgSetReq;
#endif

typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_PhyComCfgSetCnf;

#if (FEATURE_UE_MODE_NR == FEATURE_ON)

typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_NrphyComCfgSetCnf;
#endif


typedef struct {
    AT_MTA_CfgUint8 enable;      /* 0??????????????1???????????? */
    VOS_UINT8       reserved[3]; /* ?????? */
} AT_MTA_SetCrrconnReq;


typedef struct {
    VOS_UINT8 status0;
    VOS_UINT8 status1;
    VOS_UINT8 status2;
    VOS_UINT8 reserved; /* ?????? */
} MTA_AT_CrrconnStatusInd;


typedef MTA_AT_ResultCnf MTA_AT_SetCrrconnCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    AT_MTA_CfgUint8     enable;
    VOS_UINT8           status0;
    VOS_UINT8           status1;
    VOS_UINT8           status2;
} MTA_AT_QryCrrconnCnf;


typedef struct {
    VOS_UINT32 enable;    /* 0??????????????1???????????? */
    VOS_UINT32 threshold; /* LPDCP???????????? */
} AT_MTA_SetVtrlqualrptReq;


typedef struct {
    VOS_INT16  rsrp; /* RSRP???????? */
    VOS_INT16  rsrq; /* RSRQ???????? */
    VOS_INT16  rssi; /* RSSI???????? */
    VOS_UINT16 bler; /* ?????? */
} MTA_AT_RlQualityInfoInd;


typedef struct {
    VOS_UINT32 currBuffTime;   /* ?????????????????? */
    VOS_UINT32 currBuffPktNum; /* ?????????????????? */
    /* MAC????????,??????????????????????????????????????????:bytes/s */
    VOS_UINT32 macUlThrput;
    VOS_UINT32 maxBuffTime; /* ??????????????????ms */
} MTA_AT_VideoDiagInfoRpt;


typedef MTA_AT_ResultCnf MTA_AT_SetVtrlqualrptCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT8           dieSn[MTA_PMU_MAX_DIE_SN_LEN];
} MTA_AT_PmuDieSnReqCnf;


typedef struct {
    VOS_UINT32 extendFlag;
    VOS_UINT32 mipiId;
    VOS_UINT32 slaveId;
    VOS_UINT32 regAddr;
    VOS_UINT32 value;
    VOS_UINT32 byteCnt;
} AT_MTA_MipiWrexReq;


typedef struct {
    VOS_UINT32 extendFlag;
    VOS_UINT32 mipiId;
    VOS_UINT32 slaveId;
    VOS_UINT32 regAddr;
    VOS_UINT32 byteCnt;
    VOS_UINT32 speedType;
} AT_MTA_MipiRdexReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_MipiWrexCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT32          value;
} MTA_AT_MipiRdexCnf;


typedef struct {
    AT_MTA_ModemCapUpdateTypeUint8 modemCapUpdateType; /* MODEM???????????????? */
    VOS_UINT8                      reserved[3];
} AT_MTA_ModemCapUpdateReq;


typedef struct {
    MTA_AT_ResultUint32 rslt; /* MODEM???????????????? */
} MTA_AT_ModemCapUpdateCnf;


typedef struct {
    VOS_UINT8 dlCategery;  /* ????category */
    VOS_UINT8 ulCategery;  /* ????category */
    VOS_UINT8 reserved[2]; /* ?????? */
} MTA_AT_LteCategoryInfoInd;

/*
 * H2ASN????????????????
 */
typedef struct {
    /* _H2ASN_MsgChoice_Export AT_MTA_MSG_TYPE_ENUM_UINT32 */
    AT_MTA_MsgTypeUint32 msgId;
    AT_APPCTRL           appCtrl;
    VOS_UINT8            msgBlock[4];
    /*
     * _H2ASN_MsgChoice_When_Comment          AT_MTA_MsgTypeUint32
     */
} AT_MTA_MsgData;
/* _H2ASN_Length UINT32 */

typedef struct {
    VOS_MSG_HEADER
    AT_MTA_MsgData msgData;
} AtMtaInterface_Msg;


typedef struct {
    VOS_INT32 sec;
    VOS_INT32 min;
    VOS_INT32 hour;
    VOS_INT32 day;
    VOS_INT32 month;
    VOS_INT32 year;
    VOS_INT32 zone;
} AT_MTA_ModemTime;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetTimeCnf;


typedef struct {
    VOS_UINT32 value;
} AT_MTA_Gnssnty;



typedef struct {
    VOS_UINT8 deviceId; /* ??????????????????ID, 0??????????1-255???????????????? */
    VOS_UINT8 mode;     /* 0??????????????????1???????????????? */
    VOS_UINT8 reserved[2];
} AT_MTA_BestfreqSetReq;


enum MTA_AT_RcmTasTestRatmode {
    MTA_AT_RATMODE_GSM   = 0,
    MTA_AT_RATMODE_WCDMA = 1,
    MTA_AT_RATMODE_LTE   = 2,
    MTA_AT_RATMODE_TDS   = 3,
    MTA_AT_RATMODE_1X    = 4,
    MTA_AT_RATMODE_HRPD  = 5,
    MTA_AT_RATMODE_BUTT
};
typedef VOS_UINT32 MTA_AT_TasTestRatmodeUint32;


typedef struct {
    MTA_AT_TasTestRatmodeUint32 ratMode; /* 1-WCDMA   2-TLE */
    VOS_UINT32                  para0;
    VOS_UINT32                  para1;
    VOS_UINT32                  para2;
    VOS_UINT32                  para3;
} AT_MTA_TasTestCfg;


typedef struct {
    VOS_RATMODE_ENUM_UINT32 ratMode; /* 1-WCDMA   2-TLE */
} AT_MTA_TasTestQry;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_TasTestCfgCnf;


typedef struct {
    VOS_UINT16 uhwSrcAntTimeLength;  /* ??(????)??????????????:ms */
    VOS_UINT16 uhwDestAntTimeLength; /* ??????????????????:ms */
    /* ??(????)????????????????????????:0.1dB */
    VOS_INT16 srcAntTxPowerGain;
    /* ????????????????????????????:0.1dB */
    VOS_INT16 destAntTxPowerGain;
} MTA_AT_TxStateiiLevel;


typedef struct {
    VOS_UINT16            uhwLevelNum;
    VOS_UINT16            uhwRsv;
    MTA_AT_TxStateiiLevel levelItem[MTA_AT_MAX_STATEII_LEVEL_ITEM];
} MTA_AT_TxStateiiLevelTable;


typedef struct {
    MTA_AT_ResultUint32         result;
    MTA_AT_TasTestRatmodeUint32 ratMode;
    VOS_UINT32                  currLevel; /* ???????????? */
    MTA_AT_TxStateiiLevel       levelInfo; /* ?????????????????? */
    MTA_AT_TxStateiiLevelTable  usedTable; /* ?????? */
} MTA_AT_TasTestQryCnf;


typedef struct {
    VOS_UINT8 pmicId;
    VOS_UINT8 reserved[3];
} AT_MTA_MultiPmuDieIdSet;


typedef struct {
    AT_MTA_RsInfoTypeUint32 rsInfoType; /* 0:????RSRP??1:????RSRQ */
} AT_MTA_RsInfoQryReq;


typedef struct {
    VOS_UINT32 cellId; /* ????ID */
    VOS_UINT32 earfcn; /* ???????? */
    /* ??????????????LRRC??100????????AT???????????????? */
    VOS_INT32 rsrp;
} MTA_AT_RsrpInfo;


typedef struct {
    VOS_UINT32 cellId; /* ????ID */
    VOS_UINT32 earfcn; /* ???????? */
    /* ??????????????LRRC??100????????AT???????????????? */
    VOS_INT32 rsrq;
} MTA_AT_RsrqInfo;


typedef struct {
    AT_MTA_RsInfoTypeUint32 rsInfoType; /* 0:????RSRP??1:????RSRQ */
    VOS_UINT32              rsInfoNum;
    union {
        MTA_AT_RsrpInfo rsrpInfo[AT_MAX_RS_INFO_NUM]; /* RSRP???????? */
        MTA_AT_RsrqInfo rsrqInfo[AT_MAX_RS_INFO_NUM]; /* RSRQ???????? */
    } u;
} MTA_AT_RsInfoRslt;


typedef struct {
    MTA_AT_ResultUint32 result;
    MTA_AT_RsInfoRslt   rsInfoRslt;
} MTA_AT_RsInfoQryCnf;


typedef struct {
    VOS_UINT32 errcCapType;
    VOS_UINT32 para1;
    VOS_UINT32 para2;
    VOS_UINT32 para3;
} AT_MTA_ErrccapCfgReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_ErrccapCfgCnf;


typedef struct {
    VOS_UINT32 errcCapType;
} AT_MTA_ErrccapQryReq;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT32          errcCapType;
    VOS_UINT32          para1;
    VOS_UINT32          para2;
    VOS_UINT32          para3;
} MTA_AT_ErrccapQryCnf;


typedef struct {
    VOS_UINT32                     mcc;
    VOS_UINT32                     mnc;
    VOS_UINT32                     cellId;
    VOS_UINT32                     lac;
    AT_MTA_SysModeUint32           sysmode;
    AT_MTA_PseucellNotifyTypeUint8 pseucellNotifyType; /* 0:????????????????:?????? */
    VOS_UINT8                      reserved[3];
} AT_MTA_PseucellInfoSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_PseucellInfoSetCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_INT16           powerDet;     /* ??????????????0.1dBm???? */
    VOS_UINT8           reserved1[2]; /* ?????? */
} MTA_AT_PowerDetQryCnf;


typedef struct {
    VOS_UINT16 readType;
    VOS_UINT16 mipiId;
    VOS_UINT16 slaveId;
    VOS_UINT16 regAddr;
    VOS_UINT16 speedType;
    VOS_UINT16 readBitMask;
    VOS_UINT16 reserved1;
    VOS_UINT16 reserved2;
} AT_MTA_MipiReadReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????? */
    VOS_UINT32          value;
} MTA_AT_MipiReadCnf;


typedef struct {
    VOS_UINT16 writeType;
    VOS_UINT16 mipiId;
    VOS_UINT16 slaveId;
    VOS_UINT16 regAddr;
    VOS_UINT16 mipiData;
    VOS_UINT16 reserved1;
} AT_MTA_PhyMipiWriteReq;


typedef struct {
    MTA_AT_ResultUint32 result; /* ???????? */
} MTA_AT_PhyMipiWriteCnf;


typedef struct {
    VOS_UINT32 enableFlag;
} AT_MTA_NoCardModeSetReq;

typedef MTA_AT_ResultCnf MTA_AT_NoCardModeSetCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT32          enableFlag;
} MTA_AT_NoCardModeQryCnf;


typedef struct {
    AT_MTA_ChrAlarmRlatOpUint32 alarmOp;
    VOS_UINT32                  alarmId;
    VOS_UINT32                  alarmDetail;
} AT_MTA_ChrAlarmRlatCfgSetReq;


typedef struct {
    MTA_AT_ResultUint32         result;
    AT_MTA_ChrAlarmRlatOpUint32 alarmOp;
    VOS_UINT32                  alarmDetail;
} MTA_AT_ChrAlarmRlatCfgSetCnf;


typedef struct {
    VOS_UINT16 transactionId;
    VOS_UINT8  msgBodyType;
    VOS_UINT8  locSource;
    VOS_UINT8  endFlag;
    VOS_UINT8  commonIeValidFlg;
    VOS_UINT8  id;
    VOS_UINT8  locCalcErr;
    VOS_UINT8  nameLength;
    VOS_UINT8  reserved[3];
    VOS_UINT8  name[AT_MTA_EPDU_NAME_LENGTH_MAX];
    VOS_UINT8  totalNum;
    VOS_UINT8  index;
    VOS_UINT16 epduLength;
    VOS_UINT8  epduContent[AT_MTA_EPDU_CONTENT_LENGTH_MAX];
    VOS_UINT8  reserved1[2];
} AT_MTA_EpduSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_EpduSetCnf;


typedef struct {
    VOS_UINT32 freqBegin; /* ????100khz */
    VOS_UINT32 freqEnd;   /* ????100khz */
} AT_MTA_FreqRange;


typedef struct {
    VOS_UINT16 bandInd; /* Band:1-255 */
    VOS_UINT8  reserved;
    /* 0-4,0:??????????????Band???????????????????????? */
    VOS_UINT8        freqRangeNum;
    AT_MTA_FreqRange freqRange[AT_MTA_MAX_SUB_BAND_NUM];
} AT_MTA_BandInfo;


typedef struct {
    VOS_UINT8       caA2Flg;  /* CA A2???????? */
    VOS_UINT8       caA4Flg;  /* CA A4???????? */
    VOS_UINT8       caCqiFlg; /* CA cqi=0???????? */
    VOS_UINT8       reserved[3];
    VOS_UINT16      bandNum; /* 0-8,0:????????????????CA SCell */
    AT_MTA_BandInfo bandInfo[AT_MTA_MAX_BAND_NUM];
} AT_MTA_CaInfo;


typedef struct {
    /* ??????????Ca??????0:??????  1:???? */
    VOS_UINT8     caActFlag;
    VOS_UINT8     reserved[3]; /* ?????? */
    AT_MTA_CaInfo caInfo;
} AT_MTA_CaCfgSetReq;


typedef struct {
    VOS_UINT8             cellIndex; /* ????????, 0: PCell, 1~7: SCell */
    MTA_AT_BandWidthUint8 bandWidth; /* SCell???????? */
    VOS_UINT16            bandInd;   /* SCell???? */

    /* CA????????????????0:????????1:?????? */
    VOS_UINT8 ulConfigured;
    /* CA????????????????0:????????1:?????? */
    VOS_UINT8 dlConfigured;
    /* SCell????????????0:????????1:???? */
    VOS_UINT8 actived;
    /* ??SCell??????LaaScell, 0:????, 1:?? */
    VOS_UINT8 laaScellFlg;

    VOS_UINT32 earfcn; /* SCell???? */
} MTA_AT_CaCellInfo;


typedef struct {
    MTA_AT_ResultUint32 result;                           /* ???????? */
    VOS_UINT32          totalCellNum;                     /* ??????????????Cell?????? */
    MTA_AT_CaCellInfo   cellInfo[MTA_AT_CA_MAX_CELL_NUM]; /* ??ulTotalCellNum?????????? */
} MTA_AT_CaCellInfoCnf;


typedef struct {
    VOS_UINT32        totalCellNum;                     /* ??????????????Cell?????? */
    MTA_AT_CaCellInfo cellInfo[MTA_AT_CA_MAX_CELL_NUM]; /* ??ulTotalCellNum?????????? */
} MTA_AT_CaCellInfoNtf;


typedef struct {
    VOS_UINT8               fineTimeType;
    VOS_UINT8               forceFlag;
    VOS_UINT16              num;
    MTA_AT_FineTimeRatUint8 ratMode; /* ???????????? */
    VOS_UINT8               reserved[3];
} AT_MTA_FineTimeSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_FineTimeSetCnf;


typedef struct {
    MTA_AT_ResultUint32       result;
    VOS_INT32                 sinr;                                 /* ?????????? */
    VOS_UINT8                 utcTime[MTA_AT_UTC_MAX_LENGTH];       /* (0..549755813887) */
    VOS_UINT8                 utcTimeOffset[MTA_AT_UTC_MAX_LENGTH]; /* (0..549755813887) */
    VOS_INT16                 ta;                                   /* ???????????????????? */
    VOS_INT16                 leapSecond;                           /* ?????????? */
    VOS_UINT8                 leapSecondValid;                      /* ???????????????? */
    MTA_AT_FineTimeRatUint8   rat;
    MTA_AT_ProtocolStateUint8 state; /* ????LRRC???????? */
    VOS_UINT8                 reserved[3];
} MTA_AT_SibFineTimeInd;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT16          sysFn;
    VOS_UINT8           reserved[2];
} MTA_AT_LppFineTimeInd;


typedef struct {
    MTA_AT_RatModeUint8          overHeatingType; /* ????????????????LTE??NR */
    AT_MTA_OoverheatingParaUint8 overHeatingFlag; /* ???????????????????? */
    VOS_UINT8                    reserved[2];
    VOS_UINT32                   setParamFlag; /* ???????????????? */
    VOS_UINT32                   param1;       /* ????1 */
    VOS_UINT32                   param2;       /* ????2 */
    VOS_UINT32                   param3;       /* ????3 */
    VOS_UINT32                   param4;       /* ????4 */
    VOS_UINT32                   param5;       /* ????5 */
    VOS_UINT32                   param6;       /* ????6 */
    VOS_UINT32                   param7;       /* ????7 */
    VOS_UINT32                   param8;       /* ????8 */
    VOS_UINT32                   param9;       /* ????9 */
    VOS_UINT32                   param10;      /* ????10 */
} AT_MTA_OverHeatingSetReq;


typedef struct {
    MTA_AT_RatModeUint8 overHeatingType; /* ????????????????LTE??NR */
} AT_MTA_OverHeatingQryReq;


typedef struct {
    VOS_UINT32          seq;     /* ?????? */
    VOS_BOOL            endFlag; /* ?????????????????? */
    AT_MTA_RatModeUint8 ratMode;
    VOS_UINT8           reserved[3];
    VOS_UINT32          msgLen;
    VOS_UINT8           msg[0];  //lint !e43
} AT_MTA_UeCapParamSet;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_OverHeatingSetCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_UeCapParamSetCnf;


typedef struct {
    MTA_AT_ResultUint32          result;                 /* ???? */
    AT_MTA_OoverheatingParaUint8 overHeatingSupportFlag; /* ???????????????????? */
    VOS_UINT8                    reserved[3];
    VOS_UINT32                   lastReportParamFlag; /* ???????????????? */
    VOS_UINT32                   param1;              /* ????1 */
    VOS_UINT32                   param2;              /* ????2 */
    VOS_UINT32                   param3;              /* ????3 */
    VOS_UINT32                   param4;              /* ????4 */
    VOS_UINT32                   param5;              /* ????5 */
    VOS_UINT32                   param6;              /* ????6 */
    VOS_UINT32                   param7;              /* ????7 */
    VOS_UINT32                   param8;              /* ????8 */
    VOS_UINT32                   param9;              /* ????9 */
    VOS_UINT32                   param10;             /* ????10 */
} MTA_AT_OverHeatingQryCnf;


typedef struct {
    VOS_UINT32 msgLen;  /* ??????????????????2400???? */
    VOS_UINT8  msg[0];  //lint !e43
} MTA_AT_LrrcUeCapInfoNotify;


typedef struct {
    VOS_UINT32 msgLen;  /* ??????????????????2400???? */
    VOS_UINT8  msg[0];  //lint !e43
} MTA_AT_NrrcUeCapInfoNotify;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_CaCellSetCnf;


typedef struct {
    VOS_BOOL blEnableType;
} AT_MTA_CaCellSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_BOOL            blEnableType;
} MTA_AT_CaCellQryCnf;


typedef struct {
    VOS_UINT32 cmdType;
    VOS_UINT32 para1;
    VOS_UINT32 para2;
    VOS_UINT32 para3;
} AT_MTA_L2ComCfgSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_L2ComCfgSetCnf;


typedef struct {
    VOS_UINT32 cmdType;
} AT_MTA_L2ComCfgQryReq;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT32          cmdType;
    VOS_UINT32          para1;
    VOS_UINT32          para2;
    VOS_UINT32          para3;
} MTA_AT_L2ComCfgQryCnf;


typedef struct {
    VOS_UINT32 operation;  /* 0:????  1:???? */
    VOS_UINT32 sleepThres; /* ????????????????????????????????active -> sleep????????????:ms */
} AT_MTA_NPdcpSleepThresCfgReq;


typedef struct {
    VOS_UINT32 result; /* ????????????, 0: ????, 1: ???? */
    VOS_UINT32 curThres;
} MTA_AT_NPdcpSleepThresCfgCnf;


typedef struct {
    VOS_UINT32 ackType;   /* ACK???? */
    VOS_UINT32 ackValue1; /* ACK??1 */
    VOS_UINT32 ackValue2; /* ACK??2 */
    VOS_UINT32 ackValue3; /* ACK??3 */
} MTA_AT_PhyCommAckInd;


typedef struct {
    AT_MTA_SmsDomainUint8 smsDomain;
    VOS_UINT8             reserved[3];
} AT_MTA_SmsDomainSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SmsDomainSetCnf;


typedef struct {
    MTA_AT_ResultUint32   result;
    AT_MTA_SmsDomainUint8 smsDomain;
    VOS_UINT8             reserved[3];
} MTA_AT_SmsDomainQryCnf;


typedef struct {
    VOS_UINT32 mcc;
    VOS_UINT32 mnc;
    VOS_UINT8  length;
    VOS_UINT8  epsNetwork[MTA_AT_EPS_NETWORK_BYTE];
    VOS_UINT8  reserved;
} MTA_AT_EpsNetworkInfo;


typedef struct {
    MTA_AT_ResultUint32   result;
    MTA_AT_EpsNetworkInfo epsNetworkInfo;
} MTA_AT_EpsNetworkQryCnf;


typedef struct {
    VOS_UINT32 locationPermitFlag;
} AT_MTA_GpslocsetSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_GpslocsetSetCnf;



typedef struct {
    MTA_AT_ResultUint32 result;
    TIME_ZONE_Time      time;
} MTA_AT_CclkQryCnf;



typedef struct {
    VOS_INT32 tempResult;
} MTA_AT_TempProtectInd;


typedef struct {
    AT_MTA_NvRefreshReasonUint8 reason;
    VOS_UINT8                   reserved[3];
} AT_MTA_NvRefreshSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_NvRefreshSetCnf;


typedef struct {
    VOS_UINT32 pseudBtsType;
} MTA_AT_PseudBtsIdentInd;


typedef struct {
    VOS_UINT16 num; /* ?????????????? */
    VOS_UINT8  rsv[2];

} AT_MTA_SetForcesyncReq;


typedef struct {
    VOS_UINT32 result; /* ???????? */
} MTA_AT_SetForcesyncCnf;

/*
 * ????????: AT??MTA????LTEPWRDISS??????????????
 */
typedef struct {
    VOS_UINT8 mode;
    VOS_UINT8 reserved;
    VOS_INT16 para;
} AT_MTA_LtepwrdissSetReq;

/*
 * ????????: MTA??AT????LTEPWRDISS??????????????????
 */
typedef struct {
    MTA_AT_ResultUint32 result;
} AT_MTA_LtepwrdissSetCnf;


typedef struct {
    AT_MTA_DcxoSampleTypeUint16 dcxoSampleType; /* DCXO_SAMPLE???????? */
    VOS_UINT8                   rsv[2];
} AT_MTA_DcxoSampeQryReq;

/*
 * ????????:
 * ASN.1????:
 * ????????: ????????DCXO????
 */
typedef struct {
    /* ??????????2016.4????????1604,????1604?????????????? */
    VOS_INT32 swTime : 24;
    /* ????????4bit??modem_id,??4bit????????0:G??1:U??2:L??3:TD??4:1X??5:EVDO */
    VOS_INT32 swMode : 8;
    VOS_INT32 swTemp; /* ??????Boston????????0.001?? */
    VOS_INT32 swPpm;  /* ????????????????2^31/10^6 */
} MTA_AT_DcxoSample;

/*
 * ????????:
 * ASN.1????:
 * ????????:2.2????????????????????????????
 */
typedef struct {
    /* ??????????????????????????????????2^31/10^6 */
    VOS_INT32 swInitFrequency;
    /* ????????????????????????????0.001?? */
    VOS_INT32 swInitTemperature;
} MTA_AT_XoInitFrequency;


typedef union {
    MTA_AT_DcxoSample      sample[UCOM_NV_DCXO_SAMPLE_H_MAX_NUM]; /* ???????????????? */
    MTA_AT_XoInitFrequency dcxoInitPpm;                           /* ???????????? */
} MTA_AT_DCXO_SECTION_DATA_UNION_STRU;


typedef struct {
    AT_MTA_DcxoSampleTypeUint16         dcxoSampleType; /* DCXO_SAMPLE???????? */
    MTA_AT_DcxoSampleResultUint16       result;
    MTA_AT_DCXO_SECTION_DATA_UNION_STRU sctionData; /* ?????????????????????? */
} MTA_AT_DcxoSampeQryCnf;


typedef struct {
    VOS_UINT32 bandCnt;                                /* ???? */
    VOS_UINT16 bandInfo[AT_MTA_UECAP_MAX_NR_BAND_NUM]; /* Band???? */
} MTA_NRRC_BandInfo;


typedef struct {
    VOS_UINT32 bandWcdmaI2100 : 1;
    VOS_UINT32 bandWcdmaIi1900 : 1;
    VOS_UINT32 bandWcdmaIii1800 : 1;
    VOS_UINT32 bandWcdmaIv1700 : 1;
    VOS_UINT32 bandWcdmaV850 : 1;
    VOS_UINT32 bandWcdmaVi800 : 1;
    VOS_UINT32 bandWcdmaVii2600 : 1;
    VOS_UINT32 bandWcdmaViii900 : 1;
    VOS_UINT32 bandWcdmaIxJ1700 : 1;
    VOS_UINT32 bandSpare1 : 1;
    VOS_UINT32 bandWcdmaXi1500 : 1;
    VOS_UINT32 bandSpare7 : 7;
    VOS_UINT32 bandWcdmaXix850 : 1;
    VOS_UINT32 bandSpare13 : 13;
} AT_WCDMA_PrefBand;


typedef struct {
    VOS_UINT32 bandGsm450 : 1;
    VOS_UINT32 bandGsm480 : 1;
    VOS_UINT32 bandGsm850 : 1;
    VOS_UINT32 bandGsmP900 : 1;
    VOS_UINT32 bandGsmR900 : 1;
    VOS_UINT32 bandGsmE900 : 1;
    VOS_UINT32 bandGsm1800 : 1;
    VOS_UINT32 bandGsm1900 : 1;
    VOS_UINT32 bandGsm700 : 1;
    VOS_UINT32 bandSpare7 : 23;

} AT_GsmPrefBand;


typedef union {
    VOS_UINT32        band;
    AT_WCDMA_PrefBand bitBand;
} AT_WCDMA_BAND_SET_UN;


typedef union {
    VOS_UINT32     band;
    AT_GsmPrefBand bitBand;
} AT_GSM_BAND_SET_UN;

#if (FEATURE_LTEV == FEATURE_ON)

typedef struct {
    VOS_UINT32 bandNum;
    VOS_UINT32 opBand[MTA_AT_LTEV_BAND_MAX_NUM];
} MTA_AT_LtevBandInfo;
#endif


typedef struct {
    VOS_UINT32           ueGSptBand;
    VOS_UINT32           ueWSptBand;
    VOS_UINT32           allUeBand;
    AT_WCDMA_BAND_SET_UN unWRFSptBand;
    AT_GSM_BAND_SET_UN   unGRFSptBand;
    MTA_NRRC_BandInfo    nrBand;
#if (FEATURE_LTEV == FEATURE_ON)
    MTA_AT_LtevBandInfo  ltevBand;
#endif
} AT_UE_BandCapaSt;


typedef struct {
    MTA_AT_ResultUint32 result;
    AT_UE_BandCapaSt    bandFeature;
} MTA_AT_SfeatureQryCnf;

#if (FEATURE_ON == FEATURE_UE_MODE_NR)

typedef struct {
    VOS_UINT32 nrrcCfgNetMode;
    VOS_UINT32 para[AT_MTA_NRRCCAP_PARA_MAX_NUM];
} AT_MTA_NrrccapCfgSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_NrrccapCfgSetCnf;


typedef struct {
    VOS_UINT32 nrrcCfgNetMode;
} AT_MTA_NrrccapQryReq;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT32          nrrcCfgNetMode;
    VOS_UINT32          para[AT_MTA_NRRCCAP_PARA_MAX_NUM];
} MTA_AT_NrrccapQryCnf;


typedef struct {
    VOS_UINT8 mode;
    VOS_UINT8 reserved;
    VOS_INT16 para;
} AT_MTA_NrpwrctrlSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_NrpwrctrlSetCnf;


typedef struct {
    VOS_UINT32 saSupportFlg;
} MTA_AT_NrNwSaCapInfoPara;


typedef struct {
    VOS_UINT32 para1;
    VOS_UINT32 para2;
    VOS_UINT32 para3;
    VOS_UINT32 para4;
    VOS_UINT32 para5;
    VOS_UINT32 para6;
    VOS_UINT32 para7;
    VOS_UINT32 para8;
    VOS_UINT32 para9;
    VOS_UINT32 para10;
} MTA_AT_NrNwCapInfoCommPara;


typedef union {
    /* nwCapType=0???????????????????? */
    MTA_AT_NrNwSaCapInfoPara   nrSaPara;
    MTA_AT_NrNwCapInfoCommPara commPara;
} MTA_AT_NrNwCapInfoPara;


enum AT_MTA_NwCapInfoType {
    /* ??????????????????SA???? */
    AT_MTA_NR_NW_CAP_INFO_SA = 1,
    AT_MTA_NR_NW_CAP_INFO_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_NrNwCapInfoTypeUint32;


enum AT_MTA_NrNwCapOperType {
    AT_MTA_NR_NW_CAP_RPT_CFG_SET = 0,
    AT_MTA_NR_NW_CAP_OPER_TYPE_BUTT
};
typedef VOS_UINT32 AT_MTA_NrNwCapOperTypeUint32;


typedef struct {
    AT_MTA_NrNwCapInfoTypeUint32 type;
    MTA_AT_NrNwCapInfoPara       capInfo;
} MTA_AT_NrNwCapInfoReportInd;


typedef struct {
    AT_MTA_NrNwCapInfoTypeUint32 type;
    VOS_UINT32                   rptFlg;
} AT_MTA_NrNwCapInfoRptCfgSetReq;

/*
 * ????????????????????????????
 */
typedef VOS_VOID (*TAF_MTA_NrNWCAPOPER_PROC_FUNC_PTR)(AT_MTA_NrNwCapInfoTypeUint32 capType, VOS_UINT32 reserve);


typedef struct {
    AT_MTA_NrNwCapOperTypeUint32 opertype;
    AT_MTA_NrNwCapInfoTypeUint32 capType;
    TAF_MTA_NrNWCAPOPER_PROC_FUNC_PTR operProcFunc;
} MTA_AT_NrNwCapOperProcMapdTbl;

#endif


typedef struct {
    VOS_UINT16 ulMcs[MTA_AT_MAX_CODE_NUMBER];
    VOS_UINT16 dlMcs[MTA_AT_MAX_CODE_NUMBER];
} AT_LTE_McsInfo;


typedef struct {
    MTA_AT_UlModeUint32 ulMode;
    /* NR??????MCS???????????????????????????????? 3GPP TS38.214 5.1.3.1 6.1.4.1 */
    MTA_AT_IndexTableUint8 ulMcsTable;
    MTA_AT_IndexTableUint8 sulMcsTable;
    MTA_AT_IndexTableUint8 dlMcsTable;
    VOS_UINT8              rsv;
    VOS_UINT16             ulMcs[MTA_AT_MAX_CODE_NUMBER];
    VOS_UINT16             sulMcs[MTA_AT_MAX_CODE_NUMBER];
    VOS_UINT16             dlMcs[MTA_AT_MAX_CODE_NUMBER];
} AT_NR_McsInfo;


typedef struct {
    MTA_AT_ResultUint32    result;
    MTA_AT_ResultTypeUint8 resultType;
    VOS_UINT8              rsv;
    VOS_UINT16             nrCellNum;
    AT_LTE_McsInfo         lteMcsInfo;
    AT_NR_McsInfo          nrMcsInfo[MTA_AT_MAX_CC_NUMBER];
} MTA_AT_McsQryCnf;


typedef struct {
    VOS_UINT32 ulFreq;
    VOS_UINT32 ulEarfcn;
    VOS_UINT32 ulBandWidth;
    VOS_UINT32 dlFreq;
    VOS_UINT32 dlEarfcn;
    VOS_UINT32 dlBandWidth;
    VOS_UINT16 band;
    VOS_UINT8  rsv[2];
} AT_LTE_HfreqInfo;


typedef struct {
    MTA_AT_UlModeUint32 ulMode;
    VOS_UINT32          ulFreq;
    VOS_UINT32          ulNarfcn;
    VOS_UINT32          ulBandWidth;
    VOS_UINT32          sulFreq;
    VOS_UINT32          sulNarfcn;
    VOS_UINT32          sulBandWidth;
    VOS_UINT32          dlFreq;
    VOS_UINT32          dlNarfcn;
    VOS_UINT32          dlBandWidth;
    VOS_UINT16          band;
    VOS_UINT16          sulBand;
} AT_NR_HfreqInfo;

typedef struct {
    MTA_AT_ResultUint32    result;
    MTA_AT_ResultTypeUint8 resultType;
    VOS_UINT8              isreportFlg;
    VOS_UINT16             nrCellNum;
    AT_LTE_HfreqInfo       lteHfreqInfo;
    AT_NR_HfreqInfo        nrHfreqInfo[MTA_AT_MAX_CC_NUMBER];
} MTA_AT_HfreqinfoQryCnf;


typedef struct {
    MTA_AT_ResultUint32    result;
    MTA_AT_ResultTypeUint8 resultType;
    VOS_UINT8              rsv;
    VOS_UINT16             nrCellNum;
    AT_LTE_HfreqInfo       lteHfreqInfo;
    AT_NR_HfreqInfo        nrHfreqInfo[MTA_AT_MAX_CC_NUMBER];
} MTA_AT_HfreqinfoInd;


typedef struct {
    VOS_INT16 guTxPwr;
    VOS_INT16 puschPwr;
    VOS_INT16 pucchPwr;
    VOS_INT16 srsPwr;
    VOS_INT16 prachPwr;
    VOS_UINT8 rsv[2];
} AT_TXPOWER_Info;


typedef struct {
    MTA_AT_UlModeUint32 ulMode;
    VOS_UINT32          ulFreq; /* ????????????UL???????? */
    VOS_INT16           ulPuschPwr;
    VOS_INT16           ulPucchPwr;
    VOS_INT16           ulSrsPwr;
    VOS_INT16           ulPrachPwr;
    VOS_UINT32          sulFreq; /* SUL????????????SUL???????? */
    VOS_INT16           sulPuschPwr;
    VOS_INT16           sulPucchPwr;
    VOS_INT16           sulSrsPwr;
    VOS_INT16           sulPrachPwr;
} AT_NTXPOWER_Info;


typedef struct {
    MTA_AT_ResultUint32 result;
    AT_TXPOWER_Info     txpwrInfo;
} MTA_AT_TxpowerQryCnf;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT16          nrCellNum;
    VOS_UINT8           rsv[2];
    AT_NTXPOWER_Info    nrTxPwrInfo[MTA_AT_MAX_CC_NUMBER];
} MTA_AT_NtxpowerQryCnf;


typedef struct {
    AT_MTA_NssaiSetTypeUint32 sNssaiSetType;
    PS_CONFIGURED_Nssai       st5gNssai;
} AT_MTA_5GNssaiSetReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_5GNssaiSetCnf;


typedef struct {
    VOS_UINT32                opPlmn : 1;
    VOS_UINT32                opSpare : 31;
    PS_NR_PlmnId              plmn;
    AT_MTA_NssaiQryTypeUint32 sNssaiQryType;
} AT_MTA_5GNssaiQryReq;


typedef struct {
    PS_NR_PlmnId        plmnId;
    PS_ALLOW_Nssai      allowNssai;
    PS_CONFIGURED_Nssai cfgNssai;
} MTA_AT_5GAllowedAndCfgNssaiWithPlmnId;


typedef struct {
    VOS_UINT32                            plmnNum;
    MTA_AT_5GAllowedAndCfgNssaiWithPlmnId nssai[MTA_AT_MAX_ALLOWED_AND_CFG_NSSAI_PLMN_NUM];
} MTA_AT_5GAllowedAndCfgNssaiQryCnf;


typedef struct {
    MTA_AT_ResultUint32               result;
    AT_MTA_NssaiQryTypeUint32         sNssaiQryType;
    PS_CONFIGURED_Nssai               st5gDefCfgNssai;   /* default config nssai */
    PS_CONFIGURED_Nssai               st5gPreferNssai;   /* prefer nssai */
    PS_REJECTED_NssaiInfo             st5gRejNssai;      /* reject nssai */
    MTA_AT_5GAllowedAndCfgNssaiQryCnf st5gAllowCfgNssai; /* allow????cfg nssai */
} MTA_AT_5GNssaiQryCnf;


typedef struct {
    VOS_UINT32 unsolicitedRptFlg; /* ????????????????land info, 0:????????????1:???????? */
} AT_MTA_SetLadnRptReq;


typedef struct {
    MTA_AT_ResultUint32 result;
} MTA_AT_SetLadnRptCnf;


typedef struct {
    VOS_UINT32 availFlg; /* DNN??????????VOS_TRUE:??????VOS_FALSE:?????? */
    PS_APN     dnn;
} MTA_AT_LadnDnn;


typedef struct {
    MTA_AT_ResultUint32 result;
    VOS_UINT32          rptFlg;
    VOS_UINT32          ladnDnnNum;
    MTA_AT_LadnDnn      ladnList[MTA_AT_MAX_LADN_DNN_NUM];
} MTA_AT_QryLadnInfoCnf;


typedef struct {
    VOS_UINT32     ladnDnnNum;
    MTA_AT_LadnDnn ladnList[MTA_AT_MAX_LADN_DNN_NUM];
} MTA_AT_LadnInfoInd;


typedef struct {
    VOS_UINT8                  highSpeedFlg; /* GU??????0 */
    MTA_AT_HsrcellInfoRatUint8 rat;
    VOS_INT16                  rsrp;
    VOS_UINT32                 cellIdLowBit;  /* ????ID??4???? */
    VOS_UINT32                 cellIdHighBit; /* ????ID??4??????????NR Cell Id???? */
} MTA_AT_HsrcellInfoInd;


typedef struct {
    VOS_UINT8 ssbId; /* SSBID */
    VOS_UINT8 rsv;
    VOS_INT16 rsrp; /* RSRP???????? */
} MTA_AT_NrRsrpMeasRslt;


typedef struct {
    VOS_UINT32            arFcn;     /* arfcn????????????-1 */
    VOS_UINT16            phyCellId; /* ??????????ID */
    VOS_UINT8             rsv1[2];
    VOS_UINT64            cgi; /* Cell Global Identity??NSA??????(????0xFFFFFFFFFFFFFFFF)??SA???????????????????????? */
    VOS_INT16             rsrp;                                       /* PCELL??RSRP??????????????????????????0x7FFF */
    VOS_INT16             sinr;                                       /* PCELL??SINR??????????????????????????0x7FFF */
    VOS_INT32             ta;                                         /* time advance */
    MTA_AT_NrRsrpMeasRslt pscellMeasRslt[MTA_AT_MAX_NR_SSB_BEAM_NUM]; /* ??????SSB ID?????????????????????? */
} MTA_AT_NrPscellDescription;


typedef struct {
    VOS_UINT32            arFcn;     /* arfcn??????????SSB????????????????0xFFFFFFFF */
    VOS_UINT16            phyCellId; /* NR??????????????ID */
    VOS_INT16             rsrp;      /* ???????????????????? */
    VOS_INT16             sinr;      /* ??????????????????????????0x7FFF */
    VOS_UINT8             rsv[2];
    MTA_AT_NrRsrpMeasRslt ncellMeasRslt[MTA_AT_MAX_NR_NCELL_BEAM_RPT_NUM]; /* SSB????????=RSRP+SINR */
} MTA_AT_NrNcellDescription;


typedef struct {
    MTA_AT_ResultUint32        result;        /* ???????????????? */
    VOS_UINT8                  spcellPresent; /* ????????????TRUE??????pscell??ncell???????????? */
    VOS_UINT8                  ncellPresent;  /* ????????????TRUE??????ncell???????????? */
    VOS_UINT8                  ncellNum;
    VOS_UINT8                  rsv;
    MTA_AT_NrPscellDescription spcellSsbInfo;
    MTA_AT_NrNcellDescription  ncellSsbInfo[MTA_AT_MAX_NR_NCELL_RPT_NUM]; /* ?????????????????? */
} MTA_AT_NrSsbIdQryCnf;
/*****************************************************************************
  10 ????????
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
