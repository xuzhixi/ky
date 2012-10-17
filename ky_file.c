//===============================================
/**
 *  @file ky_file.c
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:11:29
 *  Last   modified:  2012-10-17 08:11:29
 *
 *  Description: 
 */
//================================================

#include <stdio.h>
#include <malloc.h>
#include "ky_file.h"


ky_file_t *ky_file_open(const char *fileName, const char *mode)
{
	ky_file_t *file;
	FILE *fp;

	if ( (fp=fopen(fileName, mode)) )
	{
		file = (ky_file_t *)malloc( sizeof(ky_file_t) );	
		file->fp = fp;
		file->buffer = ky_str_new("");
		return file;
	}

	return NULL;
}

void ky_file_close(ky_file_t *file)
{
	ky_str_release( file->buffer );
	free( file );
}

const ky_str_t *ky_file_read_line(ky_file_t *file)
{
	char buf[512];
	
	if ( fgets(buf, 512, file->fp) )
	{
		ky_str_set(file->buffer, buf);	
		return file->buffer;
	}

	return NULL;
}

const ky_str_t *ky_file_read_all(ky_file_t *file)
{
	char buf[512];
	
	while ( fgets(buf, 512, file->fp) )
	{
		ky_str_catc(file->buffer, buf);	
	}

	return file->buffer;
}

