#include "IdshStart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN_BUFSIZE 1024
#define MIN_TOKEN 16
static char * idsh_getline(void);
static char ** idsh_tokenize(char *);
int idsh_exec(char **);

int idsh_loop(void)
{
  char * inpText;
  char ** tokenList;
  int loop;

  do{
    printf("IdSH> ");
    loop = idsh_exec(tokenList = idsh_tokenize(inpText = idsh_getline()));
    free(tokenList);
    free(inpText);
  }while(loop);
  return 0;
}

char * idsh_getline(void)
{
  return NULL;
}

char ** idsh_tokenize(char * inpText)
{
  (void)inpText;
  return NULL;
}

int idsh_exec(char ** cmdTok)
{
  (void)cmdTok;
  return 0;
}
//getchar();
