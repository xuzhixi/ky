#ifndef _KY_LINKLIST_H
#define _KY_LINKLIST_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct ky_linklist_s
{
	void *value;
	struct ky_linklist_s *next;
}ky_linklist_s, ky_linklist_iter_t;

typedef size_t ky_linklist_value_len_t;
typedef int (*ky_linklist_comparefun_t)(void *, void *);

typedef struct ky_linklist_t
{
	ky_linklist_value_len_t value_len;
	ky_linklist_comparefun_t cmp_fun;
	ky_linklist_s *head;
	ky_linklist_s *tail;
}ky_linklist_t;


/**
 * @brief new一个链表
 *
 * 这个函数新建的链表，在不再使用的时候，要调用ky_linklist_release来释放
 *
 * @param  valueLen		值的长度
 * @param  cmpFun		值的比较函数
 * @return				返回新建的链表
 */
extern ky_linklist_t *ky_linklist_new(ky_linklist_value_len_t valueLen, ky_linklist_comparefun_t cmpFun);
/**
 * @brief 清空链表
 */
extern void ky_linklist_clear(ky_linklist_t *linklist);
/**
 * @brief 释放通过 ky_linklist_new 函数生成的链表
 */
extern void ky_linklist_release(ky_linklist_t *linklist);
/**
 * @brief 判断链表是否为空 
 *
 * @retval  1	为空
 * @retval	0	不为空
 */
extern int ky_linklist_is_null(ky_linklist_t *linklist);
/**
 * @brief 查找链表中,是否有某个值
 *
 * 如果找到, 则返回这个value, 否则返回NULL
 * 需要注意的是: 返回的value指针，是指向链表中实际的value的; 对其修改，会影响链表里这个key所对应的value
 */
extern void *ky_linklist_find(ky_linklist_t *linklist, void *value);
/**
 * @brief 在链表中末尾添加一个值
 *
 * 链表保存的值，是value所指内容的一个copy
 */
extern void ky_linklist_add(ky_linklist_t *linklist, void *value);
extern void ky_linklist_addv(ky_linklist_t *linklist, void *value, ky_linklist_value_len_t valueLen);
/**
 * @brief 在链表中插入一个值
 *
 * 如果没有找到插入的位置，则在末尾插入
 *
 * @param  linklist		操作的链表
 * @param  value		插入的值
 * @param  insertValue  插入的位置
 */
extern void ky_linklist_insert(ky_linklist_t *linklist, void *value, void *insertValue);
extern void ky_linklist_insertv(ky_linklist_t *linklist, void *value, void *insertValue, ky_linklist_value_len_t valueLen);
/**
 * @brief 修改链表的值
 *
 * 如果链表中存在这个value, 则修改这个value
 * 如果链表中中不存在这个value, 则把这个value添加到链表的末尾
 */
extern void ky_linklist_mod(ky_linklist_t *linklist, void *value);
extern void ky_linklist_modv(ky_linklist_t *linklist, void *value, ky_linklist_value_len_t valueLen);
/**
 * @brief 删除链表中的某个值
 */
extern void ky_linklist_del(ky_linklist_t *linklist, void *value);

/**
 * @brief 为链表创建一个迭代器
 */
extern ky_linklist_iter_t *ky_linklist_iter(ky_linklist_t *linklist);
/**
 * @brief 迭代器移动到下一项
 */
extern ky_linklist_iter_t *ky_linklist_iter_next(ky_linklist_iter_t *iter);
/**
 * @brief 获取迭代器当前所指向的值
 */
extern void *ky_linklist_iter_value(ky_linklist_iter_t *iter);


#ifdef __cplusplus
}
#endif

#endif // _KY_LINKLIST_H
