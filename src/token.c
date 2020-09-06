#include "Tokenizer.h"
#include "Memory.h"
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN_STR_LEN 32

static int is_special(int);
static char const * process_str(char const * str, struct TokenNode * tok);

char const * dish_tokenize(char const * str, struct TokenNode * tok)
{
  /* String Preparation */
  if(!tok || !str){
    return NULL;
  }
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
  default:
    return process_str(str, tok);
    /* This means it's the default string */
  }
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

static char const * string_token(char const * str, char ** curStr, size_t * curSize);

char const * process_str(char const * str, struct TokenNode * tok)
{
  char * strBuff = NULL;
  size_t curSize = 0;
  int repeat = 0;
  char const * retStr = str;
  do{
    repeat = 0;
    retStr = string_token(retStr, &strBuff, &curSize);
    if(!retStr){
      return retStr;
    }
    if(retStr[0] == '\'' || retStr[0] == '"'){
      /* Found a quoter */
      int delim = retStr[0];
      char const * findStr = retStr + 1u;
      size_t finder = 0;
      repeat = 1;
      while(findStr[finder] != delim && findStr[finder] != '\0'){
        finder++;
      }
      if(findStr[finder] == '\0'){
        return NULL;
      }
      strBuff = xrealloc(strBuff, (sizeof(char) * (finder + curSize)) + 1u, "Unable to allocate memory!");
      char * strBuffMod = strBuff + curSize;
      memcpy(strBuffMod, findStr, finder);
      strBuffMod[finder] = '\0';
      curSize += finder;
      retStr = findStr + finder + 1u;
    }
  }while(repeat);
  tok->type = TOK_STRING;
  tok->str = strBuff;
  return retStr;
}

char const * string_token(char const * str, char ** curStr, size_t * curSize)
{
  size_t strPos = 0;
  while(!is_special(str[strPos])){
    strPos++;
  }
  if(!strPos){
    return str;
  }
  size_t const strFinSize = strPos + *curSize;
  char * strBuff = xrealloc(*curStr, (sizeof(char) * (strFinSize)) + 1u, "Unable to allocate memory!");
  char * strModf = strBuff + *curSize;
  memcpy(strModf, str, strPos);
  strModf[strPos] = '\0';
  *curStr = strBuff;
  *curSize = strFinSize;
  return str + strPos;
}
