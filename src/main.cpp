#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "diagnostics/controller.hpp"
#include "parser/parser.hpp"
#include "writer/directory.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return -1;
  }

  std::ifstream t(argv[1]);

  if (!t.is_open()) {
    cerr << "There was an error trying to read " << argv[1] << endl;
    return -1;
  }

  std::stringstream buffer;
  buffer << t.rdbuf();

  IR::Program* program = Parser::createProgram(buffer.str());

  if (Diagnostics::Controller::hasError()) {
    Diagnostics::Controller::dumpAll();
    return -1;
  }

  std::cout << program->hasPermission("Person") << std::endl;

  return 0;
}