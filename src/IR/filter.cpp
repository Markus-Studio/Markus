#include "IR/filter.hpp"

namespace IR {
Filter::Filter(enum FilterKind kind) {
  this->kind = kind;
}

bool Filter::isIs() {
  return kind == FILTER_KIND_IS;
}
}  // namespace IR