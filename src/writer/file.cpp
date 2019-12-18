#include "writer/file.hpp"

namespace Writer {
void File::writeTo(std::stringstream& stream) {
  stream << inMemory.rdbuf();
}

void File::writeTo(std::ofstream& stream) {
  stream << inMemory.rdbuf();
}

void File::writeTo(File& file) {
  file << inMemory.rdbuf();
}

std::string File::str() {
  return inMemory.str();
}

void File::close() {
  closed = true;
  // TODO(qti3e) Close files.
}

void File::operator<<(std::string data) {
  inMemory << data;
}

void File::operator<<(std::stringstream& stream) {
  inMemory << stream.rdbuf();
}

void File::operator<<(std::stringbuf* buf) {
  inMemory << buf;
}

void File::operator<<(int number) {
  inMemory << number;
}

}  // namespace Writer