#include "ir/layers/group.hpp"

namespace IR {
GroupLayer::GroupLayer() {}

GroupLayer::GroupLayer(FilterCollection filter) {
  this->filter = filter;
}

void GroupLayer::sort(Type::Uri axis) {
  sorted.push_back(axis);
}

void GroupLayer::addAxis(Type::Uri axis) {
  axises.push_back(axis);
}

FilterCollection GroupLayer::getFilter() {
  return filter;
}

std::vector<Type::Uri> GroupLayer::getAxises() {
  return axises;
}

std::vector<Type::Uri> GroupLayer::getSorted() {
  return sorted;
}
}  // namespace IR