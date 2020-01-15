#ifndef __MARKUS_PARSER_PARSER__
#define __MARKUS_PARSER_PARSER__

#include <string>

#include "ast/program.hpp"
#include "parser/scanner.hpp"
#include "parser/tokenizer.hpp"
#include "parser/types.hpp"

namespace Parser {
/**
 * Parse the given Markus code and turn into a Program.
 */
AST::Program* createProgram(std::string code);
}  // namespace Parser

#endif