#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ast/query.hpp"
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

  AST::Source* program = Parser::createProgram(buffer.str());

  if (Diagnostics::Controller::hasError()) {
    Diagnostics::Controller::dumpAll();
    return -1;
  }

  std::cout << program->hasPermission("Person") << std::endl;
  program->getPermission("Person")->getQuery()->getResultType().dump();

  std::cout << program->hasQuery("XXX") << std::endl;
  program->getQuery("XXX")->getResultType().dump();

  return 0;
}