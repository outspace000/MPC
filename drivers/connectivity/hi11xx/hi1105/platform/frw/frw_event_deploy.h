

#ifndef __FRW_EVENT_DEPLOY_H__
#define __FRW_EVENT_DEPLOY_H__

/* 其他头文件包含 */
#include "oal_ext_if.h"
#include "frw_event_main.h"
#include "frw_ipc_msgqueue.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_DEPLOY_H

/* 枚举定义 */
typedef enum {
    FRW_IPC_CORE_ID_MASTER = 0,
    FRW_IPC_CORE_ID_SLAVE = 1,

    FRW_IPC_CORE_NUM_BUTT
} frw_ipc_core_id_enum;
typedef oal_uint8 frw_ipc_core_id_enum_uint8;

typedef enum {
    FRW_IPC_CORE_TYPE_MASTER = 0,
    FRW_IPC_CORE_TYPE_SLAVE = 1,

    FRW_IPC_CORE_TYPE_BUTT
} frw_ipc_core_type_enum;
typedef oal_uint8 frw_ipc_core_type_enum_uint8;

/* 状态定义，中断上下文可能更改，因此需要原子变量 */
typedef enum {
    FRW_IPC_CORE_STATE_INIT = 0,
    FRW_IPC_CORE_STATE_CONNECTED = 1,
    FRW_IPC_CORE_STATE_RESET = 2,
    FRW_IPC_CORE_STATE_EXIT = 3,

    FRW_IPC_CORE_STATE_BUTT
} frw_ipc_core_state_enum;
typedef OAL_VOLATILE oal_uint8 frw_ipc_core_state_enum_uint8;

typedef enum {
    FRW_IPC_MSG_TYPE_EVENT = 0,             /* 外部事件 */
    FRW_IPC_MSG_TYPE_CONNECT_REQUEST = 1,   /* IPC连接请求 */
    FRW_IPC_MSG_TYPE_CONNECT_RESPONSE = 2,  /* IPC连接响应 */
    FRW_IPC_MSG_TYPE_CONFIG_REQUEST = 3,    /* IPC配置请求 */
    FRW_IPC_MSG_TYPE_CONFIG_RESPONSE = 4,   /* IPC配置响应 */
    FRW_IPC_MSG_TYPE_ERROR_NOTICE = 5,      /* IPC异常通知 */
    FRW_IPC_MSG_TYPE_RESET_REQUEST = 6,     /* IPC复位请求 */
    FRW_IPC_MSG_TYPE_RESET_RESPONSE = 7,    /* IPC复位响应 */
    FRW_IPC_MSG_TYPE_OPEN_OAM = 8,          /* IPC打开维测 */
    FRW_IPC_MSG_TYPE_CLOSE_OAM = 9,         /* IPC关闭维测 */
    FRW_IPC_MSG_TYPE_EXIT_REQUEST = 10,     /* IPC卸载请求 */
    FRW_IPC_MSG_TYPE_EXIT_RESPONSE = 11,    /* IPC卸载响应 */
    FRW_IPC_MSG_TYPE_TX_INT_ENABLE = 12,    /* IPC TX中断开启 */
    FRW_IPC_MSG_TYPE_TX_INT_DISENABLE = 13, /* IPC TX中断关闭 */

    FRW_IPC_MSG_TYPE_BUTT
} frw_ipc_msg_type_enum;
typedef oal_uint8 frw_ipc_msg_type_enum_uint8;

/* 最大序列号掩码 */
#define FRW_IPC_MAX_SEQ_NUMBER 0xFFFF

/* 获取消息队列 */
#define FRW_IPC_GET_MSG_QUEUE(_queue, _type) ((_queue) = ((_type) == FRW_IPC_CORE_TYPE_MASTER) ? \
    &queue_master_to_slave : &queue_slave_to_master)

/* IPC内部消息结构体 */
typedef struct {
    frw_ipc_msg_header_stru st_ipc_hdr;
    oal_uint8 auc_resv[2];
    oal_uint16 ul_length; /* 数据长度 */
    oal_uint8 auc_data[4];
} frw_ipc_inter_msg_stru;

/* STRUCT 定义 */
typedef struct {
    frw_ipc_core_id_enum_uint8 en_cpuid;           /* 本核cpuid */
    frw_ipc_core_id_enum_uint8 en_target_cpuid;    /* 目标内核cpuid */
    frw_ipc_core_state_enum_uint8 en_states;       /* 节点当前状态: 初始化, 关联, 复位, 关闭等状态 */
    frw_ipc_tx_ctrl_enum_uint8 en_tx_int_ctl;      /* TX中断控制 */
    frw_ipc_core_type_enum_uint8 en_cpu_type;      /* 当前CPU类型，是主核或从核 */
    oal_uint8 uc_resv[3];                          /* 保留 */
    oal_uint16 us_seq_num_rx_expect;               /* 接收消息的序列号,初始值为0,存放下一次期望接收的序列号 */
    oal_uint16 us_seq_num_tx_expect;               /* 发送消息的序列号,初始值为0,存放下一次期望发送的序列号 */
    frw_ipc_msg_callback_stru st_ipc_msg_callback; /* 回调处理函数 */
    oal_irq_dev_stru st_irq_dev;                   /* 中断结构体 */
#ifdef _PRE_DEBUG_MODE
    frw_ipc_log_stru st_log; /* 日志结构体 */
#endif
} frw_ipc_node_stru;

/*
 * 函 数 名  : frw_ipc_get_core_type
 * 功能描述  : 获取CPU类型
 * 返 回 值  : CPU类型: master or slave
 */
OAL_STATIC OAL_INLINE frw_ipc_core_type_enum frw_ipc_get_core_type(oal_void)
{
    if (OAL_GET_CORE_ID() == FRW_IPC_CORE_ID_MASTER) {
        return FRW_IPC_CORE_TYPE_MASTER;
    }

    return FRW_IPC_CORE_TYPE_SLAVE;
}

/*
 * 函 数 名  : frw_ipc_get_header
 * 功能描述  : 获取IPC头
 * 输入参数  : pst_ipc_mem_msg － 事件内存块地址
 */
OAL_STATIC OAL_INLINE oal_uint8 *frw_ipc_get_header(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    pst_ipc_mem_msg->puc_data -= FRW_IPC_MSG_HEADER_LENGTH;
    return pst_ipc_mem_msg->puc_data;
}

extern oal_uint32 frw_event_deploy_init_etc(oal_void);
extern oal_uint32 frw_event_deploy_exit_etc(oal_void);

#endif /* end of frw_event_deploy.h */
