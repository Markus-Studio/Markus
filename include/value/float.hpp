#ifndef __MARKUS_VALUE_FLOAT__
#define __MARKUS_VALUE_FLOAT__

#include <string>

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

 public:
  /**
   * Parse the string and construct a new Float.
   */

  Float(std::string string);

  /**
   * Return the value stored in this float instance.
   */
  float getValue();
};
}  // namespace Value

#endif