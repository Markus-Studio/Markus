#pragma once
#include "ir/filterCollection.hpp"

namespace IR {
/**
 * The index layer connects the current layer to the next layer based on some
 * parameters.
 */
class IndexLayer {
 private:
  /**
   * The filter that is applied to the index.
   */
  FilterCollection filter;

 public:
  /**
   * Default constructor.
   */
  IndexLayer();

  /**
   * Construct a index filter with the given filter.
   */
  IndexLayer(FilterCollection filter);

  /**
   * Returns current filters in the index.
   */
  FilterCollection getFilters();

  /**
   * Replace the current filter with the given filter.
   */
  void replaceFilters(FilterCollection filter);

  /**
   * Returns true if the filter is empty.
   */
  bool isEmpty();
};
}  // namespace IR