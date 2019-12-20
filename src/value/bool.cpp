#include "value/bool.hpp"

namespace Value {
Bool::Bool(std::string word) {
  value = word == "true";
}

bool Bool::getValue() {
  return value;
}
}  // namespace Value