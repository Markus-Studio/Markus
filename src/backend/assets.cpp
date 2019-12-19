#include "backend/assets.hpp"

namespace Backend {
namespace Assets {
// The virtual directroy that contains all of the assets.
static Writer::Directory* dir;

Writer::Directory* getAssetsDirectory() {
  return dir;
}

InternalAutoReg::InternalAutoReg(std::string name, const char* data) {
  static Writer::Directory directory;
  dir = &directory;

  Writer::File* file = dir->createFile(name);
  *file << "Hello";
}
}  // namespace Assets
}  // namespace Backend