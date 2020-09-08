#include "GlobalState.h"
#include <unistd.h>

int initialize_global(void){
  global.inTty = isatty(STDIN_FILENO);
  global.outTty = isatty(STDOUT_FILENO);
  global.errTty = isatty(STDERR_FILENO);
  return 0;
}

struct GlobalState global = {0};
