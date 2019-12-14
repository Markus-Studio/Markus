#ifndef __MARKUS_PARSER_SCANNER__
#define __MARKUS_PARSER_SCANNER__

#include <vector>
#include "parser/tokenizer.hpp"

namespace Parser
{
class Scanner
{
public:
    Scanner(std::vector<Token> *tokens);
};
} // namespace Parser

#endif