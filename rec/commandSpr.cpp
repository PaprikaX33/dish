#include "CmdSepar.hpp"

namespace Di {
  namespace Exc {
    struct UnimplementedToken : public Di::Exc::ParsingException{
      virtual char const * err_txt() const noexcept override {
        return "UNIMPLEMENTED token has been found";
      }
      ~UnimplementedToken(){}
    };
    struct SyntaxError : public Di::Exc::ParsingException{
      std::string _errStr;
      virtual char const * err_txt() const noexcept override {
        return _errStr.c_str();
      }
      ~SyntaxError(){}
      SyntaxError(Di::TokenType const tok):
        _errStr{"Syntax error near unexpected token: "}
      {
        _errStr += this->tok_to_str(tok);
      }
      char const * tok_to_str(Di::TokenType const tok) {
        switch(tok){
        default:
          return "";
        case Di::TokenType::TOK_PIPE:
          return "|";
        case Di::TokenType::TOK_RIGHT_REDIR:
          return ">";
        case Di::TokenType::TOK_LEFT_REDIR:
          return "<";
        case Di::TokenType::TOK_PRG_SEPAR:
          return ";";
        case Di::TokenType::TOK_PRG_SEPAR_COND_SUCC:
          return "&&";
        case Di::TokenType::TOK_PRG_SEPAR_COND_FAIL:
          return "||";
        }
      }
    };
  }
}

Di::CommandArr Di::parse_token(Di::TokenArr const & tok)
{
  auto curTok = tok.begin();
  auto const endTok = tok.end();
  bool stopParse = false;
  CommandArr arr;
  do{
    Di::CommandBlock block;
    // Skip the separator before the string if any
    while(curTok->_type == Di::TokenType::TOK_SEPAR){
      curTok++;
    }
    if(curTok->_type == Di::TokenType::TOK_END){
      stopParse = true;
      break;
    }
    if(curTok->_type == Di::TokenType::TOK_UNIMPLEMENTED){
      throw Di::Exc::UnimplementedToken{};
    }
    // First string should be the command
    if(curTok->_type != Di::TokenType::TOK_STRING &&
       curTok->_type != Di::TokenType::TOK_VAR){
      throw Di::Exc::SyntaxError{curTok->_type};
    }
    while(curTok->_type == Di::TokenType::TOK_STRING ||
          curTok->_type == Di::TokenType::TOK_VAR){
      block._cmd.push_back(*curTok);
    }
  }while(!stopParse || curTok != endTok);
  return arr;
}
