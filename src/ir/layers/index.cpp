#include "ir/layers/index.hpp"

namespace IR {
IndexLayer::IndexLayer() {}

IndexLayer::IndexLayer(FilterCollection filter) {
  this->filter = filter;
}

FilterCollection IndexLayer::getFilters() {
  return filter;
}

void IndexLayer::replaceFilters(FilterCollection filter) {
  this->filter = filter;
}

bool IndexLayer::isEmpty() {
  return filter.isEmpty();
}
}  // namespace IR