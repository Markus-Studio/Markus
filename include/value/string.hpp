#pragma once
#include <string>

#include "parser/range.hpp"
#include "parser/tokenizer.hpp"

namespace Value {
/**
 * An string value in the program.
 */
class String {
 private:
  /**
   * The actual string value.
   */
  std::string value;

  /**
   * The source code range that contains this value.
   */
  Parser::Range range;

 public:
  /**
   * Construct a new String.
   */
  String(std::string string);

  /**
   * Constructs a new string value from the given token.
   */
  String(Parser::Token token);

  /**
   * Return the value.
   */
  std::string getValue();

  /**
   * Returns the range which this value is derived from in the source code.
   */
  Parser::Range getRange();

  /**
   * Returns true if the current value is equal to one of the rhs.
   */
  bool operator==(String rhs);
};
}  // namespace Value