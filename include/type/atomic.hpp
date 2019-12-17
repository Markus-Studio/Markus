#ifndef __MARKUS_TYPE_ATOMIC__
#define __MARKUS_TYPE_ATOMIC__

#include <string>

namespace Type {
// Forward declaration.
class Union;

/**
 * Every instance of Atomic class represents a markus atomic type
 * such as `int`, `float` and more.
 */
class Atomic {
 private:
  /**
   * Unique name of this type.
   */
  std::string name;

 public:
  /**
   * Constructs a new atomic type with the given name.
   */
  Atomic(std::string name);

  /**
   * Returns name of this type.
   */
  std::string getName();

  /**
   * Returns the result of evaluating `this is type`, where `type` is
   * another atomic type passed as the first parameter.
   *
   * It only checks if the name of both types are the same.
   */
  bool is(Atomic* type);

  /**
   * Returns the result of evaluating `this is type`, where `type` is
   * an union type passed as the first parameter.
   *
   * It is equal to calling `type.has(this)`.
   */
  bool is(Union* type);
};
}  // namespace Type

#endif