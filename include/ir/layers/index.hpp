#pragma once

#include "ir/filterCollection.hpp"

namespace IR {
namespace Layers {
/**
 * The index layer.
 */
class Index {
 private:
  /**
   * The function that is used for indexing.
   */
  FilterCollection function;

 public:
  /**
   * Request this index to add the given filter to its `function` return false
   * if it does not add the filter.
   */
  bool addFilter(Filter filter);

  /**
   * Returns the indexing function.
   */
  FilterCollection getFunction();
};
}  // namespace Layers
}  // namespace IR