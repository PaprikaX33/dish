#include "Tokenizer.h"
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

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
  /* A stop plug to test the end token */
  while(*str != '\0'){
    str++;
  }
  if(*str == '\0'){
    tok->type = TOK_END;
    return str+1;
  }
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
  return str + endPos;
}
