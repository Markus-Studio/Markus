#include "writer/directory.hpp"

#include "../test.hpp"

using namespace Writer;

namespace {
TEST("Directory: has") {
  Directory dir;
  File file;

  CHECK(!dir.has("X"));

  dir.addFile("X", &file);
  dir.createFile("A");

  CHECK(dir.has("X"));
  CHECK(dir.has("A"));
}

TEST("Directory: sync") {
  File file;
  file << "A";
  file << 123;
  file << "B";
  file << "C";
  file << "\n";

  Directory dir("/tmp/markus/x/y");
  dir.addFile("file.txt", &file);
  dir.close();

  std::ifstream contentStream;
  std::stringstream stream;
  contentStream.open("/tmp/markus/x/y/file.txt", std::ios::in);
  CHECK(contentStream.is_open());
  stream << contentStream.rdbuf();

  CHECK(stream.str() == "A123BC\n");
}
}  // namespace