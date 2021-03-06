

/* 1 头文件包含 */
#include "oam_ext_if.h"
#include "dmac_ext_if.h"
#include "hmac_user.h"
#include "hmac_main.h"
#include "hmac_tx_amsdu.h"
#include "hmac_protection.h"
#include "hmac_smps.h"
#include "hmac_ext_if.h"
#include "hmac_config.h"
#include "hmac_mgmt_ap.h"
#include "hmac_chan_mgmt.h"
#include "hmac_fsm.h"
#include "hmac_sme_sta.h"
#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
#include "hmac_wapi.h"
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif  // _PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_SUPPORT_ACS
#include "hmac_acs.h"
#endif

#include "hmac_blockack.h"
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#if defined(_PRE_WLAN_FEATURE_WDS) || defined(_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
#include "hmac_wds.h"
#endif
#include "hmac_scan.h"

#include "securec.h"
#include "securectype.h"
#ifdef _PRE_WLAN_FEATURE_11AX
#include "mac_ie.h"
#endif
#ifdef _PRE_WLAN_FEATURE_HIEX
#include "hmac_hiex.h"
#endif
#include "hmac_ht_self_cure.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_USER_C
/* 2 全局变量定义 */
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
hmac_user_stru g_ast_hmac_user[MAC_RES_MAX_USER_LIMIT];
#endif
extern oal_uint8 wlan_ps_mode;

/* 3 函数实现 */

hmac_user_stru *mac_res_get_hmac_user_alloc_etc(oal_uint16 us_idx)
{
    hmac_user_stru *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru *)_mac_res_get_hmac_user(us_idx);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{mac_res_get_hmac_user_init::pst_hmac_user null,user_idx=%d.}", us_idx);
        return OAL_PTR_NULL;
    }

    /* 重复申请异常,避免影响业务，暂时打印error但正常申请 */
    if (pst_hmac_user->st_user_base_info.uc_is_user_alloced == MAC_USER_ALLOCED) {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{mac_res_get_hmac_user_init::[E]user has been alloced,user_idx=%d.}", us_idx);
    }

    return pst_hmac_user;
}


hmac_user_stru *mac_res_get_hmac_user_etc(oal_uint16 us_idx)
{
    hmac_user_stru *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru *)_mac_res_get_hmac_user(us_idx);
    if (pst_hmac_user == OAL_PTR_NULL) {
        return OAL_PTR_NULL;
    }

    /* 异常: 用户资源已被释放 */
    if (pst_hmac_user->st_user_base_info.uc_is_user_alloced != MAC_USER_ALLOCED) {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        oal_mem_print_funcname_etc(OAL_RET_ADDR);
#endif
        /*
         * host侧获取用户时用户已经释放属于正常，返回空指针，
         * 后续调用者查找用户失败，请打印WARNING并直接释放buf，
         * 走其他分支等等
         */
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{mac_res_get_hmac_user_etc::[E]user has been freed,user_idx=%d.}", us_idx);
        return OAL_PTR_NULL;
    }

    return pst_hmac_user;
}


oal_uint32 hmac_user_alloc_etc(oal_uint16 *pus_user_idx)
{
    hmac_user_stru *pst_hmac_user = OAL_PTR_NULL;
    oal_uint32 ul_rslt;
    oal_uint16 us_user_idx_temp;

    if (OAL_UNLIKELY(pus_user_idx == OAL_PTR_NULL)) {
        OAM_ERROR_LOG0(0, OAM_SF_UM, "{hmac_user_alloc_etc::pus_user_idx null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 申请hmac user内存 */
    /*lint -e413*/
    ul_rslt = mac_res_alloc_hmac_user(&us_user_idx_temp, OAL_OFFSET_OF(hmac_user_stru, st_user_base_info));
    if (ul_rslt != OAL_SUCC) {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{hmac_user_alloc_etc::mac_res_alloc_hmac_user failed[%d].}", ul_rslt);
        return ul_rslt;
    }
    /*lint +e413*/
    pst_hmac_user = mac_res_get_hmac_user_alloc_etc(us_user_idx_temp);
    if (pst_hmac_user == OAL_PTR_NULL) {
        mac_res_free_mac_user_etc(us_user_idx_temp);
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_alloc_etc::pst_hmac_user null,user_idx=%d.}", us_user_idx_temp);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 初始清0 */
    memset_s(pst_hmac_user, OAL_SIZEOF(hmac_user_stru), 0, OAL_SIZEOF(hmac_user_stru));
    /* 标记user资源已被alloc */
    pst_hmac_user->st_user_base_info.uc_is_user_alloced = MAC_USER_ALLOCED;

    *pus_user_idx = us_user_idx_temp;

    return OAL_SUCC;
}


oal_uint32 hmac_user_free_etc(oal_uint16 us_idx)
{
    hmac_user_stru *pst_hmac_user;
    oal_uint32 ul_ret;

    pst_hmac_user = mac_res_get_hmac_user_etc(us_idx);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_free_etc::pst_hmac_user null,user_idx=%d.}", us_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = mac_res_free_mac_user_etc(us_idx);
    if (ul_ret == OAL_SUCC) {
        /* 清除alloc标志 */
        pst_hmac_user->st_user_base_info.uc_is_user_alloced = MAC_USER_FREED;
    }

    return ul_ret;
}


oal_uint32 hmac_user_free_asoc_req_ie(oal_uint16 us_idx)
{
    hmac_user_stru *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_idx);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_WARNING_LOG1(0, OAM_SF_ASSOC, "{hmac_vap_free_asoc_req_ie::pst_hmac_user[%d] null.}", us_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_hmac_user->puc_assoc_req_ie_buff != OAL_PTR_NULL) {
        OAL_MEM_FREE(pst_hmac_user->puc_assoc_req_ie_buff, OAL_TRUE);
        pst_hmac_user->puc_assoc_req_ie_buff = OAL_PTR_NULL;
        pst_hmac_user->ul_assoc_req_ie_len = 0;
    } else {
        pst_hmac_user->ul_assoc_req_ie_len = 0;
    }
    return OAL_SUCC;
}


oal_uint32 hmac_user_set_asoc_req_ie(hmac_user_stru *pst_hmac_user,
                                     oal_uint8 *puc_payload, oal_uint32 ul_payload_len, oal_uint8 uc_reass_flag)
{
    /* 重关联比关联请求帧头多了AP的MAC地址  */
    ul_payload_len -= ((uc_reass_flag == OAL_TRUE) ? WLAN_MAC_ADDR_LEN : 0);

    pst_hmac_user->puc_assoc_req_ie_buff = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)ul_payload_len, OAL_TRUE);
    if (pst_hmac_user->puc_assoc_req_ie_buff == OAL_PTR_NULL) {
        OAM_ERROR_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_user_set_asoc_req_ie :: Alloc %u bytes failed for puc_assoc_req_ie_buff failed .}",
                       (oal_uint16)ul_payload_len);
        pst_hmac_user->ul_assoc_req_ie_len = 0;
        return OAL_FAIL;
    }
    if (EOK != memcpy_s(pst_hmac_user->puc_assoc_req_ie_buff, ul_payload_len,
                        puc_payload + ((uc_reass_flag == OAL_TRUE) ? WLAN_MAC_ADDR_LEN : 0),
                        ul_payload_len)) {
        OAL_MEM_FREE(pst_hmac_user->puc_assoc_req_ie_buff, OAL_TRUE);
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "hmac_user_set_asoc_req_ie::memcpy fail!");
        return OAL_FAIL;
    }
    pst_hmac_user->ul_assoc_req_ie_len = ul_payload_len;

    return OAL_SUCC;
}


oal_uint32 hmac_user_init_etc(hmac_user_stru *pst_hmac_user)
{
    oal_uint8 uc_tid_loop;
    hmac_ba_tx_stru *pst_tx_ba = OAL_PTR_NULL;

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    oal_uint8 uc_ac_idx;
    oal_uint8 uc_data_idx;
#endif

    /* 初始化tid信息 */
    for (uc_tid_loop = 0; uc_tid_loop < WLAN_TID_MAX_NUM; uc_tid_loop++) {
        pst_hmac_user->ast_tid_info[uc_tid_loop].uc_tid_no = (oal_uint8)uc_tid_loop;

        // pst_hmac_user->ast_tid_info[uc_tid_loop].pst_hmac_user  = (oal_void *)pst_hmac_user;
        pst_hmac_user->ast_tid_info[uc_tid_loop].us_hmac_user_idx = pst_hmac_user->st_user_base_info.us_assoc_id;

        /* 初始化ba rx操作句柄 */
        pst_hmac_user->ast_tid_info[uc_tid_loop].pst_ba_rx_info = OAL_PTR_NULL;
        oal_spin_lock_init(&(pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.st_ba_status_lock));
        pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.en_ba_status = DMAC_BA_INIT;
        pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.uc_addba_attemps = 0;
        pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.uc_dialog_token = 0;
        pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.uc_ba_policy = 0;
        pst_hmac_user->ast_tid_info[uc_tid_loop].en_ba_handle_tx_enable = OAL_TRUE;
        pst_hmac_user->ast_tid_info[uc_tid_loop].en_ba_handle_rx_enable = OAL_TRUE;

        pst_hmac_user->auc_ba_flag[uc_tid_loop] = 0;

        /* addba req超时处理函数入参填写 */
        pst_tx_ba = &pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info;
        pst_tx_ba->st_alarm_data.pst_ba = (oal_void *)pst_tx_ba;
        pst_tx_ba->st_alarm_data.uc_tid = uc_tid_loop;
        pst_tx_ba->st_alarm_data.us_mac_user_idx = pst_hmac_user->st_user_base_info.us_assoc_id;
        pst_tx_ba->st_alarm_data.uc_vap_id = pst_hmac_user->st_user_base_info.uc_vap_id;

        /* 初始化用户关联请求帧参数 */
        pst_hmac_user->puc_assoc_req_ie_buff = OAL_PTR_NULL;
        pst_hmac_user->ul_assoc_req_ie_len = 0;

        oal_spin_lock_init(&(pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_timer_lock));
    }

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    for (uc_ac_idx = 0; uc_ac_idx < WLAN_WME_AC_BUTT; uc_ac_idx++) {
        for (uc_data_idx = 0; uc_data_idx < WLAN_TXRX_DATA_BUTT; uc_data_idx++) {
            pst_hmac_user->aaul_txrx_data_stat[uc_ac_idx][uc_data_idx] = 0;
        }
    }
#endif

    pst_hmac_user->pst_defrag_netbuf = OAL_PTR_NULL;
    pst_hmac_user->en_user_bw_limit = OAL_FALSE;
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    pst_hmac_user->st_sa_query_info.ul_sa_query_count = 0;
    pst_hmac_user->st_sa_query_info.ul_sa_query_start_time = 0;
#endif
    memset_s(&pst_hmac_user->st_defrag_timer, OAL_SIZEOF(frw_timeout_stru), 0, OAL_SIZEOF(frw_timeout_stru));
    pst_hmac_user->ul_rx_pkt_drop = 0;

#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
    /* 清除usr统计信息 */
    oam_stats_clear_user_stat_info_etc(pst_hmac_user->st_user_base_info.us_assoc_id);
#endif

    pst_hmac_user->ul_first_add_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
    pst_hmac_user->us_clear_judge_count = 0;
#endif

    return OAL_SUCC;
}

oal_uint32 hmac_user_set_avail_num_space_stream_etc(mac_user_stru *pst_mac_user, wlan_nss_enum_uint8 en_vap_nss)
{
    mac_user_ht_hdl_stru *pst_mac_ht_hdl;
    mac_vht_hdl_stru *pst_mac_vht_hdl;
#ifdef _PRE_WLAN_FEATURE_11AX
    mac_he_hdl_stru *pst_mac_he_hdl;
#endif
    wlan_nss_enum_uint8 en_user_num_spatial_stream = 0;
    oal_uint32 ul_ret = OAL_SUCC;

    /* AP(STA)为legacy设备，只支持1根天线，不需要再判断天线个数 */
    /* 获取HT和VHT结构体指针 */
    pst_mac_ht_hdl = &(pst_mac_user->st_ht_hdl);
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);
#ifdef _PRE_WLAN_FEATURE_11AX
    pst_mac_he_hdl = MAC_USER_HE_HDL_STRU(pst_mac_user);
    if (pst_mac_he_hdl->en_he_capable == OAL_TRUE) {
        ul_ret = mac_ie_from_he_cap_get_nss(pst_mac_he_hdl, &en_user_num_spatial_stream);
    } else if (pst_mac_vht_hdl->en_vht_capable == OAL_TRUE)
#else
    if (pst_mac_vht_hdl->en_vht_capable == OAL_TRUE)
#endif
    {
        if (pst_mac_vht_hdl->st_rx_max_mcs_map.us_max_mcs_4ss != 3) {
            en_user_num_spatial_stream = WLAN_FOUR_NSS;
        } else if (pst_mac_vht_hdl->st_rx_max_mcs_map.us_max_mcs_3ss != 3) {
            en_user_num_spatial_stream = WLAN_TRIPLE_NSS;
        } else if (pst_mac_vht_hdl->st_rx_max_mcs_map.us_max_mcs_2ss != 3) {
            en_user_num_spatial_stream = WLAN_DOUBLE_NSS;
        } else if (pst_mac_vht_hdl->st_rx_max_mcs_map.us_max_mcs_1ss != 3) {
            en_user_num_spatial_stream = WLAN_SINGLE_NSS;
        } else {
            OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY,
                             "{hmac_user_set_avail_num_space_stream_etc::invalid vht nss.}");

            ul_ret = OAL_FAIL;
        }
    } else if (pst_mac_ht_hdl->en_ht_capable == OAL_TRUE) {
        if (pst_mac_ht_hdl->uc_rx_mcs_bitmask[3] > 0) {
            en_user_num_spatial_stream = WLAN_FOUR_NSS;
        } else if (pst_mac_ht_hdl->uc_rx_mcs_bitmask[2] > 0) {
            en_user_num_spatial_stream = WLAN_TRIPLE_NSS;
        } else if (pst_mac_ht_hdl->uc_rx_mcs_bitmask[1] > 0) {
            en_user_num_spatial_stream = WLAN_DOUBLE_NSS;
        } else if (pst_mac_ht_hdl->uc_rx_mcs_bitmask[0] > 0) {
            en_user_num_spatial_stream = WLAN_SINGLE_NSS;
        } else {
            OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY,
                             "{hmac_user_set_avail_num_space_stream_etc::invalid ht nss.}");

            ul_ret = OAL_FAIL;
        }
    } else {
        en_user_num_spatial_stream = WLAN_SINGLE_NSS;
    }

    /* 赋值给用户结构体变量 */
    mac_user_set_num_spatial_stream_etc(pst_mac_user, en_user_num_spatial_stream);
    mac_user_set_avail_num_spatial_stream_etc(pst_mac_user,
                                              OAL_MIN(pst_mac_user->en_user_max_cap_nss, en_vap_nss));
    mac_user_set_smps_opmode_notify_nss(pst_mac_user, WLAN_NSS_LIMIT);

    return ul_ret;
}


oal_uint8 hmac_user_calculate_num_spatial_stream(wlan_nss_enum_uint8 *puc_nss1, wlan_nss_enum_uint8 *puc_nss2)
{
    oal_uint8 uc_nss_valid_flag = OAL_TRUE;

    switch (*puc_nss1) {
        case 0: /* 0流表示不支持 */
            *puc_nss1 = WLAN_NSS_LIMIT;
            break;

        case 1: /* 1流的宏定义WLAN_SINGLE_NSS(值是0) */
            *puc_nss1 = WLAN_SINGLE_NSS;
            break;

        case 2: /* 2流的宏定义WLAN_DOUBLE_NSS(值是1) */
            *puc_nss1 = WLAN_DOUBLE_NSS;
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_user_calculate_num_spatial_stream::error puc_nss1[%d]}", *puc_nss1);
            uc_nss_valid_flag = OAL_FALSE;
            break;
    }

    switch (*puc_nss2) {
        case 0: /* 0流表示不支持 */
            *puc_nss2 = WLAN_NSS_LIMIT;
            break;

        case 1: /* 1流的宏定义WLAN_SINGLE_NSS(值是0) */
            *puc_nss2 = WLAN_SINGLE_NSS;
            break;

        case 2: /* 2流的宏定义WLAN_DOUBLE_NSS(值是1) */
            *puc_nss2 = WLAN_DOUBLE_NSS;
            break;

        case 3: /* 3流的宏定义WLAN_DOUBLE_NSS(值是2) */
            *puc_nss2 = WLAN_TRIPLE_NSS;
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_user_calculate_num_spatial_stream::error puc_nss2[%d]}", *puc_nss2);
            uc_nss_valid_flag = OAL_FALSE;
            break;
    }
    return uc_nss_valid_flag;
}


oal_void hmac_user_set_num_spatial_stream_160M(mac_user_stru *pst_mac_user)
{
    mac_vht_hdl_stru *pst_mac_vht_hdl = OAL_PTR_NULL;
    /* 计算结果是实际流数，取值 0 或 1 或 2 */
    wlan_nss_enum_uint8 en_user_num_spatial_stream1 = ((pst_mac_user->en_user_max_cap_nss + 1) >> 1);
    /* 计算结果是实际流数，取值 0 或 1 或 2 或 3  */
    wlan_nss_enum_uint8 en_user_num_spatial_stream2 = (((pst_mac_user->en_user_max_cap_nss + 1) * 3) >> 2);
    wlan_nss_enum_uint8 en_user_num_spatial_stream = WLAN_NSS_LIMIT;
    oal_uint8 uc_ret;

    uc_ret = hmac_user_calculate_num_spatial_stream(&en_user_num_spatial_stream1, &en_user_num_spatial_stream2);
    if (uc_ret == OAL_FALSE) {
        OAM_ERROR_LOG0(0, OAM_SF_ANY,
                       "{hmac_user_set_num_spatial_stream_160M::hmac_user_calculate_num_spatial_stream error!}");
        return;
    }

    /* 获取HT和VHT结构体指针 */
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);

    if (WLAN_MIB_VHT_SUPP_WIDTH_80 < pst_mac_vht_hdl->bit_supported_channel_width) {
        en_user_num_spatial_stream = pst_mac_user->en_user_max_cap_nss;
    } else {
        switch (pst_mac_vht_hdl->bit_extend_nss_bw_supp) {
            case WLAN_EXTEND_NSS_BW_SUPP0:
                en_user_num_spatial_stream = WLAN_NSS_LIMIT;
                break;

            case WLAN_EXTEND_NSS_BW_SUPP1:
            case WLAN_EXTEND_NSS_BW_SUPP2:
                en_user_num_spatial_stream = en_user_num_spatial_stream1;
                break;

            case WLAN_EXTEND_NSS_BW_SUPP3:
                en_user_num_spatial_stream = en_user_num_spatial_stream2;
                break;

            default:
                OAM_WARNING_LOG1(0, OAM_SF_ANY,
                                 "{hmac_user_set_num_spatial_stream_160M::error extend_nss_bw_supp[%d]}",
                                 pst_mac_vht_hdl->bit_extend_nss_bw_supp);
                break;
        }
    }
    mac_user_set_num_spatial_stream_160M(pst_mac_user, en_user_num_spatial_stream);
}

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

OAL_STATIC oal_void hmac_stop_sa_query_timer(hmac_user_stru *pst_hmac_user)
{
    frw_timeout_stru *pst_sa_query_interval_timer;

    pst_sa_query_interval_timer = &(pst_hmac_user->st_sa_query_info.st_sa_query_interval_timer);
    if (pst_sa_query_interval_timer->en_is_registerd != OAL_FALSE) {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(pst_sa_query_interval_timer);
    }
}
#endif


#ifdef _PRE_WLAN_FEATURE_WAPI
hmac_wapi_stru *hmac_user_get_wapi_ptr_etc(mac_vap_stru *pst_mac_vap,
                                           oal_bool_enum_uint8 en_pairwise,
                                           oal_uint16 us_pairwise_idx)
{
    hmac_user_stru *pst_hmac_user;
    // oal_uint32                       ul_ret;
    oal_uint16 us_user_index;

    if (en_pairwise == OAL_TRUE) {
        us_user_index = us_pairwise_idx;
    } else {
        us_user_index = pst_mac_vap->us_multi_user_idx;
    }

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_index);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                         "{hmac_user_get_wapi_ptr_etc::pst_hmac_user[%d] null.}", us_user_index);
        return OAL_PTR_NULL;
    }

    return &pst_hmac_user->st_wapi;
}
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX

oal_void hmac_compability_ap_tpye_identify_for_btcoex_etc(mac_vap_stru *pst_mac_vap,
                                                          mac_bss_dscr_stru *pst_bss_dscr, oal_uint8 *puc_mac_addr,
                                                          mac_ap_type_enum_uint16 *pen_ap_type)
{
    wlan_nss_enum_uint8 en_support_max_nss = WLAN_SINGLE_NSS;
    if (pst_bss_dscr != OAL_PTR_NULL) {
        /* 一级生效，直接置self-cts,苹果路由器有其他方案，这里暂时不开 */
        /* 二级生效，需要考虑mac地址约束 */
        if (pst_bss_dscr->en_btcoex_blacklist_chip_oui & MAC_BTCOEX_BLACKLIST_LEV0) {
            /* 关联ap识别: AP OUI + chip OUI + 双流 + 2G 需要dmac侧刷新ps机制时one pkt帧发送类型 */
            if (MAC_IS_DLINK_AP(puc_mac_addr) || MAC_IS_HAIER_AP(puc_mac_addr) ||
                MAC_IS_FAST_AP(puc_mac_addr) || MAC_IS_TPINK_845_AP(puc_mac_addr)) {
#ifdef _PRE_WLAN_FEATURE_M2S
                en_support_max_nss = pst_bss_dscr->en_support_max_nss;
#endif
                if ((en_support_max_nss == WLAN_DOUBLE_NSS) && (pst_mac_vap->st_channel.en_band == WLAN_BAND_2G)) {
                    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX,
                        "hmac_compability_ap_tpye_identify_for_btcoex_etc: lev0 btcoex ps self-cts blacklist!");
                    *pen_ap_type |= MAC_AP_TYPE_BTCOEX_PS_BLACKLIST;
                }
            } else if (MAC_IS_JCG_AP(puc_mac_addr)) {
                /* JCG路由器为了兼容aptxHD和660,需要关闭cts回复功能 */
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX,
                    "hmac_compability_ap_tpye_identify_for_btcoex_etc: lev0 JCG btcoex disable cts blacklist!");
                *pen_ap_type |= MAC_AP_TYPE_BTCOEX_DISABLE_CTS;
            } else if (MAC_IS_FEIXUN_K3(puc_mac_addr)) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX,
                    "hmac_compability_ap_tpye_identify_for_btcoex_etc: lev0 k3 btcoex ps self-cts blacklist!");
                *pen_ap_type |= MAC_AP_TYPE_BTCOEX_PS_BLACKLIST;
            } else if (MAC_IS_FAST_FW450R(puc_mac_addr)) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX,
                    "hmac_compability_ap_tpye_identify_for_btcoex_etc: lev0 btcoex sco part middle priority!");
                *pen_ap_type |= MAC_AP_TYPE_BTCOEX_SCO_MIDDLE_PRIORITY;
            }
#ifdef _PRE_WLAN_FEATURE_11AX
            if (MAC_IS_AX3000(puc_mac_addr) && (pst_mac_vap->en_protocol == WLAN_HE_MODE)) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX,
                    "hmac_compability_ap_tpye_identify_for_btcoex_etc: lev0 btcoex 20dbm blacklist!!");
                *pen_ap_type |= MAC_AP_TYPE_BTCOEX_20DBM_BLACKLIST;
            }
#endif
            
            if (MAC_IS_SCO_RETRY_BLACKLIST(puc_mac_addr)) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX,
                    "hmac_compability_ap_tpye_identify_for_btcoex_etc: lev0 btcoex sco retry middle priority!");
                *pen_ap_type |= MAC_AP_TYPE_BTCOEX_SCO_RETRY_MIDDLE_PRIORITY;
            }
        }
    }
}
#endif

OAL_STATIC oal_void hmac_get_ap_tpye(mac_vap_stru *pst_mac_vap, mac_bss_dscr_stru *pst_bss_dscr)
{
#ifdef _PRE_WLAN_FEATURE_11AX
    pst_mac_vap->st_cap_flag.bit_rx_stbc = OAL_TRUE;
    if (MAC_IS_HUAWEITE_AP(pst_bss_dscr)) {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, 0, "hmac_get_ap_tpye: rx stbc blacklist!");
        pst_mac_vap->st_cap_flag.bit_rx_stbc = OAL_FALSE;
    }
#endif
}


mac_ap_type_enum_uint16 hmac_compability_ap_tpye_identify_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr)
{
    mac_ap_type_enum_uint16 en_ap_type = 0;

#if defined(_PRE_WLAN_1103_DDC_BUGFIX)
    wlan_nss_enum_uint8 en_support_max_nss = WLAN_SINGLE_NSS;
#endif

    mac_bss_dscr_stru *pst_bss_dscr = OAL_PTR_NULL;

    pst_bss_dscr = (mac_bss_dscr_stru *)hmac_scan_get_scanned_bss_by_bssid(pst_mac_vap, puc_mac_addr);

    if (MAC_IS_GOLDEN_AP(puc_mac_addr)) {
        en_ap_type |= MAC_AP_TYPE_GOLDENAP;
    }

    if (pst_bss_dscr != OAL_PTR_NULL) {
#ifdef _PRE_WLAN_1103_DDC_BUGFIX
        /* DDC白名单: AP OUI + chip OUI + 三流 + 2G */
        if (MAC_IS_BELKIN_AP(puc_mac_addr) || MAC_IS_TRENDNET_AP(puc_mac_addr) ||
            MAC_IS_NETGEAR_WNDR_AP(puc_mac_addr)) {
#ifdef _PRE_WLAN_FEATURE_M2S
            en_support_max_nss = pst_bss_dscr->en_support_max_nss;
#endif
            if (pst_bss_dscr->en_atheros_chip_oui == OAL_TRUE) {
                if ((MAC_IS_NETGEAR_WNDR_AP(puc_mac_addr) && en_support_max_nss == WLAN_DOUBLE_NSS) ||
                    ((MAC_IS_BELKIN_AP(puc_mac_addr) || MAC_IS_TRENDNET_AP(puc_mac_addr)) &&
                     (en_support_max_nss == WLAN_TRIPLE_NSS) && (pst_mac_vap->st_channel.en_band == WLAN_BAND_2G))) {
                    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                                     "hmac_compability_ap_tpye_identify_etc is in ddc whitelist!");
                    en_ap_type |= MAC_AP_TYPE_DDC_WHITELIST;
                }
            }
        }
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
        hmac_compability_ap_tpye_identify_for_btcoex_etc(pst_mac_vap, pst_bss_dscr, puc_mac_addr, &en_ap_type);
#endif

#ifdef _PRE_WLAN_FEATURE_M2S
        /* 关联时候识别360随身wifi或者2G的TP-LINK7300,后续不能切siso */
        if (MAC_IS_360_AP0(puc_mac_addr) || MAC_IS_360_AP1(puc_mac_addr) || MAC_IS_360_AP2(puc_mac_addr) ||
            (MAC_IS_TP_LINK_7300(pst_bss_dscr) && (pst_mac_vap->st_channel.en_band == WLAN_BAND_2G))) {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_M2S,
                             "hmac_compability_ap_tpye_identify_etc: m2s blacklist!");
            en_ap_type |= MAC_AP_TYPE_M2S;
        }
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
        /* 关闭时候识别斐讯k3，不能进行漫游 */
        if (MAC_IS_FEIXUN_K3(puc_mac_addr)) {
            if (pst_bss_dscr->en_roam_blacklist_chip_oui == OAL_TRUE) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, 0, "hmac_compability_ap_tpye_identify_etc: roam blacklist!");
                en_ap_type |= MAC_AP_TYPE_ROAM;
            }
        }
#endif

        /* 识别HUAWEI ，不支持rx stbc */
        hmac_get_ap_tpye(pst_mac_vap, pst_bss_dscr);
        pst_mac_vap->bit_ap_chip_oui = pst_bss_dscr->en_is_tplink_oui;

        if ((pst_bss_dscr->en_atheros_chip_oui == OAL_TRUE) && (MAC_IS_LINKSYS_EA8500_AP(puc_mac_addr))) {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ROAM,
                             "hmac_compability_ap_tpye_identify_etc: aggr blacklist!");
            en_ap_type |= MAC_AP_TYPE_AGGR_BLACKLIST;
        }
    }

    /* 打桩1102逻辑 */
    en_ap_type |= MAC_AP_TYPE_NORMAL;

    return en_ap_type;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

oal_void hmac_sdio_to_pcie_switch(mac_vap_stru *pst_mac_vap)
{
    /* 如果VAP工作在5G,则切换为PCIE */
    if (WLAN_BAND_5G == pst_mac_vap->st_channel.en_band) {
        hi110x_switch_to_hcc_highspeed_chan(1);
    }
}



oal_void hmac_pcie_to_sdio_switch(mac_chip_stru *pst_mac_chip)
{
    /* chip下无其他关联用户，则切换为SDIO */
    if (pst_mac_chip->uc_assoc_user_cnt == 0) {
        hi110x_switch_to_hcc_highspeed_chan(0);
    }
}
#endif


oal_void hmac_dbdc_need_kick_user(mac_vap_stru *pst_mac_vap, mac_device_stru *pst_mac_dev)
{
    oal_uint8 uc_vap_idx;
    mac_vap_stru *pst_another_vap = OAL_PTR_NULL;
    mac_cfg_kick_user_param_stru st_kick_user_param;
    oal_uint8 auc_mac_addr[WLAN_MAC_ADDR_LEN] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

    if (pst_mac_dev->en_dbdc_running == OAL_FALSE) {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_UM, "hmac_dbdc_need_kick_user::dbdc running[%d] band[%d]",
                         pst_mac_dev->en_dbdc_running, pst_mac_vap->st_channel.en_band);
        return;
    }

    /* DBDC状态下，优先踢掉处于关联状态的用户 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_dev->uc_vap_num; uc_vap_idx++) {
        pst_another_vap = mac_res_get_mac_vap(pst_mac_dev->auc_vap_id[uc_vap_idx]);
        if (pst_another_vap == OAL_PTR_NULL) {
            continue;
        }

        if (pst_another_vap->uc_vap_id == pst_mac_vap->uc_vap_id) {
            continue;
        }

        if (pst_another_vap->en_vap_state >= MAC_VAP_STATE_STA_JOIN_COMP &&
            pst_another_vap->en_vap_state <= MAC_VAP_STATE_STA_WAIT_ASOC) {
            OAM_WARNING_LOG2(pst_another_vap->uc_vap_id, OAM_SF_UM,
                             "hmac_dbdc_need_kick_user::vap mode[%d] state[%d] kick user",
                             pst_another_vap->en_vap_mode, pst_another_vap->en_vap_state);

            st_kick_user_param.us_reason_code = MAC_UNSPEC_REASON;
            oal_set_mac_addr(st_kick_user_param.auc_mac_addr, auc_mac_addr);
            hmac_config_kick_user_etc(pst_another_vap, OAL_SIZEOF(oal_uint32), (oal_uint8 *)&st_kick_user_param);

            return;
        }
    }
}
OAL_STATIC oal_void hmac_user_del_destroy_timer(hmac_user_stru *pst_hmac_user)
{
    if (pst_hmac_user->st_mgmt_timer.en_is_registerd == OAL_TRUE) {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_user->st_mgmt_timer);
    }

    if (pst_hmac_user->st_defrag_timer.en_is_registerd == OAL_TRUE) {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_user->st_defrag_timer);
    }
}

oal_uint32 hmac_user_del_etc(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user)
{
    oal_uint16 us_user_index;
    frw_event_mem_stru *pst_event_mem = OAL_PTR_NULL;
    frw_event_stru *pst_event = OAL_PTR_NULL;
    dmac_ctx_del_user_stru *pst_del_user_payload = OAL_PTR_NULL;
    hmac_vap_stru *pst_hmac_vap = OAL_PTR_NULL;
    mac_device_stru *pst_mac_device = OAL_PTR_NULL;
    mac_user_stru *pst_mac_user = OAL_PTR_NULL;
    oal_uint32 ul_ret;
    mac_chip_stru *pst_mac_chip = OAL_PTR_NULL;
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_user_stru *pst_hmac_user_multi;
#endif
    mac_ap_type_enum_uint16 en_ap_type = 0;

#ifdef _PRE_WLAN_FEATURE_WMMAC
    oal_uint8 uc_ac_index = 0;
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_int8 pc_param[16] = { 0 };
    oal_int8 pc_tmp[8] = { 0 };
    oal_uint16 us_len;
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    frw_timeout_stru *pst_delba_opt_timer;
#endif

    if (OAL_UNLIKELY(OAL_ANY_NULL_PTR2(pst_mac_vap, pst_hmac_user))) {
        OAM_ERROR_LOG2(0, OAM_SF_UM, "{hmac_user_del_etc::param null,%x %x.}",
                       (uintptr_t)pst_mac_vap, (uintptr_t)pst_hmac_user);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user = (mac_user_stru *)(&pst_hmac_user->st_user_base_info);
    if (OAL_UNLIKELY(pst_mac_user == OAL_PTR_NULL)) {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_del_etc::pst_mac_user param null,%x.}", (uintptr_t)pst_mac_user);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev_etc(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(pst_mac_device == OAL_PTR_NULL)) {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del_etc::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_dbdc_need_kick_user(pst_mac_vap, pst_mac_device);

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                     "{hmac_user_del_etc::del user[%d] start,is multi user[%d], user mac:XX:XX:XX:XX:%02X:%02X}",
                     pst_mac_user->us_assoc_id, pst_mac_user->en_is_multi_user, pst_mac_user->auc_user_mac_addr[4],
                     pst_mac_user->auc_user_mac_addr[5]);

#ifdef _PRE_WLAN_FEATURE_HIEX
    hmac_hiex_user_exit(pst_mac_vap, pst_hmac_user);
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    pst_delba_opt_timer = &pst_hmac_user->st_hmac_user_btcoex.st_hmac_btcoex_arp_req_process.st_delba_opt_timer;

    /* 清理arp探测timer */
    if (pst_delba_opt_timer->en_is_registerd == OAL_TRUE) {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(
            &(pst_hmac_user->st_hmac_user_btcoex.st_hmac_btcoex_arp_req_process.st_delba_opt_timer));
    }
#endif

    /* 删除user时候，需要更新保护机制 */
    ul_ret = hmac_protection_del_user_etc(pst_mac_vap, &(pst_hmac_user->st_user_base_info));
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{hmac_user_del_etc::hmac_protection_del_user_etc[%d]}", ul_ret);
    }

    /* 删除用户统计保护相关的信息，向dmac同步然后设置相应的保护模式 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_AP) {
        ul_ret = hmac_user_protection_sync_data(pst_mac_vap);
        if (ul_ret != OAL_SUCC) {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                             "{hmac_ap_up_update_sta_user::protection update mib failed, ret=%d.}", ul_ret);
        }
    }
#endif

    /* 获取用户对应的索引 */
    us_user_index = pst_hmac_user->st_user_base_info.us_assoc_id;

    /* 删除hmac user 的关联请求帧空间 */
    hmac_user_free_asoc_req_ie(pst_hmac_user->st_user_base_info.us_assoc_id);

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    hmac_stop_sa_query_timer(pst_hmac_user);
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
    hmac_proxy_remove_mac(pst_mac_vap, pst_hmac_user->st_user_base_info.auc_user_mac_addr);
#endif

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (pst_hmac_vap == OAL_PTR_NULL) {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del_etc::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_VOWIFI
    if (pst_hmac_vap->st_vap_base_info.pst_vowifi_cfg_param != OAL_PTR_NULL) {
        if (pst_hmac_vap->st_vap_base_info.pst_vowifi_cfg_param->en_vowifi_mode == VOWIFI_LOW_THRES_REPORT) {
            /* 针对漫游和去关联场景,切换vowifi语音状态 */
            hmac_config_vowifi_report_etc((&pst_hmac_vap->st_vap_base_info), 0, OAL_PTR_NULL);
        }
    }
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

    pst_mac_chip = hmac_res_get_mac_chip(pst_mac_device->uc_chip_id);
    if (pst_mac_chip == OAL_PTR_NULL) {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del_etc::pst_mac_chip null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_wapi_deinit_etc(&pst_hmac_user->st_wapi);

    /* STA模式下，清组播wapi加密端口 */
    pst_hmac_user_multi = (hmac_user_stru *)mac_res_get_hmac_user_etc(pst_hmac_vap->st_vap_base_info.us_multi_user_idx);
    if (pst_hmac_user_multi == OAL_PTR_NULL) {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                       "{hmac_user_del_etc::mac_res_get_hmac_user_etc fail! user_idx[%u]}",
                       pst_hmac_vap->st_vap_base_info.us_multi_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_wapi_reset_port_etc(&pst_hmac_user_multi->st_wapi);

    pst_mac_device->uc_wapi = OAL_FALSE;

#endif

#if defined(_PRE_WLAN_FEATURE_MCAST) || defined(_PRE_WLAN_FEATURE_HERA_MCAST)
    /* 用户去关联时清空snoop链表中的该成员 */
    if (pst_hmac_vap->pst_m2u != OAL_PTR_NULL) {
        hmac_m2u_cleanup_snoopwds_node(pst_hmac_user);
    }
#endif

    if (pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_STA) {
        hmac_device_create_random_mac_addr_etc(pst_mac_device, pst_mac_vap);

#ifdef _PRE_WLAN_FEATURE_STA_PM
        mac_vap_set_aid_etc(pst_mac_vap, 0);
        /* fastsleep可能修改ps mode，去关联时重置 */
        pst_hmac_vap->uc_ps_mode = wlan_ps_mode;
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
        
        hmac_roam_wpas_connect_state_notify_etc(pst_hmac_vap, WPAS_CONNECT_STATE_IPADDR_REMOVED);

        hmac_roam_exit_etc(pst_hmac_vap);
#endif  // _PRE_WLAN_FEATURE_ROAM

        en_ap_type = hmac_compability_ap_tpye_identify_etc(pst_mac_vap, pst_mac_user->auc_user_mac_addr);
    }

    /* 删除对应wds节点 */
#if defined(_PRE_WLAN_FEATURE_WDS) || defined(_PRE_WLAN_FEATURE_VIRTUAL_MULTI_STA)
    if ((pst_hmac_user->uc_is_wds == OAL_TRUE) &&
        (OAL_SUCC != hmac_wds_del_node(pst_hmac_vap, pst_mac_user->auc_user_mac_addr))) {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del_etc::hmac_wds_del_node fail.}");
    }
#endif

    /***************************************************************************
        抛事件到DMAC层, 删除dmac用户
    ***************************************************************************/
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_del_user_stru));
    if (OAL_UNLIKELY(pst_event_mem == OAL_PTR_NULL)) {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del_etc::pst_event_mem null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = frw_get_event_stru(pst_event_mem);
    pst_del_user_payload = (dmac_ctx_del_user_stru *)pst_event->auc_event_data;
    pst_del_user_payload->us_user_idx = us_user_index;
    pst_del_user_payload->en_ap_type = en_ap_type;
#if (_PRE_OS_VERSION_WIN32 != _PRE_OS_VERSION)
    /* TBD: 添加此操作51DMT异常，暂看不出异常原因 */
    /* 用户 mac地址和idx 需至少一份有效，供dmac侧查找待删除的用户 */
    memcpy_s(pst_del_user_payload->auc_user_mac_addr, WLAN_MAC_ADDR_LEN,
             pst_mac_user->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
#endif

    /* 填充事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_DEL_USER,
                       OAL_SIZEOF(dmac_ctx_del_user_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    ul_ret = frw_event_dispatch_event_etc(pst_event_mem);
    if (OAL_UNLIKELY(ul_ret != OAL_SUCC)) {
        /* 做维测，如果删除用户失败，前面清hmac资源的操作本身已经异常，需要定位 */
        FRW_EVENT_FREE(pst_event_mem);
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                       "{hmac_user_del_etc::frw_event_dispatch_event_etc failed[%d].}", ul_ret);
        return ul_ret;
    }

    FRW_EVENT_FREE(pst_event_mem);

#ifdef _PRE_WLAN_FEATURE_SMPS
    /* 删除用户，更新SMPS能力 */
    mac_user_set_sm_power_save(&pst_hmac_user->st_user_base_info, 0);
#endif

#if defined(_PRE_PRODUCT_ID_HI110X_HOST) && defined(_PRE_WLAN_FEATURE_WMMAC)
    /* 删除user时删除发送addts req超时定时器 */
    for (uc_ac_index = 0; uc_ac_index < WLAN_WME_AC_BUTT; uc_ac_index++) {
        if (pst_hmac_user->st_user_base_info.st_ts_info[uc_ac_index].st_addts_timer.en_is_registerd == OAL_TRUE) {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(
                &(pst_hmac_user->st_user_base_info.st_ts_info[uc_ac_index].st_addts_timer));
        }

        memset_s(&(pst_hmac_user->st_user_base_info.st_ts_info[uc_ac_index]),
                 OAL_SIZEOF(mac_ts_stru), 0,
                 OAL_SIZEOF(mac_ts_stru));
        pst_hmac_user->st_user_base_info.st_ts_info[uc_ac_index].uc_tsid = 0xFF;
    }
#endif  // #if defined(_PRE_PRODUCT_ID_HI110X_HOST) && defined(_PRE_WLAN_FEATURE_WMMAC)

    hmac_tid_clear_etc(pst_mac_vap, pst_hmac_user);
    hmac_user_del_destroy_timer(pst_hmac_user);

    /* 从vap中删除用户 */
    mac_vap_del_user_etc(pst_mac_vap, us_user_index);
    hmac_arp_probe_destory(pst_hmac_vap, pst_hmac_user);

    hmac_chan_update_40M_intol_user_etc(pst_mac_vap);

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (pst_mac_vap->us_user_nums == 5) {
        /* AP用户达到5时，调整流控参数为配置文件原有值 */
        oal_itoa(hwifi_get_init_value_etc(CUS_TAG_INI, WLAN_CFG_INIT_USED_MEM_FOR_START), pc_param, 5);
        oal_itoa(hwifi_get_init_value_etc(CUS_TAG_INI, WLAN_CFG_INIT_USED_MEM_FOR_STOP), pc_tmp, 5);
        pc_param[OAL_STRLEN(pc_param)] = ' ';
        if (EOK != memcpy_s(pc_param + OAL_STRLEN(pc_param), sizeof(pc_param) - OAL_STRLEN(pc_param),
                            pc_tmp, OAL_STRLEN(pc_tmp))) {
            OAM_ERROR_LOG0(0, OAM_SF_UM, "hmac_user_del_etc::memcpy fail!");
            return OAL_FAIL;
        }

        us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);
        hmac_config_sdio_flowctrl_etc(pst_mac_vap, us_len, pc_param);
    }
#endif
#endif
    /* 释放用户内存 */
    ul_ret = hmac_user_free_etc(us_user_index);
    if (ul_ret == OAL_SUCC) {
        /* chip下已关联user个数-- */
        mac_chip_dec_assoc_user(pst_mac_chip);
    } else {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_del_etc::mac_res_free_mac_user_etc fail[%d].}", ul_ret);
    }

#ifdef _PRE_SUPPORT_ACS
    hmac_acs_register_rescan_timer(pst_mac_vap->uc_device_id);
#endif

    if (pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_STA) {
        hmac_fsm_change_state_etc(pst_hmac_vap, MAC_VAP_STATE_STA_FAKE_UP);
    }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 删除5G用户时需考虑是不是切为SDIO */
    hmac_pcie_to_sdio_switch(pst_mac_chip);
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
    pst_hmac_vap->en_roam_prohibit_on = OAL_FALSE;
#endif

    return OAL_SUCC;
}


oal_uint32 hmac_user_add_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint16 *pus_user_index)
{
    hmac_vap_stru *pst_hmac_vap = OAL_PTR_NULL;
    hmac_user_stru *pst_hmac_user = OAL_PTR_NULL;
    oal_uint32 ul_ret;
    frw_event_mem_stru *pst_event_mem = OAL_PTR_NULL;
    frw_event_stru *pst_event = OAL_PTR_NULL;
    dmac_ctx_add_user_stru *pst_add_user_payload = OAL_PTR_NULL;
    oal_uint16 us_user_idx;
    mac_cfg_80211_ucast_switch_stru st_80211_ucast_switch;
    mac_ap_type_enum_uint16 en_ap_type = 0;
    mac_chip_stru *pst_mac_chip = OAL_PTR_NULL;
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_int8 pc_param[] = "30 25";
    oal_uint16 us_len;
#endif
#endif
#ifdef _PRE_WLAN_FEATURE_WAPI
    mac_device_stru *pst_mac_device;
#endif
    mac_bss_dscr_stru *pst_bss_dscr = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_ANY_NULL_PTR3(pst_mac_vap, puc_mac_addr, pus_user_index))) {
        OAM_ERROR_LOG3(0, OAM_SF_UM, "{hmac_user_add_etc::param null, %x %x %x.}",
            (uintptr_t)pst_mac_vap, (uintptr_t)puc_mac_addr, (uintptr_t)pus_user_index);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (pst_hmac_vap == OAL_PTR_NULL) {
        OAM_WARNING_LOG0(0, OAM_SF_UM, "{hmac_user_add_etc::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_WAPI
    pst_mac_device = mac_res_get_dev_etc(pst_mac_vap->uc_device_id);
    if (pst_mac_device == OAL_PTR_NULL) {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add_etc::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    pst_mac_chip = hmac_res_get_mac_chip(pst_mac_vap->uc_chip_id);
    if (pst_mac_chip == OAL_PTR_NULL) {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add_etc::pst_mac_chip null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* chip级别最大用户数判断 */
    if (pst_mac_chip->uc_assoc_user_cnt >= mac_chip_get_max_asoc_user(pst_mac_chip->uc_chip_id)) {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{hmac_user_add_etc::invalid uc_assoc_user_cnt[%d].}",
                         pst_mac_chip->uc_assoc_user_cnt);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    if (pst_hmac_vap->st_vap_base_info.us_user_nums >= mac_mib_get_MaxAssocUserNums(pst_mac_vap)) {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_user_add_etc::invalid us_user_nums[%d], us_user_nums_max[%d].}",
                         pst_hmac_vap->st_vap_base_info.us_user_nums, mac_mib_get_MaxAssocUserNums(pst_mac_vap));
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    /* 如果此用户已经创建，则返回失败 */
    ul_ret = mac_vap_find_user_by_macaddr_etc(pst_mac_vap, puc_mac_addr, &us_user_idx);
    if (ul_ret == OAL_SUCC) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_user_add_etc::mac_vap_find_user_by_macaddr_etc success[%d].}", ul_ret);
        return OAL_FAIL;
    }

    if (pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_STA) {
#ifdef _PRE_WLAN_FEATURE_P2P
        if (IS_P2P_CL(pst_mac_vap)) {
            if (pst_hmac_vap->st_vap_base_info.us_user_nums >= 2) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                                 "{hmac_user_add_etc::a STA can only associated with 2 ap.}");
                return OAL_FAIL;
            }
        } else
#endif
        {
            if (pst_hmac_vap->st_vap_base_info.us_user_nums >= 1) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                                 "{hmac_user_add_etc::a STA can only associated with one ap.}");
                return OAL_FAIL;
            }
            en_ap_type = hmac_compability_ap_tpye_identify_etc(pst_mac_vap, puc_mac_addr);
        }
#ifdef _PRE_WLAN_FEATURE_ROAM
        hmac_roam_init_etc(pst_hmac_vap);
#endif  // _PRE_WLAN_FEATURE_ROAM
    }

    /* 申请hmac用户内存，并初始清0 */
    ul_ret = hmac_user_alloc_etc(&us_user_idx);
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_user_add_etc::hmac_user_alloc_etc failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 单播用户不能使用userid为0，需重新申请一个。将userid作为aid分配给对端，处理psm时会出错 */
    if (us_user_idx == 0) {
        hmac_user_free_etc(us_user_idx);
        ul_ret = hmac_user_alloc_etc(&us_user_idx);
        if ((ul_ret != OAL_SUCC) || (us_user_idx == 0)) {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                             "{hmac_user_add_etc::hmac_user_alloc_etc failed ret[%d] us_user_idx[%d].}",
                             ul_ret, us_user_idx);
            return ul_ret;
        }
    }

    *pus_user_index = us_user_idx; /* 出参赋值 */

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_idx);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add_etc::pst_hmac_user[%d] null}", us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_user->en_user_ap_type = en_ap_type; /* AP类型 */

    /* 初始化mac_user_stru */
    mac_user_init_etc(&(pst_hmac_user->st_user_base_info), us_user_idx, puc_mac_addr,
                      pst_mac_vap->uc_chip_id,
                      pst_mac_vap->uc_device_id,
                      pst_mac_vap->uc_vap_id);
    mac_user_init_rom(&(pst_hmac_user->st_user_base_info), us_user_idx);

#ifdef _PRE_WLAN_FEATURE_WAPI
    /* 初始化单播wapi对象 */
    hmac_wapi_init_etc(&pst_hmac_user->st_wapi, OAL_TRUE);
    pst_mac_device->uc_wapi = OAL_FALSE;
#endif

#ifdef _PRE_WLAN_FEATURE_HIEX
    hmac_hiex_user_init(pst_hmac_user);
#endif

    /* 设置amsdu域 */
    hmac_amsdu_init_user_etc(pst_hmac_user);

    pst_hmac_user->uc_tx_ba_limit = DMAC_UCAST_FRAME_TX_COMP_TIMES;

    /***************************************************************************
        抛事件到DMAC层, 创建dmac用户
    ***************************************************************************/
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_add_user_stru));
    if (OAL_UNLIKELY(pst_event_mem == OAL_PTR_NULL)) {
        /* 异常处理，释放内存，device下关联用户数还没有++，这里不需要判断返回值做--操作 */
        hmac_user_free_etc(us_user_idx);

        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add_etc::pst_event_mem null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = frw_get_event_stru(pst_event_mem);
    pst_add_user_payload = (dmac_ctx_add_user_stru *)pst_event->auc_event_data;
    pst_add_user_payload->us_user_idx = us_user_idx;
    pst_add_user_payload->en_ap_type = en_ap_type;
    oal_set_mac_addr(pst_add_user_payload->auc_user_mac_addr, puc_mac_addr);

    /* 获取扫描的bss信息 */
    pst_bss_dscr = (mac_bss_dscr_stru *)hmac_scan_get_scanned_bss_by_bssid(pst_mac_vap, puc_mac_addr);
    pst_add_user_payload->c_rssi = (pst_bss_dscr != OAL_PTR_NULL) ?
        pst_bss_dscr->c_rssi : oal_get_real_rssi((oal_int16)OAL_RSSI_INIT_MARKER);

    /* 填充事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_ADD_USER,
                       OAL_SIZEOF(dmac_ctx_add_user_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    ul_ret = frw_event_dispatch_event_etc(pst_event_mem);
    if (OAL_UNLIKELY(ul_ret != OAL_SUCC)) {
        /* 异常处理，释放内存，device下关联用户数还没有++，这里不需要判断返回值做--操作 */
        hmac_user_free_etc(us_user_idx);
        FRW_EVENT_FREE(pst_event_mem);
        /* 不应该出现用户添加失败，失败需要定位具体原因 */
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                       "{hmac_user_add_etc::frw_event_dispatch_event_etc failed[%d].}", ul_ret);
        return ul_ret;
    }

    FRW_EVENT_FREE(pst_event_mem);

    /* 添加用户到MAC VAP */
    ul_ret = mac_vap_add_assoc_user_etc(pst_mac_vap, us_user_idx);
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_user_add_etc::mac_vap_add_assoc_user_etc failed[%d].}", ul_ret);

        /* 异常处理，释放内存，device下关联用户数还没有++，这里不需要判断返回值做--操作 */
        hmac_user_free_etc(us_user_idx);
        return OAL_FAIL;
    }

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (pst_mac_vap->us_user_nums == 6) {
        /* AP用户达到6时，调整流控参数为Stop为25，Start为30 */
        us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);
        hmac_config_sdio_flowctrl_etc(pst_mac_vap, us_len, pc_param);
    }
#endif
#endif

    /* 初始话hmac user部分信息 */
    hmac_user_init_etc(pst_hmac_user);
    hmac_arp_probe_init(pst_hmac_vap, pst_hmac_user);
    mac_chip_inc_assoc_user(pst_mac_chip);

    /* 打开80211单播管理帧开关，观察关联过程，关联成功了就关闭 */
    st_80211_ucast_switch.en_frame_direction = OAM_OTA_FRAME_DIRECTION_TYPE_TX;
    st_80211_ucast_switch.en_frame_type = OAM_USER_TRACK_FRAME_TYPE_MGMT;
    st_80211_ucast_switch.en_frame_switch = OAL_SWITCH_ON;
    st_80211_ucast_switch.en_cb_switch = OAL_SWITCH_ON;
    st_80211_ucast_switch.en_dscr_switch = OAL_SWITCH_ON;
    if (EOK != memcpy_s(st_80211_ucast_switch.auc_user_macaddr,
                        OAL_SIZEOF(st_80211_ucast_switch.auc_user_macaddr),
                        (const oal_void *)puc_mac_addr,
                        OAL_SIZEOF(st_80211_ucast_switch.auc_user_macaddr))) {
        OAM_ERROR_LOG0(0, OAM_SF_UM, "hmac_user_add_etc::memcpy fail!");
        return OAL_FAIL;
    }
    hmac_config_80211_ucast_switch_etc(pst_mac_vap, OAL_SIZEOF(st_80211_ucast_switch),
                                       (oal_uint8 *)&st_80211_ucast_switch);

    st_80211_ucast_switch.en_frame_direction = OAM_OTA_FRAME_DIRECTION_TYPE_RX;
    st_80211_ucast_switch.en_frame_type = OAM_USER_TRACK_FRAME_TYPE_MGMT;
    st_80211_ucast_switch.en_frame_switch = OAL_SWITCH_ON;
    st_80211_ucast_switch.en_cb_switch = OAL_SWITCH_ON;
    st_80211_ucast_switch.en_dscr_switch = OAL_SWITCH_ON;
    hmac_config_80211_ucast_switch_etc(pst_mac_vap, OAL_SIZEOF(st_80211_ucast_switch),
                                       (oal_uint8 *)&st_80211_ucast_switch);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 添加5G用户时需考虑是不是切为PCIE */
    hmac_sdio_to_pcie_switch(pst_mac_vap);
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
    if (en_ap_type & MAC_AP_TYPE_ROAM) {
        pst_hmac_vap->en_roam_prohibit_on = OAL_TRUE;
    } else {
        pst_hmac_vap->en_roam_prohibit_on = OAL_FALSE;
    }
#endif

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add_etc::user[%d] mac:%02X:XX:XX:XX:%02X:%02X}",
                     us_user_idx,
                     puc_mac_addr[0],
                     puc_mac_addr[4],
                     puc_mac_addr[5]);

    return OAL_SUCC;
}


oal_uint32 hmac_config_add_user_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_add_user_param_stru *pst_add_user = OAL_PTR_NULL;
    oal_uint16 us_user_index;
    hmac_vap_stru *pst_hmac_vap = OAL_PTR_NULL;
    hmac_user_stru *pst_hmac_user = OAL_PTR_NULL;
    oal_uint32 ul_ret;
    mac_user_ht_hdl_stru st_ht_hdl;
    oal_uint32 ul_rslt;
    mac_device_stru *pst_mac_device = OAL_PTR_NULL;
    mac_chip_stru *pst_mac_chip = OAL_PTR_NULL;

    pst_add_user = (mac_cfg_add_user_param_stru *)puc_param;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    if (pst_hmac_vap == OAL_PTR_NULL) {
        OAM_WARNING_LOG0(0, OAM_SF_UM, "{hmac_config_add_user_etc::pst_hmac_vap null.}");
        return OAL_FAIL;
    }

    ul_ret = hmac_user_add_etc(pst_mac_vap, pst_add_user->auc_mac_addr, &us_user_index);
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_config_add_user_etc::hmac_user_add_etc failed.}", ul_ret);
        return ul_ret;
    }

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_index);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_config_add_user_etc::pst_hmac_user[%d] null.}", us_user_index);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD hmac_config_add_user_etc 此接口删除，相应调用需要整改，duankaiyong&guyanjie */
    /* 设置qos域，后续如有需要可以通过配置命令参数配置 */
    mac_user_set_qos_etc(&pst_hmac_user->st_user_base_info, OAL_TRUE);

    /* 设置HT域 */
    mac_user_get_ht_hdl_etc(&pst_hmac_user->st_user_base_info, &st_ht_hdl);
    st_ht_hdl.en_ht_capable = pst_add_user->en_ht_cap;

    if (pst_add_user->en_ht_cap == OAL_TRUE) {
        pst_hmac_user->st_user_base_info.en_cur_protocol_mode = WLAN_HT_MODE;
        pst_hmac_user->st_user_base_info.en_avail_protocol_mode = WLAN_HT_MODE;
    }

    /* 设置HT相关的信息:应该在关联的时候赋值 这个值配置的合理性有待考究 2012->page:786 */
    st_ht_hdl.uc_min_mpdu_start_spacing = 6;
    st_ht_hdl.uc_max_rx_ampdu_factor = 3;
    mac_user_set_ht_hdl_etc(&pst_hmac_user->st_user_base_info, &st_ht_hdl);

    mac_user_set_asoc_state_etc(&pst_hmac_user->st_user_base_info, MAC_USER_STATE_ASSOC);

    /* 设置amsdu域 */
    hmac_amsdu_init_user_etc(pst_hmac_user);

    /***************************************************************************
        抛事件到DMAC层, 同步DMAC数据
    ***************************************************************************/
    /* 重新设置DMAC需要的参数 */
    pst_add_user->us_user_idx = us_user_index;

    ul_ret = hmac_config_send_event_etc(&pst_hmac_vap->st_vap_base_info,
                                        WLAN_CFGID_ADD_USER,
                                        us_len,
                                        puc_param);
    if (OAL_UNLIKELY(ul_ret != OAL_SUCC)) {
        /* 异常处理，释放内存 */
        ul_rslt = hmac_user_free_etc(us_user_index);
        if (ul_rslt == OAL_SUCC) {
            pst_mac_device = mac_res_get_dev_etc(pst_mac_vap->uc_device_id);
            if (pst_mac_device == OAL_PTR_NULL) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_add_user_etc::pst_mac_device null.}");
                return OAL_ERR_CODE_PTR_NULL;
            }

            pst_mac_chip = hmac_res_get_mac_chip(pst_mac_device->uc_chip_id);
            if (pst_mac_chip == OAL_PTR_NULL) {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add_etc::pst_mac_chip null.}");
                return OAL_ERR_CODE_PTR_NULL;
            }

            /* hmac_add_user成功时chip下关联用户数已经++, 这里的chip下已关联user个数要-- */
            mac_chip_dec_assoc_user(pst_mac_chip);
        }

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_config_add_user_etc::hmac_config_send_event_etc failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 增加用户后通知算法初始化用户结构体 */
    hmac_user_add_notify_alg_etc(&pst_hmac_vap->st_vap_base_info, us_user_index);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (IS_LEGACY_VAP(pst_mac_vap)) {
        mac_vap_state_change_etc(pst_mac_vap, MAC_VAP_STATE_UP);
    }
#endif

    return OAL_SUCC;
}


oal_uint32 hmac_config_del_user_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_del_user_param_stru *pst_del_user = OAL_PTR_NULL;
    hmac_user_stru *pst_hmac_user = OAL_PTR_NULL;
    hmac_vap_stru *pst_hmac_vap;
    oal_uint16 us_user_index;
    oal_uint32 ul_ret;

    pst_del_user = (mac_cfg_add_user_param_stru *)puc_param;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    if (pst_hmac_vap == OAL_PTR_NULL) {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_del_user_etc::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取用户对应的索引 */
    ul_ret = mac_vap_find_user_by_macaddr_etc(pst_mac_vap, pst_del_user->auc_mac_addr, &us_user_index);
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_config_del_user_etc::mac_vap_find_user_by_macaddr_etc failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 获取hmac用户 */
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_index);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_config_del_user_etc::pst_hmac_user[%d] null.}", us_user_index);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_user_del_etc(pst_mac_vap, pst_hmac_user);
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_config_del_user_etc::hmac_user_del_etc failed[%d] device_id[%d].}",
                         ul_ret, pst_mac_vap->uc_device_id);
        return ul_ret;
    }

    return OAL_SUCC;
}


oal_uint32 hmac_user_add_multi_user_etc(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_user_index)
{
    oal_uint32 ul_ret;
    oal_uint16 us_user_index;
    mac_user_stru *pst_mac_user = OAL_PTR_NULL;
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_user_stru *pst_hmac_user;
#endif

    ul_ret = hmac_user_alloc_etc(&us_user_index);
    if (ul_ret != OAL_SUCC) {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                       "{hmac_user_add_multi_user_etc::hmac_user_alloc_etc failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 初始化组播用户基本信息 */
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user_etc(us_user_index);
    if (pst_mac_user == OAL_PTR_NULL) {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM,
                         "{hmac_user_add_multi_user_etc::pst_mac_user[%d] null.}", us_user_index);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_init_etc(pst_mac_user, us_user_index, OAL_PTR_NULL,
                      pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, pst_mac_vap->uc_vap_id);
    mac_user_init_rom(pst_mac_user, us_user_index);

    *pus_user_index = us_user_index;

#ifdef _PRE_WLAN_FEATURE_WAPI
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_index);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                       "{hmac_user_add_multi_user_etc::hmac_user[%d] null.}", us_user_index);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 初始化wapi对象 */
    hmac_wapi_init_etc(&pst_hmac_user->st_wapi, OAL_FALSE);
#endif

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                     "{hmac_user_add_multi_user_etc, user index[%d].}", us_user_index);

    return OAL_SUCC;
}


oal_uint32 hmac_user_del_multi_user_etc(mac_vap_stru *pst_mac_vap)
{
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_user_stru *pst_hmac_user;
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(pst_mac_vap->us_multi_user_idx);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_del_multi_user_etc::get hmac_user[%d] null.}",
                       pst_mac_vap->us_multi_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_wapi_deinit_etc(&pst_hmac_user->st_wapi);
#endif

    hmac_user_free_etc(pst_mac_vap->us_multi_user_idx);

    return OAL_SUCC;
}


#ifdef _PRE_WLAN_FEATURE_WAPI
oal_uint8 hmac_user_is_wapi_connected_etc(oal_uint8 uc_device_id)
{
    oal_uint8 uc_vap_idx;
    hmac_user_stru *pst_hmac_user_multi;
    mac_device_stru *pst_mac_device;
    mac_vap_stru *pst_mac_vap;

    pst_mac_device = mac_res_get_dev_etc(uc_device_id);
    if (OAL_UNLIKELY(pst_mac_device == OAL_PTR_NULL)) {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_is_wapi_connected_etc::pst_mac_device null.id %u}", uc_device_id);
        return OAL_FALSE;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++) {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(pst_mac_vap == OAL_PTR_NULL)) {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "vap is null! vap id is %d", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (!IS_STA(pst_mac_vap)) {
            continue;
        }

        pst_hmac_user_multi = (hmac_user_stru *)mac_res_get_hmac_user_etc(pst_mac_vap->us_multi_user_idx);
        if ((pst_hmac_user_multi != OAL_PTR_NULL)
            && (OAL_TRUE == WAPI_PORT_FLAG(&pst_hmac_user_multi->st_wapi))) {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}
#endif /* #ifdef _PRE_WLAN_FEATURE_WAPI */


oal_uint32 hmac_user_add_notify_alg_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx)
{
    frw_event_mem_stru *pst_event_mem = OAL_PTR_NULL;
    frw_event_stru *pst_event = OAL_PTR_NULL;
    dmac_ctx_add_user_stru *pst_add_user_payload = OAL_PTR_NULL;
    oal_uint32 ul_ret;
    hmac_user_stru *pst_hmac_user = OAL_PTR_NULL;

    /* 抛事件给Dmac，在dmac层挂用户算法钩子 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_add_user_stru));
    if (OAL_UNLIKELY(pst_event_mem == OAL_PTR_NULL)) {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_add_notify_alg_etc::pst_event_mem null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = frw_get_event_stru(pst_event_mem);
    pst_add_user_payload = (dmac_ctx_add_user_stru *)pst_event->auc_event_data;
    pst_add_user_payload->us_user_idx = us_user_idx;
    pst_add_user_payload->us_sta_aid = pst_mac_vap->us_sta_aid;
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user_etc(us_user_idx);
    if (OAL_UNLIKELY(pst_hmac_user == OAL_PTR_NULL)) {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{hmac_user_add_notify_alg_etc::null param,pst_hmac_user[%d].}", us_user_idx);
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_get_vht_hdl_etc(&pst_hmac_user->st_user_base_info, &pst_add_user_payload->st_vht_hdl);
    mac_user_get_ht_hdl_etc(&pst_hmac_user->st_user_base_info, &pst_add_user_payload->st_ht_hdl);
    /* 填充事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_NOTIFY_ALG_ADD_USER,
                       OAL_SIZEOF(dmac_ctx_add_user_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    ul_ret = frw_event_dispatch_event_etc(pst_event_mem);
    if (OAL_UNLIKELY(ul_ret != OAL_SUCC)) {
        /* 异常处理，释放内存 */
        FRW_EVENT_FREE(pst_event_mem);

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                         "{hmac_user_add_notify_alg_etc::frw_event_dispatch_event_etc failed[%d].}", ul_ret);
        return ul_ret;
    }
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}


hmac_user_stru *mac_vap_get_hmac_user_by_addr_etc(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr)
{
    oal_uint32 ul_ret;
    oal_uint16 us_user_idx = 0xffff;
    hmac_user_stru *pst_hmac_user = OAL_PTR_NULL;

    /* 根据mac addr找sta索引 */
    ul_ret = mac_vap_find_user_by_macaddr_etc(pst_mac_vap, puc_mac_addr, &us_user_idx);
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG1(0, OAM_SF_ANY,
                         "{mac_vap_get_hmac_user_by_addr_etc::find_user_by_macaddr failed[%d].}", ul_ret);
        if (puc_mac_addr != OAL_PTR_NULL) {
            OAM_WARNING_LOG3(0, OAM_SF_ANY, "{mac_vap_get_hmac_user_by_addr_etc:: mac_addr[%02x XX XX XX %02x %02x]!.}",
                             puc_mac_addr[0], puc_mac_addr[4], puc_mac_addr[5]);
        }
        return OAL_PTR_NULL;
    }

    /* 根据sta索引找到user内存区域 */
    pst_hmac_user = mac_res_get_hmac_user_etc(us_user_idx);
    if (pst_hmac_user == OAL_PTR_NULL) {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_vap_get_hmac_user_by_addr_etc::user[%d] ptr null.}", us_user_idx);
    }
    return pst_hmac_user;
}


oal_void hmac_user_set_amsdu_level(hmac_user_stru *pst_hmac_user,
    wlan_tx_amsdu_enum_uint8 en_amsdu_level)
{
    pst_hmac_user->en_amsdu_level = en_amsdu_level;

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_user_set_amsdu_level::en_amsdu_level=[%d].}",
        pst_hmac_user->en_amsdu_level);
}


oal_void hmac_user_set_amsdu_level_by_max_mpdu_len(hmac_user_stru *pst_hmac_user,
    oal_uint16 us_max_mpdu_len)
{
    wlan_tx_amsdu_enum_uint8 en_amsdu_level;

    if (us_max_mpdu_len == 3895) {
        en_amsdu_level = WLAN_TX_AMSDU_BY_2;
    } else {
        en_amsdu_level = WLAN_TX_AMSDU_BY_4;
    }

    hmac_user_set_amsdu_level(pst_hmac_user, en_amsdu_level);
}

oal_void hmac_user_set_close_ht_flag(mac_vap_stru *p_mac_vap, hmac_user_stru *p_hmac_user)
{
    if (p_mac_vap->en_protocol >= WLAN_HT_MODE) {
        return;
    }

    /* 首次入网 */
    if (p_mac_vap->en_vap_state != MAC_VAP_STATE_ROAMING) {
        if (hmac_ht_self_cure_in_blacklist(p_hmac_user->st_user_base_info.auc_user_mac_addr)) {
            p_hmac_user->closeHtFalg = OAL_TRUE;

            OAM_WARNING_LOG4(0, OAM_SF_SCAN, "hmac_user_set_close_ht_flag::closeHtFalg=%d, %02X:XX:XX:XX:%02X:%02X",
                p_hmac_user->closeHtFalg,
                p_hmac_user->st_user_base_info.auc_user_mac_addr[0],
                p_hmac_user->st_user_base_info.auc_user_mac_addr[4],
                p_hmac_user->st_user_base_info.auc_user_mac_addr[5]);
        }
    }

}

oal_void hmac_user_cap_update_by_hisi_cap_ie(hmac_user_stru *pst_hmac_user,
    oal_uint8 *puc_payload, oal_uint32 ul_msg_len)
{
    mac_hisi_cap_vendor_ie_stru st_hisi_cap_ie;

    pst_hmac_user->st_user_base_info.st_cap_info.bit_p2p_support_csa = OAL_FALSE;
    pst_hmac_user->st_user_base_info.st_cap_info.bit_support_he_cap  = OAL_FALSE;
    pst_hmac_user->st_user_base_info.st_cap_info.bit_dcm_cap         = OAL_FALSE;

    if (mac_get_hisi_cap_vendor_ie(puc_payload, ul_msg_len, &st_hisi_cap_ie) == OAL_SUCC) {
        pst_hmac_user->st_user_base_info.st_cap_info.bit_support_he_cap  =
            st_hisi_cap_ie.bit_11ax_support;
        pst_hmac_user->st_user_base_info.st_cap_info.bit_dcm_cap         =
            st_hisi_cap_ie.bit_dcm_support;
        pst_hmac_user->st_user_base_info.st_cap_info.bit_p2p_support_csa =
            st_hisi_cap_ie.bit_p2p_csa_support;
    }
}

/*lint -e19*/
oal_module_symbol(hmac_user_alloc_etc);
oal_module_symbol(hmac_user_init_etc);
oal_module_symbol(hmac_config_kick_user_etc);
oal_module_symbol(mac_vap_get_hmac_user_by_addr_etc);
oal_module_symbol(mac_res_get_hmac_user_etc);
oal_module_symbol(hmac_user_free_asoc_req_ie);
oal_module_symbol(hmac_user_set_asoc_req_ie); /*lint +e19*/
