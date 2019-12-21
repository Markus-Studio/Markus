#ifndef __MARKUS_PARSER_PARSER__
#define __MARKUS_PARSER_PARSER__

#include <string>
#include "IR/program.hpp"

namespace Parser {
/**
 * Parse the given Markus code and turn into a Program.
 */
IR::Program* createProgram(std::string code);
}  // namespace Parser

#endif