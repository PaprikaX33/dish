#ifndef DISH_TOKENIZER_HEAD_H
#define DISH_TOKENIZER_HEAD_H

enum TokenType{
  STRING,
  PIPE,
  RIGHT_REDIR,
  LEFT_REDIR,
  END
};

struct TokenNode{
  enum TokenType type;
  char * str;
};

char const * dish_tokenize(char const * str, struct TokenNode * tok);
/* Return null pointer on failure */

#endif //DISH_TOKENIZER_HEAD_H
