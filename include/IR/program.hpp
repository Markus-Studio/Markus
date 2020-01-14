#ifndef __MARKUS_IR_PROGRAM__
#define __MARKUS_IR_PROGRAM__

#include <list>
#include <map>

#include "IR/permission.hpp"
#include "indexer/engine.hpp"
#include "parser/scanner.hpp"
#include "parser/types.hpp"
#include "type/array.hpp"
#include "type/object.hpp"
#include "type/union.hpp"

namespace IR {
/**
 * The intermediate representation for a Markus program, it includes all of the
 * user-defined types, permissions, queries and actions, it can be passed to the
 * optimization backends and then to a code generation backend to generate the
 * binary.
 */
class Program {
 private:
  /**
   * The types in this program.
   */
  std::list<Type::Object*> types;

  /**
   * The permissions in this program.
   */
  std::list<Permission*> permissions;

  /**
   * List of all the queries defined in this program.
   */
  std::map<std::string, Query*> queries;

  /**
   * The built-in user type.
   */
  Type::Object* user;

  /**
   * Types that are extended from the User type.
   */
  Type::Union users;

  /**
   * All of the user defined types in the system.
   */
  Type::Union objects;

  /**
   * Array of all of the types.
   */
  Type::Array* typesArray;

  /**
   * Result of parsing the types, we use it to resolve builtin
   * types.
   */
  Parser::Types parserTypes;

  /**
   * The indexer engine for this program.
   */
  Indexer::Engine* indexerEngine;

 public:
  /**
   * Constructs a new program.
   */
  Program(Parser::Scanner* scanner);

  /**
   * Returns whatever there is a type with the given name in this program.
   */
  bool hasType(std::string name);

  /**
   * Returns the type with the given name.
   */
  Type::Object* getType(std::string name);

  /**
   * Return an array of an union containing all of the types.
   */
  Type::Array* arrayOfTypes();

  /**
   * Returns an union containing all of types that are User.
   */
  Type::Union* unionOfUsers();

  /**
   * Return whatever this program contains a permission with the given name.
   */
  bool hasPermission(std::string name);

  /**
   * Return the Permission IR of the permission with the given name.
   */
  Permission* getPermission(std::string name);

  /**
   * Returns true if there is a query in this program with the given name.
   */
  bool hasQuery(std::string name);

  /**
   * Returns the query with the given name that is defined in this program.
   */
  Query* getQuery(std::string name);

  /**
   * Resolve a built-in type.
   */
  Type::Container* resolveBuiltin(std::string name);

  /**
   * Returns the indexer engine.
   */
  Indexer::Engine* getIndexer();
};
}  // namespace IR

#endif