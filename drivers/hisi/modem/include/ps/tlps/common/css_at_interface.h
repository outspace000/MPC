/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2019. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef CSS_AT_INTERFACE_H
#define CSS_AT_INTERFACE_H

#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#define MCC_INFO_VERSION_LEN (9)
#define AT_CSS_MAX_MCC_ID_NUM (17)
/* Added for BlackCell Feature 2017-4-22 begin */
#define AT_CSS_BLACK_CELL_LIST_VERSION_LEN (9)
/* Added for BlackCell Feature 2017-4-22 end */
/* add for CloudLine Feature 2017-6-28 begin */
#define AT_CSS_CLOUD_LINE_VERSION_LEN (9) /* ???????????????????????????????? */
#define AT_CSS_PLMN_MAX_LINE_NUM (64)     /* ????????????????????PLMN???????????????????? */
#define AT_CSS_TACLAC_MAX_LINE_NUM (10)   /* ????????????????????TAC/LAC???????????????????? */
/* add for CloudLine Feature 2017-6-28 end */

/* Added for EMC, 2018-1-9, begin */
#define AT_CSS_MRU_MAX_NUM (10) /* MRU?????????????????? */
/* Added for EMC, 2018-1-9, end */


enum CSS_AT_MsgType {
    /* AT->CSS */
    ID_AT_CSS_MCC_INFO_SET_REQ          = 0x0001, /* _H2ASN_MsgChoice AT_CSS_MccInfoSetReq */
    ID_AT_CSS_MCC_VERSION_INFO_REQ      = 0x0002, /* _H2ASN_MsgChoice AT_CSS_MccVersionInfoReq */
    ID_AT_CSS_BLACK_CELL_LIST_SET_REQ   = 0x0003, /* _H2ASN_MsgChoice AT_CSS_BlackCellListSetReq */
    ID_AT_CSS_BLACK_CELL_LIST_QUERY_REQ = 0x0004, /* _H2ASN_MsgChoice AT_CSS_BlackCellListQueryReq */
    ID_AT_CSS_LINE_INDEX_LIST_SET_REQ   = 0x0005, /* _H2ASN_MsgChoice AT_CSS_LineIndexListSetReq */
    ID_AT_CSS_LINE_DETAIL_SET_REQ       = 0x0006, /* _H2ASN_MsgChoice AT_CSS_LineDetailSetReq */
    ID_AT_CSS_LINE_INDEX_LIST_QUERY_REQ = 0x0007, /* _H2ASN_MsgChoice AT_CSS_LineIndexListQueryReq */
    /* Added for EMC, 2018-1-9, begin */
    ID_AT_CSS_VZWMRUC_SET_REQ   = 0x0008, /* _H2ASN_MsgChoice AT_CSS_VzwmrucSetReq */
    ID_AT_CSS_VZWMRUE_SET_REQ   = 0x0009, /* _H2ASN_MsgChoice AT_CSS_VzwMrueSetReq */
    ID_AT_CSS_VZWMRUE_QUERY_REQ = 0x000a, /* _H2ASN_MsgChoice AT_CSS_VzwMrueQueryReq */
    /* Added for EMC, 2018-1-9, end */

    /* CSS->AT */
    ID_CSS_AT_MCC_INFO_SET_CNF          = 0x1001, /* _H2ASN_MsgChoice CSS_AT_MccInfoSetCnf */
    ID_CSS_AT_MCC_VERSION_INFO_CNF      = 0x1002, /* _H2ASN_MsgChoice CSS_AT_MccVersionInfoCnf */
    ID_CSS_AT_QUERY_MCC_INFO_NOTIFY     = 0x1003, /* _H2ASN_MsgChoice CSS_AT_QueryMccInfoNotify */
    ID_CSS_AT_BLACK_CELL_LIST_SET_CNF   = 0x1004, /* _H2ASN_MsgChoice CSS_AT_BlackCellListSetCnf */
    ID_CSS_AT_BLACK_CELL_LIST_QUERY_CNF = 0x1005, /* _H2ASN_MsgChoice CSS_AT_BlackCellListQueryCnf */
    ID_CSS_AT_BLACK_CELL_MCC_NOTIFY     = 0x1006, /* _H2ASN_MsgChoice CSS_AT_BlackCellMccNotify */
    ID_CSS_AT_LINE_INDEX_LIST_SET_CNF   = 0x1007, /* _H2ASN_MsgChoice CSS_AT_LineIndexListSetCnf */
    ID_CSS_AT_LINE_DETAIL_SET_CNF       = 0x1008, /* _H2ASN_MsgChoice CSS_AT_LineDetailSetCnf */
    ID_CSS_AT_LINE_INDEX_LIST_QUERY_CNF = 0x1009, /* _H2ASN_MsgChoice CSS_AT_LineIndexListQueryCnf */
    ID_CSS_AT_LINE_PLMN_NOTIFY          = 0x100a, /* _H2ASN_MsgChoice CSS_AT_LinePlmnNotify */
    ID_CSS_AT_LINE_INDEX_NOTIFY         = 0x100b, /* _H2ASN_MsgChoice CSS_AT_LineIndexNotify */
    /* Added for VZW EMC, 2018-1-9, begin */
    ID_CSS_AT_VZWMRUC_SET_CNF   = 0x100c, /* _H2ASN_MsgChoice CSS_AT_VzwmrucSetCnf */
    ID_CSS_AT_VZWMRUE_SET_CNF   = 0x100d, /* _H2ASN_MsgChoice CSS_AT_VzwMrueSetCnf */
    ID_CSS_AT_VZWMRUE_QUERY_CNF = 0x100e, /* _H2ASN_MsgChoice CSS_AT_VzwmrueQueryCnf */
    /* Added for VZW EMC, 2018-1-9, end */

    ID_CSS_AT_MSG_BUTT
};
typedef VOS_UINT32 CSS_AT_MsgTypeUint32;

enum AT_CSS_Rat {
    AT_CSS_RAT_TYPE_GSM = 0, /* GSM???????? */
    AT_CSS_RAT_TYPE_WCDMA,   /* WCDMA???????? */
    AT_CSS_RAT_TYPE_LTE,     /* LTE???????? */

    AT_CSS_RAT_TYPE_BUTT
};
typedef VOS_UINT8 AT_CSS_RatUint8;

enum AT_CSS_SetMccOperateType {
    AT_CSS_SET_MCC_TYPE_ADD_MCC = 0,    /* ????MCC */
    AT_CSS_SET_MCC_TYPE_DELETE_ALL_MCC, /* ????????MCC???? */
    AT_CSS_SET_MCC_TYPE_DELETE_ONE_MCC, /* ????????MCC???? */

    AT_CSS_SET_MCC_TYPE_BUTT
};
typedef VOS_UINT8 AT_CSS_SetMccOperateTypeUint8;

/* Added for BlackCell Feature 2017-4-22 begin */

enum AT_CSS_BlackCellListOperateType {
    AT_CSS_BLACK_CELL_LIST_ADD_ONE = 0, /* ?????????????????? */
    AT_CSS_BLACK_CELL_LIST_DELETE_ALL,  /* ?????????????????? */

    AT_CSS_BLACK_CELL_LIST_TYPE_BUTT
};
typedef VOS_UINT8 AT_CSS_BlackCellListOperateTypeUint8;
/* Added for BlackCell Feature 2017-4-22 end */

/* add for CloudLine Feature 2017-6-29 begin */
/* ????????: ?????????????????? */
enum AT_CSS_LineIndexListOperateType {
    AT_CSS_LINE_INDEX_LIST_ADD = 0,    /* ???????????????? */
    AT_CSS_LINE_INDEX_LIST_DELETE_ALL, /* ???????????????? */

    AT_CSS_LINE_INDEX_LIST_TYPE_BUTT
};
typedef VOS_UINT8 AT_CSS_LineIndexListOperateTypeUint8;

/* ????????: ?????????????????????????? */
enum AT_CSS_LineDetailOperateType {
    AT_CSS_LINE_DETAIL_ADD = 0,    /* ???????????????????? */
    AT_CSS_LINE_DETAIL_DELETE_ALL, /* ???????????????????? */

    AT_CSS_LINE_DETAIL_TYPE_BUTT
};
typedef VOS_UINT8 AT_CSS_LineDetailOperateTypeUint8;

/* ????????: ?????????????????????? */
enum AT_CSS_LineDetailInfoType {
    AT_CSS_LINE_DETAIL_INFO_TACLAC_PAIR = 0, /* TACLAC?? */
    AT_CSS_LINE_DETAIL_INFO_HO_PATH,         /* HO???????? */
    AT_CSS_LINE_DETAIL_INFO_HO_BAR,          /* HO????Bar???? */
    /* add for Cloudline Lte Feature 2018-4-16 begin */
    AT_CSS_LINE_DETAIL_INFO_LTE_HO_PATH, /* LTE???????? */
    /* add for Cloudline Lte Feature 2018-4-16 end */
    AT_CSS_LINE_DETAIL_INFO_NO_INFO = 0xFF /* ?????????????????????????? */
};
typedef VOS_UINT8 AT_CSS_LineDetailInfoTypeUint8;
/* add for CloudLine Feature 2017-6-29 end */

typedef struct {
    /*
     * MCC??aucMcc[2]????????????,mcc??460:
     *              ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
     *     ---------------------------------------------------------------------------
     * aucMcc[0]    ||    MCC digit 2 = 6        |           MCC digit 1 = 4
     *     ---------------------------------------------------------------------------
     * aucMcc[1]    ||    ????                   |           MCC digit 3 = 0
     */
    VOS_UINT8 mcc[2]; /* MCC ID */
    VOS_UINT8 rsv[2];
} AT_CSS_MccId;


typedef struct {
    VOS_UINT32 mcc;
    VOS_UINT32 mnc;
} CSS_AT_PlmnId;

typedef struct {
    VOS_UINT32 freqHigh;
    VOS_UINT32 freqLow;
} AT_CSS_FreqRange;

typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      rsv[2];
} AT_CSS_MccVersionInfoReq;

typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      rsv[1];
    VOS_UINT8      versionId[MCC_INFO_VERSION_LEN]; /* ??????????????xx.xx.xxx */
} CSS_AT_MccVersionInfoCnf;


typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    /* add for fill right clientId 2016-02-23, begin  */
    MODEM_ID_ENUM_UINT16 modemId;
    /* add for fill right clientId 2016-02-23, end  */
    VOS_UINT16                    clientId;
    VOS_UINT8                     seq;                             /* ?????? */
    AT_CSS_SetMccOperateTypeUint8 operateType;                     /* ???????? */
    VOS_UINT8                     versionId[MCC_INFO_VERSION_LEN]; /* ??????????????xx.xx.xxx */
    /* modified for fill right clientId 2016-02-23, begin  */
    VOS_UINT8 rsv[1];
    /* modified for fill right clientId 2016-02-23, end  */

    /*
     * 1)aucMccINfoBuff??????????MCC??????????????????????????ulMccInfoBuffLen????????????????
     * 2)aucMccINfoBuff??????????AT_CSS_MCC_INFO_STRU????????????????MNC????,
     *   BAND??????????????????????????????????????????????
     * typedef struct
     * {
     *     VOS_UINT8                           supportFlag;    // 1:????????GSM 2:????????WCDMA 4:????????LTE??????????????????
     *     AT_CSS_FreqRange              freqRange;
     * } AT_CSS_FreqRangeWithRat;
     * typedef struct
     * {
     *     VOS_UINT8                                   bandInd;
     *     VOS_UINT8                                   breqRangNum;
     *     //????????????ucFreqRangNum??AT_CSS_FreqRangeWithRat????
     *       ??FreqRange??????????????FreqRange??????????ucFreqRangNum????0
     *     AT_CSS_FreqRangeWithRat             freqRangeArray[ucFreqRangNum];
     *     VOS_UINT8                                   preConfigFreqNum;
     *     //????????????ucPreConfigFreqNum??AT_CSS_FreqRangeWithRat????
     *       ??PreConfigFreq??????????????PreConfigFreq??????????ucPreConfigFreqNum????0
     *     AT_CSS_FreqRangeWithRat             preConfigFreqArray[ucPreConfigFreqNum];      //????????????
     * }AT_CSS_BandInfo;
     * typedef struct
     * {
     *     MNC??aucMnc[2]??????????????mnc??01:
     *         ---------------------------------------------------------------------------
     *                  ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
     *         ---------------------------------------------------------------------------
     *     aucMnc[0]    ||    MNC digit 3 = f        |           ????
     *         ---------------------------------------------------------------------------
     *     aucMnc[1]    ||    MNC digit 2 = 1        |           MNC digit 1 = 0
     *         ---------------------------------------------------------------------------
     *     VOS_UINT8                           aucMnc[2];
     *     VOS_UINT8                           ucBandCount;// BAND??????
     *     //????????????ucBandCount??band????????????????BAND??????????ucBandCount????0
     *     AT_CSS_BandInfo               bandArray[ucBandCount];
     * }AT_CSS_MncInfo;
     * typedef struct
     * {
     *     MCC??aucMcc[2]????????????,mcc??460:
     *         ---------------------------------------------------------------------------
     *                  ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
     *         ---------------------------------------------------------------------------
     *     aucMcc[0]    ||    MCC digit 2 = 6        |           MCC digit 1 = 4
     *         ---------------------------------------------------------------------------
     *     aucMcc[1]    ||    ????                   |           MCC digit 3 = 0
     *         ---------------------------------------------------------------------------
     *     VOS_UINT8                           aucMcc[2];
     *     VOS_UINT8                           ucMncCount;// MNC??????
     *     //????????????ucMncCount??AT_CSS_MncInfo??????mnc??????????????mnc??????????ucMncCount????0
     *     AT_CSS_MncInfo                mncAarry[ucMncCount];
     * }AT_CSS_MCC_INFO_STRU;
     * 3)aucMccINfoBuff????????????????AP??CSS??????????AT??????????????AP??????????????????
     *   ??????????????????????AT??AT????????????????????????????????????CSS??
     *   ????AP????????????????0x22??????????????????'22'??AT????????????0x22;
     * 4)aucMccINfoBuff????????????????
     * 5)ulMccInfoBuffLen????????1.6K??
     */
    VOS_UINT32 mccInfoBuffLen;
    VOS_UINT8  mccInfoBuff[4];
} AT_CSS_MccInfoSetReq;

/* Added for BlackCell Feature 2017-4-22 begin */

typedef struct {
    VOS_MSG_HEADER                              /* _H2ASN_Skip */
        VOS_UINT32                       msgId; /* _H2ASN_Skip */
    VOS_UINT16                           clientId;
    VOS_UINT8                            seq;                                           /* ?????? */
    AT_CSS_BlackCellListOperateTypeUint8 operateType;                                   /* ???????? */
    VOS_UINT8                            versionId[AT_CSS_BLACK_CELL_LIST_VERSION_LEN]; /* ??????????????xx.xx.xxx */
    AT_CSS_RatUint8                      ratType;                                       /* ???????? */
    VOS_UINT8                            rsv[2];

    /*
     * 1)aucBlackCellListBuff??????????????????????????????????????????ulBlackCellListBuffLen????????????????
     * 2)aucBlackCellListBuff??????????AT_CSS_GsmCloudBlackcell??????????
     * ????????BS1,BS2??BS3????????????????????AT_CSS_GsmCloudBlackcell????????????????
     * ????ucPairCount??astBlackListArray??????????
     * typedef struct
     * {
     *     CSS_PlmnId    plmn;
     *     VOS_UNIT8           pairCount;
     *     //????????????ucPairCount??AT_CSS_GsmCloudBlackcellPair??????pair??????
     *       ??????????????mcc????????????????AP????????????MCC????????Modem??????MCC????????????????
     *       ????????????????^REPORTBLACKCELLMCC????????????
     *     AT_CSS_GsmCloudBlackcellPair blackListPairArray[ucPairCount];
     * }AT_CSS_GsmCloudBlackcell;
     * typedef struct
     * {
     *     VOS_UNIT32  ulMcc; //Modem????plmn????;????460---0x00000604
     *     VOS_UNIT32  ulMnc; //Modem????plmn????;???? 01---0x000F0100
     * }CSS_PlmnId;
     * typedef struct
     * {
     *     VOS_UNIT16  usSourceCellLai;
     *     VOS_UNIT16  usSourceCellId;
     *     VOS_UNIT16  usBlackCellArfcn; //??????GSM????????????????0x1029????GSM900????,41????
     *     VOS_UNIT8   ucBlackCellBsic;  //????ncc,bcc;????0x14????<2,4>
     *     VOS_UNIT8   ucBlackCellReduceVal;//??????????????????????????db??
     * }AT_CSS_GsmCloudBlackcellPair;
     */

    VOS_UINT32 blackCellListBuffLen;
    VOS_UINT8  blackCellListBuff[4];
} AT_CSS_BlackCellListSetReq;


typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      rsv[2];
} AT_CSS_BlackCellListQueryReq;
/* Added for BlackCell Feature 2017-4-22 end */

typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      seq; /* ?????? */
    VOS_UINT8      rsv[1];

    VOS_UINT32 result; /* 0??????????1???????? */
} CSS_AT_MccInfoSetCnf;

typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      rsv[1];
    VOS_UINT8      versionId[MCC_INFO_VERSION_LEN]; /* ??????????????xx.xx.xxx */
    VOS_UINT32     mccNum;                          /* MCC ???? */
    AT_CSS_MccId   mccId[AT_CSS_MAX_MCC_ID_NUM];    /* MCC ID???? */
} CSS_AT_QueryMccInfoNotify;


typedef struct {
    VOS_UINT32 mccNum;                     /* MCC ???? */
    VOS_UINT32 mcc[AT_CSS_MAX_MCC_ID_NUM]; /* MCC ????,Modem????plmn????;????460---0x00000604 */
} CSS_AT_BlackCellMccInfo;

/* Added for BlackCell Feature 2017-4-22 begin */

typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      seq;   /* ?????? */
    VOS_UINT8      reserved;
    VOS_UINT32     result; /* VOS_OK??????????VOS_ERR???????? */
} CSS_AT_BlackCellListSetCnf;


typedef struct {
    VOS_MSG_HEADER                 /* _H2ASN_Skip */
    VOS_UINT32              msgId; /* _H2ASN_Skip */
    VOS_UINT16              clientId;
    VOS_UINT8               reserved;
    VOS_UINT8               versionId[AT_CSS_BLACK_CELL_LIST_VERSION_LEN]; /* ??????????????xx.xx.xxx */
    CSS_AT_BlackCellMccInfo mccInfo;                                       /* ??????MCC???? */
} CSS_AT_BlackCellListQueryCnf;


typedef struct {
    VOS_MSG_HEADER                 /* _H2ASN_Skip */
    VOS_UINT32              msgId; /* _H2ASN_Skip */
    VOS_UINT16              clientId;
    VOS_UINT8               reserved;
    VOS_UINT8               versionId[AT_CSS_BLACK_CELL_LIST_VERSION_LEN]; /* ??????????????xx.xx.xxx */
    CSS_AT_BlackCellMccInfo mccInfo;                                       /* ??????MCC???? */
} CSS_AT_BlackCellMccNotify;
/* Added for BlackCell Feature 2017-4-22 end */

/* add for CloudLine Feature 2017-6-29 begin */


typedef struct {
    VOS_MSG_HEADER                              /* _H2ASN_Skip */
        VOS_UINT32                       msgId; /* _H2ASN_Skip */
    VOS_UINT16                           clientId;
    MODEM_ID_ENUM_UINT16                 modemId;
    VOS_UINT8                            seq;                                      /* ?????? */
    AT_CSS_LineIndexListOperateTypeUint8 operateType;                              /* ???????? */
    VOS_UINT8                            versionId[AT_CSS_CLOUD_LINE_VERSION_LEN]; /* ??????????????xx.xx.xxx */
    VOS_UINT8                            rsv;

    /*
     * 1)aucLineIndexListBuff????????????????????????????????????????????????ulLineIndexListBuffLen????????????????
     * 2)aucLineIndexListBuff??????????AT_CSS_CLOUD_LINE_INDEX_LIST_INFO_STRU??????????
     * ??LineIndex??0xFFFF????????PLMN????????????????????
     * typedef struct
     * {
     *     CSS_PlmnId stPlmn;
     *     VOS_UNIT16          usLineIndex;
     *     VOS_UINT8           ucTacNum;
     *     VOS_UINT8           ucLacNum;
     *     //????????????ucTacNum??VOS_UINT16??TAC??????????
     *     VOS_UINT16          ausTacList[ucTacNum];
     *     //????????????ucLacNum??VOS_UINT16??LAC??????????
     *     VOS_UINT16          ausLacList[ucLacNum];
     * }AT_CSS_CloudLineIndexInfo;
     */
    VOS_UINT32 lineIndexListBuffLen;
    VOS_UINT8  lineIndexListBuff[4];
} AT_CSS_LineIndexListSetReq;


typedef struct {
    VOS_MSG_HEADER         /* _H2ASN_Skip */
    VOS_UINT32     msgId;  /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      seq;    /* ?????? */
    VOS_UINT8      rsv;
    VOS_UINT32     result; /* VOS_OK??????????VOS_ERR???????? */
} CSS_AT_LineIndexListSetCnf;


typedef struct {
    VOS_MSG_HEADER                           /* _H2ASN_Skip */
    VOS_UINT32                        msgId; /* _H2ASN_Skip */
    VOS_UINT16                        clientId;
    MODEM_ID_ENUM_UINT16              modemId;
    VOS_UINT8                         seq;                                      /* ?????? */
    AT_CSS_LineDetailOperateTypeUint8 operateType;                              /* ???????? */
    VOS_UINT8                         versionId[AT_CSS_CLOUD_LINE_VERSION_LEN]; /* ??????????????xx.xx.xxx */
    VOS_UINT8                         rsv;

    /*
     * 1)aucLineDetailBuff????????????????????????????????????????????????ulLineDetailBuffLen????????????????
     * 2)aucLineDetailBuff??????????AT_CSS_LineDetailInfo??????????:
     * typedef struct
     * {
     *     CSS_PlmnId                             stPlmn;
     *     VOS_UNIT16                                      usLineIndex;
     *     AT_CSS_LineDetailInfoTypeUint8          enInfoType;
     *     VOS_UINT8                                       aucLeftBuff[ulLineDetailBuffLen-11];
     * }AT_CSS_LineDetailInfo;
     * 3)AT_CSS_LineDetailInfo????????aucLeftBuff????enInfoType????????????????
     *   i.??enInfoType??AT_CSS_LINE_DETAIL_INFO_TACLAC_PAIR??aucLeftBuff??????????AT_CSS_CloudLineTaclacMapInfo????????????
     *     typedef struct
     *     {
     *         VOS_UITN16                                       usTac;
     *         VOS_UINT16                                       usLac;
     *     }AT_CSS_CloudLineTaclacPairInfo;
     *     typedef struct
     *     {
     *         VOS_UINT8                                        ucPairNum;
     *         //????????????ucPairNum??AT_CSS_CloudLineTaclacPairInfo????????
     *         AT_CSS_CloudLineTaclacPairInfo          astCloudTacLacPairInfoList[ucPairNum];
     *     }AT_CSS_CloudLineTaclacMapInfo;
     *   ii.??enInfoType??AT_CSS_LINE_DETAIL_INFO_HO_PATH??aucLeftBuff??????????AT_CSS_CLOUD_LINE_HO_PATH_INFO_STRU????????????
     *     typedef struct
     *     {
     *         VOS_UINT32                                       usSrcCellId;
     *         VOS_UINT16                                       usSrcArfcn;
     *         VOS_UINT16                                       usSrcBsic;
     *         VOS_UINT16                                       usDstArfcn;
     *         VOS_UINT16                                       usDstBsic;
     *         VOS_UINT16                                       usRxlevA;
     *         VOS_UINT16                                       usRxlevB;
     *     }AT_CSS_CLOUD_LINE_HO_PATH_CELL_INFO_STRU;
     *     typedef struct
     *     {
     *         VOS_UITN16                                       usLac;
     *         VOS_UINT8                                        ucCellNum;
     *         //????????????ucCellNum??AT_CSS_CLOUD_LINE_HO_PATH_CELL_INFO_STRU????????
     *         AT_CSS_CLOUD_LINE_HO_PATH_CELL_INFO_STRU         astCellInfoList[ucCellNum];
     *     }AT_CSS_CLOUD_LINE_HO_PATH_LAC_INFO_STRU;
     *     typedef struct
     *     {
     *         VOS_UINT8                                        ucRat;
     *         VOS_UINT8                                        ucDirection;
     *         VOS_UINT8                                        ucLacNum;
     *         //????????????ucLacNum??AT_CSS_CLOUD_LINE_HO_PATH_LAC_INFO_STRU????????
     *         AT_CSS_CLOUD_LINE_HO_PATH_LAC_INFO_STRU          astLacInfoList[ucLacNum];
     *     }AT_CSS_CLOUD_LINE_HO_PATH_INFO_STRU;
     *   iii.??enInfoType??AT_CSS_LINE_DETAIL_INFO_HO_BAR??aucLeftBuff??????????AT_CSS_CLOUD_LINE_HO_BAR_INFO_STRU????????????
     *     typedef struct
     *     {
     *         VOS_UINT16                                       usLac;
     *         VOS_UINT32                                       usSrcCellId;
     *         VOS_UINT16                                       usSrcArfcn;
     *         VOS_UINT16                                       usSrcBsic;
     *         VOS_UINT16                                       usDstArfcn;
     *         VOS_UINT16                                       usDstBsic;
     *     }AT_CSS_CLOUD_LINE_HO_BAR_CELL_INFO_STRU;
     *     typedef struct
     *     {
     *         VOS_UINT8                                        ucRat;
     *         VOS_UINT8                                        ucCellNum;
     *         //????????????ucCellNum??AT_CSS_CLOUD_LINE_HO_BAR_CELL_INFO_STRU????????
     *         AT_CSS_CLOUD_LINE_HO_BAR_CELL_INFO_STRU          astCellInfoList[ucCellNum];
     *     }AT_CSS_CLOUD_LINE_HO_BAR_INFO_STRU;
     *   iiii.??enInfoType??AT_CSS_LINE_DETAIL_INFO_NO_INFO????????PLMN/??????????????????????????????modem??????ap??????PLMN/??????????????
     *   iiiii.??enInfoType????????????????????????????????????????????????????
     */
    VOS_UINT32 lineDetailBuffLen;
    VOS_UINT8  lineDetailBuff[4];
} AT_CSS_LineDetailSetReq;


typedef struct {
    VOS_MSG_HEADER         /* _H2ASN_Skip */
    VOS_UINT32     msgId;  /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      seq;    /* ?????? */
    VOS_UINT8      rsv;
    VOS_UINT32     result; /* VOS_OK??????????VOS_ERR???????? */
} CSS_AT_LineDetailSetCnf;


typedef struct {
    VOS_MSG_HEADER              /* _H2ASN_Skip */
    VOS_UINT32           msgId; /* _H2ASN_Skip */
    VOS_UINT16           clientId;
    MODEM_ID_ENUM_UINT16 modemId;
} AT_CSS_LineIndexListQueryReq;


typedef struct {
    VOS_MSG_HEADER                 /* _H2ASN_Skip */
    VOS_UINT32          msgId;     /* _H2ASN_Skip */
    VOS_UINT16          clientId;
    VOS_UINT8           versionId[AT_CSS_CLOUD_LINE_VERSION_LEN]; /* ?????? */
    VOS_UINT8           rsv;
    CSS_AT_PlmnId       rplmnInfo; /* rplmn???? */
    VOS_UINT32          result;    /* ???????????????? */
} CSS_AT_LineIndexListQueryCnf;


typedef struct {
    VOS_MSG_HEADER         /* _H2ASN_Skip */
    VOS_UINT32      msgId; /* _H2ASN_Skip */
    VOS_UINT16      clientId;
    VOS_UINT8       rsv[2];
    CSS_AT_PlmnId   rplmnInfo; /* rplmn???? */
} CSS_AT_LinePlmnNotify;


typedef struct {
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    VOS_UINT32 msgId;                                         /* _H2ASN_Skip */
    VOS_UINT16     clientId;                                  /* _H2ASN_Skip */
    VOS_UINT16     lineNum;                                   /* ???????? */
    VOS_UINT16     lineIndexList[AT_CSS_TACLAC_MAX_LINE_NUM]; /* ???????? */
    CSS_AT_PlmnId  plmnId;                                    /* plmn id */
} CSS_AT_LineIndexNotify;

/* add for CloudLine Feature 2017-6-29 end */

/* Added for VZW EMC, 2018-1-9, begin */

typedef struct {
    VOS_MSG_HEADER              /* _H2ASN_Skip */
    VOS_UINT32           msgId; /* _H2ASN_Skip */
    VOS_UINT16           clientId;
    MODEM_ID_ENUM_UINT16 modemId;
} AT_CSS_VzwmrucSetReq;


typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      rsv[2];
    VOS_UINT32     result; /* VOS_OK??????????VOS_ERR???????? */
} CSS_AT_VzwmrucSetCnf;


typedef struct {
    VOS_UINT8       entry;
    AT_CSS_RatUint8 rat;
    VOS_UINT16      bandId;
    CSS_AT_PlmnId   plmnId;
} AT_CSS_Mru;


typedef struct {
    VOS_MSG_HEADER              /* _H2ASN_Skip */
        VOS_UINT32       msgId; /* _H2ASN_Skip */
    VOS_UINT16           clientId;
    MODEM_ID_ENUM_UINT16 modemId;
    AT_CSS_Mru           mru;
} AT_CSS_VzwMrueSetReq;


typedef struct {
    VOS_MSG_HEADER        /* _H2ASN_Skip */
    VOS_UINT32     msgId; /* _H2ASN_Skip */
    VOS_UINT16     clientId;
    VOS_UINT8      rsv[2];
    VOS_UINT32     result; /* VOS_OK??????????VOS_ERR???????? */
} CSS_AT_VzwMrueSetCnf;


typedef struct {
    VOS_MSG_HEADER              /* _H2ASN_Skip */
    VOS_UINT32           msgId; /* _H2ASN_Skip */
    VOS_UINT16           clientId;
    MODEM_ID_ENUM_UINT16 modemId;
} AT_CSS_VzwMrueQueryReq;


typedef struct {
    VOS_MSG_HEADER         /* _H2ASN_Skip */
    VOS_UINT32     msgId;  /* _H2ASN_Skip */
    VOS_UINT32     result; /* VOS_OK??????????VOS_ERR???????? */
    VOS_UINT16     clientId;
    VOS_UINT8      rsv;
    VOS_UINT8      mruNum;
    AT_CSS_Mru     mru[AT_CSS_MRU_MAX_NUM];
} CSS_AT_VzwmrueQueryCnf;

/* Added for VZW EMC, 2018-1-9, end */

/* ASN???????? */
typedef struct {
    VOS_UINT32 msgId; /* _H2ASN_MsgChoice_Export CSS_AT_MsgTypeUint32  */
    VOS_UINT8  msg[4];
    /* _H2ASN_MsgChoice_When_Comment          CSS_AT_MSG_TYPE_ENUM_UINT32 */
} CSS_AT_InterfaceMsgData;
/* _H2ASN_Length UINT32 */

typedef struct {
    VOS_MSG_HEADER
    CSS_AT_InterfaceMsgData msgData;
} CSS_AT_InterfaceMsg;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
