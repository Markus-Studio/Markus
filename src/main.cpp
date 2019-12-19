#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "backend/binding.hpp"
#include "diagnostics/controller.hpp"
#include "diagnostics/error.hpp"
#include "parser/scanner.hpp"
#include "parser/tokenizer.hpp"
#include "parser/types.hpp"
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

  Parser::TokenVec tokens = Parser::tokenize(buffer.str());
  Parser::Scanner scanner(tokens);
  Parser::Types types(&scanner);

  if (Diagnostics::Controller::hasError()) {
    Diagnostics::Controller::dumpAll();
    return -1;
  }

  Writer::Directory output("/tmp/markus-output");

  struct Backend::Binding c = Backend::createCBinding();
  c.generateRuntime(&output);
  c.generateTypes(&output, &types);
}