#ifndef _KY_CORE_H
#define _KY_CORE_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 在指定的范围内产生一个随机数
 */
extern unsigned int ky_rand(unsigned int start, unsigned int end);
/**
 * @brief 内存清0
 */
extern void *ky_memzero(void *s, size_t n);
/**
 * @brief 把进程ID保存到文件
 * 
 * @reval  0	成功
 * @reval  -1	失败
 */
extern int ky_save_pid_file(const char *fileName);


#ifdef __cplusplus
}
#endif

#endif // _KY_CORE_H
