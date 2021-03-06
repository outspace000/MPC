

/* 1 头文件包含 */
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "hmac_ext_if.h"
#include "wlan_spec.h"
#include "wal_main.h"
#ifdef _PRE_WLAN_FEATURE_IP_FILTER
#ifdef CONFIG_DOZE_FILTER
#include <huawei_platform/power/wifi_filter/wifi_filter.h>
#endif
#endif /* _PRE_WLAN_FEATURE_IP_FILTER */
#include "wal_config.h"
#include "wal_linux_ioctl.h"
#include "wal_linux_cfg80211.h"
#include "oal_cfg80211.h"
#include "oal_net.h"
#include "wal_linux_flowctl.h"
#include "wal_config_acs.h"

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
#include "oal_kernel_file.h"
#endif

#include "wal_dfx.h"

#include "hmac_vap.h"
#include "wal_linux_atcmdsrv.h"
#include "securec.h"
#include "securectype.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_MAIN_C
/* 2 全局变量定义 */
/* HOST CRX子表 */
OAL_STATIC frw_event_sub_table_item_stru g_ast_wal_host_crx_table[WAL_HOST_CRX_SUBTYPE_BUTT];

/* HOST CTX字表 */
OAL_STATIC frw_event_sub_table_item_stru g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_BUTT];

/* HOST DRX子表 */
/* wal对外钩子函数 */
oam_wal_func_hook_stru g_st_wal_drv_func_hook_etc;

oal_wakelock_stru g_st_wal_wakelock_etc;
#if (defined(_PRE_E5_722_PLATFORM) || defined(_PRE_CPE_711_PLATFORM) || defined(_PRE_CPE_722_PLATFORM))
oal_wakelock_stru g_st_wifi_wakelock;
#endif

#ifdef _PRE_WLAN_FEATURE_IP_FILTER
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
wal_hw_wlan_filter_ops g_st_ip_filter_ops_etc = {
    .set_filter_enable = wal_set_ip_filter_enable_etc,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 14, 0))
    .set_filter_enable_ex = wal_set_assigned_filter_enable_etc,
#endif
    .add_filter_items = wal_add_ip_filter_items_etc,
    .clear_filters = wal_clear_ip_filter_etc,
    .get_filter_pkg_stat = NULL,
};
#else
wal_hw_wlan_filter_ops g_st_ip_filter_ops_etc;
#endif
#endif /* _PRE_WLAN_FEATURE_IP_FILTER */

/* 3 函数实现 */

oal_uint32 wal_event_fsm_init_etc(oal_void)
{
    g_ast_wal_host_crx_table[WAL_HOST_CRX_SUBTYPE_CFG].p_func = wal_config_process_pkt_etc;
#ifdef _PRE_SUPPORT_ACS
    g_ast_wal_host_crx_table[WAL_HOST_CRX_SUBTYPE_CFG_ACS].p_func = wal_acs_netlink_recv_handle;
#endif
    frw_event_table_register_etc(FRW_EVENT_TYPE_HOST_CRX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_wal_host_crx_table);

    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_SCAN_COMP_STA].p_func = wal_scan_comp_proc_sta_etc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_ASOC_COMP_STA].p_func = wal_asoc_comp_proc_sta_etc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_DISASOC_COMP_STA].p_func = wal_disasoc_comp_proc_sta_etc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_STA_CONNECT_AP].p_func = wal_connect_new_sta_proc_ap_etc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_STA_DISCONNECT_AP].p_func = wal_disconnect_sta_proc_ap_etc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_MIC_FAILURE].p_func = wal_mic_failure_proc_etc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_RX_MGMT].p_func = wal_send_mgmt_to_host_etc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_LISTEN_EXPIRED].p_func = wal_p2p_listen_timeout_etc;

#ifdef _PRE_SUPPORT_ACS
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_ACS_RESPONSE].p_func = wal_acs_response_event_handler;
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_FLOWCTL_BACKP].p_func = wal_flowctl_backp_event_handler;
#endif

    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_INIT].p_func = wal_cfg80211_init_evt_handle_etc;
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_MGMT_TX_STATUS].p_func = wal_cfg80211_mgmt_tx_status_etc;

#ifdef _PRE_WLAN_FEATURE_ROAM
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_ROAM_COMP_STA].p_func = wal_roam_comp_proc_sta_etc;
#endif  // _PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_11R
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_FT_EVENT_STA].p_func = wal_ft_event_proc_sta_etc;
#endif  // _PRE_WLAN_FEATURE_11R
#ifdef _PRE_WLAN_FEATURE_VOWIFI
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_VOWIFI_REPORT].p_func = wal_cfg80211_vowifi_report_etc;
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

#if defined(_PRE_WLAN_FEATURE_DATA_SAMPLE) || defined(_PRE_WLAN_FEATURE_PSD_ANALYSIS)
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_SAMPLE_REPORT].p_func = wal_sample_report2sdt;
#endif

#ifdef _PRE_WLAN_ONLINE_DPD
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_DPD].p_func = wal_dpd_report2sdt;
#endif
#ifdef _PRE_WLAN_RF_AUTOCALI
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_AUTOCALI_REPORT].p_func = wal_autocali_report2sdt;
#endif

#ifdef _PRE_WLAN_FEATURE_DFS
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_CAC_REPORT].p_func = wal_cfg80211_cac_report;
#endif

#ifdef _PRE_WLAN_FEATURE_M2S
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_M2S_STATUS].p_func = wal_cfg80211_m2s_status_report;
#endif

#ifdef _PRE_WLAN_FEATURE_TAS_ANT_SWITCH
    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_TAS_NOTIFY_RSSI].p_func = wal_cfg80211_tas_rssi_access_report;
#endif

    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_EXT_AUTH_REQ].p_func = wal_report_external_auth_req_etc;

    g_ast_wal_host_ctx_table[HMAC_HOST_CTX_EVENT_SUB_TYPE_CH_SWITCH_NOTIFY].p_func = wal_report_channel_switch_etc;

    frw_event_table_register_etc(FRW_EVENT_TYPE_HOST_CTX, FRW_EVENT_PIPELINE_STAGE_0, g_ast_wal_host_ctx_table);

    return OAL_SUCC;
}


oal_uint32 wal_event_fsm_exit_etc(oal_void)
{
    memset_s(g_ast_wal_host_crx_table, OAL_SIZEOF(g_ast_wal_host_crx_table),
             0, OAL_SIZEOF(g_ast_wal_host_crx_table));

    memset_s(g_ast_wal_host_ctx_table, OAL_SIZEOF(g_ast_wal_host_ctx_table),
             0, OAL_SIZEOF(g_ast_wal_host_ctx_table));

    return OAL_SUCC;
}

#if defined(_PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/* debug sysfs */
OAL_STATIC oal_kobject *g_conn_syfs_wal_object = NULL;

oal_int32 wal_wakelock_info_print_etc(char *buf, oal_int32 buf_len)
{
    oal_int32 ret = 0;

#ifdef CONFIG_PRINTK
    if (g_st_wal_wakelock_etc.locked_addr) {
        ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1, "wakelocked by:%pf\n",
                          (oal_void *)g_st_wal_wakelock_etc.locked_addr);
    }
#endif

    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "hold %lu locks\n", g_st_wal_wakelock_etc.lock_count);

    return ret;
}

OAL_STATIC ssize_t wal_get_wakelock_info(struct kobject *dev, struct kobj_attribute *attr, char *buf)
{
    int ret = 0;

    if (buf == NULL) {
        OAL_IO_PRINT("buf is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (attr == NULL) {
        OAL_IO_PRINT("attr is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (dev == NULL) {
        OAL_IO_PRINT("dev is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    ret += wal_wakelock_info_print_etc(buf, PAGE_SIZE - ret);

    return ret;
}

extern oal_int32 wal_atcmsrv_ioctl_get_rx_pckg_old_etc(oal_net_device_stru *pst_net_dev,
                                                       oal_int32 *pl_rx_pckg_succ_num);
OAL_STATIC ssize_t wal_get_packet_statistics_wlan0_info(struct kobject *dev, struct kobj_attribute *attr, char *buf)
{
    ssize_t ret = 0;
    oal_net_device_stru *pst_net_dev = OAL_PTR_NULL;
    mac_vap_stru *pst_vap = OAL_PTR_NULL;
    hmac_vap_stru *pst_hmac_vap = OAL_PTR_NULL;
    oal_int32 l_rx_pckg_succ_num;
    oal_int32 l_ret;

    if (buf == NULL) {
        OAL_IO_PRINT("buf is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (attr == NULL) {
        OAL_IO_PRINT("attr is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (dev == NULL) {
        OAL_IO_PRINT("dev is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    pst_net_dev = wal_config_get_netdev_etc("wlan0", OAL_STRLEN("wlan0"));
    if (pst_net_dev == OAL_PTR_NULL) {
        OAM_WARNING_LOG0(0, OAM_SF_ANY,
                         "{wal_packet_statistics_wlan0_info_print::wal_config_get_netdev_etc return null ptr!}\r\n");
        return ret;
    }
    oal_dev_put(pst_net_dev); /* 调用oal_dev_get_by_name后，必须调用oal_dev_put使net_dev的引用计数减一 */
    /* 获取VAP结构体 */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev);
    /* 如果VAP结构体不存在，返回0 */
    if (OAL_UNLIKELY(pst_vap == OAL_PTR_NULL)) {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_packet_statistics_wlan0_info_print::pst_vap = OAL_PTR_NULL!}\r\n");
        return ret;
    }
    /* 非STA直接返回 */
    if (pst_vap->en_vap_mode != WLAN_VAP_MODE_BSS_STA) {
        OAM_WARNING_LOG1(0, OAM_SF_ANY,
                         "{wal_packet_statistics_wlan0_info_print::vap_mode:%d.}\r\n", pst_vap->en_vap_mode);
        return ret;
    }
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (pst_hmac_vap == OAL_PTR_NULL) {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_CFG, "{wal_packet_statistics_wlan0_info_print::pst_hmac_vap null.}");
        return ret;
    }

    l_ret = wal_atcmsrv_ioctl_get_rx_pckg_old_etc(pst_net_dev, &l_rx_pckg_succ_num);
    if (OAL_UNLIKELY(l_ret != OAL_SUCC)) {
        OAM_WARNING_LOG1(0, OAM_SF_ANY,
            "{wal_packet_statistics_wlan0_info_print::wal_atcmsrv_ioctl_get_rx_pckg_etc fail, failed err:%d!}", l_ret);
        return ret;
    }

    ret += snprintf_s(buf, PAGE_SIZE, PAGE_SIZE - 1, "rx_packet=%d\r\n", l_rx_pckg_succ_num);

    return ret;
}

OAL_STATIC struct kobj_attribute dev_attr_wakelock =
    __ATTR(wakelock, S_IRUGO, wal_get_wakelock_info, NULL);
OAL_STATIC struct kobj_attribute dev_attr_packet_statistics_wlan0 =
    __ATTR(packet_statistics_wlan0, S_IRUGO, wal_get_packet_statistics_wlan0_info, NULL);

oal_int32 wal_msg_queue_info_print_etc(char *buf, oal_int32 buf_len)
{
    oal_int32 ret = 0;

    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "message count:%u\n", wal_get_request_msg_count_etc());

    return ret;
}

OAL_STATIC ssize_t wal_get_msg_queue_info(struct kobject *dev, struct kobj_attribute *attr, char *buf)
{
    int ret = 0;

    if (buf == NULL) {
        OAL_IO_PRINT("buf is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (attr == NULL) {
        OAL_IO_PRINT("attr is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (dev == NULL) {
        OAL_IO_PRINT("dev is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    ret += wal_msg_queue_info_print_etc(buf, PAGE_SIZE - ret);

    return ret;
}
OAL_STATIC ssize_t wal_get_dev_wifi_info_print(char *buf, oal_int32 buf_len)
{
    ssize_t ret = 0;
    oal_net_device_stru *pst_net_dev = OAL_PTR_NULL;
    mac_vap_stru *pst_vap = OAL_PTR_NULL;
    hmac_vap_stru *pst_hmac_vap = OAL_PTR_NULL;

    if (buf == NULL) {
        OAM_WARNING_LOG1 (0, OAM_SF_ANY, "%s error: buf is null\r\n", (uintptr_t)(__FUNCTION__));
        return 0;
    }

    pst_net_dev = wal_config_get_netdev_etc("wlan0", OAL_STRLEN("wlan0"));
    if (pst_net_dev == OAL_PTR_NULL) {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_get_dev_wifi_info_print::wal_config_get_netdev_etc return null ptr!}\r\n");
        return ret;
    }
    oal_dev_put(pst_net_dev); /* 调用oal_dev_get_by_name后，必须调用oal_dev_put使net_dev的引用计数减一 */
    /* 获取VAP结构体 */
    pst_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev);
    /* 如果VAP结构体不存在，返回0 */
    if (OAL_UNLIKELY(pst_vap == OAL_PTR_NULL)) {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_get_dev_wifi_info_print::pst_vap = OAL_PTR_NULL!}\r\n");
        return ret;
    }
    /* 非STA直接返回 */
    if (pst_vap->en_vap_mode != WLAN_VAP_MODE_BSS_STA) {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_get_dev_wifi_info_print::vap_mode:%d.}\r\n", pst_vap->en_vap_mode);
        return ret;
    }
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_vap->uc_vap_id);
    if (pst_hmac_vap == OAL_PTR_NULL) {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_CFG, "{wal_get_dev_wifi_info_print::pst_hmac_vap null.}");
        return ret;
    }

    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "tx_frame_amount:%d\n", pst_hmac_vap->station_info.tx_packets);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "tx_byte_amount:%d\n", (oal_uint32)pst_hmac_vap->station_info.tx_bytes);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "tx_data_frame_error_amount:%d\n", pst_hmac_vap->station_info.tx_failed);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "tx_retrans_amount:%d\n", pst_hmac_vap->station_info.tx_retries);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "rx_frame_amount:%d\n", pst_hmac_vap->station_info.rx_packets);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "rx_byte_amount:%d\n", (oal_uint32)pst_hmac_vap->station_info.rx_bytes);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "rx_beacon_from_assoc_ap:%d\n", pst_hmac_vap->st_station_info_extend.ul_bcn_cnt);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "ap_distance:%d\n", pst_hmac_vap->st_station_info_extend.uc_distance);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "disturbing_degree:%d\n", pst_hmac_vap->st_station_info_extend.uc_cca_intr);
    ret += snprintf_s(buf + ret, buf_len - ret, (buf_len - ret) - 1,
                      "lost_beacon_amount:%d\n", pst_hmac_vap->st_station_info_extend.ul_bcn_tout_cnt);

    return ret;
}
OAL_STATIC ssize_t wal_get_dev_wifi_info(struct kobject *dev, struct kobj_attribute *attr, char *buf)
{
    int ret = 0;

    if (buf == NULL) {
        OAL_IO_PRINT("buf is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (attr == NULL) {
        OAL_IO_PRINT("attr is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (dev == NULL) {
        OAL_IO_PRINT("dev is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    ret += wal_get_dev_wifi_info_print(buf, PAGE_SIZE - ret);

    return ret;
}
#ifdef _PRE_WLAN_FEATURE_PC_KK_DEMAND
#define NETCARD_INFO 2
#define HI1103_11AC_MCS9_160M_2STREAMS_RATE "1.73Gbps"
#define HI1105_11AX_MCS9_160M_2STREAMS_RATE "1.92Gbps"

OAL_STATIC ssize_t wal_get_wifi_devices_info_print(char *buf, int32_t buf_len)
{
    ssize_t ret;
    int32_t chip_type = get_hi110x_subchip_type();
    char *netcard_info[BOARD_VERSION_BOTT][NETCARD_INFO] = {
        { "Hi1102", "NULL" }, { "Hi1103", HI1103_11AC_MCS9_160M_2STREAMS_RATE },
        { "Hi1102a", "NULL" }, { "Hi1105", HI1105_11AX_MCS9_160M_2STREAMS_RATE }
    };

    if (chip_type >= BOARD_VERSION_BOTT) {
        ret = snprintf_s(buf, buf_len, buf_len - 1, "This Chip is not supported\n");
        return ret;
    }

    ret = snprintf_s(buf, buf_len, buf_len - 1,
                     "Chip Type: HUAWEI %s\n" \
                     "NIC  Type: WLAN\n" \
                     "NIC  Rate(theory): %s\n", netcard_info[chip_type][0], netcard_info[chip_type][1]);

    return ret;
}

OAL_STATIC ssize_t wal_get_wifi_devices_info(struct kobject *dev, struct kobj_attribute *attr, char *buf)
{
    int ret;

    if (buf == NULL) {
        OAL_IO_PRINT("buf is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (attr == NULL) {
        OAL_IO_PRINT("attr is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    if (dev == NULL) {
        OAL_IO_PRINT("dev is null r failed!%s\n", __FUNCTION__);
        return 0;
    }

    ret = wal_get_wifi_devices_info_print(buf, PAGE_SIZE);

    return ret;
}
#endif

OAL_STATIC struct kobj_attribute dev_attr_dev_wifi_info =
    __ATTR(dev_wifi_info, S_IRUGO, wal_get_dev_wifi_info, NULL);

OAL_STATIC struct kobj_attribute dev_attr_msg_queue =
    __ATTR(msg_queue, S_IRUGO, wal_get_msg_queue_info, NULL);

#ifdef _PRE_WLAN_FEATURE_PC_KK_DEMAND
OAL_STATIC struct kobj_attribute g_dev_attr_wifi_devices_info =
    __ATTR(wifi_devices_info, S_IRUGO, wal_get_wifi_devices_info, NULL);
#endif

OAL_STATIC struct attribute *wal_sysfs_entries[] = {
    &dev_attr_wakelock.attr,
    &dev_attr_msg_queue.attr,
    &dev_attr_packet_statistics_wlan0.attr,
    &dev_attr_dev_wifi_info.attr,
#ifdef _PRE_WLAN_FEATURE_PC_KK_DEMAND
    &g_dev_attr_wifi_devices_info.attr,
#endif
    NULL
};

OAL_STATIC struct attribute_group wal_attribute_group = {
    // .name = "vap",
    .attrs = wal_sysfs_entries,
};

OAL_STATIC oal_int32 wal_sysfs_entry_init(oal_void)
{
    oal_int32 ret;
    oal_kobject *pst_root_object = NULL;
    pst_root_object = oal_get_sysfs_root_object_etc();
    if (pst_root_object == NULL) {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_sysfs_entry_init::get sysfs root object failed!}");
        return -OAL_EFAIL;
    }

    g_conn_syfs_wal_object = kobject_create_and_add("wal", pst_root_object);
    if (g_conn_syfs_wal_object == NULL) {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_sysfs_entry_init::create wal object failed!}");
        return -OAL_EFAIL;
    }

    ret = sysfs_create_group(g_conn_syfs_wal_object, &wal_attribute_group);
    if (ret) {
        kobject_put(g_conn_syfs_wal_object);
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_sysfs_entry_init::sysfs create group failed!}");
        return ret;
    }
    return OAL_SUCC;
}

OAL_STATIC oal_int32 wal_sysfs_entry_exit(oal_void)
{
    if (g_conn_syfs_wal_object) {
        sysfs_remove_group(g_conn_syfs_wal_object, &wal_attribute_group);
        kobject_put(g_conn_syfs_wal_object);
    }
    return OAL_SUCC;
}
#endif


oal_int32 wal_main_init_etc(oal_void)
{
    oal_uint32 ul_ret;
    frw_init_enum_uint16 en_init_state;

    oal_wake_lock_init(&g_st_wal_wakelock_etc, "wlan_wal_lock");
    wal_msg_queue_init_etc();

    en_init_state = frw_get_init_state_etc();
    /* WAL模块初始化开始时，说明HMAC肯定已经初始化成功 */
    if ((en_init_state == FRW_INIT_STATE_BUTT) || (en_init_state < FRW_INIT_STATE_HMAC_CONFIG_VAP_SUCC)) {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_main_init_etc::en_init_state has a invalid value [%d]!}", en_init_state);

        frw_timer_delete_all_timer_etc();
        return -OAL_EFAIL;
    }

    wal_event_fsm_init_etc();

    /* 创建proc */
    ul_ret = wal_hipriv_create_proc_etc(OAL_PTR_NULL);
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG1(0, 0, "{wal_main_init_etc::wal_hipriv_create_proc_etc has a wrong return value[%d]!}", ul_ret);

        frw_timer_delete_all_timer_etc();
        return -OAL_EFAIL;
    }

#ifdef _PRE_WLAN_FEATURE_DFR
    wal_dfx_init_etc();
#endif  // #ifdef _PRE_WLAN_FEATURE_DFR
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    wal_set_custom_process_func_etc();
#endif

    /* 初始化每个device硬件设备对应的wiphy */
    ul_ret = wal_cfg80211_init_etc();
    if (ul_ret != OAL_SUCC) {
        OAM_WARNING_LOG1(0, 0, "{wal_main_init_etc::wal_cfg80211_init_etc has a wrong return value [%d]!}", ul_ret);

        frw_timer_delete_all_timer_etc();
        return -OAL_EFAIL;
    }

    /* 在host侧如果WAL初始化成功，即为全部初始化成功 */
    frw_set_init_state_etc(FRW_INIT_STATE_ALL_SUCC);

    /* wal钩子函数初始化 */
    wal_drv_cfg_func_hook_init_etc();

    /* wal层对外钩子函数注册至oam模块 */
    oam_wal_func_fook_register_etc(&g_st_wal_drv_func_hook_etc);

#ifdef _PRE_SUPPORT_ACS
    wal_acs_init();
#endif

#if defined(_PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* debug sysfs */
    wal_sysfs_entry_init();
#endif

#ifdef _PRE_WLAN_FEATURE_IP_FILTER
    wal_register_ip_filter_etc(&g_st_ip_filter_ops_etc);
#endif /* _PRE_WLAN_FEATURE_IP_FILTER */

    if (hmac_get_feature_switch(HMAC_MIRACAST_SINK_SWITCH)) {
        wal_register_lights_suspend();
    }
    return OAL_SUCC;
}


oal_void wal_destroy_all_vap_etc(oal_void)
{
#if (_PRE_TEST_MODE_UT != _PRE_TEST_MODE)

    oal_uint8 uc_vap_id = 0;
    oal_net_device_stru *pst_net_dev;
    oal_int8 ac_param[10] = { 0 };
    OAL_IO_PRINT("wal_destroy_all_vap_etc start");

    for (uc_vap_id = oal_board_get_service_vap_start_id(); uc_vap_id < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vap_id++) {
        pst_net_dev = hmac_vap_get_net_device_etc(uc_vap_id);
        if (pst_net_dev != OAL_PTR_NULL) {
            oal_net_close_dev(pst_net_dev);

            wal_hipriv_del_vap_etc(pst_net_dev, ac_param);
            frw_event_process_all_event_etc(0);
        }
    }
#endif

    return;
}


oal_void wal_main_exit_etc(oal_void)
{
#if defined(_PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* debug sysfs */
    wal_sysfs_entry_exit();
#endif
    /* down掉所有的vap */
    wal_destroy_all_vap_etc();
    wal_event_fsm_exit_etc();

    /* 删除proc */
    wal_hipriv_remove_proc_etc();

    /* 卸载成功时，将初始化状态置为HMAC初始化成功 */
    frw_set_init_state_etc(FRW_INIT_STATE_HMAC_CONFIG_VAP_SUCC);

    /* 去注册钩子函数 */
    oam_wal_func_fook_unregister_etc();
#ifdef _PRE_WLAN_FEATURE_P2P
    /* DTSxxxxxx 删除cfg80211 删除网络设备工作队列 */
#endif

#ifdef _PRE_SUPPORT_ACS
    wal_acs_exit();
#endif
#ifdef _PRE_WLAN_FEATURE_DFR
    wal_dfx_exit_etc();
#endif  // #ifdef _PRE_WLAN_FEATURE_DFR

    oal_wake_lock_exit(&g_st_wal_wakelock_etc);
    frw_timer_clean_timer(OAM_MODULE_ID_WAL);

#ifdef _PRE_WLAN_FEATURE_IP_FILTER
    wal_unregister_ip_filter_etc();
#endif /* _PRE_WLAN_FEATURE_IP_FILTER */

    if (hmac_get_feature_switch(HMAC_MIRACAST_SINK_SWITCH)) {
        wal_unregister_lights_suspend();
    }

}

/*lint -e578*/ /*lint -e19*/
oal_module_symbol(wal_main_init_etc);
oal_module_symbol(wal_main_exit_etc);

oal_module_license("GPL"); /*lint +e578*/ /*lint +e19*/




