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
// Must not contain the initial $ symbol
static Pairret process_var(char const *);

Di::TokenStrPair::TokenStrPair(void) noexcept :
  _type(Di::TokenType::TOK_UNIMPLEMENTED),
  _str()
{}

Di::TokenStrPair::TokenStrPair(enum Di::TokenType type) noexcept :
  _type(type),
  _str()
{}

std::vector<Di::TokenStrPair> Di::scan_string(char const * string)
{
  // String Preparation
  if(!string){
    throw Di::Exc::LogicalError{"Null Pointer on input String"};
  }
  auto str = string;
  // Skip Initial Whitespace
  while(std::isspace(*str)){
    str++;
  }
  std::vector<Di::TokenStrPair> retObj;
  Pairret ret = std::make_pair(str, Di::TokenStrPair{});
  do{
    ret = parse_block(ret.first);
    retObj.emplace_back(ret.second);
  }while(ret.second._type != Di::TokenType::TOK_END);
  return retObj;
}

Pairret parse_block(char const * string)
{
  auto str = string;
  // Special Char detection
  switch(*str){
  case ' ' :
  case '\t':
  case '\v':
  case '\f':
  case '\r':
    while(isspace(*str)){
      str++;
    }
    return std::make_pair(str, Di::TokenType::TOK_SEPAR);
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
  case '$':
    return process_var(str);
  default:
    // Default string
    return process_string(str);
  }
  (void)is_special(string[0]);
}

Pairret process_string(char const * str)
{
  // TODO: Check for the quotation string
  Di::TokenStrPair strPair{Di::TokenType::TOK_STRING};
  std::size_t len = 0;
  do{
    len++;
  }while(!is_special(str[len]));
  strPair._str = std::string{str, len};
  return std::make_pair(str + len, strPair);
}

Pairret process_var(char const * str)
{
  Di::TokenStrPair strPair{Di::TokenType::TOK_VAR};
  std::size_t len = 0;
  while(std::isalnum(str[len])){
    len++;
  }
  strPair._str = std::string{str, len};
  return std::make_pair(str + len, strPair);
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
