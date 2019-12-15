#include <string>
#include <sstream>
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
    return new Error(E_MISMATCHED_BRACE, fmt.str());
}

} // namespace Diagnostics