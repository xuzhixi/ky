//===============================================
/**
 *  @file ky_string.c
 *
 *  @author XuZhiXi
 *  Email   932834199@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:15:16
 *  Last   modified:  2012-10-17 08:15:16
 *
 *  Description: 
 */
//================================================

#include <string.h>
#include <stdlib.h>
#include "ky_string.h"


static void ky_str_init(ky_str_t *str, const char *s)
{
	str->len = strlen(s);
	str->s = (char *)malloc( str->len + 1 );
	strcpy(str->s, s);
}

ky_str_t *ky_str_new(const char *s)
{
	ky_str_t *str;

	str = (ky_str_t *)malloc( sizeof(ky_str_t) );
	ky_str_init( str, s );

	return str;
}

void ky_str_release(ky_str_t *str)
{
	free( str->s );
	free( str );
}

void ky_str_set(ky_str_t *str, const char *cs)
{
	free( str->s );
	ky_str_init( str, cs );
}

void ky_str_tolower(ky_str_t *str)
{
	size_t i;

	for (i=0; i<str->len; i++)
	{
		str->s[i] = ky_tolower( str->s[i] );
	}
}

void ky_str_toupper(ky_str_t *str)
{
	size_t i;

	for (i=0; i<str->len; i++)
	{
		str->s[i] = ky_toupper( str->s[i] );
	}
}

void ky_str_catc(ky_str_t *dst, const char *src)
{
	char *oldStr;

	oldStr = dst->s;
	dst->len += strlen( src );
	dst->s = (char *)malloc( dst->len + 1 );
	strcpy( dst->s, oldStr );
	strcat( dst->s, src );
	free( oldStr);
}

void ky_str_cat(ky_str_t *dst, const ky_str_t *src)
{
	ky_str_catc(dst, src->s);
}

int ky_str_cmp(const ky_str_t *str1, const ky_str_t *str2)
{
	return strcmp(str1->s, str2->s);
}

void ky_strcpy(char *dst, size_t dstLen, char *src, size_t srcLen)
{    
	size_t len;

	len = srcLen < dstLen ? srcLen : dstLen - 1;
	memcpy(dst, src, len);
	dst[ len ] = '\0';
}
