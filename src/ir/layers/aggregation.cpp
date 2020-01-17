#include "ir/layers/aggregation.hpp"

namespace IR {
AggregationLayer::AggregationLayer(enum AggregationKind kind, Type::Uri field) {
  this->kind = kind;
  this->field = field;
}

enum AggregationKind AggregationLayer::getKind() {
  return kind;
}

Type::Uri AggregationLayer::getField() {
  return field;
}
}  // namespace IR