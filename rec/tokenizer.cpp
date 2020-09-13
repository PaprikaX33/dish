#include "Token.hpp"

Di::TokenStrPair::TokenStrPair(void) noexcept :
  type(Di::TokenType::TOK_UNIMPLEMENTED),
  str(nullptr)
{}

std::vector<Di::TokenStrPair> Di::scan_string(char const * string)
{
  (void) string;
  return std::vector<Di::TokenStrPair>{};
}
