#ifndef __MARKUS_VALUE_CONTAINER__
#define __MARKUS_VALUE_CONTAINER__

#include "parser/range.hpp"
#include "value/bool.hpp"
#include "value/call.hpp"
#include "value/float.hpp"
#include "value/int.hpp"
#include "value/string.hpp"
#include "value/type.hpp"
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
  VALUE_KIND_VARIABLE,
  VALUE_KIND_CALL,
  VALUE_KIND_TYPE
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
   * Construct a new container containing a call expression.
   */
  Container(Call* call);

  /**
   * Construct a new container containing a type value.
   */
  Container(TypeValue* type);

  /**
   * Returns whatever the contained value is an integer or not.
   */
  bool isInt();

  /**
   * Returns whatever the contained value is a float or not.
   */
  bool isFloat();

  /**
   * Returns whatever the contained value is numeric literal.
   */
  bool isNumericLiteral();

  /**
   * Returns whatever the contained value is a boolean literal.
   */
  bool isBool();

  /**
   * Returns whatever the contained value is a string literal.
   */
  bool isString();

  /**
   * Returns whatever the contained value is a literal or not.
   */
  bool isLiteral();

  /**
   * Returns whatever the contained value is a variable.
   */
  bool isVariable();

  /**
   * Returns whatever the contained value is a call expression or not.
   */
  bool isCall();

  /**
   * Returns whatever the contained value us a type value.
   */
  bool isType();

  /**
   * Return the value as an integer.
   */
  Int* asInt();

  /**
   * Return the value as an int.
   */
  Float* asFloat();

  /**
   * Return the value as a boolean.
   */
  Bool* asBool();

  /**
   * Return the value as a string.
   */
  String* asString();

  /**
   * Return the value as a variable.
   */
  Variable* asVariable();

  /**
   * Return the value as a call expression.
   */
  Call* asCall();

  /**
   * Return the value as a type expression.
   */
  TypeValue* asType();

  /**
   * Return the kind of data this container is holding.
   */
  enum ValueKind getKind();

  /**
   * Returns the range which this value is derived from in the source code.
   */
  Parser::Range getRange();
};
}  // namespace Value

#endif