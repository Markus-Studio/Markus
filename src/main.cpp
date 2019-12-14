#include <iostream>
#include <vector>
#include <string>

#include "parser/tokenizer.hpp"
#include "type/union.hpp"
#include "type/atomic.hpp"
#include "type/container.hpp"

using namespace std;

void x(Type::Union &u, Type::Atomic a)
{
    u.add(&a);
    cout << u.has(&a) << endl;
}

int main()
{
    string source = "$x $y %yo $1 true false h1 \"Hello\\\"d\" x + = & 34 56.4\n4.6";

    vector<Parser::Token *> tokens = Parser::tokenize(source);

    for (Parser::Token *token : tokens)
        token->dump();

    Type::Atomic intT("int");
    Type::Union union1;

    Type::Container intContainer(&intT);
    Type::Atomic p = *intContainer.asAtomic();

    cout << p.is(&intT) << endl;

    x(union1, intT);
    cout << union1.has(&intT) << endl;
}