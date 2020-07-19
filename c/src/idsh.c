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
                            .tok = malloc(sizeof(char *) * (MIN_TOKEN + 1)),
                            .len = MIN_TOKEN + 1
  };
  if(!token.tok){
    fprintf(stderr, "Unable to allocate memory!");
    return -1;
  }
  struct StringPair string = {
                              .str = malloc(sizeof(char) * (MIN_BUFFSIZE + 1)),
                              .len = MIN_BUFFSIZE + 1
  };
  if(!string.str){
    fprintf(stderr, "Unable to allocate memory!");
    return -1;
  }
  int loop;

  do{
    printf("IdSH> ");
    loop = idsh_exec(token = idsh_tokenize(token, string = idsh_getline(string)));
  }while(loop);
  return 0;
}

struct StringPair idsh_getline(struct StringPair str)
{
  size_t pos = 0;
  do{
    int chr = getchar();
    if(chr == EOF){
      str.str[pos] = '\0';
      return str;
    }
    if(chr == '\n'){
      if(!pos){
        if(str.str[pos - 1] != '\\'){
          str.str[pos] = '\0';
          return str;
        }
        pos--;
        continue;
      }
      else {
        str.str[0] = '\0';
        return str;
      }
    }

    str.str[pos] = (char)chr;
    pos++;
    //TODO: CHECK FOR REQUIRING REALLOCATE BUFFER
    //return str;
  }while(1);
  return str;
}

struct TokenPair idsh_tokenize(struct TokenPair tok, struct StringPair str)
{
  for(size_t i = 0; i < 20; i++){
    putc(str.str[i], stdout);
  }
  putc('\n',stdout);
  return tok;
}

int idsh_exec(struct TokenPair tok)
{
  (void)tok;
  return 0;
}
//getchar();
