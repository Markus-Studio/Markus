#ifndef __MARKUS_VALUE_CALL__
#define __MARKUS_VALUE_CALL__

#include <string>
#include <vector>

#include "parser/range.hpp"
#include "parser/tokenizer.hpp"

namespace Value {
class Container;

/**
 * A function call.
 */
class Call {
 private:
  /**
   * Arguments passed to this function.
   */
  std::vector<Container*> arguments;

  /**
   * Callee name.
   */
  std::string functionName;

  /**
   * The source code range that contains this value.
   */
  Parser::Range range;

 public:
  /**
   * Constructs a new call value.
   */
  Call(std::string calleeName);

  /**
   * Construct a new call value using the given token.
   */
  Call(Parser::Token* token);

  /**
   * Add an argument to this call value.
   */
  void addArgument(Container* value);

  /**
   * Returns the callee name.
   */
  std::string getCalleeName();

  /**
   * Returns a vector containing arguments passed in this function called.
   */
  std::vector<Container*> getArguments();

  /**
   * Expands the range to contain the given range.
   */
  void expandRange(Parser::Range r);

  /**
   * Returns the range which this value is derived from in the source code.
   */
  Parser::Range getRange();
};
}  // namespace Value

#endif