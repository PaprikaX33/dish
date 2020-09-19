#include "CmdSepar.hpp"

namespace Di {
  namespace Exc {
    struct UnimplementedToken : public Di::Exc::ParsingException{
      virtual char const * err_txt() const noexcept override {
        return "UNIMPLEMENTED token has been found";
      }
      ~UnimplementedToken(){}
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
  }while(!stopParse || curTok != endTok);
  return arr;
}
