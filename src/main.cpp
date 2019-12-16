#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "parser/tokenizer.hpp"
#include "parser/scanner.hpp"
#include "parser/types.hpp"
#include "diagnostics/error.hpp"
#include "diagnostics/controller.hpp"

using namespace std;

int main(int argc, char *argv[])
{
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

    if (Diagnostics::Controller::hasError())
        Diagnostics::Controller::dumpAll();
}