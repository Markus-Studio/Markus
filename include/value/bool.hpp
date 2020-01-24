#pragma once
#include <string>

#include "parser/range.hpp"
#include "parser/tokenizer.hpp"

namespace Value {
/**
 * A boolean literal value.
 */
class Bool {
 private:
  /**
   * The value.
   */
  bool value;

  /**
   * The source code range that contains this value.
   */
  Parser::Range range;

 public:
  /**
   * Constructs a new boolean literal.
   */
  Bool(std::string word);

  /**
   * Constructs a new boolean from the given token.
   */
  Bool(Parser::Token token);

  /**
   * Returns the value.
   */
  bool getValue();

  /**
   * Returns the range which this value is derived from in the source code.
   */
  Parser::Range getRange();

  /**
   * Returns true if the boolean values are equal.
   */
  bool operator==(Bool rhs);
};
}  // namespace Value