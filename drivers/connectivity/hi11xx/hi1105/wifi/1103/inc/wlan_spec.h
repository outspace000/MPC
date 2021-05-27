 

#ifndef __WLAN_SPEC_H__
#define __WLAN_SPEC_H__

// �˴�����extern "C" UT���벻��
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* 1 ����ͷ�ļ����� */
#include "platform_spec.h"
#include "wlan_types.h"
#if (((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1105_DEV)) || \
    (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST))
#include "wlan_spec_1103.h"
#endif

/* 2 �궨�� */
#define ALG_SCH_WMM_ENSURE  1 /* ֧��WMM���� */
#define ALG_SCH_ROUND_ROBIN 2 /* ��ѯ���� */
#define ALG_SCH_PROPO_FAIR  3 /* ������ƽ���� */

#define WLAN_MU_BFEE_ENABLE  1 /* ֧��mu bfee */
#define WLAN_MU_BFEE_DISABLE 0 /* ��֧��mu bfee */

#define WLAN_M2S_BLACKLIST_MAX_NUM 16 /* m2s�·��������û�������Ҫ���ϲ㱣��һ�� */

#define WLAN_NSS_MAX_NUM_LIMIT (WLAN_MAX_NSS_NUM + 1) /* ���ռ�����Ŀ�����������С��Ҫ+1 */
/* 4 ȫ�ֱ������� */
/* 5 ��Ϣͷ���� */
/* 6 ��Ϣ���� */
/* 7 STRUCT���� */
/* hal device id ö�� */
typedef enum {
    HAL_DEVICE_ID_MASTER        = 0,    /* master��hal device id */
    HAL_DEVICE_ID_SLAVE         = 1,    /* slave��hal device id */

    HAL_DEVICE_ID_BUTT                  /* ���id */
} hal_device_id_enum;
typedef oal_uint8 hal_device_id_enum_enum_uint8;

/* 8 UNION���� */
/* 9 OTHERS���� */
/* 10 �������� */
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of wlan_spec.h */
