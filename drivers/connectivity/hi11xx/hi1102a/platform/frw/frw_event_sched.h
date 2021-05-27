

#ifndef __FRW_EVENT_SCHED_H__
#define __FRW_EVENT_SCHED_H__
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* ����ͷ�ļ����� */
#include "oal_ext_if.h"
#include "frw_main.h"

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_SCHED_H

/* �궨�� */
/* ��ȡ�¼��������Ѿ�������¼����� */
#define FRW_EVENT_QUEUE_GET_PENDING_EVENTS_NUM(_pst_event_queue) oal_queue_get_length(&(_pst_event_queue)->st_queue)

/* ö�ٶ��� */
/*
 * ö����  : frw_sched_policy_enum_uint8
 * ö��˵��: �¼����ж�Ӧ�ĵ��Ȳ���
 */
typedef enum {
    FRW_SCHED_POLICY_HI = 0,     /* �����ȼ����� */
    FRW_SCHED_POLICY_NORMAL = 1, /* ��ͨ���ȼ����� */

    FRW_SCHED_POLICY_BUTT
} frw_sched_policy_enum;
typedef oal_uint8 frw_sched_policy_enum_uint8;

/*
 * ö����  : frw_event_queue_state_enum_uint8
 * ö��˵��: �¼�����״̬
 */
typedef enum {
    FRW_EVENT_QUEUE_STATE_INACTIVE = 0, /* �¼����в���Ծ(���ɱ�����) */
    FRW_EVENT_QUEUE_STATE_ACTIVE,       /* �¼����л�Ծ(�ɱ�����) */

    FRW_EVENT_QUEUE_STATE_BUTT
} frw_event_queue_state_enum;
typedef oal_uint8 frw_event_queue_state_enum_uint8;

/*
 * ö����  : frw_vap_state_enum_uint8
 * ö��˵��: �¼���������
 */
typedef enum {
    FRW_VAP_STATE_RESUME = 0, /* VAP�ָ� */
    FRW_VAP_STATE_PAUSE,      /* VAP��ͣ */

    FRW_VAP_STATE_BUTT
} frw_vap_state_enum;
typedef oal_uint8 frw_vap_state_enum_uint8;

/*
 * �ṹ��  : frw_event_sched_queue_stru
 * �ṹ˵��: �ɵ��ȶ���
 */
typedef struct {
    oal_spin_lock_stru st_lock;
    oal_uint32 ul_total_weight_cnt; /* �ɵ��ȶ����ϵ���Ȩ�ؼ����� */
    oal_dlist_head_stru st_head;    /* �ɵ��ȶ��е��¼�����ͷ */
} frw_event_sched_queue_stru;

/*
 * �ṹ��  : frw_event_queue_stru
 * �ṹ˵��: �¼����нṹ��
 */
typedef struct tag_frw_event_queue_stru {
    oal_spin_lock_stru st_lock;
    oal_queue_stru st_queue;                   /* ���� */
    frw_event_queue_state_enum_uint8 en_state; /* ����״̬ */
    frw_sched_policy_enum_uint8 en_policy;     /* ���е��Ȳ���(�����ȼ�����ͨ���ȼ�) */

    oal_uint8 uc_weight;     /* WRRȨ������ֵ */
    oal_uint8 uc_weight_cnt; /* WRRȨ�ؼ����� */

    frw_vap_state_enum_uint8 en_vap_state; /* VAP��״ֵ̬��0Ϊ�ָ���1Ϊ��ͣ */
    oal_uint8 auc_resv[3];

    oal_dlist_head_stru st_list;
} frw_event_queue_stru;

/* �������� */
extern oal_uint32 frw_event_sched_init(frw_event_sched_queue_stru *pst_sched_queue);
extern oal_uint32 frw_event_queue_init(frw_event_queue_stru *pst_event_queue,
                                       oal_uint8 uc_weight,
                                       frw_sched_policy_enum_uint8 en_policy,
                                       frw_event_queue_state_enum_uint8 en_state,
                                       oal_uint8 uc_max_events);
extern oal_void frw_event_queue_destroy(frw_event_queue_stru *pst_event_queue);
extern oal_void *frw_event_sched_pick_next_event_queue_wrr(frw_event_sched_queue_stru *pst_sched_queue);
extern oal_uint32 frw_event_sched_deactivate_queue(frw_event_sched_queue_stru *pst_sched_queue,
                                                   frw_event_queue_stru *pst_event_queue);

extern oal_uint32 frw_event_sched_activate_queue(frw_event_sched_queue_stru *pst_sched_queue,
                                                 frw_event_queue_stru *pst_event_queue);

extern oal_void frw_event_sched_pause_queue(frw_event_sched_queue_stru *pst_sched_queue,
                                            frw_event_queue_stru *pst_event_queue);
extern oal_void frw_event_sched_resume_queue(frw_event_sched_queue_stru *pst_sched_queue,
                                             frw_event_queue_stru *pst_event_queue);

/*
 * �� �� ��  : frw_event_sched_reset_weight
 * ��������  : ���õ��ȶ����ϸ����¼����е�Ȩ�ؼ�����
 * �������  : pst_sched_queue: ���ȶ���ָ��
 * �� �� ֵ  : OAL_SUCC ������������
 */
OAL_STATIC OAL_INLINE oal_void frw_event_sched_reset_weight(frw_event_sched_queue_stru *pst_sched_queue)
{
    oal_dlist_head_stru *pst_list = NULL;
    frw_event_queue_stru *pst_event_queue = NULL;

    if (OAL_UNLIKELY(pst_sched_queue == NULL)) {
        OAL_WARN_ON(1);
        return;
    }

    /* ���������������� */
    OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_sched_queue->st_head)
    {
        /* ��ȡ���������е�һ���¼����� */
        pst_event_queue = OAL_DLIST_GET_ENTRY(pst_list, frw_event_queue_stru, st_list);

        /* ֻ�����ûָ�״̬VAP��Ȩ��ֵ */
        if (pst_event_queue->en_vap_state == FRW_VAP_STATE_RESUME) {
            /* �����¼����е�Ȩ�ؼ����� */
            pst_event_queue->uc_weight_cnt = pst_event_queue->uc_weight;

            /* ���µ��ȶ����ϵ���Ȩ�ؼ����� */
            pst_sched_queue->ul_total_weight_cnt += pst_event_queue->uc_weight;
        }
    }
}

/*
 * �� �� ��  : frw_event_schedule
 * ��������  : �¼�������ں���
 * �������  : pst_sched_queue: ���ȶ���ָ��
 * �� �� ֵ  : �ɹ�: �¼��ڴ�ָ��
 */
OAL_STATIC OAL_INLINE oal_void *frw_event_schedule(frw_event_sched_queue_stru *pst_sched_queue)
{
    oal_void *p_event = NULL;
    frw_event_sched_queue_stru *pst_queue = NULL;

    if (OAL_UNLIKELY(pst_sched_queue == NULL)) {
        OAL_WARN_ON(1);
        return NULL;
    }

    /* ����ȫ�������� */
    pst_queue = &pst_sched_queue[FRW_SCHED_POLICY_HI];

    /* ��������ȼ����ȶ���Ϊ�գ���ȡ��һ�����ȶ��� */
    if (!oal_dlist_is_empty(&pst_queue->st_head)) {
        /* �ӵ���������ѡ��һ�����������¼� */
        p_event = frw_event_sched_pick_next_event_queue_wrr(pst_queue);

        if (p_event != NULL) {
            return p_event;
        }
    }

    pst_queue = &pst_sched_queue[FRW_SCHED_POLICY_NORMAL];

    /* �����ͨ���ȼ����ȶ���Ϊ�գ���ȡ��һ�����ȶ��� */
    if (!oal_dlist_is_empty(&pst_queue->st_head)) {
        /* �ӵ���������ѡ��һ�����������¼� */
        p_event = frw_event_sched_pick_next_event_queue_wrr(pst_queue);

        if (p_event != NULL) {
            return p_event;
        }
    }

    return OAL_PTR_NULL;
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_event_sched.h */