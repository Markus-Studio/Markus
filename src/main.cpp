#include <iostream>
#include <vector>
#include <string>
#include "parser/tokenizer.hpp"
#include "parser/scanner.hpp"
#include "diagnostics/error.hpp"
#include "diagnostics/controller.hpp"

using namespace std;

int main()
{
    string source =
        "query X() {\n"
        "}\n"
        "action Y{}\n"
        "query Y{}\n";

    cout << source << endl;

    Parser::TokenVec tokens = Parser::tokenize(source);
    Parser::Scanner scanner(tokens);

    cout << scanner.hasQuery("Y") << endl;
    cout << scanner.hasQuery("Z") << endl;

    if (Diagnostics::Controller::hasError())
        Diagnostics::Controller::dumpAll();
}