#include "writer/file.hpp"

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

}  // namespace