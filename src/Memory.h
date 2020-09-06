#ifndef DISH_MEMORY_HEAD_H
#define DISH_MEMORY_HEAD_H
#include <stddef.h>

void * xmalloc(size_t size, char const * errMsg);
void * xrealloc(void * ptr, size_t size, char const * errMsg);

#endif //DISH_MEMORY_HEAD_H
