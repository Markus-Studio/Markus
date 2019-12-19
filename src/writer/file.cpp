#include "writer/file.hpp"

#include <iostream>

namespace Writer {
void File::keepSync(std::ofstream* stream) {
  *stream << inMemory.str();
  files.push_back(stream);
}

void File::writeTo(std::stringstream& stream) {
  stream << inMemory.str();
}

void File::writeTo(std::ofstream& stream) {
  stream << inMemory.str();
}

void File::writeTo(File& file) {
  file << inMemory.str();
}

std::string File::str() {
  return inMemory.str();
}

void File::operator<<(std::string data) {
  inMemory << data;
  if (!files.empty()) {
    buffer << data;
    flush();
  }
}

void File::operator<<(std::stringstream& stream) {
  inMemory << stream.rdbuf();
  if (!files.empty()) {
    buffer << stream.rdbuf();
    flush();
  }
}

void File::operator<<(std::stringbuf* buf) {
  inMemory << buf;
  if (!files.empty()) {
    buffer << buf;
    flush();
  }
}

void File::operator<<(int number) {
  inMemory << number;
  if (!files.empty()) {
    buffer << number;
    flush();
  }
}

void File::flush() {
  std::string str = buffer.str();

  if (str.empty())
    return;

  std::vector<std::ofstream*>::iterator it = files.begin();

  for (; it != files.end(); ++it) {
    (**it) << str;
    (*it)->flush();
  }

  buffer.str(std::string());
}

void File::close() {
  closed = true;
  std::vector<std::ofstream*>::iterator it = files.begin();
  flush();

  for (; it != files.end(); ++it)
    (*it)->close();
}

}  // namespace Writer