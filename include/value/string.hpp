#ifndef __MARKUS_VALUE_STRING__
#define __MARKUS_VALUE_STRING__

#include <string>

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

 public:
  /**
   * Construct a new String.
   */
  String(std::string string);

  /**
   * Return the value.
   */
  std::string getValue();
};
}  // namespace Value

#endif