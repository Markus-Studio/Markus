#pragma once
#include "parser/range.hpp"
#include "type/container.hpp"

namespace Value {
/**
 * When there is a reference to a type in the program, like in `is(User)`, that
 * thing is a type-value, and this class implements the type-value.
 */
class TypeValue {
 private:
  /**
   * The reference.
   */
  Type::Container type;

  /**
   * The source code range that contains this value.
   */
  Parser::Range range;

 public:
  /**
   * Constructs a new type value.
   */
  TypeValue(Type::Container type, Parser::Range range);

  /**
   * Returns the type that this type-value is refering to.
   */
  Type::Container getType();

  /**
   * Returns the range which this value is derived from in the source code.
   */
  Parser::Range getRange();

  /**
   * Returns true if the current value is equal to one of the rhs.
   */
  bool operator==(TypeValue rhs);
};
}  // namespace Value