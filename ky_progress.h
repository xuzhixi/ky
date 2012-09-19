#ifndef _KY_PROGRESS_H
#define _KY_PROGRESS_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief 创建进程池
 *
 * @param  count	进程的个数
 * @param  content  进程执行的操作(一般要在最后有个return操作)
 */
#define KY_PROGRESS_POOL(count, content) { int __ky_i; for(__ky_i=0; __ky_i<count; __ky_i++){ pid_t __ky_pid = fork(); if ( __ky_pid == 0 )content } }

#endif // _KY_PROGRESS_H

