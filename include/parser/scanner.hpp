#pragma once
#include <map>
#include <string>
#include <vector>

#include "parser/tokenizer.hpp"

namespace Parser {
/**
 * Well, first of all you should know that Markus has somewhat an unusual
 * parsing strategy which I've never seen in any other system, instead of
 * creating an AST and then running the type checker to validate that AST
 * and then doing next steps including code generation and similar stuff,
 * we try to compute the actual types while parsing.
 *
 * And yes, I'm crazy enough to jump from tokenization phase to the program
 * validation.
 *
 *
 * To do so we have this `Scanner` class which scans a list of tokens and
 * then creates several maps, those maps map a name into start and end of
 * a code block.
 */
class Scanner {
 private:
  /**
   * Every type in this document.
   */
  std::map<std::string, TokenVec> types;

  /**
   * Every permission in this document.
   */
  std::map<std::string, TokenVec> permissions;

  /**
   * Every query in this document.
   */
  std::map<std::string, TokenVec> queries;

  /**
   * Every action in this document.
   */
  std::map<std::string, TokenVec> actions;

  /**
   * Reads a section of the code and parses it, calls it self
   * recursively until it reaches end of the iterator.
   */
  void parse(std::vector<Token>::iterator iter,
             std::vector<Token>::iterator end);

 public:
  /**
   * Constructs a new scanner from a vector of tokens.
   */
  Scanner(TokenVec tokens);

  /**
   * Returns list of all the types defined in this document.
   */
  std::vector<std::string> getTypeNames();

  /**
   * Returns true if a type with the given name exists in this document.
   */
  bool hasType(std::string name);

  /**
   * Finds and returns the tokens of a type declaration with the given name.
   */
  TokenVec lookupType(std::string name);

  /**
   * Returns list of all the permissions defined in this document.
   */
  std::vector<std::string> getPermissionNames();

  /**
   * Returns true if a permission with the given name exists in this document.
   */
  bool hasPermission(std::string name);

  /**
   * Finds and returns the tokens of a type declaration with the given name.
   */
  TokenVec lookupPermission(std::string name);

  /**
   * Returns list of all the queries defined in this document.
   */
  std::vector<std::string> getQueryNames();

  /**
   * Returns true if a query with the given name exists in this document.
   */
  bool hasQuery(std::string name);

  /**
   * Finds and returns the tokens of a query declaration with the given name.
   */
  TokenVec lookupQuery(std::string name);

  /**
   * Returns list of all the actions defined in this document.
   */
  std::vector<std::string> getActionNames();

  /**
   * Returns true if an action with the given name exists in this document.
   */
  bool hasAction(std::string name);

  /**
   * Finds and returns the tokens of an action declaration with the given name.
   */
  TokenVec lookupAction(std::string name);
};
}  // namespace Parser