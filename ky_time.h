#ifndef _KY_TIME_H
#define _KY_TIME_H

#ifdef _CPLUSPLUS
extern "C" {
#endif


/**
 * @brief 获取当前时间,已指定格式的字符串形式返回
 *
 * 格式化字符串，请参见strftime()函数支持的格式化选项
 *
 * @see ky_now()
 */ 
extern char *ky_strftime(char *dst, size_t dstLen, const char *format);
/**
 * @brief 获取当前时间,已指定格式的字符串形式返回
 *
 * @param  dst		保存返回字符串的缓冲区
 * @param  dstLen	缓冲区的长度
 * @param  format	格式化字符串(例: 2012-09-26 15:07:32)
 *					yyyy	2012
 *					yy		12
 *					MM		09
 *					M		9
 *					dd		26
 *					d		26
 *					hh		15
 *					h		15
 *					mm		07
 *					m		7
 *					ss		32
 *					s		32
 * @return			返回缓存区的首地址
 */
extern char *ky_now(char *dst, size_t dstLen, const char *format);


#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_TIME_H
