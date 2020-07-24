#ifndef DISH_HEAD_H
#define DISH_HEAD_H
#include <stddef.h>
int idsh_loop(void);

struct StringPair {
  char * str;
  size_t len;
};

struct TokenPair {
  char ** tok;
  size_t  len;
};

#endif //DISH_HEAD_H
