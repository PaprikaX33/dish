#include "ExecLoc.h"
#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#define MIN_EXEC_LEN 16

int set_shell_env(void)
{
  char * execName = malloc(MIN_EXEC_LEN * sizeof(char));
  size_t execLen = MIN_EXEC_LEN;
  if(!execName){
    return -1;
  }
  ssize_t retval;
  int loop = 0;
  do{
    loop = 0;
    retval = readlink("/proc/self/exe", execName, execLen);
    if(retval < 0){
      return -1;
    }
    if(((size_t) retval) == execLen){
      //resize the execName
      loop = 1;
      free(execName);
      execLen *= 2u;
      execName = malloc(execLen * sizeof(char));
      if(!execName){
        return -1;
      }
    }
  }while(loop);

  if(setenv("SHELL", execName, 1) < 0){
    return -1;
  }
  free(execName);
  return 0;
}
