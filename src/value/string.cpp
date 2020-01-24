#include "value/string.hpp"

#include <assert.h>

namespace Value {
String::String(std::string string) {
  value = string;
}

String::String(Parser::Token token) {
  assert(token.isStringLiteral());
  value = token.getWord();
  range = Parser::Range::fromToken(token);
}

std::string String::getValue() {
  return value;
}

Parser::Range String::getRange() {
  return range;
}

bool String::operator==(String rhs) {
  return value == rhs.value;
}
}  // namespace Value