#include "Dish.h"
#include "GlobalState.h"
#include "verString.inc"
#include "Tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int arg_parse(int argc, char ** argv);
static int tokDebug = 0;
static int dish_tok_test(void);

int main(int argc, char ** argv)
{
  int retcode;
  if(initialize_global()){
    return -1;
  }
  printf("in\t: %d\nout\t: %d\nerr\t: %d\n", global.inTty, global.outTty, global.errTty);
  if((retcode = arg_parse(argc, argv))){
    return (retcode < 0 ? retcode : 0);
  }
  if(tokDebug){
    return dish_tok_test();
  }
  return idsh_loop();
}

static void write_help(void);
static void write_vers(void);

int arg_parse(int argc, char ** argv)
{
  for(int i = 1; i < argc; i++){
    char const * const arg = argv[i];
    if(arg[0] == '-'){
      char const * const argf = arg+1;
      if(!strcmp(argf, "-help") || !strcmp(argf, "?")){
        write_help();
        return 1;
      }
      if(!strcmp(argf, "-version") || !strcmp(argf, "V")){
        write_vers();
        return 1;
      }
      if(!strcmp(argf, "-token") || !strcmp(argf, "t")){
        tokDebug = 1;
        continue;
      }
      printf("idsh: unrecognized option '%s'\n", arg);
      puts("Try 'idsh --help' for more information.");
      return -1;
    }
  }
  return 0;
}

void write_help(void)
{
  puts(usageString);
  putc('\n', stdout);
  puts(optionString);
}
void write_vers(void)
{
  puts(versionString);
}

#define MIN_BUFFSIZE 1024
#define MIN_TOKEN 16

int dish_tok_test(void)
{
  if(!global.inTty){
    puts("Only in TTY");
    return 0;
  }
  printf("TokenTest>");
  size_t pos = 0;
  size_t len = MIN_BUFFSIZE;
  char * buffer = malloc(MIN_BUFFSIZE);
  if(!buffer){
    fprintf(stderr, "Unable to allocate memory!");
    exit(-1);
  }
  do{
    int chr = getchar();
    if(chr =='\n'){
      buffer[pos] = '\0';
      break;
    }
    buffer[pos] = (char)chr;
    pos++;

    if(pos == len){
      buffer = realloc(buffer, len * 2u * sizeof(char));
      if(!buffer){
        fprintf(stderr, "Unable to allocate memory!");
        exit(-1);
      }
      len *= 2u;
    }
  }while(1);
  char * end = buffer + pos + 1u;
  char const * start = buffer;
  struct TokenNode * tokBuff = malloc(sizeof(struct TokenNode) * MIN_TOKEN);
  size_t tokLen = MIN_TOKEN;
  size_t tokPos = 0;
  while(start != end){
    start = dish_tokenize(start, tokBuff + tokPos);
    tokPos++;
    printf("AFTER TOKENIZING. st: %p\ted: %p", start, end);
    if(!end){
      fprintf(stderr, "Tokenizing error. Possibly unmatched apostroph!");
      exit(-1);
    }
    if(tokPos == tokLen){
      tokBuff = realloc(tokBuff, tokLen * 2u * sizeof(struct TokenNode));
      if(!tokBuff){
        fprintf(stderr, "Unable to allocate memory!");
        exit(-1);
      }
      tokLen *= 2u;
    }
  }
  for(size_t cPos = 0; cPos < tokPos; cPos++){
    struct TokenNode * tok = tokBuff + cPos;
    switch(tok->type){
    default: break;
    case TOK_STRING:
      puts(tok->str);
      break;
    case TOK_PIPE:
      puts("<<TOKEN>> PIPE");
      break;
    case TOK_RIGHT_REDIR:
      puts("<<TOKEN>> RIGHT REDIR");
      break;
    case TOK_LEFT_REDIR:
      puts("<<TOKEN>> LEFT REDIR");
      break;
    case TOK_END:
      puts("<<TOKEN>> END");
      break;
    }
  }
  free(buffer);
  return 0;
}
