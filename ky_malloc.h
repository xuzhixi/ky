#ifndef _KY_MALLOC_H
#define _KY_MALLOC_H

#ifdef _CPLUSPLUS
extern "C" {
#endif 

void *ky_malloc(size_t size);
void ky_free(void *ptr);

#ifdef _CPLUSPLUS
}
#endif

#endif // _KY_MALLOC_H
