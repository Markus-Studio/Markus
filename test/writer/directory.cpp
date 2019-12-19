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

TEST("Directory: sync2") {
  Directory dir("/tmp/markus-test-2");
  File* file = dir.file("hello");
  *file << "Test\n";
  dir.close();

  std::ifstream contentStream;
  std::stringstream stream;
  contentStream.open("/tmp/markus-test-2/hello", std::ios::in);
  CHECK(contentStream.is_open());
  stream << contentStream.rdbuf();
  CHECK(stream.str() == "Test\n");
}

TEST("Directory: file() and dir()") {
  Directory dir, x, *x2, *y, *y2;
  dir.addDirectory("x", &x);
  x2 = dir.dir("x");
  x.file("file.txt");
  CHECK(x2->has("file.txt"));

  y = dir.dir("y");
  y->file("hello.txt");
  y2 = dir.dir("y");
  CHECK(y2->has("hello.txt"));

  CHECK(dir.has("x"));
  CHECK(dir.has("y"));
}
}  // namespace