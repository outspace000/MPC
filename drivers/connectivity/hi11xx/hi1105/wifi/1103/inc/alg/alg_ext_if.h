

#ifndef __ALG_EXT_IF_H__
#define __ALG_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* 1 其他头文件包含 */
#include "oal_types.h"
#include "hal_ext_if.h"
#include "dmac_ext_if.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_ALG_EXT_IF_H

/* 2 宏定义 */
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/* 功率表相关参数 */
#define ALG_TPC_11B_RATE_NUM 4  /* 11b速率数目 */
#define ALG_TPC_11G_RATE_NUM 8  /* 11g速率数目 */
#define ALG_TPC_11A_RATE_NUM 8  /* 11a速率数目 */
#define ALG_TPC_11AC_20M_NUM 9  /* 11n_11ac_2g速率数目 */
#define ALG_TPC_11AC_40M_NUM 11 /* 11n_11ac_2g速率数目 */
#define ALG_TPC_11AC_80M_NUM 10 /* 11n_11ac_2g速率数目 */
/* rate-tpccode table中速率个数 */
#define ALG_TPC_RATE_TPC_CODE_TABLE_LEN \
    (ALG_TPC_11B_RATE_NUM + ALG_TPC_11G_RATE_NUM + ALG_TPC_11AC_20M_NUM + ALG_TPC_11AC_40M_NUM + ALG_TPC_11AC_80M_NUM)
#endif
/* 3 枚举定义 */
/* 4 全局变量声明 */
/* 5 消息头定义 */
/* 6 消息定义 */
/* 7 STRUCT定义 */
/* 8 UNION定义 */
/* 9 OTHERS定义 */
/* 10 函数声明 */
extern oal_int32 alg_main_init(oal_void);
extern oal_void alg_main_exit(oal_void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of alg_ext_if.h */
