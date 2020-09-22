#ifndef DISH_GET_LINE_HEAD_HPP
#define DISH_GET_LINE_HEAD_HPP
#include "Common.hpp"
#include <string>

namespace Di {
  namespace Exc {
    struct GetStringException{
      virtual bool soft_exit(void) const noexcept = 0;
      virtual char const * err_txt(void) const noexcept = 0;
      virtual ~GetStringException(){}
    };
  }
  std::string getStr(void);
}

#endif //DISH_GET_LINE_HEAD_HPP
