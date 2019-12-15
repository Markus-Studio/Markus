#ifndef __MARKUS_DIAGNOSTICS_ERROR__
#define __MARKUS_DIAGNOSTICS_ERROR__

#include <string>
#include "parser/tokenizer.hpp"

namespace Diagnostics
{

/**
 * All of the error numbers.
 */
enum ErrorNo
{
    E_NOT_AN_ERROR,
    E_UNEXPECTED_CHARACTER,
    E_UNTERMINATED_QUOTE,
    E_UNEXPECTED_TOKEN,
    E_MISMATCHED_BRACE,
    E_EARLY_EOF,
    E_NAME_ALREADY_IN_USE
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

    /**
     * Constructs a new unterminated quote/string-literal error.
     */
    static Error *unterminatedQuote(int line, int column);

    /**
     * Construct a new unexpected token error.
     */
    static Error *unexpectedToken(Parser::Token *token);

    /**
     * Construct a new unexpected token error that also says what was expected.
     */
    static Error *unexpectedToken(Parser::Token *token, std::string expected);

    /**
     * Constructs a new mismatched brace error.
     */
    static Error *mismatchedBrace(Parser::Token *token);

    /**
     * Constructs a new early end of file error.
     */
    static Error *earlyEOF();

    /**
     * Constructs a new name already in use error.
     */
    static Error *nameAlreadyInUse(std::string name);

    /**
     * Constructs a new name already in use error from a token
     * and stating position of the error.
     */
    static Error *nameAlreadyInUse(Parser::Token *token);
};
} // namespace Diagnostics

#endif