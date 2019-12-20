#include "value/float.hpp"

namespace Value {
Float::Float(std::string string) {
  value = std::stof(string);
}

float Float::getValue() {
  return value;
}
}  // namespace Value