#include "Dish.h"
#include "ChDir.h"
#include "ExecLoc.h"
#include "Memory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MIN_BUFFSIZE 1024
#define MIN_TOKEN 16
#define EXIT_STAT_STR_LENGTH 64
static int exitStats = 0;
static char strExitStats[EXIT_STAT_STR_LENGTH];
static char emptyString[] = "";

static struct StringPair idsh_getline(struct StringPair);
static struct TokenPair idsh_tokenize(struct TokenPair, struct StringPair);
static struct TokenPair idsh_replace_args(struct TokenPair);
static int idsh_exec(struct TokenPair);


int idsh_loop(void)
{
  if(set_shell_env()){
    perror(dishPerrorTag);
    return -1;
  }
  struct TokenPair token = {
    .tok = xmalloc(sizeof(char *) * MIN_TOKEN, "Unable to allocate memory!"),
                            .len = MIN_TOKEN
  };
  struct StringPair string = {
    .str = xmalloc(sizeof(char) * MIN_BUFFSIZE, "Unable to allocate memory!"),
                              .len = MIN_BUFFSIZE
  };
  int loop;
  do{
    printf("%02d-IdSH> ", exitStats);
    loop = idsh_exec(token = idsh_replace_args(idsh_tokenize(token, string = idsh_getline(string))));
  }while(loop);
  puts("Terminating DiSH");
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
      str.str = xrealloc(str.str, str.len * 2 * sizeof(char), "Unable to allocate memory!");
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
    //Check whether there is another char after the space
    if(*str == '\0'){
      tok.tok[pos] = NULL;
      return tok;
    }
    //set token
    tok.tok[pos] = str;
    pos++;
    //reallocate if required
    if(pos == tok.len){
      tok.tok = xrealloc(tok.tok, tok.len * 2 * sizeof(char*), "Unable to allocate memory!");
      tok.len *= 2;
    }
    //Find next whitespace
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
  if(tokn.tok[0] == NULL){
    //Check for empty token
    return 1;
  }
  if(!strcmp(tokn.tok[0], "exit") || !strcmp(tokn.tok[0], "quit")){
    return 0;
  }
  if(!strcmp(tokn.tok[0], "cd")){
    execute_changedir(tokn.tok+1);
    return 1;
  }
  //Call external program as shell
  pid_t frk = fork();
  if(frk == -1){
    perror(dishPerrorTag);
    return 1;
  }
  if(frk){
    //mother
    int wstat;
    if(waitpid(frk, &wstat, 0) == -1) {
      perror(dishPerrorTag);
      exit(-1);
    }
    exitStats = WEXITSTATUS(wstat);
  }
  else{
    //Child
    if(execvp(tokn.tok[0], tokn.tok) == -1) {
      perror(dishPerrorTag);
      exit(-1);
    }
  }
  return 1;
}


struct TokenPair idsh_replace_args(struct TokenPair tok)
{
  //TODO: make a check to replace the char in case of an escaped dolar sign e.g.: \$FOO
  for(size_t i = 0; tok.tok[i] != NULL; i++){
    char * const tokstr = tok.tok[i];
    if(tokstr[0] == '$'){
      //IS VARIABLE / need to be subsituted
      char * const toknStr = tokstr + 1;
      if(!strcmp(toknStr, "?")){
        //Is asking for the latest return code
        snprintf(strExitStats, EXIT_STAT_STR_LENGTH, "%d", exitStats);
        tok.tok[i] = strExitStats;
        continue;
      }
      //TODO: check for Internal variable

      //Is environment variable
      tok.tok[i] = getenv(toknStr);
      if(!tok.tok[i]){
        tok.tok[i] = emptyString;
      }
    }
  }
  return tok;
}

char * dishPerrorTag = "DiSH";
