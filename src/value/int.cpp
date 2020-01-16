#include "value/int.hpp"

#include <assert.h>

namespace Value {
Int::Int(std::string string) {
  value = std::stoi(string);
}

Int::Int(Parser::Token token) {
  assert(token.isIntLiteral());
  value = std::stoi(token.getWord());
  range = Parser::Range::fromToken(token);
}

int Int::getValue() {
  return value;
}

Parser::Range Int::getRange() {
  return range;
}
}  // namespace Value