#ifndef DISH_COMMAND_SEPARATOR_HEAD_HPP
#define DISH_COMMAND_SEPARATOR_HEAD_HPP
#include "Token.hpp"
#include <string>
#include <vector>
#include <optional>

namespace Di {
  namespace Exc {
    struct ParsingException{
      virtual char const * err_txt() const noexcept = 0;
      virtual ~ParsingException(){}
    };
  }

  struct CommandBlock {
    struct Interface {
      //TODO: FiLL
      std::optional<std::string> _stdin;
      std::optional<std::string> _stdout;
      std::optional<std::string> _stderr;
    } _inter;
    std::string _cmd;
    std::vector<std::string> _args;
  };

  using CommandArr = std::vector<CommandBlock>;
  CommandArr parse_token(Di::TokenArr const & tok);
}

#endif //DISH_COMMAND_SEPARATOR_HEAD_HPP
