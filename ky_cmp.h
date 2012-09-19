#ifndef _KY_CMP_H
#define _KY_CMP_H

#ifdef _CPLUSPLUS
extern "C" {
#endif

/**
 * @brief 比较两个个整形值的大小
 * 
 * val1 和 val2 都是指向整形的指针
 *
 * @param  val1
 * @param  val2
 * @retval 1	如果 *val1 大于 *val2
 * @retval -1	如果 *val1 小于 *val2
 * @retval 0	如果 *val1 等于 *val2
 */
extern sint8 ky_cmp_int(void *val1, void *val2);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_CMP_H
