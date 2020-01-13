#ifndef __MARKUS_PARSER_QUERY__
#define __MARKUS_PARSER_QUERY__

#include "IR/query.hpp"
#include "parser/tokenizer.hpp"
#include "value/container.hpp"

namespace Parser {
Value::Variable* parseVariable(IR::Query* query,
                               std::vector<Token*>::iterator& token,
                               int variableId);

Value::Container* parseValue(IR::Query* query,
                             std::vector<Token*>::iterator& token);
/**
 * Parse a permission and emit an Permission IR.
 */
bool parseQueryBody(IR::Query* query, std::vector<Token*>::iterator& tokens);

/**
 * Parse a query declaration and return the Query IR.
 */
IR::Query* parseQuery(IR::Program* program, TokenVec* tokens);
}  // namespace Parser

#endif