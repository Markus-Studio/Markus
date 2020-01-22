#pragma once
#include <vector>

#include "ast/query.hpp"
#include "ir/layer.hpp"

namespace IR {
/**
 * A Query IR is basically a list of layers.
 */
class Query {
 private:
  /**
   * List of layers in this query.
   */
  std::vector<Layer> layers;

 public:
  /**
   * Create a Query IR from a verified Query AST Node.
   */
  Query(AST::Query* query);

  /**
   * Returns the layers.
   */
  std::vector<Layer> getLayers();
};
}  // namespace IR
