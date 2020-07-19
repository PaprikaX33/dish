#include "verString.inc"
#include <stdio.h>
#include <string.h>

static int arg_parse(int argc, char ** argv);

int main(int argc, char ** argv)
{
  if(arg_parse(argc, argv)){
    return 0;
  }
  printf("Hello World\n");
  return 0;
}

static void write_help(void);
static void write_vers(void);

int arg_parse(int argc, char ** argv)
{
  for(int i = 1; i < argc; i++){
    char const * arg = argv[i];
    if(arg[0] != '-'){
      continue;
    }
    arg++;
    if(!strcmp(arg, "-help") || !strcmp(arg, "h") || !strcmp(arg, "?")){
      write_help();
      return -1;
    }
    if(!strcmp(arg, "-version") || !strcmp(arg, "V")){
      write_vers();
      return -1;
    }
  }
  return 0;
}

void write_help(void)
{

}
void write_vers(void)
{
  puts(VersionString);
}
