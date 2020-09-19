#include "CmdSepar.hpp"

Di::CommandArr Di::parse_token(Di::TokenArr const & tok)
{
  auto curTok = tok.begin();
  auto const endTok = tok.end();
  bool stopParse = false;
  CommandArr arr;
  do{

  }while(!stopParse || curTok != endTok);
  return arr;
}
