#include "ir/layers/list.hpp"

#include <assert.h>

namespace IR {
namespace Layers {
List::List() {
  aggregation = nullptr;
}

List::~List() {
  if (aggregation != nullptr)
    delete aggregation;
}

bool List::hasAggregation() {
  return aggregation != nullptr;
}

bool List::isStaticlyFiltered() {
  return !staticFilter.isEmpty();
}

bool List::isDynamicallyFiltered() {
  return !dynamicFilter.isEmpty();
}

bool List::hasSelection() {
  return !selected.isEmpty();
}

bool List::isSorted() {
  return !sortedAxises.empty();
}

Aggregation List::getAggregation() {
  assert(aggregation != nullptr);
  return *aggregation;
}

void List::setAggregation(Aggregation aggregation) {
  assert(this->aggregation == nullptr);
  this->aggregation =
      new Aggregation(aggregation.getFunction(), aggregation.getSubject());
}

void List::filter(Filter filter) {
  if (filter.isStatic()) {
    staticFilter.add(filter);
  } else {
    dynamicFilter.add(filter);
  }
}

FilterCollection List::getDynamicFilter() {
  return dynamicFilter;
}

FilterCollection List::getStaticFilter() {
  return staticFilter;
}

Type::Uri List::getSelected() {
  return selected;
}

void List::select(Type::Uri field) {
  selected = field.prepend(selected);
}

std::vector<Type::Uri> List::getSortAxises() {
  return sortedAxises;
}

void List::sort(Type::Uri axis) {
  for (int i = 0; i < sortedAxises.size(); ++i)
    if (sortedAxises[i] == axis)
      return;
  sortedAxises.push_back(axis);
}
}  // namespace Layers
}  // namespace IR