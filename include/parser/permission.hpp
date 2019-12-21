#ifndef __MARKUS_PARSER_PERMISSIONS__
#define __MARKUS_PARSER_PERMISSIONS__

#include "IR/program.hpp"

namespace Parser {
/**
 * Parse a permission and emit an Permission IR.
 */
IR::Permission* parsePermission(IR::Program* program, TokenVec* tokens);
}  // namespace Parser

#endif