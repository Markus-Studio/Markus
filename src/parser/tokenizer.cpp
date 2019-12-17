#include "parser/tokenizer.hpp"

#include <assert.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "diagnostics/controller.hpp"
#include "diagnostics/error.hpp"

namespace Parser {
using namespace Diagnostics;

inline bool isValidIdentifierStart(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

inline bool isValidIdentifierEnd(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9') || c == '_';
}

Token::Token(std::string word, int line, int column, enum TokenKind kind) {
  this->word = word;
  this->line = line;
  this->column = column;
  this->kind = kind;
}

std::string Token::getWord() {
  return word;
}

int Token::getLine() {
  return line;
}

int Token::getColumn() {
  return column;
}

bool Token::isPunctuation() {
  return kind == TOKEN_KIND_PUNCTUATION;
}

bool Token::isIdentifier() {
  return kind == TOKEN_KIND_IDENTIFIER;
}

bool Token::isIdentifierWord() {
  return (kind == TOKEN_KIND_IDENTIFIER || kind == TOKEN_KIND_BOOL_LITERAL);
}

bool Token::isInternalVariableName() {
  return kind == TOKEN_KIND_INTERNAL_VARIABLE_NAME;
}

bool Token::isVariableName() {
  return kind == TOKEN_KIND_VARIABLE_NAME;
}

bool Token::isFloatLiteral() {
  return kind == TOKEN_KIND_FLOAT_LITERAL;
}

bool Token::isIntLiteral() {
  return kind == TOKEN_KIND_INT_LITERAL;
}

bool Token::isNumericLiteral() {
  return (kind == TOKEN_KIND_INT_LITERAL || kind == TOKEN_KIND_FLOAT_LITERAL);
}

bool Token::isStringLiteral() {
  return kind == TOKEN_KIND_STRING_LITERAL;
}

bool Token::isBoolLiteral() {
  return kind == TOKEN_KIND_BOOL_LITERAL;
}

bool Token::isLiteral() {
  return (kind == TOKEN_KIND_INT_LITERAL || kind == TOKEN_KIND_FLOAT_LITERAL ||
          kind == TOKEN_KIND_STRING_LITERAL || kind == TOKEN_KIND_BOOL_LITERAL);
}

bool Token::operator==(std::string value) {
  return word == value;
}

bool Token::operator!=(std::string value) {
  return word != value;
}

void Token::dump() {
  std::cout << "Token[" << kind << "] {" << std::endl
            << "  " << word << std::endl
            << "  "
            << "l: " << line << " c: " << column << std::endl
            << "};" << std::endl;
}

std::vector<Token*> tokenize(std::string source) {
  std::vector<Token*> tokens;
  std::string word = "";
  int cursor = 0;
  int line = 1;
  int column;
  int currentLineBegining = 0;

  while (source[cursor]) {
    column = cursor - currentLineBegining + 1;

    if (source[cursor] == '\r') {
      if (source[cursor + 1] == '\n') {
        cursor += 2;
        line += 1;
        currentLineBegining = cursor;
        continue;
      }

      cursor += 1;
      continue;
    }

    if (source[cursor] == '\n') {
      cursor += 1;
      line += 1;
      currentLineBegining = cursor;
      continue;
    }

    if (source[cursor] == '#') {
      while (source[cursor] != '\n')
        cursor += 1;
      continue;
    }

    if ((source[cursor] == '$' || source[cursor] == '%') &&
        isValidIdentifierEnd(source[cursor + 1])) {
      bool isInternal = source[cursor] == '%';
      word += source[cursor];
      cursor += 1;

      while (isValidIdentifierEnd(source[cursor])) {
        word += source[cursor];
        cursor += 1;
      }

      Token* token = new Token(word, line, column,
                               isInternal ? TOKEN_KIND_INTERNAL_VARIABLE_NAME
                                          : TOKEN_KIND_VARIABLE_NAME);
      tokens.push_back(token);
      word = "";
      continue;
    }

    if (source[cursor] == '"') {
      bool escaped = false;
      bool finished = false;
      cursor += 1;

      while (source[cursor]) {
        if (!escaped && source[cursor] == '"') {
          cursor += 1;
          finished = true;
          break;
        }

        if (escaped) {
          switch (source[cursor]) {
            case 'n':
              word += '\n';
              break;
            case 'r':
              word += '\r';
              break;
            case 't':
              word += '\t';
              break;
            case '\\':
              word += '\\';
              break;
            case '"':
              word += '"';
              break;
            default:
              word += source[cursor];
          }
          escaped = false;
        } else {
          if (source[cursor] == '\\')
            escaped = true;
          else
            word += source[cursor];
        }

        cursor += 1;
      }

      if (!finished) {
        Controller::report(Error::unterminatedQuote(line, column));
        return tokens;
      }

      Token* token = new Token(word, line, column, TOKEN_KIND_STRING_LITERAL);
      tokens.push_back(token);
      word = "";
      continue;
    }

    if (isValidIdentifierStart(source[cursor])) {
      word += source[cursor++];

      while (isValidIdentifierEnd(source[cursor]))
        word += source[cursor++];

      if (word == "true" || word == "false") {
        Token* token = new Token(word, line, column, TOKEN_KIND_BOOL_LITERAL);
        tokens.push_back(token);
        word = "";
        continue;
      }

      Token* token = new Token(word, line, column, TOKEN_KIND_IDENTIFIER);
      tokens.push_back(token);
      word = "";
      continue;
    }

    if (ispunct(source[cursor])) {
      word = source[cursor];
      Token* token = new Token(word, line, column, TOKEN_KIND_PUNCTUATION);
      tokens.push_back(token);
      word = "";
      cursor += 1;
      continue;
    }

    if (isdigit(source[cursor])) {
      bool isFloat = false;

      while (source[cursor]) {
        if (!isFloat && source[cursor] == '.' && isdigit(source[cursor + 1])) {
          word += '.';
          cursor += 1;
          isFloat = true;
          continue;
        }

        if (isdigit(source[cursor])) {
          word += source[cursor];
          cursor += 1;
          continue;
        }

        break;
      }

      Token* token = new Token(
          word, line, column,
          isFloat ? TOKEN_KIND_FLOAT_LITERAL : TOKEN_KIND_INT_LITERAL);
      word = "";
      tokens.push_back(token);
      continue;
    }

    if (isspace(source[cursor])) {
      cursor += 1;
      continue;
    }

    Controller::report(Error::unexpectedCharacter(line, column));
    return tokens;
  }

  return tokens;
}

}  // namespace Parser
