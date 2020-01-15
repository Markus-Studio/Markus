#include "parser/range.hpp"

namespace Parser {
Range::Range() {
  lineEnd = 0;
  lineStart = 0;
  columnEnd = 0;
  columnStart = 0;
}

Range Range::fromToken(Token* token) {
  Range range;
  range.lineEnd = range.lineStart = token->getLine();
  range.columnStart = token->getColumn();
  range.columnEnd = range.columnStart + token->getWord().length();
  return range;
}

int Range::getLineStart() {
  return lineStart;
}

int Range::getLineEnd() {
  return lineEnd;
}

int Range::getColumnStart() {
  return columnStart;
}

int Range::getColumnEnd() {
  return columnEnd;
}

inline int min(int a, int b) {
  return a < b ? a : b;
}

inline int max(int a, int b) {
  return a > b ? a : b;
}

Range Range::operator+(Range range) {
  Range result;
  result.lineStart = min(range.lineStart, this->lineStart);
  result.columnStart = min(range.columnStart, this->columnStart);
  result.lineEnd = max(range.lineEnd, this->lineEnd);
  result.columnEnd = max(range.columnEnd, this->columnEnd);
  return result;
}
}  // namespace Parser