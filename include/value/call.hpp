#ifndef __MARKUS_VALUE_CALL__
#define __MARKUS_VALUE_CALL__

#include <string>
#include <vector>

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
   * Constructs a new call value.
   */
  Call(std::string calleeName);

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
};
}  // namespace Value

#endif