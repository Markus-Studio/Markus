#ifndef __MARKUS_PARSER_PERMISSIONS__
#define __MARKUS_PARSER_PERMISSIONS__

#include "ast/source.hpp"

namespace Parser {
/**
 * Parse a permission and emit an Permission IR.
 */
AST::Permission* parsePermission(AST::Source* program, TokenVec tokens);
}  // namespace Parser

#endif