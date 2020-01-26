#pragma once

#include "ir/aggregation.hpp"
#include "ir/filterCollection.hpp"

namespace IR {
namespace Layers {
class GroupBy {
 private:
  /**
   * The streaming aggregation on the top of grouped elements if any.
   */
  Aggregation* aggregation;

  /**
   * The field which we use to group elements by.
   */
  Type::Uri axis;

  /**
   * True if the axis is sorted.
   */
  bool axisSorted;

  /**
   * The dynamic filters which work on grouping axis.
   */
  FilterCollection dynamicLabelFilter;

  /**
   * The static filter used to filter elements of the group.
   */
  FilterCollection staticFilter;

 public:
  /**
   * Default constructor.
   */
  GroupBy(Type::Uri axis);

  /**
   * Default deconstructor.
   */
  ~GroupBy();

  /**
   * Returns true if the grouping-axis is sorted.
   */
  bool isLabelSorted();

  /**
   * Returns true if the labels are dynamically filtered.
   */
  bool isLabelDynamicallyFiltered();

  /**
   * Returns true if the objects inside the group are filtered.
   */
  bool hasStaticFilter();

  /**
   * Returns true if the elements of each group are feeded into an aggregation
   * function.
   */
  bool hasStreamingAggregator();

  /**
   * Returns dynamic filters that are applied to the labels.
   */
  FilterCollection getLabelsDynamicFilter();

  /**
   * Returns static filters that are applied to every node in each group.
   */
  FilterCollection getStaticFilter();

  /**
   * Returns the streaming aggregation of this layer, aborts if it's not set.
   */
  Aggregation getAggregation();

  /**
   * Set this layers aggregation function to the given one, aborts if there is
   * already one in use.
   */
  void setAggregation(Aggregation aggregation);

  /**
   * Returns the grouping axis.
   */
  Type::Uri getAxis();

  /**
   * Sort labels.
   */
  void sortLabels();

  /**
   * Tries to add the given filter to this layer returns false if it's not
   * possible to find a place for it.
   */
  bool filter(Filter filter);

  /**
   * Returns a string representing this layer.
   */
  std::string toString();
};
}  // namespace Layers
}  // namespace IR