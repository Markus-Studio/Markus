#include "ir/layers/list.hpp"

#include <assert.h>

#include <sstream>

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

std::string List::toString() {
  std::stringstream stream;
  stream << "List {" << std::endl;

  if (!selected.isEmpty())
    stream << "  selected: " << selected.toString() << std::endl;

  if (!dynamicFilter.isEmpty()) {
    std::vector<Filter> filters = dynamicFilter.getFilters();
    stream << "  dynamicFilter: Filter {" << std::endl;
    for (int i = 0; i < filters.size(); ++i)
      stream << "    " << filters[i].toString() << std::endl;
    stream << "  }" << std::endl;
  }

  if (!staticFilter.isEmpty()) {
    std::vector<Filter> filters = staticFilter.getFilters();
    stream << "  staticFilter: Filter {" << std::endl;
    for (int i = 0; i < filters.size(); ++i)
      stream << "    " << filters[i].toString() << std::endl;
    stream << "  }" << std::endl;
  }

  if (!sortedAxises.empty()) {
    stream << "  sortedBy: [";
    stream << sortedAxises[0].toString();
    for (int i = 1; i < sortedAxises.size(); ++i)
      stream << ", " << sortedAxises[i].toString();
    stream << "]" << std::endl;
  }

  if (aggregation != nullptr) {
    stream << "  aggregation: {" << std::endl;
    stream << "    " << aggregation->toString() << std::endl;
    stream << "  }" << std::endl;
  }

  stream << "}";
  return stream.str();
}
}  // namespace Layers
}  // namespace IR