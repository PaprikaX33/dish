#include "ExecLoc.h"
#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#define MIN_EXEC_LEN 16


static char * execName = NULL;
static size_t execLen = 0;

char * getLoc(void)
{
  if(!execName){
    execLen = MIN_EXEC_LEN;
    execName = malloc(MIN_EXEC_LEN * sizeof(char));
  }
  if(!execName){
    return NULL;
  }

  ssize_t retval;
  int loops = 0;
  do{
    retval = readlink("/proc/self/exe", execName, execLen);
    if(retval < 0){
      perror("Dish");
      exit(-1);
    }
    if(((size_t) retval) == execLen){
      //resize the execName
      free(execName);
      execLen *= 2u;
      execName = malloc(execLen * sizeof(char));
      if(!execName){
        return NULL;
      }
    }
  }while(loops);

  return execName;
}

void freeLoc(void)
{
  free(execName);
  execName = NULL;
}
