#ifndef DISH_PROGRAM_STATE_HEAD_HPP
#define DISH_PROGRAM_STATE_HEAD_HPP
#include "Common.h"

namespace Di {
  struct GlobalState
  {
    bool inTty;
    bool outTty;
    bool errTty;
  };
  extern struct GlobalState global;
  void initialize_global(void);
}

#endif //DISH_PROGRAM_STATE_HEAD_HPP
