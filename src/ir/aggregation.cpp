#include "ir/aggregation.hpp"

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
}  // namespace IR