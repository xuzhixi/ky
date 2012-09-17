#ifndef _KY_AVLTREE_H
#define _KY_AVLTREE_H

#include <sys/types.h>
#include <ky_types.h>

#ifdef _CPLUSPLUS
extern "C" {
#endif

typedef enum ky_rbtree_color_t
{
	KY_RBTREE_RED = 0,
	KY_RBTREE_BLACK = 1
}ky_rbtree_color_t;

typedef struct ky_rbtree_s
{
	struct ky_rbtree_s *parent;
	struct ky_rbtree_s *left;
	struct ky_rbtree_s *right;
	ky_rbtree_color_t color;
	void *key;
	void  *value;
}ky_rbnode_s, ky_rbtree_s;

typedef size_t ky_rbtree_key_len_t;
typedef size_t ky_rbtree_value_len_t;
typedef sint8 (*ky_rbtree_comparefun_t)(void *, void *);

typedef struct ky_rbtree_t
{
	ky_rbtree_key_len_t key_len;
	ky_rbtree_value_len_t value_len;
	ky_rbtree_comparefun_t cmp_fun;
	ky_rbtree_s *tree;
}ky_rbtree_t;


extern ky_rbtree_s *ky_rbtree_nil;

extern ky_rbtree_t *ky_rbtree_new(ky_rbtree_key_len_t keyLen, ky_rbtree_value_len_t valueLen, ky_rbtree_comparefun_t cmpFun);
extern void ky_rbtree_clear(ky_rbtree_t *rbtree);
extern void ky_rbtree_release(ky_rbtree_t *rbtree);
extern bool ky_rbtree_is_null(ky_rbtree_t *rbtree);
extern void ky_rbtree_add(ky_rbtree_t *rbtree, void *key, void *value);
extern void ky_rbtree_mod(ky_rbtree_t *rbtree, void *key, void *value);
extern void ky_rbtree_del(ky_rbtree_t *rbtree, void *key);
extern void *ky_rbtree_find(ky_rbtree_t *rbtree, void *key);
extern void *ky_rbtree_find_max(ky_rbtree_t *rbtree);
extern void *key_rbtree_find_min(ky_rbtree_t *rbtree);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_AVLTREE_H
