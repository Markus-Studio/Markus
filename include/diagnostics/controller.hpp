#ifndef __MARKUS_DIAGNOSTICS_CONTROLLER__
#define __MARKUS_DIAGNOSTICS_CONTROLLER__

#include <list>

#include "diagnostics/error.hpp"

namespace Diagnostics {
/**
 * Well, I'm not a C++ developer and have never been, but I've heard
 * it a lot that C++ exceptions are broken and horrible and are hard
 * to be dealt with, so I'm not going to face those kind of problems
 * and here I try to invent my own error handling stuff from scratch
 * see where it leads us :)
 */
class Controller {
 private:
  /**
   * List of all of the reported errors.
   */
  static std::list<Error*> errors;

 public:
  /**
   * Report an error.
   */
  static void report(Error* err);

  /**
   * Check if any error occurred.
   */
  static bool hasError();

  /**
   * Dump all of the errors to the STDERR.
   */
  static void dumpAll();
};
}  // namespace Diagnostics

#endif
