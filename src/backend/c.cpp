#include <iostream>

#include "backend/binding.hpp"

namespace Backend {

void generateRuntime(Writer::Directory* dir) {
  std::cout << "Gen!" << std::endl;
}

void generateTypes(Writer::Directory* dir, Parser::Types* types) {}

struct Binding createCBinding() {
  struct Binding binding;
  binding.generateRuntime = generateRuntime;
  binding.generateTypes = generateTypes;
  return binding;
}

}  // namespace Backend
