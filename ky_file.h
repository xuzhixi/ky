//===============================================
/**
 *  @file ky_file.h
 *
 *  @author XuZhiXi
 *  Email   zhixi.xu@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:11:27
 *  Last   modified:  2012-10-17 08:11:27
 *
 *  Description: 
 */
//================================================

#ifndef _KY_FILE_H
#define _KY_FILE_H

#include "ky_string.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct ky_file_t {
	FILE *fp;
	ky_str_t *buffer;
}ky_file_t;

extern ky_file_t *ky_file_open(const char *fileName, const char *model);
extern void ky_file_close(ky_file_t *file);
extern const ky_str_t *ky_file_read_line(ky_file_t *file);
extern const ky_str_t *ky_file_read_all(ky_file_t *file);


#ifdef __cplusplus
}
#endif

#endif
