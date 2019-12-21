#ifndef __MARKUS_VALUE_CONTAINER__
#define __MARKUS_VALUE_CONTAINER__

#include "value/bool.hpp"
#include "value/float.hpp"
#include "value/int.hpp"
#include "value/string.hpp"
#include "value/variable.hpp"

namespace Value {
/**
 * For each kind of value there is a constant here.
 */
enum ValueKind {
  VALUE_KIND_INT,
  VALUE_KIND_FLOAT,
  VALUE_KIND_BOOL,
  VALUE_KIND_STRING,
  VALUE_KIND_VARIABLE
};

/**
 * To contain any value.
 */
class Container {
 private:
  /**
   * Value type.
   */
  enum ValueKind kind;

  /**
   * Reference to the actual value.
   */
  void* value;

 public:
  /**
   * Construct a container containing an integer literal.
   */
  Container(Int* value);

  /**
   * Construct a container containing a float literal.
   */
  Container(Float* value);

  /**
   * Construct a container containing a boolean literal.
   */
  Container(Bool* value);

  /**
   * Construct a container containing a string literal.
   */
  Container(String* value);

  /**
   * Construct a new contanier containing a variable.
   */
  Container(Variable* value);

  /**
   * Returns whatever the contained value is an integer or not.
   */
  inline bool isInt();

  /**
   * Returns whatever the contained value is a float or not.
   */
  inline bool isFloat();

  /**
   * Returns whatever the contained value is numeric literal.
   */
  inline bool isNumericLiteral();

  /**
   * Returns whatever the contained value is a boolean literal.
   */
  inline bool isBool();

  /**
   * Returns whatever the contained value is a string literal.
   */
  inline bool isString();

  /**
   * Returns whatever the contained value is a literal or not.
   */
  inline bool isLiteral();

  /**
   * Returns whatever the contained value is a variable.
   */
  inline bool isVariable();

  /**
   * Return the value as an integer.
   */
  inline Int* asInt();

  /**
   * Return the value as an int.
   */
  inline Float* asFloat();

  /**
   * Return the value as a boolean.
   */
  inline Bool* asBool();

  /**
   * Return the value as a string.
   */
  inline String* asString();

  /**
   * Return the value as a variable.
   */
  inline Variable* asVariable();
};
}  // namespace Value

#endif