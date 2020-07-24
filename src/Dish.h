#ifndef IDSH_START_HEAD_H
#define IDSH_START_HEAD_H
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

#endif //IDSH_START_HEAD_H
