#ifndef DISH_GLOBAL_STATE_HEAD_H
#define DISH_GLOBAL_STATE_HEAD_H

struct GlobalState
{
  int inTty;
  int outTty;
  int errTty;
};

extern struct GlobalState global;
int initialize_global(void); //Return error code. 0 is success

#endif //DISH_GLOBAL_STATE_HEAD_H
