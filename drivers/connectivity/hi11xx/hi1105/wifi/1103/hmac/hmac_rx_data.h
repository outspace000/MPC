

#ifndef __HMAC_RX_DATA_H__
#define __HMAC_RX_DATA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* 1 其他头文件包含 */
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "mac_frame.h"
#include "dmac_ext_if.h"
#include "hmac_user.h"
#include "oal_net.h"
#include "hmac_tcp_opt.h"
#include "hmac_device.h"
#include "hmac_vap.h"
#include "hmac_resource.h"
#ifdef _PRE_WLAN_RR_PERFORMENCE_DEBUG
#include "hmac_config.h"
#endif

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_RX_DATA_H
/* 2 宏定义 */
#define HMAC_RX_DATA_ETHER_OFFSET_LENGTH 6      /* 代表发送lan的包，protocol type的以太头需要向前偏移6 */
#define HMAC_RX_SMALL_PKT_MIPS_LIMIT     30000L /* rx小包MIPS极限，当前为30us */
/* 3 枚举定义 */
/* 4 全局变量声明 */
/* 5 消息头定义 */
/* 6 消息定义 */
/* 7 STRUCT定义 */
/* HMAC 处理 TKIP MIC FAILE 异常传递给定时器的参数 */
typedef struct {
    oal_uint8 uc_vap_id; /* 传递给定时器的 vap_id */
    oal_uint8 uc_rsv[3];
    frw_timeout_stru *pst_timeout; /* MIC faile 处理定时器资源 */
} hmac_drx_mic_faile_stru;

/* 8 UNION定义 */
/* 9 OTHERS定义 */
/* 10 函数声明 */
extern oal_uint32 hmac_rx_process_data_event(frw_event_mem_stru *pst_event_mem);
extern oal_void hmac_rx_process_data_ap_tcp_ack_opt_etc(hmac_vap_stru *pst_vap,
                                                        oal_netbuf_head_stru *pst_netbuf_header);
extern oal_uint32 hmac_rx_process_data_sta_tcp_ack_opt_etc(hmac_vap_stru *pst_vap,
                                                           oal_netbuf_head_stru *pst_netbuf_header);
#ifdef _PRE_WLAN_DFT_DUMP_FRAME
extern oal_void hmac_rx_report_eth_frame_etc(mac_vap_stru *pst_mac_vap,
                                             oal_netbuf_stru *pst_netbuf);
#endif
#ifdef _PRE_WLAN_FEATURE_MONITOR
extern oal_uint32 hmac_sniffer_save_data(oal_netbuf_stru *pst_netbuf, oal_uint16 us_netbuf_num);
#endif
extern oal_void hmac_rx_free_netbuf_etc(oal_netbuf_stru *pst_netbuf, oal_uint16 us_nums);
extern oal_void hmac_rx_free_netbuf_list_etc(oal_netbuf_head_stru *pst_netbuf_hdr,
                                             oal_uint16 us_nums_buf);

extern oal_uint32 hmac_rx_lan_frame_etc(oal_netbuf_head_stru *pst_netbuf_header);
extern oal_void hmac_pkt_mem_opt_init_etc(hmac_device_stru *pst_hmac_device);
extern oal_void hmac_pkt_mem_opt_exit_etc(hmac_device_stru *pst_hmac_device);
extern oal_void hmac_pkt_mem_opt_cfg_etc(oal_uint32 ul_cfg_tpye, oal_uint32 ul_cfg_value);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of hmac_rx_data.h */
