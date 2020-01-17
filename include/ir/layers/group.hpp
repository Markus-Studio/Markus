#ifndef __MARKUS_IR_LAYERS_GROUP__
#define __MARKUS_IR_LAYERS_GROUP__

#include <vector>

#include "ir/filterCollection.hpp"
#include "type/uri.hpp"

namespace IR {
/**
 * The group layer is used for the groupBy pipeline.
 */
class GroupLayer {
 private:
  /**
   * The GroupBy axises.
   */
  std::vector<Type::Uri> axises;

  /**
   * Sorted axises.
   */
  std::vector<Type::Uri> sorted;

  /**
   * The filter applied to the group.
   */
  FilterCollection filter;

 public:
  /**
   * Returns the layer filter.
   */
  FilterCollection getFilter();

  /**
   * Returns the axises.
   */
  std::vector<Type::Uri> getAxises();

  /**
   * Returns the sorted axises.
   */
  std::vector<Type::Uri> getSorted();
};
}  // namespace IR

#endif