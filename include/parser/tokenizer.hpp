#ifndef __MARKUS_PARSER_TOKENIZER__
#define __MARKUS_PARSER_TOKENIZER__

#include <string>
#include <vector>

namespace Parser
{

enum TokenKind {
    TOKEN_KIND_IDENTIFIER,
    TOKEN_KIND_PUNCTUATION,
    TOKEN_KIND_VARIABLE_NAME,
    TOKEN_KIND_INTERNAL_VARIABLE_NAME,
    TOKEN_KIND_INT_LITERAL,
    TOKEN_KIND_FLOAT_LITERAL,
    TOKEN_KIND_BOOL_LITERAL,
    TOKEN_KIND_STRING_LITERAL
};

/**
 * A token in the source code.
 */
class Token
{
private:
    /**
     * The text in this token.
     */
    std::string word;

    /**
     * Line of this token.
     */
    int line;

    /**
     * Start column.
     */
    int column;

    /**
     * Token kind.
     */
    enum TokenKind kind;

public:
    /**
     * Constructs a new token.
     */
    Token(std::string word, int line, int column, enum TokenKind kind);

    /**
     * Returns the inner text of this token.
     */
    std::string getWord();

    /**
     * Returns line number of this token.
     */
    int getLine();

    /**
     * Returns column in which this token was started.
     */
    int getColumn();

    /**
     * Returns true if this token is a punctuation.
     */
    bool isPunctuation();

    /**
     * Returns true if this token is an identifier.
     */
    bool isIdentifier();

    /**
     * Check if this token can be used as an identifier word.
     */
    bool isIdentifierWord();

    /**
     * Returns true if this token is an internal variable name.
     */
    bool isInternalVariableName();

    /**
     * Returns true if this token is a variable name.
     */
    bool isVariableName();

    /**
     * Returns true if this token is a float literal.
     */
    bool isFloatLiteral();

    /**
     * Returns true if this token is an int literal.
     */
    bool isIntLiteral();

    /**
     * Returns true if this token is either int or float literal.
     */
    bool isNumericLiteral();

    /**
     * Returns true if this token is a string literal.
     */
    bool isStringLiteral();

    /**
     * Returns true if this token is a boolean literal.
     */
    bool isBoolLiteral();

    /**
     * Returns true if this token is a literal.
     */
    bool isLiteral();

    /**
     * Check word of this token against the given value.
     */
    bool operator == (std::string text);

    /**
     * Dump the token to the STDIO.
     */
    void dump();
};

/**
 * Tokenize the given string into a list of Tokens.
 */
std::vector<Token> tokenize(std::string text);

}

#endif