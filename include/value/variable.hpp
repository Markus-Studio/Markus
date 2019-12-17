#ifndef __MARKUS_VALUE_VARIABLE__
#define __MARKUS_VALUE_VARIABLE__

#include <string>

#include "type/container.hpp"

namespace Value {
/**
 * An internal or user defined variable in the source code.
 */
class Variable {
 private:
  /**
   * The type of this variable.
   */
  Type::Container type;

  /**
   * Line number that contains this variable.
   */
  int line;

  /**
   * Column number on the line that contains this variable.
   */
  int column;

  /**
   * Name of this variable.
   */
  std::string name;

 public:
  /**
   * Constructs a new variable.
   */
  Variable(int line, int column, std::string name, Type::Container type);

  /**
   * Returns line number.
   */
  int getLine();

  /**
   * Returns column number.
   */
  int getColumn();

  /**
   * Returns the name of this variable.
   */
  std::string getName();

  /**
   * Returns the type of this variable.
   */
  Type::Container getType();

  /**
   * Format the variable and return it as an string.
   */
  std::string toString();
};
}  // namespace Value

#endif