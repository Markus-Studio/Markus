#ifndef __MARKUS_IR_LAYERS_LIST__
#define __MARKUS_IR_LAYERS_LIST__

#include <vector>

#include "ir/filterCollection.hpp"
#include "type/uri.hpp"

namespace IR {
/**
 * The list layer is responsible to store an ordered/unordered set of things,
 * the reader can have a dynamic filter to filter data on demand.
 */
class ListLayer {
 private:
  /**
   * Set of URIs to store sort-axises.
   */
  std::vector<Type::Uri> sortedBy;

  /**
   * The filter used in this list, every filter can be extracted into two
   * filter collections one containing only static filters and the second
   * one of which contains only dynamic filters, the static sub-filter is
   * used while we're inserting to the list and the dynamic sub-filter is
   * used when we're reading (querying) the data from the list.
   */
  FilterCollection filter;

 public:
  /**
   * Default constructor.
   */
  ListLayer();

  /**
   * Construct a new list layer with the given filter.
   */
  ListLayer(FilterCollection filter);

  /**
   * Sort the list using the given field.
   */
  void sort(Type::Uri);

  /**
   * Returns a vector containing all of the axis this list should be sorted by.
   */
  std::vector<Type::Uri> getSortAxises();

  /**
   * Returns true if the list is sorted.
   */
  bool isSorted();

  /**
   * Returns the filter of this list.
   */
  FilterCollection getFilter();

  /**
   * Replaces the filter inside this list by a new filter.
   */
  void replaceFilter(FilterCollection newFilter);

  /**
   * Returns true if the list is filtered.
   */
  bool isFiltered();

  /**
   * Returns true if there is a dynamic filter in the filters collection.
   */
  bool hasDynamicFilter();
};
}  // namespace IR

#endif