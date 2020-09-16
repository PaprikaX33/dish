#include "ProgState.hpp"
#include "GetLine.hpp"
#include <cstdio>

namespace Di{
  namespace Exc{
    struct UserEOFReturn : Di::Exc::GetStringException{
      virtual bool soft_exit(void) const noexcept
      {
        return true;
      }
      virtual char const * err_txt(void) const noexcept
      {
        return "User requested exit with EOF";
      }
      virtual ~UserEOFReturn(){}
    };
  }
}

std::string Di::getStr(void)
{
  std::string buff{};
  if(!Di::global.inTty){
    do{
      int chr = getchar();
      if(chr == EOF){
        return buff;
      }
      buff.push_back(static_cast<std::string::value_type>(chr));
    }while(1);
  }
  printf("TokenTest>");
  do{
    int chr = getchar();
    if(chr == EOF){
      throw Di::Exc::UserEOFReturn{};
    }
    if(chr == '\n'){
      return buff;
    }
    buff.push_back(static_cast<std::string::value_type>(chr));
  }while(1);
}
