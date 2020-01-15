#ifndef __MARKUS_PARSER_RANGE__
#define __MARKUS_PARSER_RANGE__

#include "parser/tokenizer.hpp"

namespace Parser {
/**
 * A range in the source code.
 */
class Range {
 private:
  /**
   * Begining line number.
   */
  int lineStart;

  /**
   * Begining column number.
   */
  int columnStart;

  /**
   * End line number.
   */
  int lineEnd;

  /**
   * End column number.
   */
  int columnEnd;

 public:
  /**
   * Default constructor.
   */
  Range();

  /**
   * Constructs a new range from the given token.
   */
  static Range fromToken(Token* token);

  /**
   * Returns the begining line number.
   */
  int getLineStart();

  /**
   * Returns the end line number.
   */
  int getLineEnd();

  /**
   * Returns the begining column number.
   */
  int getColumnStart();

  /**
   * Returns the end column number.
   */
  int getColumnEnd();

  /**
   * Add two ranges.
   */
  Range operator+(Range range);
};
}  // namespace Parser

#endif