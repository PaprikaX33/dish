#include "IdshStart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN_BUFFSIZE 1024
#define MIN_TOKEN 16

struct StringPair {
  char * str;
  size_t len;
};

struct TokenPair {
  char ** tok;
  size_t  len;
};

static struct StringPair idsh_getline(struct StringPair);
static struct TokenPair idsh_tokenize(struct TokenPair, struct StringPair);
static int idsh_exec(struct TokenPair);

int idsh_loop(void)
{
  struct TokenPair token = {
                            .tok = malloc(sizeof(char *) * MIN_TOKEN),
                            .len = MIN_TOKEN
  };
  if(!token.tok){
    fprintf(stderr, "Unable to allocate memory!");
    return -1;
  }
  struct StringPair string = {
                              .str = malloc(sizeof(char) * MIN_BUFFSIZE),
                              .len = MIN_BUFFSIZE
  };
  if(!string.str){
    fprintf(stderr, "Unable to allocate memory!");
    free(token.tok);
    return -1;
  }
  int loop;

  do{
    printf("IdSH> ");
    loop = idsh_exec(token = idsh_tokenize(token, string = idsh_getline(string)));
  }while(loop);
  free(token.tok);
  free(string.str);
  return 0;
}

struct StringPair idsh_getline(struct StringPair str)
{
  size_t pos = 0;
  do{
    int chr = getchar();
    if(chr == EOF){
      putc('\n',stdout);
      exit(0);
    }
    if(chr == '\n'){
      str.str[pos] = '\0';
      return str;
    }
    str.str[pos] = (char)chr;
    pos++;

    if(pos == str.len){
      if(!(str.str = realloc(str.str, str.len * 2 * sizeof(char)))){
        fprintf(stderr, "Unable to allocate memory!");
        exit(-1);
      }
      str.len *= 2;
    }
  }while(1);
  return str;
}

struct TokenPair idsh_tokenize(struct TokenPair tok, struct StringPair strng)
{
  size_t pos = 0;
  char * str = strng.str;
  do{
    //Skip whitespace
    while(*str == ' '){
      str++;
    }
    if(*str == '\0'){
      tok.tok[pos] = NULL;
      return tok;
    }
    tok.tok[pos] = str;
    pos++;
    if(pos == tok.len){
      if(!(tok.tok = realloc(tok.tok, tok.len * 2 * sizeof(char*)))){
        fprintf(stderr, "Unable to allocate memory!");
        exit(-1);
      }
      tok.len *= 2;
    }
    while(*str != ' '){
      if(*str == '\0'){
        tok.tok[pos] = NULL;
        return tok;
      }
      str++;
    }
    *str = '\0';
    str++;
  }while(1);
}

int idsh_exec(struct TokenPair tokn)
{
  if(!strcmp(tokn.tok[0], "exit") || !strcmp(tokn.tok[0], "quit")){
    return 0;
  }
  return 1;
}
