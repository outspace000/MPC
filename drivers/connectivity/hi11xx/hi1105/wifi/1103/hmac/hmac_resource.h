

#ifndef __HMAC_RESOURCE_H__
#define __HMAC_RESOURCE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* 1 其他头文件包含 */
#include "oal_types.h"
#include "oal_queue.h"
#include "mac_resource.h"
#include "mac_device.h"
#include "hmac_device.h"
#include "hmac_main.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_RESOURCE_H
/* 2 宏定义 */
/* 3 枚举定义 */
/* 4 全局变量声明 */
/* 5 消息头定义 */
/* 6 消息定义 */
/* 7 STRUCT定义 */
/* 存储hmac device结构的资源结构体 */
typedef struct {
    hmac_device_stru ast_hmac_dev_info[MAC_RES_MAX_DEV_NUM];
    oal_queue_stru st_queue;
    oal_uint aul_idx[MAC_RES_MAX_DEV_NUM];
    oal_uint8 auc_user_cnt[MAC_RES_MAX_DEV_NUM];
#ifdef _PRE_WLAN_FEATURE_DOUBLE_CHIP
    oal_uint8 auc_resv[2]; /* 单芯片下MAC_RES_MAX_DEV_NUM是1，双芯片下MAC_RES_MAX_DEV_NUM是2 */
#else
    oal_uint8 auc_resv[3];
#endif
} hmac_res_device_stru;

/* 存储hmac res资源结构体 */
typedef struct {
    hmac_res_device_stru st_hmac_dev_res;
} hmac_res_stru;

/* 8 UNION定义 */
/* 9 OTHERS定义 */
extern hmac_res_stru g_st_hmac_res_etc;

/* 10 函数声明 */
extern oal_uint32 hmac_res_alloc_mac_dev_etc(oal_uint32 ul_dev_idx);
extern oal_uint32 hmac_res_free_mac_dev_etc(oal_uint32 ul_dev_idx);
extern hmac_device_stru *hmac_res_get_mac_dev_etc(oal_uint32 ul_dev_idx);
extern mac_chip_stru *hmac_res_get_mac_chip(oal_uint32 ul_chip_idx);
extern oal_uint32 hmac_res_init_etc(oal_void);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 hmac_res_exit_etc(mac_board_stru *pst_hmac_board);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of mac_resource.h */
