//===============================================
/**
 *  @file ky_squeue.h
 *
 *  @author XuZhiXi
 *  Email   zhixi.xu@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:15:07
 *  Last   modified:  2012-10-17 08:15:07
 *
 *  Description: 
 */
//================================================

#ifndef _KY_SQUEUE_H
#define _KY_SQUEUE_H


#ifdef __cplusplus
extern "C" {
#endif 

typedef struct ky_squeue_s
{
	void *value;	
	struct ky_squeue_t *next;
}ky_squeue_s;

void ky_squeue_new();
void ky_squeue_release();
int	 ky_squeue_is_null();
void ky_squeue_enqueue();
void ky_squeue_dequeue();


#ifdef __cplusplus
}
#endif 

#endif // _KY_SQUEUE_H
