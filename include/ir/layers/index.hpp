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

  /**
   * Returns true if the filter collection is empty.
   */
  bool isFunctionEmpty();

  /**
   * Returns a string representing this layer.
   */
  std::string toString();
};
}  // namespace Layers
}  // namespace IR