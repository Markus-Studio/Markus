#ifndef __MARKUS_VALUE_MEMBER__
#define __MARKUS_VALUE_MEMBER__

#include "value/field.hpp"
#include "value/variable.hpp"

namespace Value {
/**
 * A member value is selection of a field on a specific variable.
 * Example: $x.a.b -> { base: $x, field: .a.b }
 */
class Member {
 private:
  /**
   */
  Variable base;

  Field field;

  int line;

  int column;
};
}  // namespace Value

#endif