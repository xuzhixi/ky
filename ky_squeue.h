#ifndef _KY_SQUEUE_H
#define _KY_SQUEUE_H

#include <ky_types.h>

#ifdef _CPLUSPLUS
extern "C" {
#endif 

typedef struct ky_squeue_s
{
	void *value;	
	struct ky_squeue_t *next;
}ky_squeue_s;

void ky_squeue_new();
void ky_squeue_release();
bool ky_squeue_is_null();
void ky_squeue_enqueue();
void ky_squeue_dequeue();


#ifdef _CPLUSPLUS
}
#endif 

#endif // _KY_SQUEUE_H
