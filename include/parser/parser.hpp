#pragma once
#include <string>

#include "ast/source.hpp"
#include "parser/scanner.hpp"
#include "parser/tokenizer.hpp"
#include "parser/types.hpp"

namespace Parser {
/**
 * Parse the given Markus code and turn into a Program.
 */
AST::Source* createProgram(std::string code);
}  // namespace Parser