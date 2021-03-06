

#ifndef __HMAC_MGMT_CLASSIFIER_H__
#define __HMAC_MGMT_CLASSIFIER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* 1 其他头文件包含 */
#include "frw_ext_if.h"
#include "dmac_ext_if.h"
#include "hmac_vap.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_MGMT_CLASSIFIER_H
/* 2 宏定义 */
/* 3 枚举定义 */
/* 4 全局变量声明 */
/* 5 消息头定义 */
/* 6 消息定义 */
/* 7 STRUCT定义 */
/* 8 UNION定义 */
/* 9 OTHERS定义 */
/* 10 函数声明 */
#ifdef _PRE_WLAN_FEATURE_TWT
extern oal_uint32 hmac_mgmt_tx_twt_action_etc(hmac_vap_stru *pst_hmac_vap,
                                              hmac_user_stru *pst_hmac_user,
                                              mac_twt_action_mgmt_args_stru *pst_twt_action_args);
#endif
#ifdef _PRE_WLAN_FEATURE_MONITOR
extern oal_void hmac_sniffer_fill_radiotap(ieee80211_radiotap_stru *pst_radiotap,
                                           mac_rx_ctl_stru *pst_rx_ctrl,
                                           hal_sniffer_rx_status_stru *pst_rx_status,
                                           hal_sniffer_rx_statistic_stru *pst_sniffer_rx_statistic,
                                           oal_uint8 *puc_mac_hdr,
                                           oal_uint32 *pul_rate_kbps,
                                           hal_statistic_stru *pst_per_rate);
#endif

extern oal_uint32 hmac_rx_process_mgmt_event_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_mgmt_rx_delba_event_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_mgmt_tx_action_etc(hmac_vap_stru *pst_hmac_vap,
                                          hmac_user_stru *pst_hmac_user,
                                          mac_action_mgmt_args_stru *pst_action_args);
extern oal_uint32 hmac_mgmt_tx_priv_req_etc(hmac_vap_stru *pst_hmac_vap,
                                            hmac_user_stru *pst_hmac_user,
                                            mac_priv_req_args_stru *pst_priv_req);
extern oal_uint32 hmac_mgmt_tbtt_event_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_mgmt_send_disasoc_deauth_event_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_disasoc_misc_event_etc(frw_event_mem_stru *pst_event_mem);

#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32 hmac_proc_roam_trigger_event_etc(frw_event_mem_stru *pst_event_mem);
#endif  // _PRE_WLAN_FEATURE_ROAM

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of hmac_mgmt_classifier.h */
