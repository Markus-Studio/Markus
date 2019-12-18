#ifndef __MARKUS_BACKEND_BINDING__
#define __MARKUS_BACKEND_BINDING__

#include "parser/types.hpp"
#include "writer/directory.hpp"

namespace Backend {
/**
 * Right now we only have one C backend, but we might want to target other
 * languages as well at the future, so we try to create a binding interface
 * that can be used to implement other languages as well.
 */
struct Binding {
  /**
   * First pass in the compiler is to genreate the runtime, which is a constant
   * set of functions or headers that are used in the library.
   */
  void (*generageRuntime)(Writer::Directory* dir);

  /**
   * Second pass in the compilation is generating the file format that contains
   * data objects, and the API to interact with this form as well as the object
   * repository.
   *
   * Object repository is a simple map between object ids to their location on
   * the disk.
   */
  void (*generateTypes)(Writer::Directory* dir, Parser::Types* types);
};

struct Binding* CBinding;
}  // namespace Backend

#endif