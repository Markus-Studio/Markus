#pragma once
#include "type/uri.hpp"
#include "value/call.hpp"
#include "value/container.hpp"

namespace IR {
enum FilterOperator {
  FILTER_IS,
  FILTER_EQ,
  FILTER_NEQ,
  FILTER_LT,
  FILTER_GT,
  FILTER_LTE,
  FILTER_GTE,
};

/**
 * A filter that is either a binary or unary can be used to "filter" data,
 * every filter can be either static or dynamic, a dynamic filter is one
 * that is depended on some query parameters or other variable things while
 * a static query is not.
 *
 * A binary query filters data based on certian values of a **field**, like
 * `eq`.
 */
class Filter {
 private:
  /**
   * Indicates if this is a binary filter or not.
   */
  bool _isBinary;

  /**
   * The field that the filter is being executed on.
   */
  Type::Uri field;

  /**
   * The value used in the filter.
   */
  Value::Container value;

  /**
   * The filter operation.
   */
  enum FilterOperator op;

  /**
   * Default constructor.
   */
  Filter();

 public:
  /**
   * Constructs a new binary filter from a call expression, aborts the program
   * if it's not possible to create the filter.
   */
  static Filter Binary(Value::Call* call);

  /**
   * Constructs a new unary filter from a call expression, aborts the program
   * if it's not possible to create the filter.
   */
  static Filter Unary(Value::Call* call);

  /**
   * Apply the select() to a filter.
   */
  static void applySelected(Filter& filter, Type::Uri selected);

  /**
   * Returns the field this (binary) filter is being applied upon.
   */
  Type::Uri getField();

  /**
   * Returns the value this filter is using to "filter" the data.
   */
  Value::Container getValue();

  /**
   * Returns the filter operator.
   */
  enum FilterOperator getOperator();

  /**
   * Returns whatever this filter is static or not, a static filter is a filter
   * that is not depended on the outter-world parameters.
   *
   * Example of static filters:
   *  eq(.x, 5)
   *  eq(.x, .y)
   *
   * Dynamic filters:
   *  eq(.owner, %user)
   *  eq(.x, $x)
   */
  bool isStatic();

  /**
   * Returns whatever the curent filter is binary or not.
   */
  bool isBinary();

  /**
   * Check to see if this (binary) filter is applied to the given uri or not.
   *
   * Field        URI            Result
   * ---------- + ----------  => ----------
   * .A           .B             False
   * .A.B         .A             True
   * .A.B         .A.B           True
   * .A.B         .A.C           False
   * .A.B         .A.B.C         True
   * .A.B.C       .A.B.D         False
   *
   */
  bool isEffecting(Type::Uri uri);

  /**
   * Compares current filter with another filter returns true if they are
   * equal.
   */
  bool operator==(Filter rhs);
};
}  // namespace IR