#ifndef __MARKUS_PARSER_QUERY__
#define __MARKUS_PARSER_QUERY__

#include "IR/query.hpp"
#include "parser/tokenizer.hpp"

namespace Parser {
/**
 * Parse a permission and emit an Permission IR.
 */
IR::Permission* parseQuery(IR::Query* query, TokenVec* tokens);
}  // namespace Parser

#endif