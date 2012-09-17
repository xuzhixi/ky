#ifndef _KY_AVLTREE_H
#define _KY_AVLTREE_H

#include <sys/types.h>
#include <ky_types.h>

#ifdef _CPLUSPLUS
extern "C" {
#endif

typedef ssize_t ky_avltree_height_t;

typedef struct ky_avltree_s
{
	struct ky_avltree_s *left;
	struct ky_avltree_s *right;
	ky_avltree_height_t height;	
	void *key;
	void  *value;
}ky_avlnode_s, ky_avltree_s;

typedef size_t ky_avltree_key_len_t;
typedef size_t ky_avltree_value_len_t;
typedef sint8 (*ky_avltree_comparefun_t)(void *, void *);

typedef struct ky_avltree_t
{
	ky_avltree_key_len_t key_len;
	ky_avltree_value_len_t value_len;
	ky_avltree_comparefun_t cmp_fun;
	ky_avltree_s *tree;
}ky_avltree_t;


extern ky_avltree_t *ky_avltree_new(ky_avltree_key_len_t keyLen, ky_avltree_value_len_t valueLen, ky_avltree_comparefun_t cmpFun);
extern void ky_avltree_clear(ky_avltree_t *avltree);
extern void ky_avltree_release(ky_avltree_t *avltree);
extern bool ky_avltree_is_null(ky_avltree_t *avltree);
extern void ky_avltree_add(ky_avltree_t *avltree, void *key, void *value);
extern void ky_avltree_mod(ky_avltree_t *avltree, void *key, void *value);
extern void ky_avltree_del(ky_avltree_t *avltree, void *key);
extern void *ky_avltree_find(ky_avltree_t *avltree, void *key);
extern void *ky_avltree_find_max(ky_avltree_t *avltree);
extern void *key_avltree_find_min(ky_avltree_t *avltree);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_AVLTREE_H
