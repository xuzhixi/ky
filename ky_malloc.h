#ifndef _KY_MALLOC_H
#define _KY_MALLOC_H

#ifdef _CPLUSPLUS
extern "C" {
#endif 

/**
 * @brief 动态申请内存，使用方法和 malloc 函数一样
 *
 * 申请的内存要用 ky_free 释放
 */
void *ky_malloc(size_t size);
/**
 * @brief 释放动态申请的内存，使用方法和 free 函数一样
 *
 * 只能用来释放由 ky_malloc 申请的内存
 */
void ky_free(void *ptr);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_MALLOC_H
