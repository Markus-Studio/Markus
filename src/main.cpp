#include <iostream>
#include <vector>
#include <string>
#include "parser/tokenizer.hpp"
#include "parser/scanner.hpp"
#include "parser/types.hpp"
#include "diagnostics/error.hpp"
#include "diagnostics/controller.hpp"

using namespace std;

int main()
{
    string source =
        "query X() {\n"
        "}\n"
        "action Y{}\n"
        "query Y{}\n"
        "type B: A, C, D {}\n"
        "type A {}\n"
        ;

    cout << source << endl;

    Parser::TokenVec tokens = Parser::tokenize(source);
    Parser::Scanner scanner(tokens);
    Parser::Types types(&scanner);

    cout << scanner.hasQuery("Y") << endl;
    cout << scanner.hasQuery("Z") << endl;

    if (Diagnostics::Controller::hasError())
        Diagnostics::Controller::dumpAll();
}