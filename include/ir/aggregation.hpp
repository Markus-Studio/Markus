#pragma once
#include "type/uri.hpp"
#include "value/call.hpp"

namespace IR {
/**
 * An aggregation function.
 */
enum AggregationFunction { AG_SUM };

/**
 * This class is used to describe an aggregation function, it used in the
 * list and group layers to represent a streaming aggregation and also in
 * the aggregation layer to describe the function in that layer.
 *
 * What's the difference between an streaming aggregation and the aggregation
 * layer?
 * The aggregation layer stores the results and acts like a pre-aggregation
 * unit, so the read happens in O(1) while an streaming aggregation acts online
 * meaning that it computes the result on demand and is more like O(n).
 *
 * ```
 * query q {
 *  groupBy(.a, {
 *    sum(.x) # This leads to an aggregation layer.
 *  }),
 *  max(.data) # But this one leads to a streaming-aggregation on top of the
 *             # `groupBy` layer.
 * }
 * ```
 */
class Aggregation {
 private:
  /**
   * The function used to compute this aggregation.
   */
  enum AggregationFunction function;

  /**
   * The field that is subjected in this aggregation.
   */
  Type::Uri field;

 public:
  /**
   * Construct a new aggregation.
   */
  Aggregation(enum AggregationFunction function, Type::Uri field);

  /**
   * Construct a new aggregation from a call value.
   */
  static Aggregation fromCall(Value::Call* call, Type::Uri selected);

  /**
   * Returns the field that is subjected in this aggregation.
   */
  Type::Uri getSubject();

  /**
   * Returns the aggregation function.
   */
  enum AggregationFunction getFunction();

  /**
   * Returns a string represneting the data inside this aggregation.
   */
  std::string toString();
};
}  // namespace IR