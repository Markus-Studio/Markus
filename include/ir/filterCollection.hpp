#ifndef __MARKUS_IR_FILTER_COLLECTION__
#define __MARKUS_IR_FILTER_COLLECTION__

#include <vector>
#include "ir/filter.hpp"

namespace IR {
/**
 * A filter collection is a list of filters.
 */
class FilterCollection {
 private:
  /**
   * Filters in this collection.
   */
  std::vector<Filter> filters;

 public:
  /**
   * Adds the given filter to this list.
   */
  void add(Filter filter);

  /**
   * Return filters in this collection.
   */
  std::vector<Filter> getFilters();

  /**
   * Returns true if all the filters in this list are static filters.
   */
  bool isStatic();

  /**
   * Extract the static filters into a new collection.
   */
  FilterCollection extractStatic();

  /**
   * Extract the dynamic filters into a new collection.
   */
  FilterCollection extractDynamic();

  /**
   * Returns true if any of the filters in this list are effecting the given
   * field.
   */
  bool isEffecting(Type::Uri uri);
};
}  // namespace IR

#endif