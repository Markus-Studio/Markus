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

} // namespace Diagnostics