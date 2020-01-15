#include "ast/program.hpp"

#include <assert.h>

#include "parser/permission.hpp"
#include "parser/query.hpp"

namespace AST {
Program::Program(Parser::Scanner* scanner) {
  indexerEngine = new Indexer::Engine();

  // --- Types.
  parserTypes = Parser::Types(scanner);

  user = parserTypes.resolve("user")->asObject();

  std::vector<std::string> typeNames = parserTypes.getTypeNames();
  std::vector<std::string>::iterator typeName;

  for (typeName = typeNames.begin(); typeName != typeNames.end(); ++typeName) {
    Type::Container* type = parserTypes.resolve(*typeName);
    if (!type->isObject() || parserTypes.isBuiltIn(*typeName))
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
    AST::Permission* permission = Parser::parsePermission(this, tokens);
    if (permission != NULL)
      permissions.push_back(permission);
  }

  // --- Queries.
  std::vector<std::string> queryNames = scanner->getQueryNames();
  std::vector<std::string>::iterator queryName = queryNames.begin();

  for (; queryName != queryNames.end(); ++queryName) {
    Parser::TokenVec* tokens = scanner->lookupQuery(*queryName);
    AST::Query* query = Parser::parseQuery(this, tokens);
    if (query != NULL)
      queries.insert(std::pair<std::string, AST::Query*>(*queryName, query));
  }
}

bool Program::hasType(std::string name) {
  std::list<Type::Object*>::iterator it = types.begin();
  for (; it != types.end(); ++it)
    if ((*it)->getName() == name)
      return true;
  return false;
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

bool Program::hasQuery(std::string name) {
  return queries.count(name) == 1;
}

Query* Program::getQuery(std::string name) {
  std::map<std::string, Query*>::iterator it = queries.find(name);
  if (it == queries.end()) {
    assert(0);
    return NULL;
  }
  return it->second;
}

Type::Container* Program::resolveBuiltin(std::string name) {
  if (!parserTypes.isBuiltIn(name))
    return new Type::Container();
  return parserTypes.resolve(name);
}

Indexer::Engine* Program::getIndexer() {
  return indexerEngine;
}

std::vector<std::string> Program::getTypeNames() {
  std::vector<std::string> names;
  std::list<Type::Object*>::iterator it = types.begin();
  for (; it != types.end(); ++it)
    names.push_back((*it)->getName());
  return names;
}

std::vector<std::string> Program::getPermissionNames() {
  std::vector<std::string> names;
  std::list<Permission*>::iterator it = permissions.begin();
  for (; it != permissions.end(); ++it)
    names.push_back((*it)->getName());
  return names;
}

std::vector<std::string> Program::getQueryNames() {
  std::vector<std::string> names;
  std::map<std::string, Query*>::iterator it = queries.begin();
  for (; it != queries.end(); ++it)
    names.push_back(it->first);
  return names;
}

}  // namespace AST