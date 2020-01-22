#pragma once
#include "type/atomic.hpp"
#include "type/container.hpp"
#include "type/object.hpp"
#include "type/union.hpp"

namespace Type {
/**
 * Array type is a container-like type that can be used to express type of
 * a list of its contained type instead of just one instance of them.
 */
class Array {
  /**
   * The contained type in this array type.
   */
  Container contained;

 public:
  /**
   * Constructs a new array type.
   */
  Array(Container container);

  /**
   * Returns the contained type.
   */
  Container getContainedType();

  /**
   * Evaluates and returns the result of `this is array`.
   */
  bool is(Array* array);

  /**
   * Evaluates and returns the result of `contained is type`, where type is
   * another array type.
   */
  bool isDeep(Array* type);

  /**
   * Evaluates and returns the result of `contained is type`, where type is an
   * atomic type.
   */
  bool isDeep(Atomic* type);

  /**
   * Evaluates and returns the result of `contained is type`, where type is an
   * object type.
   */
  bool isDeep(Object* type);

  /**
   * Evaluates and returns the result of `contained is type`, where type is an
   * union type.
   */
  bool isDeep(Union* type);

  /**
   * Evaluates and returns the result of `contained is type`, where type is any
   * type contained in a container.
   */
  bool isDeep(Container type);

  /**
   * Extract type of a field from this array type.
   */
  Array* query(Uri uri);
};
}  // namespace Type