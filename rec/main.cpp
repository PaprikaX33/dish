#include "ProgState.hpp"
#include "GetLine.hpp"
#include "Token.hpp"
#include <iostream>

#define BOOLSTR(x) (x ? "YES" : "NO")

int main(int argc, char ** argv)
{
  (void)argc;(void)argv;
  Di::initialize_global();
  std::cout << "inTTY:\t" << BOOLSTR(Di::global.inTty) << '\n'
            << "outTTY:\t" << BOOLSTR(Di::global.outTty) << '\n'
            << "errTTY:\t" << BOOLSTR(Di::global.errTty) << '\n';
  auto str = Di::getStr();
  std::cout << str << '\n';
  try{
    auto tok = Di::scan_string(str.c_str());
    std::cout << "parsed scanString\n";
    auto toka = Di::scan_string(nullptr);
    std::cout << "parsed all\n";
  }
  catch(Di::Exc::TokenException const & exc){
    std::cout << exc.err_txt();
  }

  return 0;
}
