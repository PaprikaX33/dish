#include "ProgState.hpp"
#include "GetLine.hpp"
#include "Token.hpp"
#include <iostream>

#define BOOLSTR(x) (x ? "YES" : "NO")
static char const * token_type_str(enum Di::TokenType tok);

int main(int argc, char ** argv)
{
  (void)argc;(void)argv;
  Di::initialize_global();
  std::cout << "inTTY:\t" << BOOLSTR(Di::global.inTty) << '\n'
            << "outTTY:\t" << BOOLSTR(Di::global.outTty) << '\n'
            << "errTTY:\t" << BOOLSTR(Di::global.errTty) << '\n';
  auto str = Di::getStr();
  try{
    auto tok = Di::scan_string(str.c_str());
    for(auto const & i:tok){
      std::cout << token_type_str(i._type) << '\t' << i._str.value_or("<<NULL>>") << '\n';
    }
  }
  catch(Di::Exc::TokenException const & exc){
    std::cout << exc.err_txt();
  }

  return 0;
}

char const * token_type_str(enum Di::TokenType tok)
{
  switch(tok){
  default: return "";
  case Di::TokenType::TOK_STRING:
    return "<<STRNG>>";
  case Di::TokenType::TOK_VAR:
    return "<<VARIA>>";
  case Di::TokenType::TOK_SEPAR:
    return "<<SPACE>>";
  case Di::TokenType::TOK_PIPE:
    return "<<TOKEN>> PIPE";
  case Di::TokenType::TOK_RIGHT_REDIR:
    return "<<REDIR>> RIGHT";
  case Di::TokenType::TOK_LEFT_REDIR:
    return "<<REDIR>> LEFT";
  case Di::TokenType::TOK_PRG_SEPAR:
    return "<<SEPAR>> UNC";
  case Di::TokenType::TOK_PRG_SEPAR_COND_SUCC:
    return "<<SEPAR>> SUCC";
  case Di::TokenType::TOK_PRG_SEPAR_COND_FAIL:
    return "<<SEPAR>> FAIL";
  case Di::TokenType::TOK_END:
    return "<<TOKEN>> END";
  case Di::TokenType::TOK_UNIMPLEMENTED:
    return "<<TOKEN>>UNIMPLEMENTED";
  }
}
