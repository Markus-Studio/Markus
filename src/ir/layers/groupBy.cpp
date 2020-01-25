#include "ir/layers/groupBy.hpp"

#include <assert.h>

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
}  // namespace Layers
}  // namespace IR