#include "value/bool.hpp"

#include <assert.h>

namespace Value {
Bool::Bool(std::string word) {
  value = word == "true";
}

Bool::Bool(Parser::Token* token) {
  assert(token->isBoolLiteral());
  value = token->getWord() == "true";
  range = Parser::Range::fromToken(token);
}

bool Bool::getValue() {
  return value;
}

Parser::Range Bool::getRange() {
  return range;
}
}  // namespace Value