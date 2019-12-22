#ifndef __MARKUS_VALUE_CALL__
#define __MARKUS_VALUE_CALL__

#include <string>
#include <vector>
#include "IR/query.hpp"

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

 public:
  /**
   * Verify this function call.
   */
  bool verify(IR::Query* query);

  /**
   * Return the return type of this call.
   */
  std::string getReturnType();
};
}  // namespace Value

#endif