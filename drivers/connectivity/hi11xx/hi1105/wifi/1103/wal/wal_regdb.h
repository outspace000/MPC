

#ifndef __WAL_REGDB_H__
#define __WAL_REGDB_H__

/* 1 ����ͷ�ļ����� */
#include "oal_ext_if.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_REGDB_H
/* 2 �궨�� */
#define HI1103_SPECIFIC_COUNTRY_CODE_IDX (0)

/* 3 ö�ٶ��� */
/* 4 ȫ�ֱ������� */
extern OAL_CONST oal_ieee80211_regdomain_stru g_st_default_regdom_etc;

/* 5 ��Ϣͷ���� */
/* 6 ��Ϣ���� */
/* 7 STRUCT���� */
/* 8 UNION���� */
/* 9 OTHERS���� */
/* 10 �������� */
extern OAL_CONST oal_ieee80211_regdomain_stru *wal_regdb_find_db_etc(oal_int8 *pc_str);
#endif /* end of wal_regdb.h */