#ifndef DISH_PARSER_HEAD_H
#define DISH_PARSER_HEAD_H

enum TokenType{
  TOK_STRING,
  TOK_PIPE,
  TOK_RIGHT_REDIR,
  TOK_LEFT_REDIR,
  TOK_SEPAR,
  TOK_SEPAR_COND_SUCC,
  TOK_SEPAR_COND_FAIL,
  TOK_END,
  TOK_UNIMPLEMENTED
};

struct TokenNode{
  enum TokenType type;
  char * str;
};

struct CommandNode {
  struct CommandNode * next;
  enum TokenType type;
  char const * command;
  char ** args;
};

char const * dish_tokenize(char const * str, struct TokenNode * tok);
/* Returns the last char of the string + 1 */
/* Returns null pointer on failure */

int dish_parse(struct CommandNode * dest, struct TokenNode const * token);
/* 0 is success, non zero for error */

void dish_clean_command_node(struct CommandNode *); /* Cleans up the tree if the current node has next command */

#endif //DISH_PARSER_HEAD_H
