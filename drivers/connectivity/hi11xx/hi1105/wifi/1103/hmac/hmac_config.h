

#ifndef __HMAC_CONFIG_H__
#define __HMAC_CONFIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* 1 其他头文件包含 */
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "hmac_device.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CONFIG_H

/* 2 宏定义 */
#define HMAC_MAX_MCS_NUM               8 /* 单流和双流支持的mac最大个数 */
#define HAMC_QUERY_INFO_FROM_DMAC_TIME (5 * OAL_TIME_HZ)
#define HMAC_WAIT_EVENT_RSP_TIME 10 /* 等待配置命令事件完成的超时时间(s) */
#define HMAC_S_TO_MS 1000   /* 秒和毫秒的转换系数 */
#ifdef _PRE_SUPPORT_ACS
#define HMAC_SET_RESCAN_TIMEOUT_CHECK(_pst_hmac_device, _ul_bak) \
    do {                                                         \
        if (!(_pst_hmac_device)->ul_rescan_timeout) {            \
            (_pst_hmac_device)->ul_rescan_timeout = (_ul_bak);   \
        }                                                        \
    } while (0)
#endif
/* 3 枚举定义 */
/* APUT OWE group definition, hipriv.sh BIT format transit to pst_hmac_vap->owe_group */
#define WAL_HIPRIV_OWE_19 BIT(0)
#define WAL_HIPRIV_OWE_20 BIT(1)
#define WAL_HIPRIV_OWE_21 BIT(2)
/* 4 全局变量声明 */
/* 5 消息头定义 */
/* 6 消息定义 */
/* 7 STRUCT定义 */
/* hmac_vap结构中，一部分成员的大小，这些成员在linux和windows下的定义可能不同 */
typedef struct {
    oal_uint32 ul_hmac_vap_cfg_priv_stru_size;
    oal_uint32 ul_frw_timeout_stru_size;
    oal_uint32 ul_oal_spin_lock_stru_size;
    oal_uint32 ul_mac_key_mgmt_stru_size;
    oal_uint32 ul_mac_pmkid_cache_stru_size;
    oal_uint32 ul_mac_curr_rateset_stru_size;
    oal_uint32 ul_hmac_vap_stru_size;
} hmac_vap_member_size_stru;

/* 8 UNION定义 */
/* 9 OTHERS定义 */
/* 10 函数声明 */
extern oal_uint32 hmac_config_start_vap_event_etc(mac_vap_stru *pst_mac_vap,
                                                  oal_bool_enum_uint8 en_mgmt_rate_init_flag);
extern oal_uint32 hmac_set_mode_event_etc(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_config_sta_update_rates_etc(mac_vap_stru *pst_mac_vap,
                                                   mac_cfg_mode_param_stru *pst_cfg_mode,
                                                   mac_bss_dscr_stru *pst_bss_dscr);
extern oal_uint32 hmac_event_config_syn_etc(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_event_log_syn(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_protection_update_from_user(mac_vap_stru *pst_mac_vap,
                                                   oal_uint16 us_len,
                                                   oal_uint8 *puc_param);
extern oal_uint32 hmac_40M_intol_sync_event(mac_vap_stru *pst_mac_vap,
                                            oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_tlv_cmd(mac_vap_stru *pst_mac_vap, oal_uint16 us_len,
                                          oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_str_cmd(mac_vap_stru *pst_mac_vap, oal_uint16 us_len,
                                          oal_uint8 *puc_param);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 hmac_get_thruput_info_etc(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len,
                                            oal_uint8 *puc_param);
extern oal_void hcc_msg_slave_thruput_bypass_etc(oal_void);
oal_uint32 hmac_config_set_tx_ampdu_type(mac_vap_stru *pst_mac_vap, oal_uint16 us_len,
                                         oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_STA_PM
extern oal_uint32 hmac_config_sta_pm_on_syn(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_set_ipaddr_timeout_etc(void *puc_para);
#endif
extern oal_uint32 hmac_config_pm_debug_switch(mac_vap_stru *pst_mac_vap,
                                              oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
extern oal_uint32 hmac_config_enable_arp_offload(mac_vap_stru *pst_mac_vap,
                                                 oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_set_ip_addr_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_show_arpoffload_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
oal_uint32 hmac_config_roam_enable_etc(mac_vap_stru *pst_mac_vap,
                                       oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_roam_org_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_roam_band_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_roam_start_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_roam_info_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif  // _PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_WLAN_FEATURE_11R
oal_uint32 hmac_config_set_ft_ies_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif  // _PRE_WLAN_FEATURE_11R

oal_uint32 hmac_config_enable_2040bss_etc(mac_vap_stru *pst_mac_vap,
                                          oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_get_2040bss_sw(mac_vap_stru *pst_mac_vap,
                                      oal_uint16 *pus_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_get_dieid_rsp(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_get_dieid(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#if (defined _PRE_WLAN_RF_CALI) || (defined _PRE_WLAN_RF_CALI_1151V2)
oal_uint32 hmac_config_auto_cali(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_get_cali_status(mac_vap_stru *pst_mac_vap,
                                       oal_uint16 *pus_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_cali_vref(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
oal_uint32 hmac_config_set_auto_freq_enable_etc(mac_vap_stru *pst_mac_vap,
                                                oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_FEATURE_WAVEAPP_CLASSIFY
oal_uint32 hmac_config_get_waveapp_flag_rsp(mac_vap_stru *pst_mac_vap,
                                            oal_uint8 uc_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_get_waveapp_flag(mac_vap_stru *pst_mac_vap,
                                        oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
oal_uint32 hmac_config_set_sta_pm_on_etc(mac_vap_stru *pst_mac_vap,
                                         oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_sta_pm_mode_etc(mac_vap_stru *pst_mac_vap,
                                           oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_fast_sleep_para_etc(mac_vap_stru *pst_mac_vap,
                                               oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_RX_LISTEN_POWER_SAVING
oal_uint32 hmac_config_set_rx_listen_ps_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len,
    oal_uint8 *puc_param);
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
oal_uint32 hmac_config_load_ini_power_gain(mac_vap_stru *pst_mac_vap,
                                           oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_all_log_level_etc(mac_vap_stru *pst_mac_vap,
                                             oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_cus_rf_etc(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_cus_dts_cali_etc(mac_vap_stru *pst_mac_vap,
                                            oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_cus_nvram_params_etc(mac_vap_stru *pst_mac_vap,
                                                oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_dev_customize_info_etc(mac_vap_stru *pst_mac_vap,
                                              oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_set_cus_dyn_cali(mac_vap_stru *pst_mac_vap,
                                        oal_uint16 us_len, oal_uint8 *puc_param);
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */
#if defined(_PRE_WLAN_FEATURE_11K)
oal_uint32 hmac_scan_rrm_proc_save_bss_etc(mac_vap_stru *pst_mac_vap,
                                           oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_VOWIFI
extern oal_uint32 hmac_config_vowifi_report_etc(mac_vap_stru *pst_mac_vap,
                                                oal_uint8 uc_len, oal_uint8 *puc_param);
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
extern oal_uint32 hmac_config_stop_altx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_RR_PERFORMENCE_DEBUG
extern oal_uint64 hmac_get_ktimestamp(oal_void);
extern oal_void hmac_rr_tx_w2h_timestamp(oal_void);
extern oal_void hmac_rr_tx_h2d_timestamp(oal_void);
extern oal_void hmac_rr_rx_d2h_timestamp(oal_void);
extern oal_void hmac_rr_rx_h2w_timestamp(oal_void);
#endif

#ifdef _PRE_WLAN_FEATURE_WDS
oal_uint32 hmac_config_wds_vap_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_wds_get_vap_mode(mac_vap_stru *pst_mac_vap,
                                        oal_uint16 *us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_wds_vap_show(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_wds_sta_add(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_wds_sta_del(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_wds_sta_age(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 hmac_config_wds_get_sta_num(mac_vap_stru *pst_mac_vap,
                                       oal_uint16 *us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_11K_STAT
extern oal_uint32 hmac_config_query_stat_info(mac_vap_stru *pst_mac_vap,
                                              oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_FTM
extern oal_uint32  hmac_config_ftm_dbg(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32  hmac_ftm_rx_gas_initial_response_frame(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf);

#endif
#ifdef _PRE_WLAN_FEATURE_APF
extern oal_uint32 hmac_config_apf_filter_cmd(mac_vap_stru *pst_mac_vap,
                                             oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32 hmac_config_remove_app_ie(mac_vap_stru *pst_mac_vap,
                                            oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_force_stop_filter(mac_vap_stru *pst_mac_vap,
                                                oal_uint16 us_len, oal_uint8 *puc_param);

extern oal_uint32 hmac_config_fem_lp_flag(mac_vap_stru *pst_mac_vap,
                                          oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_softap_mimo_mode(mac_vap_stru *pst_mac_vap,
                                               oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_IP_FILTER
extern oal_uint32 hmac_config_assigned_filter_etc(mac_vap_stru *pst_mac_vap,
                                                  oal_uint16 us_len, oal_uint8 *puc_param);
#endif

extern oal_uint32 hmac_config_set_owe_etc(mac_vap_stru *pst_mac_vap,
                                          oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_FEATURE_TWT
extern oal_uint32 hmac_get_chip_vap_num(mac_chip_stru *pst_chip);
extern oal_uint32 hmac_config_twt_setup_req_auto(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_config_twt_teardown_req_auto(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_config_twt_setup_req_etc(mac_vap_stru *pst_mac_vap,
                                                oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_twt_teardown_req_etc(mac_vap_stru *pst_mac_vap,
                                                   oal_uint16 us_len,
                                                   oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_MBO
extern oal_uint32 hmac_mbo_check_is_assoc_or_re_assoc_allowed(mac_vap_stru *pst_mac_vap,
                                                              mac_conn_param_stru *pst_connect_param,
                                                              mac_bss_dscr_stru *pst_bss_dscr);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of hmac_main */
