#include <iostream>
#include <vector>
#include <string>

#include "parser/tokenizer.hpp"

using namespace std;

int main()
{
    string source = "$x $y %yo $1 true false h1 \"Hello\\\"d\" x + = & 34 56.4\n4.6";

    vector<Parser::Token> tokens = Parser::tokenize(source);

    for (Parser::Token token : tokens)
        token.dump();
}