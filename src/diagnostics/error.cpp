#include <string>
#include <sstream>
#include <set>
#include "parser/tokenizer.hpp"
#include "diagnostics/error.hpp"

namespace Diagnostics
{
Error::Error()
{
    errorNo = E_NOT_AN_ERROR;
    message = "";
}

Error::Error(enum ErrorNo no, std::string msg)
{
    errorNo = no;
    message = msg;
}

std::string Error::getMessage()
{
    return message;
}

Error *Error::unexpectedCharacter(int line, int column)
{
    std::stringstream fmt;
    fmt << "Error: Found unexpected character on line "
        << line << ":" << column << ".";
    return new Error(E_UNEXPECTED_CHARACTER, fmt.str());
}

Error *Error::unterminatedQuote(int line, int column)
{
    std::stringstream fmt;
    fmt << "Error: Unterminated string literal found on line "
        << line << ":" << column << ".";
    return new Error(E_UNTERMINATED_QUOTE, fmt.str());
}

Error *Error::unexpectedToken(Parser::Token *token)
{
    std::stringstream fmt;
    fmt << "Error: Unexpected token found on line "
        << token->getLine() << ":" << token->getColumn() << ".";
    return new Error(E_UNEXPECTED_TOKEN, fmt.str());
}

Error *Error::unexpectedToken(Parser::Token *token, std::string expected)
{
    std::stringstream fmt;
    fmt << "Error: Unexpected token found on line "
        << token->getLine() << ":" << token->getColumn()
        << " expected " << expected << ".";
    return new Error(E_UNEXPECTED_TOKEN, fmt.str());
}

Error *Error::mismatchedBrace(Parser::Token *token)
{
    std::stringstream fmt;
    fmt << "Error: Mismatched brace found on line "
        << token->getLine() << ":" << token->getColumn() << ".";
    return new Error(E_MISMATCHED_BRACE, fmt.str());
}
Error *Error::earlyEOF()
{
    return new Error(E_EARLY_EOF, "Error: Early end of file.");
}

Error *Error::nameAlreadyInUse(std::string name)
{
    std::stringstream fmt;
    fmt << "Error: Name " << name << " is already in use.";
    return new Error(E_MISMATCHED_BRACE, fmt.str());
}

Error *Error::nameAlreadyInUse(Parser::Token *token)
{
    std::stringstream fmt;
    fmt << "Error: Name " << token->getWord()
        << " is already in use, on line "
        << token->getLine() << ":" << token->getColumn() << ".";
    return new Error(E_NAME_ALREADY_IN_USE, fmt.str());
}

Error *Error::circularBase(std::set<Parser::TokenVec *> vectors)
{
    std::set<Parser::TokenVec *>::iterator it = vectors.begin();

    std::stringstream fmt;
    fmt << "Error: Found circular base ";
    fmt << ((**it++)[1])->getWord();

    for (; it != vectors.end(); ++it)
    {
        fmt << "->" << (**it)[1]->getWord();
    }

    fmt << ".";

    return new Error(E_CIRCULAR_BASE, fmt.str());
}

Error *Error::baseMustBeObject(Parser::Token *token)
{
    std::stringstream fmt;
    fmt << "Error: " << token->getWord() << " is not an object-type and "
        << "is used as the base for another type on line "
        << token->getLine() << ":" << token->getColumn() << ".";
    return new Error(E_BASE_MUST_BE_OBJECT, fmt.str());
}

Error *Error::cannotResolveName(Parser::Token *token)
{
    std::stringstream fmt;
    fmt << "Error: Cannot resolve name " << token->getWord() << " on line "
        << token->getLine() << ":" << token->getColumn() << ".";
    return new Error(E_CANNOT_RESOLVE_NAME, fmt.str());
}

} // namespace Diagnostics