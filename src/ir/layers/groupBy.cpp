#include "ir/layers/groupBy.hpp"

#include <assert.h>

#include <sstream>

namespace IR {
namespace Layers {
GroupBy::GroupBy(Type::Uri axis) {
  this->aggregation = nullptr;
  this->axis = axis;
  this->axisSorted = false;
}

GroupBy::~GroupBy() {
  if (aggregation != nullptr)
    delete aggregation;
}

bool GroupBy::isLabelSorted() {
  return axisSorted;
}

bool GroupBy::isLabelDynamicallyFiltered() {
  return !dynamicLabelFilter.isEmpty();
}

bool GroupBy::hasStaticFilter() {
  return !staticFilter.isEmpty();
}

bool GroupBy::hasStreamingAggregator() {
  return aggregation != nullptr;
}

FilterCollection GroupBy::getLabelsDynamicFilter() {
  return dynamicLabelFilter;
}

FilterCollection GroupBy::getStaticFilter() {
  return staticFilter;
}

Aggregation GroupBy::getAggregation() {
  assert(aggregation != nullptr);
  return *aggregation;
}

void GroupBy::setAggregation(Aggregation aggregation) {
  assert(this->aggregation == nullptr);
  this->aggregation =
      new Aggregation(aggregation.getFunction(), aggregation.getSubject());
}

Type::Uri GroupBy::getAxis() {
  return axis;
}

void GroupBy::sortLabels() {
  axisSorted = true;
}

bool GroupBy::filter(Filter filter) {
  // TODO(qti3e)
  return false;
}

std::string GroupBy::toString() {
  std::stringstream stream;
  stream << "GroupBy {" << std::endl;
  stream << "  axis: " << this->axis.toString() << std::endl;
  if (axisSorted)
    stream << "  axisSorted: true" << std::endl;

  if (!dynamicLabelFilter.isEmpty()) {
    std::vector<Filter> filters = dynamicLabelFilter.getFilters();
    stream << "  dynamicLabelFilter: Filter {" << std::endl;
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