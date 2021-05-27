
#ifndef __NV_STRU_PAM_H__
#define __NV_STRU_PAM_H__

#include "vos.h"
#include "nv_id_pam.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
#define ESN_NV_DATA_LEN (8)
#define MEID_NV_DATA_LEN (8)

/*
 * 功能说明: 物理端口号枚举值
 */
enum AT_PHY_Port {
    AT_UART_PORT = 0,
    AT_PCUI_PORT,
    AT_CTRL_PORT,
    AT_HSUART_PORT,
    AT_PCUI2_PORT,
    AT_PORT_BUTT
};
typedef VOS_UINT32 AT_PHY_PortUint32;

enum {
    CPM_IND_PORT = AT_PORT_BUTT, /* OM数据上报端口 */
    CPM_CFG_PORT,                /* OM配置端口 */
    CPM_SD_PORT,
    CPM_WIFI_OM_IND_PORT, /* WIFI下OM数据上报端口 */
    CPM_WIFI_OM_CFG_PORT, /* WIFI下OM配置下发端口 */
    CPM_WIFI_AT_PORT,     /* WIFI下AT端口 */
    CPM_HSIC_IND_PORT,
    CPM_HSIC_CFG_PORT,
    CPM_VCOM_IND_PORT, /* VCOM上OM数据上报接口 */
    CPM_VCOM_CFG_PORT, /* VCOM上OM配置接口 */
    CPM_FS_PORT,
    CPM_PORT_BUTT
};
typedef VOS_UINT32 CPM_PHY_PortUint32;


enum {
    CPM_CBT_PORT_USB,
    CPM_CBT_PORT_VCOM,
    CPM_CBT_PORT_SOCKET,
    CBP_CBT_PORT_BUTT
};
typedef VOS_UINT32 CPM_CBT_PortUint32;

enum {
    CPM_OM_PORT_TYPE_USB,
    CPM_OM_PORT_TYPE_VCOM,
    CPM_OM_PORT_TYPE_WIFI,
    CPM_OM_PORT_TYPE_SD,
    CPM_OM_PORT_TYPE_FS,
    CPM_OM_PORT_TYPE_HSIC,
    CBP_OM_PORT_TYPE_BUTT
};
typedef VOS_UINT32 CPM_OM_PortUint32;


enum ESN_MEID_Flag {
    ESN_MEID_DISABLE     = 0,
    ESN_ME_ENABLE_FLAG   = 1,
    MEID_ME_ENABLE_FLAG  = 2,
    ESN_MEID_ENABLE_BOTH = 3,
    ESN_MEID_ENABLE_FLAG_BUTT
};
typedef VOS_UINT8 ESN_MEID_FlagUint8;


typedef struct {
    VOS_UINT8  tempOverCount;      /* 超过告警门限最大次数。 */
    VOS_UINT8  tempRsumeCount;     /* 在低功耗模式或告警模式下温度连续低于告警门的极限次数 */
    VOS_UINT8  tempCloseCount;     /* 超过软关机门限最大次数。 */
    VOS_UINT8  tempPowerOffCount; /* 超过下电门限最大次数。 */
    VOS_UINT32 waitTimer;         /* 等待定时器时长 */
} TEMP_PARA_Ctrl;


typedef struct {
    /*
     * 0：高温保护关闭；
     * 1：高温保护打开。
     */
    VOS_UINT32 isEnable;
    /*
     * 温度检测点类型ID，表示使用哪里的温度作为温保的输入。代码将该值作为参数传入底层软件的温度获取接口中，获取温度，作为温度保护的判决依据。
     * HKADC_TEMP_BATTERY = 0
     * HKADC_TEMP_PA0 = 1
     * HKADC_TEMP_PA1 = 2
     * HKIADC_TEMP_SIM_CARD = 6
     * 值6表示采用SIM卡温度做温保；值0表示采用电池温度做温保；值1或2表示采用PA0或PA1温度做温保（根据产品设计可能只有一个PA）。
     */
    VOS_UINT32 location;
    VOS_INT32  powerOffThreshold;    /* 高温下电门限。如果温度检测点为SIM卡或电池，单位为1℃；如果温度检测点为PA，单位为0.1℃。此参数仅对E5 有效。如果不需要这个保护，请将这个值配置为无穷大。 */
    VOS_INT32  closeAdcThreshold;    /* 高温软关机门限。如果温度检测点为SIM卡或电池，单位为1℃；如果温度检测点为PA，单位为0.1℃。如果不需要这个保护，请将这个值配置为无穷大。 */
    VOS_INT32  alarmAdcThreshold;    /* 高温告警门限。如果温度检测点为SIM卡或电池，单位为1℃；如果温度检测点为PA，单位为0.1℃。如果不需要这个保护，请将这个值配置为无穷大。 */
    VOS_INT32  resumeAdcThreshold;   /* 恢复门限。如果温度检测点为SIM卡或电池，单位为1℃；如果温度检测点为PA，单位为0.1℃。 */
    VOS_INT32  sIMPowerOffThreshold; /* E5形态下，用于SIM 卡过温保护的门限值，单位为1℃。 */
    TEMP_PARA_Ctrl tempCtrlPara;     /* 每个控制子项 */
} SPY_TempProtectNv;


typedef struct {
    /*
     * OM使用的通道。当前仅USB和VCOM生效。
     * 0：USB
     * 1：VCOM
     * 2：WIFI
     * 3：SD卡
     * 4：文件系统
     * 5：HSIC
     */
    CPM_OM_PortUint32   portNum;
    /*
     * 校准使用的通道。
     * 0：USB
     * 1：VCOM
     * 2：WIFI,wifi 特性因为安全原因默认不编译，需要打开特性宏重新编译版本
     */
    CPM_CBT_PortUint32  cbtPortNum;
} OM_ChannlePortCfg;


enum USIMM_NvCardapp {
    USIMM_NV_GUTL_APP     = 0x00000000,
    USIMM_NV_IMS_APP      = 0x00000001,
    USIMM_NV_CDMA_APP     = 0x00000002,
    USIMM_NV_CARDAPP_BUTT = 0x00000003
};
typedef VOS_UINT32 USIMM_NvCardappUint32;


typedef struct {
    VOS_UINT8                    appNum;  /* 需要初始化的应用个数，目前最大值为3 */
    VOS_UINT8                    rsv[3];  /* 预留字段 */
    USIMM_NvCardappUint32        appList[5];  /* 初始化应用列表，初始化优先级从高到低 */
} USIMM_AppPriorityConfig;


typedef struct {
    /*
     * 0：不开替换功能
     * 开：0x5a5a，IMEI_0替换IMEI_2功能
     */
    VOS_UINT16 imei0ReplaseImei2;
    VOS_UINT16 rsv;  /* 预留 */
} NV_SC_PersCtrl;


typedef struct {
    /*
     * 0：关闭USIM调试模式；
     * 1：开启USIM调试模式。
     */
    VOS_UINT16 flag;
    VOS_UINT16 timerValue;  /* USIM模块初始化延迟时间，已不使用。 */
} USIMM_CmdDebugMode;


typedef struct {
    /*
     * ESN或MEID是否有效标记：
     * 0：ESN和MEID都无效；
     * 1：仅ESN有效；
     * 2：仅MEID有效；
     * 3：ESN和MEID都有效；
     */
    ESN_MEID_FlagUint8       esnMeIDFlag;
    VOS_UINT8                rsv;  /* 预留字节 */
    VOS_UINT8                esn[ESN_NV_DATA_LEN];   /* ESN内容，第一个字节表示长度信息； */
    VOS_UINT8                meId[MEID_NV_DATA_LEN]; /* MEID内容，第一个字节表示长度信息； */
    VOS_UINT8                rfu[6];  /* 预留字节 */
} NV_ESN_Meid;


typedef VOS_UINT32 SI_PB_StorateTypeUint32;
/* 结构说明  : USIM卡电话本控制信息。 */
typedef struct {
    /*
     * 0：未限定类型；
     * 1：SM；
     * 2：ME；
     * 3：SM和ME均可；
     * 4：ON；
     * 5：FD；
     * 6：EN；
     * 7：BD。
     * 此参数目前不使用。
     */
    SI_PB_StorateTypeUint32 curMaterial;
    VOS_UINT8               passwords[8];  /* 存储器密码，目前不使用。 */
    VOS_UINT16              used;  /* ME存储器已使用记录数，目前不使用。 */
    VOS_UINT16              total;  /* ME存储器最大支持记录数，目前不使用。 */
    VOS_UINT8               anrMaxNum; /* 扩展电话本支持的ANR文件的最大个数。最大支持3个，最小支持1个。 */
    /*
     * 扩展电话本是否支持EMAIL文件。
     * 0：不支持；
     * 1：支持。
     */
    VOS_UINT8               emailFlag;
    /*
     * 是否开启扩展电话本功能。
     * 0：不开启；
     * 1：开启。
     */
    VOS_UINT8               spbFlag;
    VOS_UINT8               rsv;  /* 保留。 */
} SI_PB_NVCtrlInfo;


typedef struct {
    VOS_UINT8 profileLen;  /* 长度指示。 */
    VOS_UINT8 profile[47];  /* profile内容。 */
} USIMM_UsimProfile;

typedef struct {
    VOS_UINT8 profileLen;  /* 长度指示。 */
    VOS_UINT8 profile[31];  /* profile内容。 */
} USIMM_SimProfile;

/* 结构说明  : 用于设置STK功能相关参数。 */
typedef struct {
    VOS_UINT8               funcEnable;  /* STK是否激活。 */
    VOS_UINT8               timer;  /* 默认的STK超时时间。 */
    VOS_UINT8               terminalType;  /* 终端类型，暂未使用。 */
    VOS_UINT8               rsv;  /* 预留字节，对齐用。 */
    USIMM_UsimProfile       usimProfile;  /* USIM Profile配置信息 */
    USIMM_SimProfile        simProfile;  /* SIM Profile配置信息 */
} USIMM_STK_CFG_STRU;

typedef USIMM_STK_CFG_STRU USIMM_StkCfg;


typedef struct {
    /*
     * bit[0-2] : 支持SCI的个数。
     * bit[3-7] : 保留。
     * bit[8-10] : modem 0使用的SCI接口，0：SCI0 1：SCI1；2：SCI2；其余值:多卡，暂不支持 。
     * bit[11-13] : modem 0使用的SCI接口，0：SCI0 1：SCI1；2：SCI2；其余值:多卡，暂不支持 。
     * bit[14-16] : modem 0使用的SCI接口，0：SCI0 1：SCI1；2：SCI2；其余值:多卡，暂不支持 。
     * bit[17-31] : 保留 。
     */
    VOS_UINT32 value;
} NV_SCI_Cfg;

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
