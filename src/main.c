#include "Dish.h"
#include "GlobalState.h"
#include "verString.inc"
#include <stdio.h>
#include <string.h>

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


int dish_tok_test(void)
{
  printf("TokenTest>");
  return 0;
}
