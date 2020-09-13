#include "ProgState.hpp"
#include "GetLine.hpp"
#include <cstdio>

std::string Di::getStr(void)
{
  std::string buff{};
  if(!Di::global.inTty){
    std::fputs("Only in TTY\n", stderr);
    return 0;
  }
  printf("TokenTest>");
  do{
    int chr = getchar();
    if(chr =='\n'){
      return buff;
    }
    buff.push_back(static_cast<std::string::value_type>(chr));
  }while(1);
}
