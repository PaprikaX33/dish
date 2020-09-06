#include "Memory.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void * xmalloc(size_t size, char const * errMsg)
{
  void * alc = malloc(size);
  if(!alc){
    fprintf(stderr, errMsg);
    exit(-1);
  }
  return alc;
}
void * xrealloc(void * ptr, size_t size, char const * errMsg)
{
  void * alc = realloc(ptr, size);
  if(!alc){
    fprintf(stderr, errMsg);
    exit(-1);
  }
  return alc;
}

void * xcmalloc(size_t size, char const * errMsg, errCallback call)
{
  void * alc = malloc(size);
  if(!alc){
    call(errMsg);
    exit(-1);
  }
  return alc;
}
void * xcrealloc(void * ptr, size_t size, char const * errMsg, errCallback call)
{
  void * alc = realloc(ptr, size);
  if(!alc){
    call(errMsg);
    exit(-1);
  }
  return alc;
}
