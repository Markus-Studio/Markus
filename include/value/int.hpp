#ifndef __MARKUS_VALUE_INT__
#define __MARKUS_VALUE_INT__

#include <string>

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

 public:
  /**
   * Parse the given string as an int and constructs a new Int.
   */
  Int(std::string string);

  /**
   * Return the value.
   */
  int getValue();
};
}  // namespace Value

#endif