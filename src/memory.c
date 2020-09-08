#include "Memory.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static void errPrintCallb(char const * str);

void * xmalloc(size_t size, char const * errMsg)
{
  return xcmalloc(size, errMsg, errPrintCallb);
}

void * xrealloc(void * ptr, size_t size, char const * errMsg)
{
  return xcrealloc(ptr, size, errMsg, errPrintCallb);
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

void errPrintCallb(char const * str)
{
  fputs(str, stderr);
}
