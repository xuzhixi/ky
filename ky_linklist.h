#ifndef _KY_LINKLIST_H
#define _KY_LINKLIST_H

#include <ky_types.h>

#ifdef _CPLUSPLUS
extern "C" {
#endif


typedef struct ky_linklist_s
{
	void *value;
	struct ky_linklist_s *next;
}ky_linklist_s, ky_linklist_iter_t;

typedef size_t ky_linklist_value_len_t;
typedef sint8 (*ky_linklist_comparefun_t)(void *, void *);

typedef struct ky_linklist_t
{
	ky_linklist_value_len_t value_len;
	ky_linklist_comparefun_t cmp_fun;
	ky_linklist_s *head;
	ky_linklist_s *tail;
}ky_linklist_t;


extern ky_linklist_t *ky_linklist_new(ky_linklist_value_len_t valueLen, ky_linklist_comparefun_t cmpFun);
extern void ky_linklist_clear(ky_linklist_t *linklist);
extern void ky_linklist_release(ky_linklist_t *linklist);
extern bool ky_linklist_is_null(ky_linklist_t *linklist);
extern void *ky_linklist_find(ky_linklist_t *linklist, void *value);
extern void ky_linklist_add(ky_linklist_t *linklist, void *value);
extern void ky_linklist_insert(ky_linklist_t *linklist, void *value, void *insertValue);
extern void ky_linklist_mod(ky_linklist_t *linklist, void *value);
extern void ky_linklist_del(ky_linklist_t *linklist, void *value);

extern ky_linklist_iter_t *ky_linklist_iter(ky_linklist_t *linklist);
extern ky_linklist_iter_t *ky_linklist_iter_next(ky_linklist_iter_t *iter);
extern void *ky_linklist_iter_value(ky_linklist_iter_t *iter);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_LINKLIST_H
