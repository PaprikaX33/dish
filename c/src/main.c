#include "verString.inc"
#include <stdio.h>
#include <string.h>

static int arg_parse(int argc, char ** argv);

int main(int argc, char ** argv)
{
  int retcode;
  if((retcode = arg_parse(argc, argv))){
    return (retcode < 0 ? retcode : 0);
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
