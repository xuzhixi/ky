#ifndef _KY_PROGRESS_H
#define _KY_PROGRESS_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define KY_PROGRESS_POOL(count, content) { int ky_i; for(ky_i=0; ky_i<count; ky_i++){ pid_t ky_pid = fork(); if ( ky_pid == 0 )content } }

#endif // _KY_PROGRESS_H

