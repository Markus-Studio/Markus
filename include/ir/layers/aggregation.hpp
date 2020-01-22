#pragma once
#include "type/uri.hpp"

namespace IR {
enum AggregationKind { AGR_SUM };

class AggregationLayer {
 private:
  /**
   * The aggregation function.
   */
  enum AggregationKind kind;

  /**
   * The field which the aggregation is being
   */
  Type::Uri field;

 public:
  /**
   * The field.
   */
  AggregationLayer(enum AggregationKind kind, Type::Uri field);

  /**
   * Returns the aggregation function.
   */
  enum AggregationKind getKind();

  /**
   * Returns the field.
   */
  Type::Uri getField();
};
}  // namespace IR