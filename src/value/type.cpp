#include "value/type.hpp"

namespace Value {
TypeValue::TypeValue(Type::Container type, Parser::Range range) {
  this->type = type;
  this->range = range;
}

Type::Container TypeValue::getType() {
  return type;
}

Parser::Range TypeValue::getRange() {
  return range;
}

bool TypeValue::operator==(TypeValue rhs) {
  return type.is(rhs.type) && rhs.type.is(type);
}
}  // namespace Value