#ifndef __MARKUS_IR_LAYERS_AGGREGATION__
#define __MARKUS_IR_LAYERS_AGGREGATION__

#include "type/uri.hpp"

namespace IR {
enum AggregationKind { AGR_SUM };

class Aggregation {
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
  Aggregation(enum AggregationKind kind, Type::Uri field);

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

#endif