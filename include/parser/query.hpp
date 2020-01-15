#ifndef __MARKUS_PARSER_QUERY__
#define __MARKUS_PARSER_QUERY__

#include "ast/query.hpp"
#include "parser/tokenizer.hpp"
#include "value/container.hpp"

namespace Parser {
Value::Variable* parseVariable(AST::Query* query,
                               std::vector<Token*>::iterator& token,
                               int variableId);

Value::Container* parseValue(AST::Query* query,
                             std::vector<Token*>::iterator& token);
/**
 * Parse a permission and emit an Permission IR.
 */
bool parseQueryBody(AST::Query* query, std::vector<Token*>::iterator& tokens);

/**
 * Parse a query declaration and return the Query IR.
 */
AST::Query* parseQuery(AST::Program* program, TokenVec* tokens);
}  // namespace Parser

#endif