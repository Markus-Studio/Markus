#include "value/int.hpp"

namespace Value {
Int::Int(std::string string) {
  value = std::stoi(string);
}

int Int::getValue() {
  return value;
}
}  // namespace Value