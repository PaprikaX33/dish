#include "GlobalState.h"
#include <unistd.h>

int initialize_global(void){
  //STDOUT_FILENO, STDERR_FILENO
  //global.outTty, global.errTty
  /* if(isatty(STDIN_FILENO)){ */
  /*   global.inTty = 1; */
  /* } */
  /* else{ */
  /*   global.inTty = 0; */
  /* } */
  global.inTty = isatty(STDIN_FILENO);
  global.outTty = isatty(STDOUT_FILENO);
  global.errTty = isatty(STDERR_FILENO);
  return 0;
}

struct GlobalState global = {0};
