#ifndef __MARKUS_PARSER_TYPES__
#define __MARKUS_PARSER_TYPES__

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "parser/scanner.hpp"
#include "parser/tokenizer.hpp"
#include "type/container.hpp"

namespace Parser {
/**
 * Type repository for a document.
 */
class Types {
 private:
  /**
   * Map each name to the corseponding type.
   */
  std::map<std::string, Type::Container*> types;

  /**
   * Parse a token vector that is supposed to be a type declaration
   * and adds it to the space.
   */
  void parse(Scanner* scanner,
             TokenVec* tokens,
             std::set<TokenVec*>* seen,
             std::set<TokenVec*>* parsed);

  /**
   * Try to resolve a name in the middle of parsing another token.
   */
  Type::Container* tryResolve(std::string name,
                              Scanner* scanner,
                              std::set<TokenVec*>* seen,
                              std::set<TokenVec*>* parsed);

  /**
   * Setup built in types, called from constructor.
   */
  void builtins();

  /**
   * Adds the type to this space.
   */
  void add(std::string name, Type::Container* container);

 public:
  /**
   * Default constructor.
   */
  Types();

  /**
   * Construct a new type space with builtin types and thoese in the
   * scanner.
   */
  Types(Scanner* scanner);

  /**
   * Returns whatever a type with the given name exists in this space.
   */
  bool has(std::string name);

  /**
   * Resolves a type using its name and return the result, if the given type
   * does not exists in this space it returns a `never` container.
   */
  Type::Container* resolve(std::string name);

  /**
   * Return a vector of the name of every type in this document.
   */
  std::vector<std::string> getTypeNames();

  /**
   * Return whatever this type is built-in or not.
   */
  bool isBuiltIn(std::string name);
};
}  // namespace Parser

#endif