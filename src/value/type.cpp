#include "value/type.hpp"

namespace Value {
TypeValue::TypeValue(Type::Container* type) {
  this->type = type;
}

Type::Container* TypeValue::getType() {
  return type;
}
}  // namespace Value