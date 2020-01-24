#include "value/float.hpp"

#include <assert.h>

namespace Value {
Float::Float(std::string string) {
  value = std::stof(string);
}

Float::Float(Parser::Token token) {
  assert(token.isFloatLiteral());
  value = std::stof(token.getWord());
  range = Parser::Range::fromToken(token);
}

float Float::getValue() {
  return value;
}

Parser::Range Float::getRange() {
  return range;
}

bool Float::operator==(Float rhs) {
  return value == rhs.value;
}
}  // namespace Value