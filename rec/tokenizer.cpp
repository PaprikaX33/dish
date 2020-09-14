#include "Token.hpp"
#include <tuple>

namespace Di{
  namespace Exc{
    struct LogicalError : Di::Exc::TokenException{
      char const * _text;
      LogicalError(char const * txt) : _text{txt}{}
      virtual char const * err_txt() const noexcept{
        return _text;
      }
      ~LogicalError(){}
    };
  }
}

using Pairret = std::pair<char const *, Di::TokenStrPair>;
static bool is_special(int);
static Pairret parse_block(char const *);
static Pairret process_string(char const *);

Di::TokenStrPair::TokenStrPair(void) noexcept :
  _type(Di::TokenType::TOK_UNIMPLEMENTED),
  _str(nullptr)
{}

Di::TokenStrPair::TokenStrPair(enum Di::TokenType type) noexcept :
  _type(type),
  _str(nullptr)
{}

std::vector<Di::TokenStrPair> Di::scan_string(char const * string)
{
  std::vector<Di::TokenStrPair> retObj;
  Pairret ret = std::make_pair(string, Di::TokenStrPair{});
  do{
    ret = parse_block(ret.first);
    retObj.emplace_back(ret.second);
  }while(ret.second._type != Di::TokenType::TOK_END);
  return retObj;
}

Pairret parse_block(char const * string)
{
  // String Preparation
  if(!string){
    throw Di::Exc::LogicalError{"Null Pointer on input String"};
  }
  auto str = string;
  // Skip Whitespace
  while(isspace(*str)){
    str++;
  }

  // Special Char detection
 // TODO: This switch might be need replacement since now there is a token separator token
  switch(*str){
  case '\0':
    return std::make_pair(str + 1u, Di::TokenType::TOK_END);
  case ';':
    return std::make_pair(str + 1u, Di::TokenType::TOK_PRG_SEPAR);
  case '|':
    if(*(str+1u) == '|'){
      return std::make_pair(str + 2u, Di::TokenType::TOK_PRG_SEPAR_COND_FAIL);
    }
    else{
      return std::make_pair(str + 1u, Di::TokenType::TOK_PIPE);
    }
  case '&':
    if(*(str+1u) == '&'){
      return std::make_pair(str + 2u, Di::TokenType::TOK_PRG_SEPAR_COND_SUCC);
    }
    else{
      return std::make_pair(str + 1u, Di::TokenType::TOK_UNIMPLEMENTED);
    }
  case '<':
    return std::make_pair(str + 1u, Di::TokenType::TOK_LEFT_REDIR);
  case '>':
    return std::make_pair(str + 1u, Di::TokenType::TOK_RIGHT_REDIR);
  default:
    /* This means it's the default string */
    return process_string(str);
  }
  (void)is_special(string[0]);
}

Pairret process_string(char const * str)
{
 // TODO: THIS IS STILL BROKEN
  return std::make_pair(str + 1u, Di::TokenType::TOK_END);
}

bool is_special(int chr)
{
  switch(chr){
    /* Testing if end of char */
  case '\0':
    /* Whitespace */
  case ' ':
  case '\t':
  case '\v':
  case '\f':
  case '\r':
    /* Special Char */
  case '|':
  case '<':
  case '>':
    /* Prog Separ */
  case ';':
  case '&':
    /* Quote */
  case '\"':
  case '\'':
    return true;
  default:
    return false;
  }
}
