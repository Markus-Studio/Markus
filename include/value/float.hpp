#pragma once
#include <string>

#include "parser/range.hpp"
#include "parser/tokenizer.hpp"

namespace Value {
/**
 * A float value.
 */
class Float {
 private:
  /**
   * The actual value.
   */
  float value;

  /**
   * The source code range that contains this value.
   */
  Parser::Range range;

 public:
  /**
   * Parse the string and construct a new Float.
   */
  Float(std::string string);

  /**
   * Constructs a new float value from the given token.
   */
  Float(Parser::Token token);

  /**
   * Return the value stored in this float instance.
   */
  float getValue();

  /**
   * Returns the range which this value is derived from in the source code.
   */
  Parser::Range getRange();
};
}  // namespace Value