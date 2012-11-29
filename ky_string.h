//===============================================
/**
 *  @file ky_string.h
 *
 *  @author XuZhiXi
 *  Email   zhixi.xu@qq.com or 932834199@163.com
 *
 *  Create datetime:  2012-10-17 08:15:14
 *  Last   modified:  2012-10-17 08:15:14
 *
 *  Description: 
 */
//================================================

#ifndef _KY_STRING_H
#define _KY_STRING_H

#define ky_tolower(c)	((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define ky_toupper(c)	((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

#ifdef __cplusplus
extern "C" {
#endif


typedef struct ky_str_t {
	char *s;
	size_t len;	
}ky_str_t;

extern ky_str_t *ky_str_new(const char *s);
extern void ky_str_release(ky_str_t *str);
extern void ky_str_set(ky_str_t *str, const char *cs);
extern void ky_str_tolower(ky_str_t *str);
extern void ky_str_toupper(ky_str_t *str);
extern void ky_str_catc(ky_str_t *dst, const char *src);
extern void ky_str_cat(ky_str_t *dst, const ky_str_t *src);
extern int ky_str_cmp(const ky_str_t *str1, const ky_str_t *str2);

extern void ky_strcpy(char *dst, size_t dstLen, char *src, size_t srcLen);


#ifdef __cplusplus
}
#endif

#endif // _KY_STRING_H
