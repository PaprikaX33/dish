#include "Dish.h"
#include "GlobalState.h"
#include "verString.inc"
#include "Parser.h"
#include "Memory.h"
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
  char * buffer = xmalloc(sizeof(char) * MIN_BUFFSIZE, "Unable to allocate memory!");
  do{
    int chr = getchar();
    if(chr =='\n'){
      buffer[pos] = '\0';
      break;
    }
    buffer[pos] = (char)chr;
    pos++;

    if(pos == len){
      buffer = xrealloc(buffer, len * 2u * sizeof(char), "Unable to allocate memory!");
      len *= 2u;
    }
  }while(1);
  char const * start = buffer;
  struct TokenNode * tokBuff = xmalloc(sizeof(struct TokenNode) * MIN_TOKEN, "Unable to allocate memory!");
  size_t tokLen = MIN_TOKEN;
  size_t tokPos = 0;
  do{
    start = dish_tokenize(start, tokBuff + tokPos);
    tokPos++;
    if(!start){
      fprintf(stderr, "Tokenizing error. Possibly unmatched apostroph!\n");
      exit(-1);
    }
    if(tokPos == tokLen){
      tokBuff = xrealloc(tokBuff, tokLen * 2u * sizeof(struct TokenNode), "Unable to allocate memory!");
      tokLen *= 2u;
    }
  }while(tokBuff[tokPos - 1].type != TOK_END);
  for(size_t cPos = 0; cPos < tokPos; cPos++){
    struct TokenNode * tok = tokBuff + cPos;
    switch(tok->type){
    default: break;
    case TOK_STRING:
      printf("<<STRNG>> %s\n", tok->str);
      break;
    case TOK_PIPE:
      puts("<<TOKEN>> PIPE");
      break;
    case TOK_RIGHT_REDIR:
      puts("<<REDIR>> RIGHT");
      break;
    case TOK_LEFT_REDIR:
      puts("<<REDIR>> LEFT");
      break;
    case TOK_SEPAR:
      puts("<<SEPAR>> UNC");
      break;
    case TOK_SEPAR_COND_SUCC:
      puts("<<SEPAR>> SUCC");
      break;
    case TOK_SEPAR_COND_FAIL:
      puts("<<SEPAR>> FAIL");
      break;
    case TOK_END:
      puts("<<TOKEN>> END");
      break;
    case TOK_UNIMPLEMENTED:
      puts("<<TOKEN>>UNIMPLEMENTED");
      break;
    }
  }
  free(buffer);
  return 0;
}
