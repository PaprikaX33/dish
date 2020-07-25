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
  char * execName = NULL;
  size_t execLen = 0;
  if(!execName){
    execLen = MIN_EXEC_LEN;
    execName = malloc(MIN_EXEC_LEN * sizeof(char));
  }
  if(!execName){
    return NULL;
  }

  ssize_t retval;
  int loop = 0;
  do{
    loop = 0;
    retval = readlink("/proc/self/exe", execName, execLen);
    if(retval < 0){
      perror("Dish");
      exit(-1);
    }
    if(((size_t) retval) == execLen){
      //resize the execName
      loop = 1;
      free(execName);
      execLen *= 2u;
      execName = malloc(execLen * sizeof(char));
      if(!execName){
        return NULL;
      }
    }
  }while(loop);

  if(setenv("$SHELL", progName, 1) < 0){
    perror("Dish");
    return -1;
  }
  return execName;
}
