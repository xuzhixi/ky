//===============================================
/**
 *  @file ky_rbtree.h
 *
 *  @author XuZhiXi
 *  Email   zhixi.xu@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:12:48
 *  Last   modified:  2012-10-17 08:12:48
 *
 *  Description: 
 */
//================================================

#ifndef _KY_RBTREE_H
#define _KY_RBTREE_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/// 红黑树的颜色
typedef enum ky_rbtree_color_t
{
	KY_RBTREE_RED = 0,
	KY_RBTREE_BLACK = 1
}ky_rbtree_color_t;

typedef size_t ky_rbtree_key_len_t;
typedef size_t ky_rbtree_value_len_t;

/// 红黑树的一个节点，内部使用的结构体
typedef struct ky_rbtree_s
{
	struct ky_rbtree_s *parent;
	struct ky_rbtree_s *left;
	struct ky_rbtree_s *right;
	ky_rbtree_color_t color;
	void *key;
	void  *value;
	ky_rbtree_key_len_t key_len;
	ky_rbtree_value_len_t value_len;
}ky_rbnode_s, ky_rbtree_s;

typedef int (*ky_rbtree_comparefun_t)(void *, void *);

/// 红黑树的结构体
typedef struct ky_rbtree_t
{
	ky_rbtree_key_len_t key_len;
	ky_rbtree_value_len_t value_len;
	ky_rbtree_comparefun_t cmp_fun;
	ky_rbtree_s *tree;
}ky_rbtree_t;

/// 红黑树的空节点(哨兵节点)
extern ky_rbtree_s *ky_rbtree_nil;


/**
 * @brief new一个红黑树(用来存储键值对) 
 *
 * 这个函数新建的红黑树，在不再使用的时候，要调用ky_rbtree_release来释放
 *
 * @param  keyLen		键的长度
 * @param  valueLen		值的长度
 * @param  cmpFun		键的比较函数
 * @return				返回新建的红黑树
 */
extern ky_rbtree_t *ky_rbtree_new(ky_rbtree_key_len_t keyLen, ky_rbtree_value_len_t valueLen, ky_rbtree_comparefun_t cmpFun);
/**
 * @brief 清空红黑树
 */
extern void ky_rbtree_clear(ky_rbtree_t *rbtree);
/**
 * @brief 释放通过 ky_rbtree_new 函数生成的红黑树
 */
extern void ky_rbtree_release(ky_rbtree_t *rbtree);
/**
 * @brief 判断红黑树是否为空 
 *
 * @retval  1	为空
 * @retval	0	不为空
 */
extern int ky_rbtree_is_null(ky_rbtree_t *rbtree);
/**
 * @brief 在红黑树中添加一个键值对
 *
 * 红黑树保存的键值对，是key、value所指内容的一个copy
 */
extern void ky_rbtree_add(ky_rbtree_t *rbtree, void *key, void *value);
extern void ky_rbtree_addv(ky_rbtree_t *rbtree, void *key, ky_rbtree_key_len_t keyLen, void *value, ky_rbtree_value_len_t valueLen);
/**
 * @brief 修改红黑树的键值对
 *
 * 如果红黑树中存在这个key, 则修改其对应的value
 * 如果红黑树中不存在这个key, 则把这个键值对插入到红黑树中
 */
extern void ky_rbtree_mod(ky_rbtree_t *rbtree, void *key, void *value);
extern void ky_rbtree_modv(ky_rbtree_t *rbtree, void *key, ky_rbtree_key_len_t keyLen, void *value, ky_rbtree_value_len_t valueLen);
/**
 * @brief 删除红黑树的键值对
 */
extern void ky_rbtree_del(ky_rbtree_t *rbtree, void *key);
/**
 * @brief 查找红黑树中,key对应的value
 *
 * 如果找到key, 则返回对应的value, 否则返回NULL
 * 需要注意的是: 返回的value指针，是指向红黑树中实际的value的; 对其修改，会影响红黑树里这个key所对应的value
 */
extern void *ky_rbtree_find(ky_rbtree_t *rbtree, void *key);
/**
 * @brief 查找红黑树中，最大的key对应的value
 */
extern void *ky_rbtree_find_max(ky_rbtree_t *rbtree);
/**
 * @brief 查找红黑树中，最小的key对应的value
 */
extern void *key_rbtree_find_min(ky_rbtree_t *rbtree);


#ifdef __cplusplus
}
#endif

#endif // _KY_BRTREE_H
