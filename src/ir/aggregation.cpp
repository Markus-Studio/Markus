#include "ir/aggregation.hpp"

#include <sstream>

namespace IR {
Aggregation::Aggregation(enum AggregationFunction function, Type::Uri field) {
  this->function = function;
  this->field = field;
}

Type::Uri Aggregation::getSubject() {
  return field;
}

enum AggregationFunction Aggregation::getFunction() {
  return function;
}

std::string Aggregation::toString() {
  std::stringstream stream;
  switch (function) {
    case AG_SUM:
      stream << "SUM";
  }
  stream << "  " << field.toString();
  return stream.str();
}
}  // namespace IR