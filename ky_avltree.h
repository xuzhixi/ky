//===============================================
/**
 *  @file ky_avltree.h
 *
 *  @author XuZhiXi
 *  Email   zhixi.xu@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:11:10
 *  Last   modified:  2012-10-17 08:11:10
 *
 *  Description: 
 */
//================================================

#ifndef _KY_AVLTREE_H
#define _KY_AVLTREE_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef ssize_t ky_avltree_height_t;

typedef size_t ky_avltree_key_len_t;
typedef size_t ky_avltree_value_len_t;

/// AVL树的一个节点，内部使用的结构体
typedef struct ky_avltree_s
{
	struct ky_avltree_s *left;
	struct ky_avltree_s *right;
	ky_avltree_height_t height;	
	void *key;
	void  *value;
	ky_avltree_key_len_t key_len;
	ky_avltree_value_len_t value_len;
}ky_avlnode_s, ky_avltree_s;

typedef int (*ky_avltree_comparefun_t)(void *, void *);

/// AVL树结构体
typedef struct ky_avltree_t
{
	ky_avltree_key_len_t key_len;
	ky_avltree_value_len_t value_len;
	ky_avltree_comparefun_t cmp_fun;
	ky_avltree_s *tree;
}ky_avltree_t;


/**
 * @brief new一个AVL树(用来存储键值对) 
 *
 * 这个函数新建的AVL树，在不再使用的时候，要调用ky_avltree_release来释放
 *
 * @param  keyLen		键的长度
 * @param  valueLen		值的长度
 * @param  cmpFun		键的比较函数
 * @return				返回新建的AVL树
 */
extern ky_avltree_t *ky_avltree_new(ky_avltree_key_len_t keyLen, ky_avltree_value_len_t valueLen, ky_avltree_comparefun_t cmpFun);
/**
 * @brief 清空AVL树
 */
extern void ky_avltree_clear(ky_avltree_t *avltree);
/**
 * @brief 释放通过 ky_avltree_new 函数生成的AVL树
 */
extern void ky_avltree_release(ky_avltree_t *avltree);
/**
 * @brief 判断AVL树是否为空 
 *
 * @retval  1	为空
 * @retval	0	不为空
 */
extern int ky_avltree_is_null(ky_avltree_t *avltree);
/**
 * @brief 在AVL树中添加一个键值对
 *
 * AVL树保存的键值对，是key、value所指内容的一个copy
 */
extern void ky_avltree_add(ky_avltree_t *avltree, void *key, void *value);
extern void ky_avltree_addv(ky_avltree_t *avltree, void *key, ky_avltree_key_len_t keyLen, void *value, ky_avltree_value_len_t valueLen);
/**
 * @brief 修改AVL树的键值对
 *
 * 如果AVL树中存在这个key, 则修改其对应的value
 * 如果AVL树中不存在这个key, 则把这个键值对插入到AVL树中
 */
extern void ky_avltree_mod(ky_avltree_t *avltree, void *key, void *value);
extern void ky_avltree_modv(ky_avltree_t *avltree, void *key, ky_avltree_key_len_t keyLen, void *value, ky_avltree_value_len_t valueLen);
/**
 * @brief 删除AVL树的键值对
 */
extern void ky_avltree_del(ky_avltree_t *avltree, void *key);
/**
 * @brief 查找AVL树中,key对应的value
 *
 * 如果找到key, 则返回对应的value, 否则返回NULL
 * 需要注意的是: 返回的value指针，是指向AVL树中实际的value的; 对其修改，会影响AVL树里这个key所对应的value
 */
extern void *ky_avltree_find(ky_avltree_t *avltree, void *key);
/**
 * @brief 查找AVL树中，最大的key对应的value
 */
extern void *ky_avltree_find_max(ky_avltree_t *avltree);
/**
 * @brief 查找AVL树中，最小的key对应的value
 */
extern void *key_avltree_find_min(ky_avltree_t *avltree);

#ifdef __cplusplus
}
#endif

#endif // _KY_AVLTREE_H
