/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2012-2019. All rights reserved.
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
#include "AtInit.h"

/* ????????????????????????PS??????????????????????????????PS?????????????????????? */
#include "AtDataProc.h"
#include "AcpuReset.h"
#if (FEATURE_LTE == FEATURE_ON)
#include "mdrv_nvim.h"
#include "at_lte_common.h"
#endif
#include "nv_stru_was.h"
#include "nv_stru_gas.h"
#include "acore_nv_stru_msp.h"
#include "product_config.h"
#include "at_mdrv_interface.h"
#include "msp_diag_comm.h"
#include "GuNasLogFilter.h"
#include "ps_log_filter_interface.h"
#include "TafAcoreLogPrivacy.h"
#if (FEATURE_DATA_SERVICE_NEW_PLATFORM == FEATURE_ON)
#include "ads_dev_i.h"
#else
#include "ads_device_interface.h"
#endif


#include "ATCmdProc.h"
#include "securec.h"
#include "taf_type_def.h"
#include "AtMtCommFun.h"


#if (FEATURE_LTEV == FEATURE_ON)
#include "at_ltev_cmd.h"
#endif


/*
 * ??????????????????????.C??????????
 */
#define THIS_FILE_ID PS_FILE_ID_AT_INIT_C
#define AT_UE_CATEGORY_MIN_VALID_VALUE 1
#define AT_UE_CATEGORY_MAX_VALID_VALUE 12
#define AT_UE_CATEGORYEXT_MIN_VALID_VALUE 13
#define AT_UE_CATEGORYEXT_MAX_VALID_VALUE 20
#define AT_UE_CATEGORYEXT2_MIN_VALID_VALUE 21
#define AT_UE_CATEGORYEXT2_MAX_VALID_VALUE 24
#define AT_UE_CATEGORYEXT3_MIN_VALID_VALUE 25
#define AT_UE_CATEGORYEXT3_MAX_VALID_VALUE 28


VOS_VOID AT_ReadPlatformNV(VOS_VOID)
{
    ModemIdUint16           modemID;
    PLATAFORM_RatCapability platFormRat;
    VOS_UINT8               ratIndex;
    AT_ModemSptRat         *atSptRatList = VOS_NULL_PTR;

    memset_s(&platFormRat, sizeof(platFormRat), 0x00, sizeof(PLATAFORM_RatCapability));

    for (modemID = 0; modemID < MODEM_ID_BUTT; modemID++) {
        atSptRatList = AT_GetSptRatFromModemId(modemID);

        /* ????????NV???? */
        if (TAF_ACORE_NV_READ(modemID, NV_ITEM_PLATFORM_RAT_CAP, &platFormRat, sizeof(PLATAFORM_RatCapability)) ==
            NV_OK) {
            atSptRatList->platformSptGsm      = VOS_FALSE;
            atSptRatList->platformSptWcdma    = VOS_FALSE;
            atSptRatList->platformSptLte      = VOS_FALSE;
            atSptRatList->platformSptUtralTdd = VOS_FALSE;

#if (FEATURE_UE_MODE_NR == FEATURE_ON)
            atSptRatList->platformSptNr = VOS_FALSE;
#endif

            platFormRat.ratNum = AT_MIN(platFormRat.ratNum, PLATFORM_MAX_RAT_NUM);
            for (ratIndex = 0; ratIndex < platFormRat.ratNum; ratIndex++) {
#if (FEATURE_LTE == FEATURE_ON)
                /* ????????LTE */
                if (platFormRat.ratList[ratIndex] == PLATFORM_RAT_LTE) {
                    atSptRatList->platformSptLte = VOS_TRUE;
                }
#endif
                /* ????????WCDMA */
                if (platFormRat.ratList[ratIndex] == PLATFORM_RAT_WCDMA) {
                    atSptRatList->platformSptWcdma = VOS_TRUE;
                }

#if (FEATURE_UE_MODE_TDS == FEATURE_ON)
                /* ????????TDS */
                if (platFormRat.ratList[ratIndex] == PLATFORM_RAT_TDS) {
                    atSptRatList->platformSptUtralTdd = VOS_TRUE;
                }
#endif
                /* ????????GSM */
                if (platFormRat.ratList[ratIndex] == PLATFORM_RAT_GSM) {
                    atSptRatList->platformSptGsm = VOS_TRUE;
                }

#if (FEATURE_UE_MODE_NR == FEATURE_ON)
                /* ????????NR */
                if (platFormRat.ratList[ratIndex] == PLATFORM_RAT_NR) {
                    atSptRatList->platformSptNr = VOS_TRUE;
                }
#endif
            }
        }
    }

    return;
}


VOS_VOID AT_ReadClientConfigNV(VOS_VOID)
{
    TAF_AT_NvimAtClientCfg  atClientCfg;
    AT_ClinetConfigDesc    *cfgDesc   = VOS_NULL_PTR;
    AT_ClientConfiguration *clientCfg = VOS_NULL_PTR;
    AT_ClientCfgMapTab     *cfgMapTbl = VOS_NULL_PTR;
    VOS_UINT8               i;

    memset_s(&atClientCfg, sizeof(atClientCfg), 0x00, sizeof(TAF_AT_NvimAtClientCfg));

    /*
     * NV??en_NV_Item_AT_CLIENT_CONFIG??
     * aucAtClientConfig[Index]
     * Index = 0 -- AT_CLIENT_TAB_PCUI_INDEX
     * Index = 1 -- AT_CLIENT_TAB_CTRL_INDEX
     * ......
     * ??index????????
     * aucAtClientConfig[Index]
     * BIT0-BIT1????????client??????????ModemId:00:????modem0 01:????modem1
     * BIT2????????client????????????:0:?????????? 1:????????
     */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_AT_CLIENT_CFG, &atClientCfg, sizeof(TAF_AT_NvimAtClientCfg)) != VOS_OK) {
        return;
    }

    cfgDesc = (AT_ClinetConfigDesc *)&(atClientCfg.atClientConfig[0]);

    for (i = 0; i < AT_GET_CLIENT_CFG_TAB_LEN(); i++) {
        cfgMapTbl = AT_GetClientCfgMapTbl(i);
        clientCfg = AT_GetClientConfig(cfgMapTbl->clientId);

#if (MULTI_MODEM_NUMBER >= 2)
        clientCfg->modemId = cfgDesc[cfgMapTbl->nvIndex].modemId;
#endif
        clientCfg->reportFlg = cfgDesc[cfgMapTbl->nvIndex].reportFlg;
    }

    return;
}


VOS_VOID AT_GetCpmsMtMem(ModemIdUint16 modemId, MN_MSG_MemStoreUint8 *smMemStore)
{
    VOS_UINT32              ret;
    TAF_NVIM_SmsServicePara smsServicePara;
    /*
     * ??????????????????????NV??????????????????
     * VOS_TRUE        ??????????????????????NV????????
     * VOS_FALSE       ????????????????????????NV??????????????????????????SM????
     */
    VOS_BOOL        bSmMemEnable;
    AT_ModemSmsCtx *smsCtx = VOS_NULL_PTR;

    memset_s(&smsServicePara, sizeof(smsServicePara), 0x00, sizeof(TAF_NVIM_SmsServicePara));

    *smMemStore = MN_MSG_MEM_STORE_SIM;

    ret = TAF_ACORE_NV_READ(modemId, NV_ITEM_SMS_SERVICE_PARA, &smsServicePara, MN_MSG_SRV_PARAM_LEN);
    if (ret != NV_OK) {
        AT_ERR_LOG("AT_GetCpmsMtMem: Read Service Parm From Nvim Failed");
        return;
    }

    bSmMemEnable = (smsServicePara.smsServicePara)[AT_MSG_SRV_SM_MEM_ENABLE_OFFSET];

    smsCtx = AT_GetModemSmsCtxAddrFromModemId(modemId);

    if (smsCtx->msgMeStorageStatus == MN_MSG_ME_STORAGE_ENABLE) {
        if (bSmMemEnable == VOS_TRUE) {
            *smMemStore = (smsServicePara.smsServicePara)[AT_MSG_SRV_RCV_SM_MEM_STORE_OFFSET];
        }
    }

    return;
}


VOS_VOID AT_ReadSmsMeStorageInfoNV(VOS_VOID)
{
    VOS_UINT32           ret;
    MN_MSG_MeStorageParm meStorageParm;
    ModemIdUint16        modemId;
    AT_ModemSmsCtx      *smsCtx = VOS_NULL_PTR;

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        smsCtx = AT_GetModemSmsCtxAddrFromModemId(modemId);

        meStorageParm.meStorageStatus = MN_MSG_ME_STORAGE_DISABLE;
        meStorageParm.meStorageNum    = 0;

        /* ????ME?????????????????????? */
        ret = TAF_ACORE_NV_READ(modemId, NV_ITEM_SMS_ME_STORAGE_INFO, &meStorageParm, sizeof(meStorageParm));
        if ((ret == NV_OK) && (meStorageParm.meStorageStatus == MN_MSG_ME_STORAGE_ENABLE)) {
            smsCtx->msgMeStorageStatus = meStorageParm.meStorageStatus;
        }

        /* ?????????????????????????????? */
        AT_GetCpmsMtMem(modemId, &(smsCtx->cpmsInfo.rcvPath.smMemStore));
        smsCtx->cpmsInfo.rcvPath.staRptMemStore = smsCtx->cpmsInfo.rcvPath.smMemStore;
    }

    return;
}


VOS_VOID AT_ReadSmsClass0TailorNV(VOS_VOID)
{
    VOS_UINT32              ret;
    MN_MSG_NvimClass0Tailor class0Tailor;

    class0Tailor.actFlg       = MN_MSG_NVIM_ITEM_INACTIVE;
    class0Tailor.class0Tailor = MN_MSG_CLASS0_DEF;

    /* ????CLASS0?????????????????? */
    ret = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_SMS_CLASS0_TAILOR, &class0Tailor, sizeof(MN_MSG_NvimClass0Tailor));
    if ((ret == NV_OK) && (class0Tailor.actFlg == MN_MSG_NVIM_ITEM_ACTIVE)) {
        g_class0Tailor = class0Tailor.class0Tailor;
    } else {
        g_class0Tailor = MN_MSG_CLASS0_DEF;
    }

    return;
}


VOS_VOID AT_ReadSmsClosePathNV(VOS_VOID)
{
    TAF_NVIM_SmsClosePathCfg closePath;
    AT_ModemSmsCtx          *smsCtx = VOS_NULL_PTR;
    ModemIdUint16            modemId;
    VOS_UINT32               ret;

    memset_s(&closePath, sizeof(closePath), 0x00, sizeof(closePath));

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        smsCtx = AT_GetModemSmsCtxAddrFromModemId(modemId);

        /* ????ME?????????????????????? */
        ret = TAF_ACORE_NV_READ(modemId, NV_ITEM_SMS_CLOSE_PATH, &closePath, sizeof(closePath));
        if ((ret == NV_OK) && (closePath.nvimValid == VOS_TRUE)) {
            smsCtx->localStoreFlg = closePath.smsClosePathFlg;
        }
    }
}


VOS_VOID AT_ReadMtCustomizeInfo(VOS_VOID)
{
    VOS_UINT32             ret;
    MN_MSG_MtCustomizeInfo mtCustomize;
    ModemIdUint16          modemId;
    AT_ModemSmsCtx        *smsCtx = VOS_NULL_PTR;

    memset_s(&mtCustomize, (VOS_SIZE_T)sizeof(mtCustomize), 0x00, (VOS_SIZE_T)sizeof(MN_MSG_MtCustomizeInfo));

    ret = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_SMS_MT_CUSTOMIZE_INFO, &mtCustomize, sizeof(mtCustomize));
    if (ret != NV_OK) {
        AT_INFO_LOG("AT_ReadMtCustomizeInfo: Fail to read ");
        return;
    }

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        smsCtx = AT_GetModemSmsCtxAddrFromModemId(modemId);

        if (mtCustomize.actFlag == MN_MSG_NVIM_ITEM_ACTIVE) {
            smsCtx->smMeFullCustomize.actFlg      = VOS_TRUE;
            smsCtx->smMeFullCustomize.mtCustomize = mtCustomize.enMtCustomize;
        }
    }
    return;
}


VOS_VOID AT_ReadPortBuffCfgNV(VOS_VOID)
{
    AT_CommCtx        *commCtx = VOS_NULL_PTR;
    VOS_UINT32         ret;
    TAF_NV_PortBuffCfg smsBuffCfg;

    commCtx = AT_GetCommCtxAddr();

    memset_s(&smsBuffCfg, sizeof(smsBuffCfg), 0x00, sizeof(smsBuffCfg));

    ret = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_PORT_BUFF_CFG, &smsBuffCfg, sizeof(smsBuffCfg));

    if (ret == NV_OK) {
        if (smsBuffCfg.enableFlg < AT_PORT_BUFF_BUTT) {
            commCtx->portBuffCfg.smsBuffCfg = smsBuffCfg.enableFlg;
        } else {
            commCtx->portBuffCfg.smsBuffCfg = AT_PORT_BUFF_DISABLE;
        }
    } else {
        commCtx->portBuffCfg.smsBuffCfg = AT_PORT_BUFF_DISABLE;
    }

    return;
}


VOS_VOID AT_ReadSmsNV(VOS_VOID)
{
    AT_ReadSmsMeStorageInfoNV();

    AT_ReadSmsClass0TailorNV();

    AT_ReadSmsClosePathNV();

    AT_ReadMtCustomizeInfo();

    return;
}


VOS_VOID AT_ReadRoamCapaNV(VOS_VOID)
{
    NAS_NVIM_RoamCfgInfo roamCfgInfo;
    ModemIdUint16        modemId;
    AT_ModemNetCtx      *netCtx = VOS_NULL_PTR;

    memset_s(&roamCfgInfo, sizeof(roamCfgInfo), 0x00, sizeof(roamCfgInfo));

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        netCtx = AT_GetModemNetCtxAddrFromModemId(modemId);

        if (TAF_ACORE_NV_READ(modemId, NV_ITEM_ROAM_CAPA, &roamCfgInfo, sizeof(NAS_NVIM_RoamCfgInfo)) == NV_OK) {
            if (roamCfgInfo.roamFeatureFlg > 1) {
                netCtx->roamFeature = AT_ROAM_FEATURE_OFF;
            } else {
                netCtx->roamFeature = roamCfgInfo.roamFeatureFlg;
            }
        } else {
            netCtx->roamFeature = AT_ROAM_FEATURE_OFF;
        }
    }
    return;
}


VOS_VOID AT_ReadPrivacyFilterCfgNv(VOS_VOID)
{
    AT_ModemPrivacyFilterCtx *filterCtx = VOS_NULL_PTR;
    NAS_NV_PrivacyFilterCfg   privacyFilterCfg;
    ModemIdUint16             modemId;

    /* ?????? */
    memset_s(&privacyFilterCfg, sizeof(privacyFilterCfg), 0x00, sizeof(NAS_NV_PrivacyFilterCfg));

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        /* ????NV?? */
        if (TAF_ACORE_NV_READ(modemId, NV_ITEM_PRIVACY_LOG_FILTER_CFG, &privacyFilterCfg,
                              sizeof(NAS_NV_PrivacyFilterCfg)) != NV_OK) {
            privacyFilterCfg.filterEnableFlg = VOS_FALSE;
        }

        /* NV?????????? */
        if (privacyFilterCfg.filterEnableFlg == VOS_TRUE) {
            privacyFilterCfg.filterEnableFlg = VOS_TRUE;
        }

        filterCtx = AT_GetModemPrivacyFilterCtxAddrFromModemId(modemId);

        filterCtx->filterEnableFlg = VOS_TRUE;
    }

    return;
}


VOS_VOID AT_ReadSystemAppConfigNV(VOS_VOID)
{
    VOS_UINT8               *systemAppConfig = VOS_NULL_PTR;
    NAS_NVIM_SystemAppConfig sysAppConfig;

    sysAppConfig.sysAppConfigType = SYSTEM_APP_BUTT;

    /* ??????????????NV?????????? */
    systemAppConfig = AT_GetSystemAppConfigAddr();

    /* ???????????????????? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_SYSTEM_APP_CONFIG, &sysAppConfig, sizeof(NAS_NVIM_SystemAppConfig)) !=
        VOS_OK) {
        *systemAppConfig = SYSTEM_APP_MP;
        return;
    }

    if (sysAppConfig.sysAppConfigType > SYSTEM_APP_ANDROID) {
        *systemAppConfig = SYSTEM_APP_MP;
    } else {
        *systemAppConfig = (VOS_UINT8)sysAppConfig.sysAppConfigType;
    }

    return;
}


VOS_VOID AT_ReadAtDislogPwdNV(VOS_VOID)
{
    VOS_UINT8              *systemAppConfig = VOS_NULL_PTR;
    TAF_AT_NvimDislogPwdNew dislogPwdNew;
    errno_t                 memResult;

    /* ??D25??????  ??????????????, ????????NV??????????, ?????????? */
    g_ate5RightFlag = AT_E5_RIGHT_FLAG_NO;
    memset_s(&dislogPwdNew, sizeof(dislogPwdNew), 0x00, sizeof(dislogPwdNew));

    /* ????NV???????????????? */
    systemAppConfig = AT_GetSystemAppConfigAddr();

    /* ????NV??????DISLOG????(OPWORD????) */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_AT_DISLOG_PWD_NEW, &dislogPwdNew, AT_OPWORD_PWD_LEN) == NV_OK) {
        memResult = memcpy_s((VOS_INT8 *)g_atOpwordPwd, AT_OPWORD_PWD_LEN + 1, (VOS_INT8 *)(&dislogPwdNew),
                             AT_OPWORD_PWD_LEN);
        TAF_MEM_CHK_RTN_VAL(memResult, AT_OPWORD_PWD_LEN + 1, AT_OPWORD_PWD_LEN);

        /* ???????????????? */
        g_atOpwordPwd[AT_OPWORD_PWD_LEN] = 0;

        /* ??????????????????AP-Modem???????????????????? */
        if ((VOS_StrLen((VOS_CHAR *)g_atOpwordPwd) == 0) && (*systemAppConfig != SYSTEM_APP_ANDROID)) {
            /* NV???????????????????????????????????? */
            g_ate5RightFlag = AT_E5_RIGHT_FLAG_YES;
        }
    } else {
        AT_WARN_LOG("AT_ReadAtDislogPwdNV:read NV_ITEM_AT_DISLOG_PWD_NEW failed");
    }
    memset_s(&dislogPwdNew, sizeof(dislogPwdNew), 0x00, sizeof(dislogPwdNew));
    return;
}


VOS_VOID AT_ReadAtRightPasswordNV(VOS_VOID)
{
    TAF_AT_NvimRightOpenFlag nvimRightOpenFlg;
    errno_t                  memResult;

    memset_s(&nvimRightOpenFlg, sizeof(nvimRightOpenFlg), 0x00, sizeof(nvimRightOpenFlg));

    /* ??NV??????????????AT?????????? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_AT_RIGHT_PASSWORD, &nvimRightOpenFlg, sizeof(nvimRightOpenFlg)) !=
        NV_OK) {
        /* ????NV????,???????????? */
        memset_s(&g_atRightOpenFlg, sizeof(g_atRightOpenFlg), 0x00, sizeof(g_atRightOpenFlg));
        AT_WARN_LOG("AT_ReadAtRightPasswordNV:read NV_ITEM_AT_RIGHT_PASSWORD failed");
    }

    memResult = memcpy_s(&g_atRightOpenFlg, sizeof(AT_RightOpenFlagInfo), &nvimRightOpenFlg,
                         sizeof(AT_RightOpenFlagInfo));
    TAF_MEM_CHK_RTN_VAL(memResult, sizeof(AT_RightOpenFlagInfo), sizeof(AT_RightOpenFlagInfo));
    memset_s(&nvimRightOpenFlg, sizeof(nvimRightOpenFlg), 0x00, sizeof(nvimRightOpenFlg));
    return;
}


VOS_VOID AT_ReadAtDissdPwdNV(VOS_VOID)
{
    TAF_AT_NvimDissdPwd dissdPwd;
    errno_t             memResult;

    memset_s(&dissdPwd, sizeof(dissdPwd), 0x00, AT_DISSD_PWD_LEN);

    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_AT_DISSD_PWD, &dissdPwd, AT_DISSD_PWD_LEN) == NV_OK) {
        memResult = memcpy_s((VOS_INT8 *)g_ate5DissdPwd, AT_DISSD_PWD_LEN + 1, (VOS_INT8 *)(&dissdPwd),
                             AT_DISSD_PWD_LEN);
        TAF_MEM_CHK_RTN_VAL(memResult, AT_DISSD_PWD_LEN + 1, AT_DISSD_PWD_LEN);
        /* ???????????????? */
        g_ate5DissdPwd[AT_DISSD_PWD_LEN] = 0;
    } else {
        AT_WARN_LOG("AT_ReadAtDissdPwdNV:read NV_ITEM_AT_DISSD_PWD failed");
    }
    memset_s(&dissdPwd, sizeof(dissdPwd), 0x00, AT_DISSD_PWD_LEN);
    return;
}


VOS_VOID AT_ReadNotSupportRetValueNV(VOS_VOID)
{
    errno_t                       memResult;
    VOS_UINT32                    retLen;
    VOS_CHAR                      acRetVal[AT_NOTSUPPORT_STR_LEN + 1];
    TAF_AT_NotSupportCmdErrorText errorText;

    memset_s(&errorText, sizeof(errorText), 0x00, AT_NOTSUPPORT_STR_LEN);

    /*
     * ??NV??????????????????????????????E5??LCARD??DONGLE????
     * ??NV??????"ERROR",??????????????"COMMAND NOT SUPPORT"
     */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_NOT_SUPPORT_RET_VALUE, errorText.errorText, AT_NOTSUPPORT_STR_LEN) ==
        NV_OK) {
        memResult = memcpy_s(acRetVal, sizeof(acRetVal), errorText.errorText, AT_NOTSUPPORT_STR_LEN);
        TAF_MEM_CHK_RTN_VAL(memResult, sizeof(acRetVal), AT_NOTSUPPORT_STR_LEN);

        /* ???????????????? */
        acRetVal[AT_NOTSUPPORT_STR_LEN] = 0;
        retLen                          = VOS_StrLen(acRetVal);
        if (retLen > 0) {
            /* AT_NOTSUPPORT_STR_LEN + 4??gaucAtCmdNotSupportStr???????????????? */
            memResult = strcpy_s((VOS_CHAR *)g_atCmdNotSupportStr, AT_NOTSUPPORT_STR_LEN + 4, acRetVal);
            TAF_STRCPY_CHK_RTN_VAL_CONTINUE(memResult, AT_NOTSUPPORT_STR_LEN + 4, AT_NOTSUPPORT_STR_LEN + 4);
        }
    } else {
        AT_WARN_LOG("AT_ReadNotSupportRetValueNV:read NV_ITEM_NOT_SUPPORT_RET_VALUE failed");
    }

    return;
}


VOS_VOID AT_ReadE5NV(VOS_VOID)
{
    AT_ReadAtDislogPwdNV();

    AT_ReadAtRightPasswordNV();

    AT_ReadAtDissdPwdNV();

    AT_ReadNotSupportRetValueNV();

    return;
}


VOS_UINT32 AT_IsAbortCmdCharValid(VOS_UINT8 *abortCmdChar, VOS_UINT32 len)
{
    VOS_UINT32 i;

    /*
     * ??????AT??????????????????, ????????????????????????????, ??????????????????????
     * (<0x20??ASCII????,????, S3, S5)??.
     * ????NV????????ABORT??????????????????????????????????????????????, ????????????,
     * ????NV????????ABORT??????????????????????????????????????, ??????????
     */

    /* ???????????????????????????????????? */
    if (abortCmdChar == VOS_NULL_PTR) {
        return VOS_FALSE;
    }

    /* ????????????????????????????0?????? */
    if (len == 0) {
        return VOS_FALSE;
    }

    /* ??????????????????????????????????(<0x20??ASCII????,????, S3, S5)???????? */
    for (i = 0; i < len; i++) {
        if ((abortCmdChar[i] == g_atS3) || (abortCmdChar[i] == g_atS5) || (abortCmdChar[i] <= 0x20)) {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_VOID AT_ReadAbortCmdParaNV(VOS_VOID)
{
    AT_ABORT_CmdPara *abortCmdPara   = VOS_NULL_PTR;
    VOS_UINT8         dfltAbortCmd[] = "AT";
    /* ??????????????????????, ?????????????????????????? */
    VOS_UINT8            dfltAbortRsp[] = "OK";
    AT_NVIM_AbortCmdPara nvAbortCmdPara;
    VOS_UINT32           isAbortCmdValid;
    VOS_UINT32           isAbortRspValid;
    VOS_UINT32           rlst;
    VOS_UINT8            anyCharAbortCmd[] = "ANY";
    VOS_UINT32           len;
    errno_t              stringRet;

    /* ?????? ????TQE???? */
    memset_s(&nvAbortCmdPara, sizeof(nvAbortCmdPara), 0x00, sizeof(nvAbortCmdPara));

    /* ?????????????? */
    abortCmdPara = AT_GetAbortCmdPara();
    memset_s(abortCmdPara, sizeof(AT_ABORT_CmdPara), 0x00, sizeof(AT_ABORT_CmdPara));

    /* ????NV???????????????????????????? */
    rlst = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_AT_ABORT_CMD_PARA, &nvAbortCmdPara, sizeof(AT_NVIM_AbortCmdPara));

    /* NV???????????????????? */
    if (rlst != NV_OK) {
        /* ????????????????????TRUE */
        abortCmdPara->abortEnableFlg = VOS_TRUE;

        /* ?????????????? */
        stringRet = strncpy_s((VOS_CHAR *)(abortCmdPara->abortAtCmdStr), sizeof(abortCmdPara->abortAtCmdStr),
                              (VOS_CHAR *)dfltAbortCmd, AT_MAX_ABORT_CMD_STR_LEN);
        TAF_STRCPY_CHK_RTN_VAL_CONTINUE(stringRet, sizeof(abortCmdPara->abortAtCmdStr), AT_MAX_ABORT_CMD_STR_LEN);
        abortCmdPara->abortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN] = '\0';

        /* ?????????????? */
        stringRet = strncpy_s((VOS_CHAR *)(abortCmdPara->abortAtRspStr), sizeof(abortCmdPara->abortAtRspStr),
                              (VOS_CHAR *)dfltAbortRsp, AT_MAX_ABORT_RSP_STR_LEN);
        TAF_STRCPY_CHK_RTN_VAL_CONTINUE(stringRet, sizeof(abortCmdPara->abortAtRspStr), AT_MAX_ABORT_RSP_STR_LEN);
        abortCmdPara->abortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN] = '\0';

        AT_WARN_LOG("AT_ReadAbortCmdParaNV:read NV_ITEM_AT_ABORT_CMD_PARA failed");

        return;
    }

    /* ??????????????????, ?????????????????????? */
    abortCmdPara->abortEnableFlg = nvAbortCmdPara.abortEnableFlg;
    if (abortCmdPara->abortEnableFlg != VOS_TRUE) {
        return;
    }

    /*
     * ??NV??????????????????????????????????????????AT_MAX_ABORT_CMD_STR_LEN??
     * ????????????AT_MAX_ABORT_CMD_STR_LEN+1????????????????????
     * ??????????????AT_MAX_ABORT_CMD_STR_LEN
     */
    stringRet = strncpy_s((VOS_CHAR *)(abortCmdPara->abortAtCmdStr), sizeof(abortCmdPara->abortAtCmdStr),
                          (VOS_CHAR *)(nvAbortCmdPara.abortAtCmdStr), AT_MAX_ABORT_CMD_STR_LEN);
    TAF_STRCPY_CHK_RTN_VAL_CONTINUE(stringRet, sizeof(abortCmdPara->abortAtCmdStr), AT_MAX_ABORT_CMD_STR_LEN);

    abortCmdPara->abortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN] = '\0';

    /*
     * ??NV??????????????????????????????????????????AT_MAX_ABORT_CMD_STR_LEN??
     * ????????????AT_MAX_ABORT_RSP_STR_LEN+1????????????????????
     * ??????????????AT_MAX_ABORT_RSP_STR_LEN
     */
    stringRet = strncpy_s((VOS_CHAR *)(abortCmdPara->abortAtRspStr), sizeof(abortCmdPara->abortAtRspStr),
                          (VOS_CHAR *)(nvAbortCmdPara.abortAtRspStr), AT_MAX_ABORT_RSP_STR_LEN);
    TAF_STRCPY_CHK_RTN_VAL_CONTINUE(stringRet, sizeof(abortCmdPara->abortAtRspStr), AT_MAX_ABORT_RSP_STR_LEN);

    abortCmdPara->abortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN] = '\0';

    /* ??????????????NV???????????????????? */
    isAbortCmdValid = AT_IsAbortCmdCharValid(abortCmdPara->abortAtCmdStr,
                                             VOS_StrLen((VOS_CHAR *)(abortCmdPara->abortAtCmdStr)));

    isAbortRspValid = AT_IsAbortCmdCharValid(abortCmdPara->abortAtRspStr,
                                             VOS_StrLen((VOS_CHAR *)(abortCmdPara->abortAtRspStr)));

    /* ????NV????????????????????(????, S3, S5, ????x020??????), ???????????? */
    if (isAbortCmdValid != VOS_TRUE) {
        stringRet = strncpy_s((VOS_CHAR *)(abortCmdPara->abortAtCmdStr), sizeof(abortCmdPara->abortAtCmdStr),
                              (VOS_CHAR *)dfltAbortCmd, AT_MAX_ABORT_CMD_STR_LEN);
        TAF_STRCPY_CHK_RTN_VAL_CONTINUE(stringRet, sizeof(abortCmdPara->abortAtCmdStr), AT_MAX_ABORT_CMD_STR_LEN);
        abortCmdPara->abortAtCmdStr[AT_MAX_ABORT_CMD_STR_LEN] = '\0';
    }

    if (isAbortRspValid != VOS_TRUE) {
        stringRet = strncpy_s((VOS_CHAR *)(abortCmdPara->abortAtRspStr), sizeof(abortCmdPara->abortAtRspStr),
                              (VOS_CHAR *)dfltAbortRsp, AT_MAX_ABORT_RSP_STR_LEN);
        TAF_STRCPY_CHK_RTN_VAL_CONTINUE(stringRet, sizeof(abortCmdPara->abortAtRspStr), AT_MAX_ABORT_RSP_STR_LEN);
        abortCmdPara->abortAtRspStr[AT_MAX_ABORT_RSP_STR_LEN] = '\0';
    }

    len = VOS_StrLen((VOS_CHAR *)abortCmdPara->abortAtCmdStr);

    if (VOS_StrLen((VOS_CHAR *)anyCharAbortCmd) != len) {
        return;
    }

    if ((VOS_StrNiCmp((VOS_CHAR *)anyCharAbortCmd, (VOS_CHAR *)abortCmdPara->abortAtCmdStr, len) == 0)) {
        /* PS_MEM_SET??????????????????0???????????????????????????? */
        abortCmdPara->anyAbortFlg = VOS_TRUE;
    }

    return;
}


VOS_VOID AT_ReadSysNV(VOS_VOID)
{
    AT_ReadRoamCapaNV();

    AT_ReadSystemAppConfigNV();

    AT_ReadE5NV();

    AT_ReadAbortCmdParaNV();

    return;
}


VOS_VOID AT_ReadCellSignReportCfgNV(VOS_VOID)
{
    AT_ModemNetCtx            *netCtx = VOS_NULL_PTR;
    NAS_NVIM_CellSignReportCfg cellSignReportCfg;
    ModemIdUint16              modemId;

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        netCtx = AT_GetModemNetCtxAddrFromModemId(modemId);

        memset_s(&cellSignReportCfg, sizeof(cellSignReportCfg), 0x00, sizeof(cellSignReportCfg));

        if (TAF_ACORE_NV_READ(modemId, NV_ITEM_CELL_SIGN_REPORT_CFG, &cellSignReportCfg,
                              sizeof(NAS_NVIM_CellSignReportCfg)) != NV_OK) {
            AT_WARN_LOG("AT_ReadCellSignReportCfgNV:read NV_ITEM_CELL_SIGN_REPORT_CFG failed");
            return;
        }

        netCtx->cerssiReportType = cellSignReportCfg.signThreshold;

        if (cellSignReportCfg.signThreshold >= AT_CERSSI_REPORT_TYPE_BUTT) {
            netCtx->cerssiReportType = AT_CERSSI_REPORT_TYPE_NOT_REPORT;
        }

        netCtx->cerssiMinTimerInterval = cellSignReportCfg.minRptTimerInterval;

        if (cellSignReportCfg.minRptTimerInterval > AT_CERSSI_MAX_TIMER_INTERVAL) {
            netCtx->cerssiMinTimerInterval = 0;
        }
    }

    return;
}


VOS_UINT32 AT_ValidateWasCategory(AT_NvUeCapability *ueCapability)
{
    if (ueCapability->hSDSCHSupport != VOS_TRUE) {
        return VOS_ERR;
    }

    if ((ueCapability->hSDSCHPhyCategory < AT_UE_CATEGORY_MIN_VALID_VALUE) ||
        (ueCapability->hSDSCHPhyCategory > AT_UE_CATEGORY_MAX_VALID_VALUE)) {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_ValidateWasCategoryExt(AT_NvUeCapability *ueCapability)
{
    if ((ueCapability->hSDSCHSupport != VOS_TRUE) || (ueCapability->macEhsSupport != VOS_TRUE)) {
        return VOS_ERR;
    }

    if ((ueCapability->hSDSCHPhyCategoryExt < AT_UE_CATEGORYEXT_MIN_VALID_VALUE) ||
        (ueCapability->hSDSCHPhyCategoryExt > AT_UE_CATEGORYEXT_MAX_VALID_VALUE)) {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_ValidateWasCategoryExt2(AT_NvUeCapability *ueCapability)
{
    if ((ueCapability->hSDSCHSupport != VOS_TRUE) || (ueCapability->macEhsSupport != VOS_TRUE) ||
        (ueCapability->multiCellSupport != VOS_TRUE)) {
        return VOS_ERR;
    }

    if ((ueCapability->hSDSCHPhyCategoryExt2 < AT_UE_CATEGORYEXT2_MIN_VALID_VALUE) ||
        (ueCapability->hSDSCHPhyCategoryExt2 > AT_UE_CATEGORYEXT2_MAX_VALID_VALUE)) {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_ValidateWasCategoryExt3(AT_NvUeCapability *ueCapability)
{
    if ((ueCapability->hSDSCHSupport != VOS_TRUE) || (ueCapability->macEhsSupport != VOS_TRUE) ||
        (ueCapability->multiCellSupport != VOS_TRUE) || (ueCapability->dcMimoSupport != VOS_TRUE)) {
        return VOS_ERR;
    }

    if ((ueCapability->hSDSCHPhyCategoryExt3 < AT_UE_CATEGORYEXT3_MIN_VALID_VALUE) ||
        (ueCapability->hSDSCHPhyCategoryExt3 > AT_UE_CATEGORYEXT3_MAX_VALID_VALUE)) {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT8 AT_GetWasDefaultCategory(AT_NvUeCapability *ueCapability)
{
    AT_RateWcdmaCategoryUint8 rateCategory;

    switch (ueCapability->asRelIndicator) {
        case PS_PTL_VER_R5:
        case PS_PTL_VER_R6:
            rateCategory = AT_RATE_WCDMA_CATEGORY_10;
            break;

        case PS_PTL_VER_R7:
            rateCategory = AT_RATE_WCDMA_CATEGORY_18;
            break;

        case PS_PTL_VER_R8:
            rateCategory = AT_RATE_WCDMA_CATEGORY_28;
            break;

        default:
            rateCategory = AT_RATE_WCDMA_CATEGORY_10;
            break;
    }

    return rateCategory;
}


VOS_UINT8 AT_CalcWasCategory(AT_NvUeCapability *ueCapability)
{
    AT_RateWcdmaCategoryUint8 rateCategory;

    if (AT_ValidateWasCategoryExt3(ueCapability) == VOS_OK) {
        return ueCapability->hSDSCHPhyCategoryExt3;
    }

    if (AT_ValidateWasCategoryExt2(ueCapability) == VOS_OK) {
        return ueCapability->hSDSCHPhyCategoryExt2;
    }

    if (AT_ValidateWasCategoryExt(ueCapability) == VOS_OK) {
        return ueCapability->hSDSCHPhyCategoryExt;
    }

    if (AT_ValidateWasCategory(ueCapability) == VOS_OK) {
        return ueCapability->hSDSCHPhyCategory;
    }

    rateCategory = AT_GetWasDefaultCategory(ueCapability);

    return rateCategory;
}


VOS_VOID AT_ReadWasCapabilityNV(VOS_VOID)
{
    AT_NvUeCapability nvUeCapability;
    VOS_UINT32        result;

    memset_s(&nvUeCapability, sizeof(nvUeCapability), 0x00, sizeof(nvUeCapability));

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_WAS_RADIO_ACCESS_CAPA_NEW, &nvUeCapability,
                               sizeof(AT_NvUeCapability));
    if (result != VOS_OK) {
        /* NV????????, ??????????????R99 */
        g_atDlRateCategory.wasRelIndicator = PS_PTL_VER_R99;
        g_atDlRateCategory.wasCategory     = AT_RATE_WCDMA_R99;
    } else {
        g_atDlRateCategory.wasRelIndicator = (VOS_INT8)nvUeCapability.asRelIndicator;
        g_atDlRateCategory.wasCategory     = AT_CalcWasCategory(&nvUeCapability);
    }
}


VOS_VOID AT_CalcGasCategory(NVIM_GAS_HighMultiSlotClass *highMultislotclass, VOS_UINT16 gprsMultiSlotClass,
                            VOS_UINT16 egprsMultiSlotClass, VOS_UINT16 egprsFlag)
{
    /* ??????VOS_FALSE */
    g_atDlRateCategory.gasMultislotClass33Flg = VOS_FALSE;

    if ((highMultislotclass->highMultislotClassFlg == VOS_TRUE) &&
        (highMultislotclass->highMultislotClass == AT_GAS_HIGH_MULTISLOT_CLASS_0)) {
        if ((egprsFlag == VOS_FALSE) && (gprsMultiSlotClass == AT_GAS_GRR_MULTISLOT_CLASS_MAX)) {
            g_atDlRateCategory.gasMultislotClass33Flg = VOS_TRUE;
        }

        if ((egprsFlag == VOS_TRUE) && (egprsMultiSlotClass == AT_GAS_GRR_MULTISLOT_CLASS_MAX)) {
            g_atDlRateCategory.gasMultislotClass33Flg = VOS_TRUE;
        }
    }

    return;
}


VOS_VOID AT_ReadGasCapabilityNV(VOS_VOID)
{
    VOS_UINT32                  result;
    NVIM_GAS_HighMultiSlotClass highMultislotclass;
    VOS_UINT16                  gprsMultiSlotClass;
    VOS_UINT16                  egprsMultiSlotClass;
    VOS_UINT16                  egprsFlag;

    highMultislotclass.highMultislotClassFlg = VOS_FALSE;
    highMultislotclass.highMultislotClass    = AT_GAS_HIGH_MULTISLOT_CLASS_0;

    gprsMultiSlotClass  = 0;
    egprsMultiSlotClass = 0;
    egprsFlag           = VOS_FALSE;

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_EGPRS_FLAG, &egprsFlag, sizeof(VOS_UINT16));
    if (result != NV_OK || egprsFlag != VOS_FALSE) {
        egprsFlag = VOS_TRUE;
    }

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_GPRS_MULTI_SLOT_CLASS, &gprsMultiSlotClass, sizeof(VOS_UINT16));

    /* ??????????????????????????????12 */
    if (result != NV_OK) {
        gprsMultiSlotClass = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    }

    /* ????????????????????1-12 */
    if ((gprsMultiSlotClass == 0) || (gprsMultiSlotClass > AT_GAS_GRR_MULTISLOT_CLASS_MAX)) {
        gprsMultiSlotClass = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    }

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_EGPRS_MULTI_SLOT_CLASS, &egprsMultiSlotClass, sizeof(VOS_UINT16));
    if (result != NV_OK) {
        egprsMultiSlotClass = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    }

    /* ????????????????????1-12 */
    if ((egprsMultiSlotClass == 0) || (egprsMultiSlotClass > AT_GAS_GRR_MULTISLOT_CLASS_MAX)) {
        egprsMultiSlotClass = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    }

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_GAS_HIGH_MULTI_SLOT_CLASS, &highMultislotclass,
                               sizeof(NVIM_GAS_HighMultiSlotClass));

    /* ??????????????High Multislot Class ????  */
    if (result != NV_OK) {
        return;
    }

    if ((highMultislotclass.highMultislotClassFlg == VOS_TRUE) &&
        (highMultislotclass.highMultislotClass != AT_GAS_HIGH_MULTISLOT_CLASS_0)) {
        highMultislotclass.highMultislotClass = AT_GAS_HIGH_MULTISLOT_CLASS_0;
    }

    AT_CalcGasCategory(&highMultislotclass, gprsMultiSlotClass, egprsMultiSlotClass, egprsFlag);

    return;
}


VOS_VOID AT_ReadPppDialErrCodeNV(VOS_VOID)
{
    NAS_NV_PppDialErrCode pppErrRpt;
    VOS_UINT32            result;

    pppErrRpt.status     = VOS_FALSE;
    pppErrRpt.errCodeRpt = PPP_DIAL_ERR_CODE_BUTT;

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_PPP_DIAL_ERR_CODE, &pppErrRpt, sizeof(NAS_NV_PppDialErrCode));

    if ((result == NV_OK) && (pppErrRpt.status == VOS_TRUE) && (pppErrRpt.errCodeRpt == PPP_DIAL_ERR_CODE_ENABLE)) {
        g_pppDialErrCodeRpt = PPP_DIAL_ERR_CODE_ENABLE;
    } else {
        g_pppDialErrCodeRpt = PPP_DIAL_ERR_CODE_DISABLE;
    }

    return;
}


VOS_VOID AT_ReadReportRegActFlgNV(VOS_VOID)
{
    VOS_UINT32                 result;
    TAF_AT_NvimReportRegActFlg reportRegFlg;

    memset_s(&reportRegFlg, sizeof(reportRegFlg), 0x00, sizeof(TAF_AT_NvimReportRegActFlg));

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_REPORT_REG_ACT_FLG, &(reportRegFlg.reportRegActFlg),
                               sizeof(reportRegFlg.reportRegActFlg));

    if ((result == NV_OK) && (reportRegFlg.reportRegActFlg == VOS_TRUE)) {
        g_reportCregActParaFlg = reportRegFlg.reportRegActFlg;
    } else {
        g_reportCregActParaFlg = VOS_FALSE;
    }

    return;
}


VOS_VOID AT_ReadCregAndCgregCiFourByteRptNV(VOS_VOID)
{
    NAS_NV_CregCgregCiFourByteRpt ciFourByteRpt;
    VOS_UINT32                    result;

    ciFourByteRpt.status     = VOS_FALSE;
    ciFourByteRpt.ciBytesRpt = 0;

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_CREG_CGREG_CI_FOUR_BYTE_RPT, &ciFourByteRpt,
                               sizeof(NAS_NV_CregCgregCiFourByteRpt));

    if ((result == NV_OK) && (ciFourByteRpt.status == VOS_TRUE) &&
        (ciFourByteRpt.ciBytesRpt == CREG_CGREG_CI_RPT_FOUR_BYTE)) {
        g_ciRptByte = CREG_CGREG_CI_RPT_FOUR_BYTE;
    } else {
        g_ciRptByte = CREG_CGREG_CI_RPT_TWO_BYTE;
    }

    return;
}


VOS_VOID AT_ReadIpv6CapabilityNV(VOS_VOID)
{
    AT_NV_Ipv6Capability nvIpv6Capability;
    VOS_UINT32           rslt;
    AT_CommPsCtx        *commPsCtx = VOS_NULL_PTR;
    VOS_UINT32           ipv6CapabilityValid;

    memset_s(&nvIpv6Capability, sizeof(nvIpv6Capability), 0x00, sizeof(AT_NV_Ipv6Capability));

    commPsCtx = AT_GetCommPsCtxAddr();

    rslt = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_IPV6_CAPABILITY, &nvIpv6Capability, sizeof(AT_NV_Ipv6Capability));

    ipv6CapabilityValid = AT_PS_IsIpv6CapabilityValid(nvIpv6Capability.ipv6Capablity);

    if ((rslt == NV_OK) && (nvIpv6Capability.status == VOS_TRUE) && (ipv6CapabilityValid == VOS_TRUE)) {
        commPsCtx->ipv6Capability = nvIpv6Capability.ipv6Capablity;
    } else {
        commPsCtx->ipv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
    }

    return;
}


VOS_VOID AT_ReadIpv6AddrTestModeCfgNV(VOS_VOID)
{
    TAF_NVIM_Ipv6AddrTestModeCfg ipv6AddrTestModeCfg;
    AT_CommPsCtx                *commPsCtx = VOS_NULL_PTR;
    VOS_UINT32                   rslt;

    memset_s(&ipv6AddrTestModeCfg, sizeof(ipv6AddrTestModeCfg), 0x00, sizeof(TAF_NVIM_Ipv6AddrTestModeCfg));

    commPsCtx = AT_GetCommPsCtxAddr();

    rslt = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_IPV6_ADDRESS_TEST_MODE_CFG, &ipv6AddrTestModeCfg,
                             sizeof(ipv6AddrTestModeCfg));

    if (rslt == NV_OK) {
        commPsCtx->ipv6AddrTestModeCfg = ipv6AddrTestModeCfg.ipv6AddrTestModeCfg;
    } else {
        commPsCtx->ipv6AddrTestModeCfg = 0;
    }

    return;
}


VOS_VOID AT_ReadSharePdpInfoNV(VOS_VOID)
{
    TAF_NVIM_SharePdpInfo sharePdpInfo;
    AT_CommPsCtx         *commPsCtx = VOS_NULL_PTR;
    VOS_UINT32            rslt;

    memset_s(&sharePdpInfo, sizeof(sharePdpInfo), 0x00, sizeof(TAF_NVIM_SharePdpInfo));

    commPsCtx = AT_GetCommPsCtxAddr();

    rslt = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_SHARE_PDP_INFO, &sharePdpInfo, sizeof(sharePdpInfo));

    if ((rslt == NV_OK) && (sharePdpInfo.enableFlag == VOS_TRUE)) {
        commPsCtx->sharePdpFlag = sharePdpInfo.enableFlag;
    } else {
        commPsCtx->sharePdpFlag = VOS_FALSE;
    }

    return;
}


VOS_VOID AT_ReadDialConnectDisplayRateNV(VOS_VOID)
{
    VOS_UINT32                     result;
    AT_NVIM_DialConnectDisplayRate dialConnectDisplayRate;

    memset_s(&dialConnectDisplayRate, sizeof(dialConnectDisplayRate), 0x00, sizeof(dialConnectDisplayRate));

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_DIAL_CONNECT_DISPLAY_RATE, &dialConnectDisplayRate,
                               sizeof(AT_NVIM_DialConnectDisplayRate));
    if (result != NV_OK) {
        memset_s(&g_dialConnectDisplayRate, sizeof(g_dialConnectDisplayRate), 0x00, sizeof(g_dialConnectDisplayRate));
        return;
    }

    g_dialConnectDisplayRate.dpaConnectRate   = dialConnectDisplayRate.dpaConnectRate;
    g_dialConnectDisplayRate.edgeConnectRate  = dialConnectDisplayRate.edgeConnectRate;
    g_dialConnectDisplayRate.gprsConnectRate  = dialConnectDisplayRate.gprsConnectRate;
    g_dialConnectDisplayRate.gsmConnectRate   = dialConnectDisplayRate.gsmConnectRate;
    g_dialConnectDisplayRate.reserve1         = dialConnectDisplayRate.reserve1;
    g_dialConnectDisplayRate.reserve2         = dialConnectDisplayRate.reserve2;
    g_dialConnectDisplayRate.reserve3         = dialConnectDisplayRate.reserve3;
    g_dialConnectDisplayRate.wcdmaConnectRate = dialConnectDisplayRate.wcdmaConnectRate;

    return;
}

LOCAL VOS_VOID AT_SetApnCustFormatCfg(TAF_NVIM_ApnCustomFormatCfg *apnNVCfg, AT_PS_ApnCustomFormatCfg *apnAtCfg)
{
    VOS_UINT32 charNum;
    VOS_UINT32 charNvNum;
    VOS_UINT32 i;

    apnAtCfg->protocolStringCheckFlag = (apnNVCfg->ucProtocolStringCheckFlag == VOS_TRUE) ? VOS_TRUE : VOS_FALSE;

    charNum   = 0;
    charNvNum = TAF_MIN(apnNVCfg->ucCustomCharNum, AT_PS_APN_CUSTOM_CHAR_MAX_NUM);
    for (i = 0; i < charNvNum; i++) {
        /* ????????,???????????????????????????? */
        if ((apnNVCfg->aucCustomChar[i] > AT_PS_ASCII_UINT_SEPARATOR) &&
            (apnNVCfg->aucCustomChar[i] != AT_PS_ASCII_DELETE) && (apnNVCfg->aucCustomChar[i] != AT_PS_ASCII_SLASH) &&
            (apnNVCfg->aucCustomChar[i] != AT_PS_ASCII_BACKSLASH)) {
            apnAtCfg->customChar[charNum] = apnNVCfg->aucCustomChar[i];
            charNum++;
        }
    }
    apnAtCfg->customCharNum = (VOS_UINT8)charNum;
}

VOS_VOID AT_ReadApnCustomFormatCfgNV(VOS_VOID)
{
    TAF_NVIM_ApnCustomFormatCfg apnCustomFormatCfg;
    AT_CommPsCtx               *commPsCtx = VOS_NULL_PTR;
    VOS_UINT32                  rslt;
    VOS_UINT32                  i;

    memset_s(&apnCustomFormatCfg, sizeof(apnCustomFormatCfg), 0x00, sizeof(TAF_NVIM_ApnCustomFormatCfg));

    commPsCtx = AT_GetCommPsCtxAddr();

    /* ??Modem???????? */
    for (i = 0; i < MODEM_ID_BUTT; i++) {
        rslt = TAF_ACORE_NV_READ(i, NV_ITEM_APN_CUSTOM_FORMAT_CFG, &apnCustomFormatCfg, sizeof(apnCustomFormatCfg));

        if (rslt != NV_OK) {
            commPsCtx->apnCustomFormatCfg[i].customCharNum           = 0;
            commPsCtx->apnCustomFormatCfg[i].protocolStringCheckFlag = VOS_FALSE;
        } else {
            AT_SetApnCustFormatCfg(&apnCustomFormatCfg, &(commPsCtx->apnCustomFormatCfg[i]));
        }
    }

    return;
}


VOS_VOID AT_ReadPsNV(VOS_VOID)
{
    /* ??????????????????NV */
    AT_ReadPppDialErrCodeNV();

    /* ????????????CREG/CGREG??ACT????????NV */
    AT_ReadReportRegActFlgNV();

    /* ????CREG/CGREG??CI??????????4??????????????NV(Vodafone????) */
    AT_ReadCregAndCgregCiFourByteRptNV();

    /* ????IPV6??????NV, ????IPV6??????????????IPV4V6_OVER_ONE_PDP */
    AT_ReadIpv6CapabilityNV();

    AT_ReadIpv6AddrTestModeCfgNV();

    /* ????????????????????????????NV */
    AT_ReadDialConnectDisplayRateNV();

    /* ????WCDMA????????NV, ????PS?????????????? */
    AT_ReadWasCapabilityNV();

    /* ????GAS????????CLASS33 NV???? */
    AT_ReadGasCapabilityNV();

    AT_ReadCellSignReportCfgNV();

    AT_ReadSharePdpInfoNV();

    AT_ReadApnCustomFormatCfgNV();

    return;
}


VOS_VOID AT_ReadCsNV(VOS_VOID)
{
    TAF_UssdNvimTransMode ussdTranMode;
    TAF_CCA_TelePara      timeInfo;
    ModemIdUint16         modemId;
    AT_ModemCcCtx        *ccCtx = VOS_NULL_PTR;
    AT_ModemSsCtx        *ssCtx = VOS_NULL_PTR;

    NAS_NVIM_CustomCallCfg callCfgInfo;

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        ccCtx = AT_GetModemCcCtxAddrFromModemId(modemId);
        ssCtx = AT_GetModemSsCtxAddrFromModemId(modemId);

        memset_s(&timeInfo, sizeof(timeInfo), 0x00, sizeof(timeInfo));

        /* ???????????????? */
        if (TAF_ACORE_NV_READ(modemId, NV_ITEM_CCA_TELE_PARA, &timeInfo, sizeof(TAF_CCA_TelePara)) == NV_OK) {
            ccCtx->s0TimeInfo.s0TimerLen = timeInfo.s0TimerLen;
        }

        memset_s(&ussdTranMode, sizeof(ussdTranMode), 0x00, sizeof(ussdTranMode));

        /* ????USSD???????????? */
        if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_CUST_USSD_MODE, &ussdTranMode, sizeof(TAF_UssdNvimTransMode)) ==
            NV_OK) {
            if (ussdTranMode.status == VOS_TRUE) {
                ssCtx->ussdTransMode = ussdTranMode.ussdTransMode;
            }
        }

        /* ???????????????? */
        memset_s(&callCfgInfo, sizeof(callCfgInfo), 0x00, sizeof(callCfgInfo));

        if (TAF_ACORE_NV_READ(modemId, NV_ITEM_CUSTOM_CALL_CFG, &callCfgInfo, sizeof(NAS_NVIM_CustomCallCfg)) ==
            NV_OK) {
            /* ????NV????????????????????????CVHU_MODE_0 */
            if (callCfgInfo.cvhuMode >= CVHU_MODE_BUTT) {
                ccCtx->cvhuMode = CVHU_MODE_0;
            } else {
                ccCtx->cvhuMode = callCfgInfo.cvhuMode;
            }
        }
    }

    AT_ReadSsNV();

    return;
}

#if (FEATURE_LTE == FEATURE_ON)

VOS_VOID AT_ReadLTENV(VOS_VOID)
{
    VOS_UINT32 result;

    memset_s(&g_rsrpCfg, sizeof(g_rsrpCfg), 0x00, sizeof(g_rsrpCfg));
    memset_s(&g_rscpCfg, sizeof(g_rscpCfg), 0x00, sizeof(g_rscpCfg));
    memset_s(&g_ecioCfg, sizeof(g_ecioCfg), 0x00, sizeof(g_ecioCfg));

    /* ??NV???????????? */
    result = TAF_ACORE_NV_READ(MODEM_ID_0, EN_NV_ID_RSRP_CFG, &g_rsrpCfg, sizeof(NVIM_RsrpCfg));

    if (result != NV_OK) {
        PS_PRINTF_WARNING("read RSRP NV fail!\n");
        return;
    }

    /* ??NV???????????? */
    result = TAF_ACORE_NV_READ(MODEM_ID_0, EN_NV_ID_RSCP_CFG, &g_rscpCfg, sizeof(NVIM_RscpCfg));

    if (result != NV_OK) {
        PS_PRINTF_WARNING("read RSCP NV fail!\n");
        return;
    }

    /* ??NV???????????? */
    result = TAF_ACORE_NV_READ(MODEM_ID_0, EN_NV_ID_ECIO_CFG, &g_ecioCfg, sizeof(NVIM_EcioCfg));

    if (result != NV_OK) {
        PS_PRINTF_WARNING("read ECIO NV fail!\n");
        return;
    }

    return;
}

#endif


VOS_VOID AT_ReadAgpsNv(VOS_VOID)
{
    AT_ModemAgpsCtx      *agpsCtx = VOS_NULL_PTR;
    TAF_NVIM_XcposrrptCfg xcposrRptCfg;
    ModemIdUint16         modemId;

    memset_s(&xcposrRptCfg, (VOS_SIZE_T)sizeof(xcposrRptCfg), 0x00, (VOS_SIZE_T)sizeof(xcposrRptCfg));

    /* ????NV?? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_XCPOSRRPT_CFG, &xcposrRptCfg, sizeof(xcposrRptCfg)) == NV_OK) {
        for (modemId = MODEM_ID_0; modemId < MODEM_ID_BUTT; modemId++) {
            agpsCtx               = AT_GetModemAgpsCtxAddrFromModemId(modemId);
            agpsCtx->cposrReport  = xcposrRptCfg.cposrDefault;
            agpsCtx->xcposrReport = xcposrRptCfg.xcposrRptDefault;
        }
    } else {
        AT_ERR_LOG("AT_ReadAgpsNv: NV_Read Failed!");
    }

    return;
}


LOCAL VOS_VOID AT_ReadCustomUsimmCfg(VOS_VOID)
{
    VOS_UINT32              result;
    AT_CommCtx             *commCtx = VOS_NULL_PTR;
    NAS_NVIM_CustomUsimmCfg customUsimmCfg;

    commCtx = AT_GetCommCtxAddr();

    memset_s(&customUsimmCfg, sizeof(NAS_NVIM_CustomUsimmCfg), 0, sizeof(NAS_NVIM_CustomUsimmCfg));

    result = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_CUSTOM_USIMM_CFG, &customUsimmCfg, sizeof(NAS_NVIM_CustomUsimmCfg));

    if ((result != NV_OK) || ((customUsimmCfg.simsqEnable != 0) && (customUsimmCfg.simsqEnable != 1))) {
        memset_s(&commCtx->customUsimmCfg, sizeof(NAS_NVIM_CustomUsimmCfg), 0, sizeof(NAS_NVIM_CustomUsimmCfg));
        AT_WARN_LOG("AT_ReadCustomUsimmCfg: read nv failed!");
    } else {
        commCtx->customUsimmCfg.simsqEnable = customUsimmCfg.simsqEnable;
    }

    return;
}


VOS_VOID AT_ReadNV(VOS_VOID)
{
    /* ????????????NV???? */
    AT_ReadPlatformNV();

    /* client NV???? */
    AT_ReadClientConfigNV();

    /* ??????????????NV?? */
    AT_ReadSysNV();

    /* ????PS????????NV?? */
    AT_ReadPsNV();

    /* ????cs????CC??SS??????NV) */
    AT_ReadCsNV();

    /* ????SMS??????NV */
    AT_ReadSmsNV();

#if (FEATURE_LTE == FEATURE_ON)
    /* ????LTE NV?? */
    AT_ReadLTENV();

#endif

#if (FEATURE_AT_HSUART == FEATURE_ON)
    /* ????uart????????NV?? */
    AT_ReadUartCfgNV();
#endif

    AT_ReadPortBuffCfgNV();

    AT_ReadPrivacyFilterCfgNv();

    AT_ReadAgpsNv();

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    AT_ReadCdmaModemSwitchNotResetCfgNv();
#endif

    AT_ReadCustomUsimmCfg();

    return;
}


VOS_UINT32 AT_ReadPhyNV(VOS_VOID)
{
    VOS_BOOL      bImeiIsNull;
    ModemIdUint16 modemId;

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        if (AT_PhyNumIsNull(modemId, AT_PHYNUM_TYPE_IMEI, &bImeiIsNull) != AT_OK) {
            return VOS_ERR;
        }

        if (bImeiIsNull != VOS_TRUE) {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_VOID AT_InitDeviceCmd(VOS_VOID)
{
#if (FEATURE_UE_MODE_NR == FEATURE_OFF)
    AT_DEVICE_CmdCtrl *atDevCmdCtrl = VOS_NULL_PTR;

    atDevCmdCtrl = AT_GetDevCmdCtrl();
    memset_s(atDevCmdCtrl, sizeof(AT_DEVICE_CmdCtrl), 0x00, sizeof(AT_DEVICE_CmdCtrl));
#else
    AT_MT_Info *atMtInfoCtx = VOS_NULL_PTR;

    atMtInfoCtx = AT_GetMtInfoCtx();
    memset_s(atMtInfoCtx, sizeof(AT_MT_Info), 0x00, sizeof(AT_MT_Info));
    atMtInfoCtx->atInfo.rficTestResult       = AT_RFIC_MEM_TEST_NOT_START;
    atMtInfoCtx->rserTestResult              = (VOS_INT32)AT_SERDES_TEST_NOT_START;
    atMtInfoCtx->serdesTestAsyncInfo.result  = (VOS_INT16)AT_SERDES_TEST_RST_NOT_START;
    atMtInfoCtx->serdesTestAsyncInfo.cmdType = 0;
    atMtInfoCtx->serdesTestAsyncInfo.rptFlg  = 0;
    AT_SetUartTestState(AT_UART_TEST_NOT_START);
    AT_SetI2sTestState(AT_I2S_TEST_NOT_START);
#endif

    if (AT_ReadPhyNV() != VOS_OK) {
        return;
    }

    /* IMEI??????????????DATALOCK???????? */
    g_atDataLocked = VOS_FALSE;

    return;
}


VOS_VOID AT_InitStk(VOS_VOID)
{
    USIMM_StkCfg profile;

    memset_s(&profile, sizeof(profile), 0x00, sizeof(profile));

    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_TERMINALPROFILE_SET, &profile, sizeof(USIMM_StkCfg)) != NV_OK) {
        AT_ERR_LOG("AT_StkInit: read NV_ITEM_TERMINALPROFILE_SET fail.");

        g_stkFunctionFlag = VOS_FALSE;
    } else {
        g_stkFunctionFlag = profile.funcEnable;
    }

    return;
}


VOS_VOID AT_InitPara(VOS_VOID)
{
    VOS_UINT8      *systemAppConfig       = VOS_NULL_PTR;
    VOS_UINT8       atCmdNotSupportStr1[] = "ERROR";
    VOS_UINT8       atCmdNotSupportStr2[] = "COMMAND NOT SUPPORT";
    ModemIdUint16   modemId;
    AT_ModemNetCtx *netCtx = VOS_NULL_PTR;
    errno_t         memResult;

    systemAppConfig = AT_GetSystemAppConfigAddr();

    /* ???????????????????????? */
    switch (*systemAppConfig) {
        /* E5 */
        case SYSTEM_APP_WEBUI:

            netCtx = AT_GetModemNetCtxAddrFromModemId(MODEM_ID_0);

            /* E5????????????????????ERROR */
            /* AT_NOTSUPPORT_STR_LEN + 4??gaucAtCmdNotSupportStr???????????????? */
            memResult = memcpy_s((VOS_CHAR *)g_atCmdNotSupportStr, AT_NOTSUPPORT_STR_LEN + 4,
                                 (VOS_CHAR *)atCmdNotSupportStr1, sizeof(atCmdNotSupportStr1));
            TAF_MEM_CHK_RTN_VAL(memResult, AT_NOTSUPPORT_STR_LEN + 4, sizeof(atCmdNotSupportStr1));

            /* E5?????????????????????? */
            netCtx->copsFormatType = AT_COPS_NUMERIC_TYPE;

            /* E5?????????????????? */
            g_atCmeeType = AT_CMEE_ERROR_CODE;

            break;

            /* STICK */
        case SYSTEM_APP_MP:

            netCtx = AT_GetModemNetCtxAddrFromModemId(MODEM_ID_0);

            /* ?????????????????? */
            /* AT_NOTSUPPORT_STR_LEN + 4??gaucAtCmdNotSupportStr???????????????? */
            memResult = memcpy_s((VOS_CHAR *)g_atCmdNotSupportStr, AT_NOTSUPPORT_STR_LEN + 4,
                                 (VOS_CHAR *)atCmdNotSupportStr2, sizeof(atCmdNotSupportStr2));
            TAF_MEM_CHK_RTN_VAL(memResult, AT_NOTSUPPORT_STR_LEN + 4, sizeof(atCmdNotSupportStr2));

            netCtx->copsFormatType = AT_COPS_LONG_ALPH_TYPE;

            /* ?????????????????????? */
            g_atCmeeType = AT_CMEE_ERROR_CONTENT;

            break;

        /* PAD,????????????????????????????????????stick???? */
        case SYSTEM_APP_ANDROID:

            /* ?????????????????? */
            /* AT_NOTSUPPORT_STR_LEN + 4??gaucAtCmdNotSupportStr???????????????? */
            memResult = memcpy_s((VOS_CHAR *)g_atCmdNotSupportStr, AT_NOTSUPPORT_STR_LEN + 4,
                                 (VOS_CHAR *)atCmdNotSupportStr2, sizeof(atCmdNotSupportStr2));
            TAF_MEM_CHK_RTN_VAL(memResult, AT_NOTSUPPORT_STR_LEN + 4, sizeof(atCmdNotSupportStr2));

            for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
                netCtx                 = AT_GetModemNetCtxAddrFromModemId(modemId);
                netCtx->copsFormatType = AT_COPS_LONG_ALPH_TYPE;
            }

            /* ?????????????????????? */
            g_atCmeeType = AT_CMEE_ERROR_CODE;

            break;

        default:
            break;
    }

    return;
}


VOS_VOID AT_InitPort(VOS_VOID)
{
    /*
     * ????????PC?????????? NAS GTR PC??????SDT USBCOM AT??????????client ID
     * ????????????USB COM????????????
     */
    /* USB PCUI???????????? */
    At_UsbPcuiEst();

    /* USB Control???????????? */
    At_UsbCtrEst();

    /* USB PCUI2???????????? */
    At_UsbPcui2Est();

    /* UART???????????? */
    AT_UartInitPort();

    /* NDIS MODEM???????????? */
    AT_UsbNdisEst();

    /* APP ???????? */
    AT_AppComEst();

    AT_UsbNdisDataEst();

#if (FEATURE_AT_HSUART == FEATURE_ON)
    AT_HSUART_InitPort();
#endif

    /* NDIS MODEM???????????? */
    AT_ModemEst();

    /* APP ???????? */
    AT_SockEst();

    DMS_PORT_Init();

#if (FEATURE_AT_HSUART == FEATURE_ON)
    AT_HSUART_ConfigDefaultPara();
#endif


    return;
}



VOS_UINT32 At_PidInit(enum VOS_InitPhaseDefine phase)
{
    switch (phase) {
        case VOS_IP_INITIAL:

            /* ??????AT???????? */
            AT_InitCtx();

#if (FEATURE_PHONE_ENG_AT_CMD == FEATURE_ON)
            AT_InitWakelock();
#endif

#if (FEATURE_AT_HSUART == FEATURE_ON)
            /* ??????UART???????????? */
            AT_InitUartCtx();
#endif

            AT_InitPortBuffCfg();

            AT_InitTraceMsgTab();

            /* ?????????????????????? */
            AT_InitResetCtx();

            /* ????NV?? */
            AT_ReadNV();

            /* AT ???????????? */
            At_ParseInit();

            /* ????AT?????? */
            At_RegisterBasicCmdTable();
            At_RegisterExCmdTable();
            At_RegisterExPrivateCmdTable();
            At_RegisterDeviceCmdTable();
#if (FEATURE_LTE == FEATURE_ON)
            At_RegisterDeviceCmdTLTable();
            At_RegisterTLCmdTable();
#endif
#if (FEATURE_LTEV == FEATURE_ON)
            At_RegisterLtevCmdTable();
#endif
            /* ?????????? */
            AT_InitDeviceCmd();

            /* STK??AT???????????? */
            AT_InitStk();

            /* AT???????????????? */
            AT_InitPara();

            /* AT???????????????????????? */
            AT_InitMsgNumCtrlCtx();

            /* ?????????? */
            AT_InitPort();

            /* ??????g_fcIdMaptoFcPri */
            AT_InitFcMap();

            /* ????????????????????????C???????????????? */
            AT_RegisterSysbootResetNotify(NAS_AT_FUNC_PROC_NAME, AT_CCpuResetCallback, 0, ACPU_RESET_PRIORITY_AT);

            /* ????????????????????????HIFI?????????????? */
            hifireset_regcbfunc(NAS_AT_FUNC_PROC_NAME, AT_HifiResetCallback, 0, ACPU_RESET_PRIORITY_AT);
            AT_InitMntnCtx();
            AT_RegisterDumpCallBack();

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
            /* ???????????????????? */
            GUNAS_OM_LayerMsgReplaceCBRegACore();
            TAF_OM_LayerMsgLogPrivacyMatchRegAcore();
#endif
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_VOID AT_ReadSsNV(VOS_VOID)
{
    memset_s(&g_atSsCustomizePara, sizeof(g_atSsCustomizePara), 0x00, sizeof(g_atSsCustomizePara));

    /* ????SS??????NV???????????? */
    if ((TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_SS_CUSTOMIZE_PARA, &g_atSsCustomizePara, sizeof(g_atSsCustomizePara)) !=
         NV_OK) ||
        (g_atSsCustomizePara.status != VOS_TRUE)) {
        g_atSsCustomizePara.status = VOS_FALSE;
    }

    return;
}

#if (FEATURE_AT_HSUART == FEATURE_ON)

VOS_VOID AT_ReadUartCfgNV(VOS_VOID)
{
    AT_UartCtx    *uartCtx = VOS_NULL_PTR;
    TAF_NV_UartCfg uartNVCfg;
    VOS_UINT32     ret;

    memset_s(&uartNVCfg, sizeof(uartNVCfg), 0x00, sizeof(TAF_NV_UartCfg));

    uartCtx = AT_GetUartCtxAddr();

    /* ????NV?? */
    ret = TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_UART_CFG, &uartNVCfg, sizeof(TAF_NV_UartCfg));

    if (ret == VOS_OK) {
        /* ????NV???????????????????????????????? */
        ret = AT_HSUART_IsBaudRateValid(uartNVCfg.baudRate);
        if (ret == VOS_TRUE) {
            /* ??NV???????????????????????? */
            uartCtx->phyConfig.baudRate = uartNVCfg.baudRate;
        }

        /* ????NV???????????????????????????????? */
        ret = AT_HSUART_ValidateCharFrameParam(uartNVCfg.frame.format, uartNVCfg.frame.parity);
        if (ret == VOS_TRUE) {
            uartCtx->phyConfig.frame.format = uartNVCfg.frame.format;
            uartCtx->phyConfig.frame.parity = uartNVCfg.frame.parity;
        }

        uartCtx->riConfig.smsRiOnInterval    = uartNVCfg.riConfig.smsRiOnInterval;
        uartCtx->riConfig.smsRiOffInterval   = uartNVCfg.riConfig.smsRiOffInterval;
        uartCtx->riConfig.voiceRiOnInterval  = uartNVCfg.riConfig.voiceRiOnInterval;
        uartCtx->riConfig.voiceRiOffInterval = uartNVCfg.riConfig.voiceRiOffInterval;
        uartCtx->riConfig.voiceRiCycleTimes  = uartNVCfg.riConfig.voiceRiCycleTimes;
    }

    return;
}
#endif

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_VOID AT_ReadCdmaModemSwitchNotResetCfgNv(VOS_VOID)
{
    AT_ModemCdmamodemswitchCtx         *cdmaModemSwitchCtx = VOS_NULL_PTR;
    TAF_NVIM_CdmamodemswitchNotResetCfg cdmaModemSwitchNvCfg;
    ModemIdUint16                       modemId;

    /* ?????? */
    memset_s(&cdmaModemSwitchNvCfg, (VOS_UINT32)sizeof(TAF_NVIM_CdmamodemswitchNotResetCfg), 0x00,
             (VOS_UINT32)sizeof(TAF_NVIM_CdmamodemswitchNotResetCfg));

    /* ????NV?? */
    if (TAF_ACORE_NV_READ(MODEM_ID_0, NV_ITEM_CDMAMODEMSWITCH_NOT_RESET_CFG, &cdmaModemSwitchNvCfg,
                          (VOS_UINT32)sizeof(TAF_NVIM_CdmamodemswitchNotResetCfg)) != NV_OK) {
        cdmaModemSwitchNvCfg.enableFlg = VOS_FALSE;
    }

    if (cdmaModemSwitchNvCfg.enableFlg != VOS_TRUE) {
        cdmaModemSwitchNvCfg.enableFlg = VOS_FALSE;
    }

    for (modemId = 0; modemId < MODEM_ID_BUTT; modemId++) {
        cdmaModemSwitchCtx = AT_GetModemCdmaModemSwitchCtxAddrFromModemId(modemId);

        cdmaModemSwitchCtx->enableFlg = cdmaModemSwitchNvCfg.enableFlg;
    }

    return;
}
#endif

