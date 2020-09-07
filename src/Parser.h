#ifndef DISH_PARSER_HEAD_H
#define DISH_PARSER_HEAD_H

enum TokenType{
  TOK_STRING,
  TOK_PIPE,
  TOK_RIGHT_REDIR,
  TOK_LEFT_REDIR,
  TOK_PROG_SEPAR,
  TOK_PROG_SEPAR_COND_SUCC,
  TOK_PROG_SEPAR_COND_FAIL,
  TOK_END,
  TOK_UNIMPLEMENTED
};

struct TokenNode{
  enum TokenType type;
  char * str;
};

char const * dish_tokenize(char const * str, struct TokenNode * tok);
/* Returns the last char of the string + 1 */
/* Returns null pointer on failure */

#endif //DISH_PARSER_HEAD_H
