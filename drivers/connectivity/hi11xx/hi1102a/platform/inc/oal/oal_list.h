

#ifndef __OAL_LIST_H__
#define __OAL_LIST_H__

/* 其他头文件包含 */
#include "oal_types.h"
#include "oal_mm.h"
#include "oal_util.h"

/* 宏定义 */
/* 单向链表头初始化 */
#define OAL_LIST_HEAD_INIT(_list_name)                                             \
    {                                                                              \
        (oal_list_entry_stru *)&(_list_name), (oal_list_entry_stru *)&(_list_name) \
    }

/* 单向创建链表头 */
/*lint -e773*/
#define OAL_LIST_CREATE_HEAD(_list_name) \
    oal_list_head_stru _list_name = OAL_LIST_HEAD_INIT(_list_name)

/* 单向遍历链表使用时请在其后加大括号 */
#define OAL_LIST_SEARCH_FOR_EACH(_list_pos, _list_head) \
    for ((_list_pos) = (_list_head)->pst_next; (_list_pos) != (oal_list_entry_stru *)(_list_head); \
         (_list_pos) = (_list_pos)->pst_next)

/*
 * 获得单向链表中指定的节点 第一个参数为模板链表结构体指针；
 * 第二个参数为链表中数据结构体类型名；
 * 第三个参数为数据结构体中模板链表结构体的名字
 */
#define OAL_LIST_GET_ENTRY(_list_ptr, _data_type, _data_member_list_name) \
    ((_data_type *)((oal_int8 *)(_list_ptr) - (oal_uint)(&((_data_type *)0)->_data_member_list_name))) /*lint -e(413)*/

/* 双向链表头初始化 */
#define OAL_DLIST_HEAD_INIT(_dlist_name) \
    {                                    \
        &(_dlist_name), &(_dlist_name)   \
    }

/* 创建双向链表头 */
/*lint -e773*/
#define OAL_DLIST_CREATE_HEAD(_dlist_name) \
    oal_dlist_head_stru _dlist_name = OAL_DLIST_HEAD_INIT(_dlist_name)

/* 遍历双向链表使用时请在其后加大括号 */
#define OAL_DLIST_SEARCH_FOR_EACH(_dlist_pos, _dilst_head) \
    for ((_dlist_pos) = (_dilst_head)->pst_next; (_dlist_pos) != (_dilst_head); (_dlist_pos) = (_dlist_pos)->pst_next)

/* 遍列双向链表，并可安全删除某个节点 */
#define OAL_DLIST_SEARCH_FOR_EACH_SAFE(_dlist_pos, n, _dilst_head) \
    for ((_dlist_pos) = (_dilst_head)->pst_next, (n) = (_dlist_pos)->pst_next; (_dlist_pos) != (_dilst_head); \
         (_dlist_pos) = (n), (n) = (_dlist_pos)->pst_next)

/*
 * 获得双向链表中指定的节点 第一个参数为模板链表结构体指针；
 * 第二个参数为链表中数据结构体类型名；
 * 第三个参数为数据结构体中模板链表结构体的名字
 */
#define OAL_DLIST_GET_ENTRY(_dlist_ptr, _data_type, _data_member_dlist_name) \
    ((_data_type *)((oal_int8 *)(_dlist_ptr) - (oal_uint)(&((_data_type *)0)->_data_member_dlist_name))) /*lint -e(413)*/

/* STRUCT定义 */
typedef struct tag_oal_list_entry_stru {
    struct tag_oal_list_entry_stru *pst_next;
} oal_list_entry_stru;

typedef struct {
    struct tag_oal_list_entry_stru *pst_next;
    struct tag_oal_list_entry_stru *pst_prev;
} oal_list_head_stru;

typedef struct tag_oal_dlist_head_stru {
    struct tag_oal_dlist_head_stru *pst_next;
    struct tag_oal_dlist_head_stru *pst_prev;
} oal_dlist_head_stru;

/* 函数声明 */
/*
 * 函 数 名  : oal_list_init_head
 * 功能描述  : 初始化单向链表头
 * 输入参数  : pst_list_head: 单向链表头指针
 */
OAL_STATIC OAL_INLINE oal_void oal_list_init_head(oal_list_head_stru *pst_list_head)
{
    if (OAL_UNLIKELY(pst_list_head == NULL)) {
        OAL_WARN_ON(1);
        return;
    }
    pst_list_head->pst_next = (oal_list_entry_stru *)pst_list_head;
    pst_list_head->pst_prev = (oal_list_entry_stru *)pst_list_head;
}

/*
 * 函 数 名  : oal_list_add
 * 功能描述  : 将链表节点加入到链表的尾部
 * 输入参数  : pst_new: 新加入节点指针
 *             pst_head: 链表头
 */
OAL_STATIC OAL_INLINE oal_void oal_list_add(oal_list_entry_stru *pst_new,
                                            oal_list_head_stru *pst_head)
{
    oal_list_entry_stru *pst_tail = NULL;
    if (OAL_UNLIKELY((pst_new == NULL) || (pst_head == NULL))) {
        OAL_WARN_ON(1);
        return;
    }
    pst_tail = pst_head->pst_prev;

    pst_tail->pst_next = pst_new;
    pst_new->pst_next = (oal_list_entry_stru *)pst_head;
    pst_head->pst_prev = pst_new;
}

/*
 * 函 数 名  : oal_list_delete_head
 * 功能描述  : 从链表头删除一个节点，不负责释放，不判断链表是否为空，请注意
 * 输入参数  : pst_head: 链表头
 * 返 回 值  : 被删除的节点
 */
OAL_STATIC OAL_INLINE oal_list_entry_stru *oal_list_delete_head(oal_list_head_stru *pst_head)
{
    oal_list_entry_stru *pst_node = NULL;

    if (OAL_UNLIKELY(pst_head == NULL)) {
        OAL_WARN_ON(1);
        return NULL;
    }

    if (pst_head->pst_next == (oal_list_entry_stru *)pst_head) {
        return OAL_PTR_NULL;
    }

    pst_node = pst_head->pst_next;
    pst_head->pst_next = pst_node->pst_next;

    if (pst_head->pst_next == (oal_list_entry_stru *)pst_head) {
        pst_head->pst_prev = pst_head->pst_next;
    }

    pst_node->pst_next = OAL_PTR_NULL;

    return pst_node;
}

/*
 * 函 数 名  : oal_list_jion
 * 功能描述  : 将参数2的单向链表合入参数1的单向链表中
 */
OAL_STATIC OAL_INLINE oal_void oal_list_jion(oal_list_head_stru *pst_head1, oal_list_head_stru *pst_head2)
{
    oal_list_entry_stru *pst_list1_tail = NULL;
    oal_list_entry_stru *pst_list2_tail = NULL;

    if (OAL_UNLIKELY((pst_head1 == NULL) || (pst_head2 == NULL))) {
        OAL_WARN_ON(1);
        return;
    }

    pst_list1_tail = pst_head1->pst_prev;
    pst_list2_tail = pst_head2->pst_prev;
    pst_list1_tail->pst_next = pst_head2->pst_next;
    pst_head1->pst_prev = pst_head2->pst_prev;
    pst_list2_tail->pst_next = (oal_list_entry_stru *)pst_head1;
}

/*
 * 函 数 名  : oal_list_is_empty
 * 功能描述  : 判断一个链表是否为空
 * 输入参数  : pst_head: 链表头指针
 */
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 oal_list_is_empty(oal_list_head_stru *pst_head)
{
    if (OAL_UNLIKELY(pst_head == NULL)) {
        OAL_WARN_ON(1);
        return OAL_FALSE;
    }
    return pst_head->pst_next == (oal_list_entry_stru *)pst_head;
}

/*
 * 函 数 名  : oal_dlist_init_head
 * 功能描述  : 链表初始化函数
 * 输入参数  : pst_list: 链表头指针
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_init_head(oal_dlist_head_stru *pst_list)
{
    if (OAL_UNLIKELY(pst_list == NULL)) {
        OAL_WARN_ON(1);
        return;
    }
    pst_list->pst_next = pst_list;
    pst_list->pst_prev = pst_list;
}

/*
 * 函 数 名  : oal_dlist_add
 * 功能描述  : 链表节点加入操作
 * 输入参数  : pst_new: 新加入节点指针
 *             pst_prev: 加入位置的前一个节点指针
 *             pst_next: 加入位置的下一个节点指针
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_add(oal_dlist_head_stru *pst_new,
                                             oal_dlist_head_stru *pst_prev,
                                             oal_dlist_head_stru *pst_next)
{
    if (OAL_UNLIKELY((pst_new == NULL) || (pst_prev == NULL) || (pst_prev == NULL))) {
        OAL_WARN_ON(1);
        return;
    }
    pst_next->pst_prev = pst_new;
    pst_new->pst_next = pst_next;
    pst_new->pst_prev = pst_prev;
    pst_prev->pst_next = pst_new;
}

/*
 * 函 数 名  : oal_dlist_delete
 * 功能描述  : 从链表的指定位置删除一个节点提炼
 * 输入参数  : pst_prev: 删除位置的前一个节点指针
 *             pst_next: 删除位置的下一个节点指针
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_delete(oal_dlist_head_stru *pst_prev, oal_dlist_head_stru *pst_next)
{
    if (OAL_UNLIKELY((pst_prev == NULL) || (pst_next == NULL))) {
        OAL_WARN_ON(1);
        return;
    }
    pst_next->pst_prev = pst_prev;
    pst_prev->pst_next = pst_next;
}

/*
 * 函 数 名  : oal_dlist_is_empty
 * 功能描述  : 判断一个链表是否为空
 * 输入参数  : pst_head: 链表头指针
 */
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 oal_dlist_is_empty(oal_dlist_head_stru *pst_head)
{
    if (OAL_UNLIKELY(pst_head == NULL)) {
        OAL_WARN_ON(1);
        return OAL_TRUE;
    }
    if (pst_head->pst_next == OAL_PTR_NULL || pst_head->pst_prev == OAL_PTR_NULL) {
        return OAL_TRUE;
    }

    return pst_head->pst_next == pst_head;
}

/*
 * 函 数 名  : oal_dlist_add_head
 * 功能描述  : 往链表头部插入节点
 * 输入参数  : pst_new: 要插入的新节点
 *             pst_head: 链表头指针
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_add_head(oal_dlist_head_stru *pst_new, oal_dlist_head_stru *pst_head)
{
    oal_dlist_add(pst_new, pst_head, pst_head->pst_next);
}

/*
 * 函 数 名  : oal_dlist_add_tail
 * 功能描述  : 向链表尾部插入节点
 * 输入参数  : pst_new: 要插入的新节点
 *             pst_head: 链表头指针
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_add_tail(oal_dlist_head_stru *pst_new, oal_dlist_head_stru *pst_head)
{
    oal_dlist_add(pst_new, pst_head->pst_prev, pst_head);
}

/*
 * 函 数 名  : oal_dlist_delete_entry
 * 功能描述  : 删除链表中的指定节点,不负责释放，不判断链表是否为空，请注意
 * 输入参数  : pst_entry: 需要删除的节点
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_delete_entry(oal_dlist_head_stru *pst_entry)
{
    if (OAL_UNLIKELY(pst_entry == NULL)) {
        OAL_WARN_ON(1);
        return ;
    }

    if (OAL_UNLIKELY((pst_entry->pst_next == OAL_PTR_NULL) || (pst_entry->pst_prev == OAL_PTR_NULL))) {
        return;
    }

    oal_dlist_delete(pst_entry->pst_prev, pst_entry->pst_next);
    pst_entry->pst_next = OAL_PTR_NULL;
    pst_entry->pst_prev = OAL_PTR_NULL;
}

/*
 * 函 数 名  : oal_dlist_delete_head
 * 功能描述  : 从双向链表头部删除一个节点,不判断链表是否为空，不负责释放内存 请注意
 */
OAL_STATIC OAL_INLINE oal_dlist_head_stru *oal_dlist_delete_head(oal_dlist_head_stru *pst_head)
{
    oal_dlist_head_stru *pst_node = NULL;

    if (OAL_UNLIKELY(pst_head == NULL)) {
        OAL_WARN_ON(1);
        return NULL;
    }

    pst_node = pst_head->pst_next;

    OAL_WARN_ON(pst_node == pst_head);
    OAL_WARN_ON(pst_node == OAL_PTR_NULL);

    oal_dlist_delete_entry(pst_node);

    return pst_node;
}

/*
 * 函 数 名  : oal_dlist_delete_tail
 * 功能描述  : 从双向链表头部删除一个节点,不判断链表是否为空，不负责释放内存 请注意
 */
OAL_STATIC OAL_INLINE oal_dlist_head_stru *oal_dlist_delete_tail(oal_dlist_head_stru *pst_head)
{
    oal_dlist_head_stru *pst_node = NULL;
    if (OAL_UNLIKELY(pst_head == NULL)) {
        OAL_WARN_ON(1);
        return NULL;
    }
    pst_node = pst_head->pst_prev;

    OAL_WARN_ON(pst_node == pst_head);
    OAL_WARN_ON(pst_node == OAL_PTR_NULL);

    oal_dlist_delete_entry(pst_node);

    return pst_node;
}

/*
 * 函 数 名  : oal_dlist_join_tail
 * 功能描述  : 将链表2 加入链表1的尾部
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_join_tail(oal_dlist_head_stru *pst_head1, oal_dlist_head_stru *pst_head2)
{
    oal_dlist_head_stru *pst_dlist1_tail = NULL;
    oal_dlist_head_stru *pst_dlist2_tail = NULL;
    oal_dlist_head_stru *pst_dlist2_first = NULL;

    if (OAL_UNLIKELY((pst_head1 == NULL) || (pst_head2 == NULL))) {
        OAL_WARN_ON(1);
        return;
    }

    pst_dlist1_tail = pst_head1->pst_prev;
    pst_dlist2_tail = pst_head2->pst_prev;
    pst_dlist2_first = pst_head2->pst_next;
    pst_dlist1_tail->pst_next = pst_dlist2_first;
    pst_dlist2_first->pst_prev = pst_dlist1_tail;
    pst_head1->pst_prev = pst_dlist2_tail;
    pst_dlist2_tail->pst_next = pst_head1;
}

/*
 * 函 数 名  : oal_dlist_join_head
 * 功能描述  : 将链表2 加入链表1的头部 也可用于将新链表 加入链表的指定节点后
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_join_head(oal_dlist_head_stru *pst_head1, oal_dlist_head_stru *pst_head2)
{
    oal_dlist_head_stru *pst_head2_first = NULL;
    oal_dlist_head_stru *pst_head2_tail = NULL;
    oal_dlist_head_stru *pst_head1_first = NULL;

    if (OAL_UNLIKELY((pst_head1 == NULL) || (pst_head2 == NULL))) {
        OAL_WARN_ON(1);
        return;
    }

    if (oal_dlist_is_empty(pst_head2)) {
        return;
    }

    pst_head2_first = pst_head2->pst_next;
    pst_head2_tail = pst_head2->pst_prev;
    pst_head1_first = pst_head1->pst_next;

    pst_head1->pst_next = pst_head2_first;
    pst_head2_first->pst_prev = pst_head1;
    pst_head2_tail->pst_next = pst_head1_first;
    pst_head1_first->pst_prev = pst_head2_tail;
}

/*
 * 函 数 名  : oal_dlist_remove_head
 * 功能描述  : 将链表2中从第一个元素到pst_last_dscr_entry元素摘出， 加入空链表1的头部
 * 输入参数  :  pst_head1 :链表头1, 空链表
 *              pst_head2 :链表头2
 *              pst_last_entry : 链表2中的元素
 *              默认入参都非NULL
 */
OAL_STATIC OAL_INLINE oal_void oal_dlist_remove_head(oal_dlist_head_stru *pst_head1,
                                                     oal_dlist_head_stru *pst_head2,
                                                     oal_dlist_head_stru *pst_last_entry)
{
    if (OAL_UNLIKELY((pst_head1 == NULL) || (pst_head2 == NULL) || (pst_last_entry == NULL))) {
        OAL_WARN_ON(1);
        return;
    }

    /* 对pst_head1赋值 */
    pst_head1->pst_next = pst_head2->pst_next;
    pst_head1->pst_prev = pst_last_entry;

    pst_head2->pst_next = pst_last_entry->pst_next;
    /* pst_last_entry为pst_head2中最后一个成员 */
    if (pst_last_entry->pst_next == pst_head2) {
        pst_head2->pst_prev = pst_head2;
    } else { /* pst_last_entry非pst_head2中最后一个成员 */
        ((oal_dlist_head_stru *)(pst_last_entry->pst_next))->pst_prev = pst_head2;
    }

    pst_last_entry->pst_next = pst_head1;
    /* pst_last_entry为pst_head2中第一个成员 */
    if (pst_last_entry->pst_prev == pst_head2) {
        pst_last_entry->pst_prev = pst_head1;
    }
}

#endif /* end of oal_list.h */
