#ifndef DISH_MEMORY_HEAD_H
#define DISH_MEMORY_HEAD_H
#include <stddef.h>

void * xmalloc(size_t size, char const * errMsg);
void * xrealloc(void * ptr, size_t size, char const * errMsg);

typedef void (*errCallback)(char const * str);
void * xcmalloc(size_t size, char const * errMsg, errCallback call);
void * xcrealloc(void * ptr, size_t size, char const * errMsg, errCallback call);

#endif //DISH_MEMORY_HEAD_H
