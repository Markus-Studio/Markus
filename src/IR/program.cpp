#include "IR/program.hpp"

#include <assert.h>

#include "parser/permission.hpp"
#include "parser/types.hpp"

namespace IR {
Program::Program(Parser::Scanner* scanner) {
  // --- Types.
  Parser::Types types(scanner);

  user = types.resolve("user")->asObject();

  std::vector<std::string> typeNames = types.getTypeNames();
  std::vector<std::string>::iterator typeName;

  for (typeName = typeNames.begin(); typeName != typeNames.end(); ++typeName) {
    Type::Container* type = types.resolve(*typeName);
    if (!type->isObject() || types.isBuiltIn(*typeName))
      continue;
    Type::Object* objType = type->asObject();
    this->types.push_back(objType);
    objects.add(objType);
    if (objType->is(user))
      users.add(objType);
  }

  typesArray = new Type::Array(new Type::Container(&objects));

  // --- Permissions.
  std::vector<std::string> permissionNames = scanner->getPermissionNames();
  std::vector<std::string>::iterator permissionName = permissionNames.begin();

  for (; permissionName != permissionNames.end(); ++permissionName) {
    Parser::TokenVec* tokens = scanner->lookupPermission(*permissionName);
    IR::Permission* permission = Parser::parsePermission(this, tokens);
    permissions.push_back(permission);
  }

  // Queries.
}

Type::Object* Program::getType(std::string name) {
  std::list<Type::Object*>::iterator it = types.begin();
  for (; it != types.end(); ++it)
    if ((*it)->getName() == name)
      return *it;
  assert(0);
  return NULL;
}

Type::Array* Program::arrayOfTypes() {
  return typesArray;
}

Type::Union* Program::unionOfUsers() {
  return &users;
}

bool Program::hasPermission(std::string name) {
  std::list<Permission*>::iterator it = permissions.begin();
  for (; it != permissions.end(); ++it)
    if ((*it)->getName() == name)
      return true;
  return false;
}

Permission* Program::getPermission(std::string name) {
  std::list<Permission*>::iterator it = permissions.begin();
  for (; it != permissions.end(); ++it)
    if ((*it)->getName() == name)
      return *it;
  assert(0);
  return NULL;
}

}  // namespace IR