#ifndef __MARKUS_VALUE_INT__
#define __MARKUS_VALUE_INT__

#include <string>

#include "parser/range.hpp"
#include "parser/tokenizer.hpp"

namespace Value {
/**
 * An integer value.
 */
class Int {
 private:
  /**
   * The value.
   */
  int value;

  /**
   * The source code range that contains this value.
   */
  Parser::Range range;

 public:
  /**
   * Parse the given string as an int and constructs a new Int.
   */
  Int(std::string string);

  /**
   * Constructs a new int value from the given token.
   */
  Int(Parser::Token* token);

  /**
   * Return the value.
   */
  int getValue();

  /**
   * Returns the range which this value is derived from in the source code.
   */
  Parser::Range getRange();
};
}  // namespace Value

#endif