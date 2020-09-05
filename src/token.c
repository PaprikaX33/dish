#include "Tokenizer.h"
#include "Memory.h"
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN_STR_LEN 32

static int is_special(int);
static char * push_data(char * des, char const * src, size_t des_offset, size_t src_offset, size_t len);

char const * dish_tokenize(char const * str, struct TokenNode * tok)
{
  /* String Preparation */
  if(!tok || !str){
    return NULL;
  }
  size_t endPos = 0;
  /*Skip Whitespace*/
  while(isspace(*str)){
    str++;
  }
  /* Special Char detection */
  switch(*str){
  case '\0':
    tok->type = TOK_END;
    return str + 1;
  case '|':
    tok->type = TOK_PIPE;
    return str + 1;
  case '<':
    tok->type = TOK_LEFT_REDIR;
    return str + 1;
  case '>':
    tok->type = TOK_RIGHT_REDIR;
    return str + 1;
  default: break;
  }
  /* //////////////////// */
  int inApos = 0;
  char * strBuff = 0;
  size_t strPos = 0;
  while(!is_special(str[strPos])){
    strPos++;
  }
  strBuff = xrealloc(strBuff, (sizeof(char) * strPos) + 1u, "Unable to allocate memory!");
  memcpy(strBuff, str, strPos);
  strBuff[strPos] = '\0';
  tok->type = TOK_STRING;
  tok->str = strBuff;

  if(str[strPos] == '\'' || str[strPos] == '\"'){
    int delim = str[strPos];
    size_t finder = 1;
    while(str[strPos + finder] != delim && str[strPos + finder] != '\0'){
      finder++;
    }
    if(str[strPos + finder] == '\0'){
      /* Unbalanced apostroph */
      return NULL;
    }
    printf("Found between %lu and %lu\n", strPos, finder);
    strBuff = xrealloc(strBuff, (sizeof(char) * (strPos + finder)) + 1u, "Unable to allocate memory!");
    /* Apparently this works but seems wrong tho */
    memcpy(strBuff + strPos, str + strPos + 1u, finder - 1u);
    strBuff[strPos + finder] = '\0';
    /* This part is infinite looping */
    /* if(!isspace(str[strPos + finder + 1u]) && strBuff[strPos + finder + 1u] != '\0'){ */
    /*   repeat = 1; */
    /* } */
    tok->str = strBuff;
    return str + strPos + finder + 1u;
  }

  tok->str = strBuff;
  return str + strPos;
  /* //////////////////// */
  return str + endPos;
}

int is_special(int chr)
{
  switch(chr){
    /* Testing if end of char */
  case '\0':
    /* Whitespace */
  case ' ':
  case '\t':
  case '\v':
  case '\f':
  case '\r':
    /* Special Char */
  case '|':
  case '<':
  case '>':
    /* Quote */
  case '\"':
  case '\'':
    return 1;
  default:
    return 0;
  }
}
