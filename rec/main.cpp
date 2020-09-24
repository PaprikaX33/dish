#include "ProgState.hpp"
#include "GetLine.hpp"
#include "CmdSepar.hpp"
#include "Token.hpp"
#include <iostream>

#define BOOLSTR(x) (x ? "YES" : "NO")
static char const * token_type_str(enum Di::TokenType tok);
static void pretty_print_cmd(Di::CommandBlock const & cmd);

int main(int argc, char ** argv)
{
  (void)argc;(void)argv;
  Di::initialize_global();
  std::cout << "inTTY:\t" << BOOLSTR(Di::global.inTty) << '\n'
            << "outTTY:\t" << BOOLSTR(Di::global.outTty) << '\n'
            << "errTTY:\t" << BOOLSTR(Di::global.errTty) << '\n';
  try{
    auto str = Di::getStr();
    auto tok = Di::scan_string(str.c_str());
    for(auto const & i:tok){
      std::cout << token_type_str(i._type) << '\t' << i._str.value_or("<->") << '\n';
    }
    auto cmd = Di::parse_token(tok);
#ifndef NDEBUG
    for(auto const & i : cmd){
      std::cout << "==========\n";
      pretty_print_cmd(i);
    }
#endif //NDEBUG
  }
  catch(Di::Exc::GetStringException const & exc){
    return exc.soft_exit() ? 0 : (std::cerr << "Get String Error: " << exc.err_txt() << '\n' , -1);
  }
  catch(Di::Exc::ParsingException const & exc){
    std::cerr << "Parsing Error: " << exc.err_txt() << '\n';
  }
  catch(Di::Exc::TokenException const & exc){
    std::cerr << "Tokenizing Error: " << exc.err_txt() << '\n';
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

void pretty_print_cmd(Di::CommandBlock const & cmd)
{
  std::cout << "Command: ";
  for(auto const & i : cmd._cmd){
    std::cout << i._str.value_or("<NLL>") << ' ';
  }
  std::cout << '\n' << "Args : ";
  for(auto const & i : cmd._args){
    std::cout << i._str.value_or("<NLL>") << ' ';
  }
  std::cout << '\n';
}
