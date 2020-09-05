#include "Tokenizer.h"
#include "Memory.h"
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN_STR_LEN 32

static int is_special(int);

char const * dish_tokenize(char const * str, struct TokenNode * tok)
{
  if(!tok || !str){
    return NULL;
  }
  size_t endPos = 0;
  /*Skip Whitespace*/
  while(isspace(*str)){
    str++;
  }
#if 0
  /* A stop plug to test the end token */
  while(*str != '\0'){
    str++;
  }
#endif
  /* //////////////////// */
  if(*str == '\0'){
    tok->type = TOK_END;
    return str+1;
  }
  int inApos = 0;
  char * strBuff = 0;
  size_t strPos = 0;
  int repeat = 0;
  do{
    repeat = 0;
    while(!is_special(str[strPos])){
      strPos++;
    }
    strBuff = xrealloc(strBuff, (sizeof(char) * strPos) + 1u, "Unable to allocate memory!");
    memcpy(strBuff, str, strPos);
    strBuff[strPos] = '\0';
    tok->type = TOK_STRING;

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
  }while(repeat);

  tok->str = strBuff;
  return str + strPos;
  /* //////////////////// */

#if 0
  /*Check for a quoted string*/
  if(*str == '\"'){
    str++;
    /* Search for the matching pair of quoted string */
    while(str[endPos] != '\"' && str[endPos]){
      endPos++;
    }
    /* Check if the quote is unbalanced */
    if(!str[endPos]){
      return NULL;
    }
    char * strBuff = malloc(endPos * sizeof(char));
    if(!strBuff){
      fprintf(stderr, "Unable to allocate memory!");
      exit(-1);
    }
    memcpy(strBuff, str, endPos);
    strBuff[endPos - 1] = '\0';
    tok->type = TOK_STRING;
    tok->str = strBuff;
    return str + endPos + 1u;
  }
  /* Not in quoted string */
#endif /* if 0 */
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
