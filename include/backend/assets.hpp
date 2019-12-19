#ifndef __MARKUS_BACKEND_ASSETS__
#define __MARKUS_BACKEND_ASSETS__

#include <string>

#include "writer/directory.hpp"

namespace Backend {
namespace Assets {
/**
 * Returns a reference to the assets directory.
 */
Writer::Directory* getAssetsDirectory();

struct InternalAutoReg {
  InternalAutoReg(std::string name, const char* data);
};
}  // namespace Assets
}  // namespace Backend

#endif