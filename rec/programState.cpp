#include "ProgState.hpp"
#include <unistd.h>

void Di::initialize_global(void){
  global.inTty = isatty(STDIN_FILENO);
  global.outTty = isatty(STDOUT_FILENO);
  global.errTty = isatty(STDERR_FILENO);
}

struct Di::GlobalState Di::global;
