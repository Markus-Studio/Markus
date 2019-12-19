#include "writer/file.hpp"

#include <iostream>

#include "../test.hpp"

using namespace Writer;

namespace {

TEST("File: must be writable") {
  File file;
  file << "A";
  file << "B";

  CHECK(file.str() == "AB");

  file << "X";
  CHECK(file.str() == "ABX");
}

TEST("File: write to a string stream") {
  std::stringstream stream;
  File file;

  file << "ABCD";
  file.writeTo(stream);
  file << " XYZ";

  CHECK(stream.str() == "ABCD");
  CHECK(file.str() == "ABCD XYZ");
}

TEST("File: write to another file") {
  File file, file2;
  file << "ABCD";
  file.writeTo(file2);

  CHECK(file2.str() == "ABCD");
}

TEST("File: read from a string stream") {
  std::stringstream stream, stream2;
  File file;

  stream << "A";
  stream << "B";
  file << stream;

  CHECK(file.str() == "AB");

  stream2 << "Y";
  file << stream2;

  stream << "X";
  file << stream;

  CHECK(file.str() == "ABYX");
}

TEST("File: read from a string bufffer") {
  std::stringstream stream, stream2;
  File file;

  stream << "A";
  stream << "B";
  file << stream.rdbuf();

  CHECK(file.str() == "AB");

  stream2 << "Y";
  file << stream2.rdbuf();

  stream << "X";
  file << stream.rdbuf();

  CHECK(file.str() == "ABYX");
}

TEST("File: keep data") {
  std::stringstream stream;

  File file;
  file << "A";

  file.writeTo(stream);

  file << "B";
  file.writeTo(stream);

  CHECK(file.str() == "AB");
}

TEST("File: write number") {
  File file;
  file << 123;
  CHECK(file.str() == "123");
}

TEST("File: sync") {
  File file;
  file << "A";

  std::ofstream disk;
  disk.open("/tmp/markus-test-writer-01.txt", std::ios::out | std::ios::trunc);

  CHECK(disk.is_open());

  file.keepSync(&disk);

  file << 123;
  file << "B";
  file << "C";
  file << "\n";
  file.close();

  CHECK(!disk.is_open());

  std::ifstream contentStream;
  std::stringstream stream;
  contentStream.open("/tmp/markus-test-writer-01.txt", std::ios::in);
  CHECK(contentStream.is_open());
  stream << contentStream.rdbuf();

  CHECK(stream.str() == "A123BC\n");
}

}  // namespace