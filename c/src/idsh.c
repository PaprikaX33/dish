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
  struct StringPair string = {
                              .str = malloc(sizeof(char) * (MIN_BUFFSIZE + 1)),
                              .len = MIN_BUFFSIZE + 1
  };

  int loop;

  do{
    printf("IdSH> ");
    loop = idsh_exec(token = idsh_tokenize(token, string = idsh_getline(string)));
  }while(loop);
  return 0;
}

struct StringPair idsh_getline(struct StringPair)
{
  size_t length = MIN_BUFFSIZE;
  size_t pos = 0;
  char * data = malloc(length * sizeof(char));
  do{
    int chr = getchar();
    pos++;
    return data;
  }while(1);
  return data;
}

struct TokenPair idsh_tokenize(struct TokenPair, struct StringPair)
{
  (void)inpText;
  return NULL;
}

int idsh_exec(struct TokenPair)
{
  (void)cmdTok;
  return 0;
}
//getchar();
