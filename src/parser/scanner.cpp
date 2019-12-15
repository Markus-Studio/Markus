#include <iostream>
#include <vector>
#include <stack>
#include "parser/tokenizer.hpp"
#include "parser/scanner.hpp"

#include "diagnostics/controller.hpp"
#include "diagnostics/error.hpp"

namespace Parser
{
using namespace Diagnostics;

Scanner::Scanner(TokenVec tokens)
{
    parse(tokens.begin(), tokens.end());
}

void Scanner::parse(
    std::vector<Token *>::iterator iter,
    std::vector<Token *>::iterator end)
{
    if (iter == end)
        return;

    if (!(*iter)->isIdentifier())
    {
        Controller::report(Error::unexpectedToken(*iter, " an identifier"));
        return;
    }

    std::string word, tmp;
    Token *name;
    std::vector<Token *>::iterator begining;
    begining = iter++;

    if (iter == end)
    {
        Controller::report(Error::earlyEOF());
        return;
    }

    if (!(*iter)->isIdentifier())
    {
        Controller::report(Error::unexpectedToken(*iter, " an identifier"));
        return;
    }

    name = *iter;

    bool seenBracket = false;
    std::stack<std::string> braces;

    while ((++iter) != end)
    {
        if (!(*iter)->isPunctuation())
            continue;

        word = (*iter)->getWord();

        if (word == "{")
        {
            seenBracket = true;
            braces.push("{");
            continue;
        }

        if (word == "(")
        {
            braces.push("(");
            continue;
        }

        if (word != ")" && word != "}")
            continue;

        if (braces.empty())
        {
            Controller::report(Error::mismatchedBrace(*iter));
            return;
        }

        tmp = braces.top();

        if (word == ")" && tmp != "(")
        {
            Controller::report(Error::mismatchedBrace(*iter));
            return;
        }

        if (word == "}" && tmp != "{")
        {
            Controller::report(Error::mismatchedBrace(*iter));
            return;
        }

        braces.pop();

        if (seenBracket && braces.empty())
            break;
    }

    if (!braces.empty())
    {
        if (iter == end)
        {

            Controller::report(Error::earlyEOF());
            iter--;
        }
        Controller::report(Error::mismatchedBrace(*iter));
        return;
    }

    if (!seenBracket)
    {
        Controller::report(Error::earlyEOF());
        return;
    }

    TokenVec vec;
    vec.assign(begining, iter);
    vec.shrink_to_fit();
    word = (*begining)->getWord();
    tmp = name->getWord();

    if (word == "query")
    {
        if (queries.count(tmp) > 0)
            return Controller::report(Error::nameAlreadyInUse(name));
        queries.insert(std::pair<std::string, TokenVec>(tmp, vec));
    }
    else if (word == "action")
    {
        if (actions.count(tmp) > 0)
            return Controller::report(Error::nameAlreadyInUse(name));
        actions.insert(std::pair<std::string, TokenVec>(tmp, vec));
    }
    else if (word == "type")
    {
        if (types.count(tmp) > 0)
            return Controller::report(Error::nameAlreadyInUse(name));
        types.insert(std::pair<std::string, TokenVec>(tmp, vec));
    }
    else if (word == "permission")
    {
        if (permissions.count(tmp) > 0)
            return Controller::report(Error::nameAlreadyInUse(name));
        permissions.insert(std::pair<std::string, TokenVec>(tmp, vec));
    }
    else
        return Controller::report(Error::unexpectedToken(*begining, " either action, query, permission or type"));

    parse(++iter, end);
}

} // namespace Parser