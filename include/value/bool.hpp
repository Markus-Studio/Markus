#ifndef __MARKUS_VALUE_BOOL__
#define __MARKUS_VALUE_BOOL__

#include <string>

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

 public:
  /**
   * Constructs a new boolean literal.
   */
  Bool(std::string word);

  /**
   * Returns the value.
   */
  bool getValue();
};
}  // namespace Value

#endif