#ifndef __MARKUS_VALUE_TYPE__
#define __MARKUS_VALUE_TYPE__

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
  Type::Container* type;

 public:
  /**
   * Constructs a new type value.
   */
  TypeValue(Type::Container* type);

  /**
   * Returns the type that this type-value is refering to.
   */
  Type::Container* getType();
};
}  // namespace Value

#endif