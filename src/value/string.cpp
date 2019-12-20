#include "value/string.hpp"

namespace Value {
String::String(std::string string) {
  value = string;
}

std::string String::getValue() {
  return value;
}
}  // namespace Value