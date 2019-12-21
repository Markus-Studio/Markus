#ifndef __MARKUS_IR_PROGRAM__
#define __MARKUS_IR_PROGRAM__

#include <list>

#include "IR/permission.hpp"
#include "parser/scanner.hpp"
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

 public:
  /**
   * Constructs a new program.
   */
  Program(Parser::Scanner* scanner);

  /**
   * Returns a type with the given name.
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
};
}  // namespace IR

#endif