#ifndef __MARKUS_DIAGNOSTICS_ERROR__
#define __MARKUS_DIAGNOSTICS_ERROR__

#include <string>

namespace Diagnostics
{

/**
 * All of the error numbers.
 */
enum ErrorNo
{
    E_NOT_AN_ERROR,
    E_UNEXPECTED_CHARACTER
};

/**
 * This class contains all of errors that can occur during
 * the execution period.
 */
class Error
{
private:
    /**
     * The unique error number indicating kind of this
     * error.
     */
    enum ErrorNo errorNo;

    /**
     * The error message.
     */
    std::string message;

    /**
     * The constructor which constructs an error, it should
     * not be used directly and one of the static factory
     * functions must be used instead.
     */
    Error(enum ErrorNo no, std::string msg);

public:
    /**
     * Default constructor, sets the error no to E_NOT_AN_ERROR.
     */
    Error();

    /**
     * Returns the error message.
     */
    std::string getMessage();

    /**
     * Constructs a new unexpected character error.
     */
    static Error *unexpectedCharacter(int line, int column);
};
} // namespace Diagnostics

#endif