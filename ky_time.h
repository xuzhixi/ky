#ifndef _KY_TIME_H
#define _KY_TIME_H

#ifdef _CPLUSPLUS
extern "C" {
#endif

/**
 * @brief 获取当前的日期和时间
 *
 * @param  dtStr	保存日期时间的缓存区(要大于等于20个字节)
 * @return			返回缓存区的首地址
 */
extern char *ky_date_time(char *dtStr);
/**
 * @brief 获取当前的时间
 *
 * @param  dtStr	保存时间的缓存区(要大于等于9个字节)
 * @return			返回缓存区的首地址
 */
extern char *ky_now_time(char *tStr);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_TIME_H
