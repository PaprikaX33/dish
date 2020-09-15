#ifndef DISH_TOKEN_HEAD_HPP
#define DISH_TOKEN_HEAD_HPP
#include <vector>
#include <string>
#include <optional>

namespace Di {
  namespace Exc {
  // TODO: make a proper exception base for a "catchall"
    struct TokenException{
      virtual char const * err_txt() const noexcept = 0;
      virtual ~TokenException(){}
    };
  }
  enum class TokenType{
    TOK_STRING,
    TOK_VAR,
    TOK_SEPAR,
    TOK_PIPE,
    TOK_RIGHT_REDIR,
    TOK_LEFT_REDIR,
    TOK_PRG_SEPAR,
    TOK_PRG_SEPAR_COND_SUCC,
    TOK_PRG_SEPAR_COND_FAIL,
    TOK_END,
    TOK_UNIMPLEMENTED
  };

  struct TokenStrPair{
    enum TokenType _type;
    std::optional<std::string> _str;
    TokenStrPair(void) noexcept;
    TokenStrPair(enum TokenType type) noexcept;
  };

  std::vector<TokenStrPair> scan_string(char const *);
}

#endif //DISH_TOKEN_HEAD_HPP
