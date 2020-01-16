#include "ir/layers/list.hpp"

namespace IR {
ListLayer::ListLayer() {}

ListLayer::ListLayer(FilterCollection filter) {
  this->filter = filter;
}

void ListLayer::sort(Type::Uri axis) {
  // TODO(qti3e) Insert if it's not already in the list.
  sortedBy.push_back(axis);
}

std::vector<Type::Uri> ListLayer::getSortAxises() {
  return sortedBy;
}

bool ListLayer::isSorted() {
  return !sortedBy.empty();
}

FilterCollection ListLayer::getFilter() {
  return filter;
}

void ListLayer::replaceFilter(FilterCollection newFilter) {
  filter = newFilter;
}

bool ListLayer::isFiltered() {
  return !filter.isEmpty();
}

bool ListLayer::hasDynamicFilter() {
  return !filter.isStatic();
}
}  // namespace IR
