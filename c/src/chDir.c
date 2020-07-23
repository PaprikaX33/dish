#include "ChDir.h"
#include <stdio.h>
#include <string.h>


static char const * cdHelpString =
  "cd: cd <dir>\n\n"
  "    Change the working directory\n\n"
  "    Change the working directory to dir. On the current version, The capability\n"
  "    to change to  HOME directory,  when no  DIR argument is supplied,   is not \n"
  "    implemented yet."
  ;

void execute_changedir(char const * const * token)
{
  char const * dir = NULL;
  int delimit_mode = 0;
  for(char const * const * addr = token; *addr != NULL; addr++){
    if(delimit_mode){
      if(dir){
        fprintf(stderr, "cd: Too many arguments\n");
        return;
      }
      dir = *addr;
    }
    else {
      if((*addr)[0] == '-'){
        char const * const flg = (*addr) + 1;
        if(!strcmp(flg, "-")){
          delimit_mode = 1;
          continue;
        }
        //Check for flags
        if(!strcmp(flg, "-help") || !strcmp(flg, "?")){
          puts(cdHelpString);
          return;
        }
        fprintf(stderr, "cd: Invalid flag %s\n", *addr);
        return;
      }
      if(dir){
        fprintf(stderr, "cd: Too many arguments\n");
        return;
      }
      dir = *addr;
    }
  }
  if(!dir){
    fprintf(stderr, "cd: Empty DIR is not supported yet\n");
    return;
  }
  printf("Changing to: %s\n", dir);
}
