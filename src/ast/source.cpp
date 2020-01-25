#include "ast/source.hpp"

#include <assert.h>

#include "parser/permission.hpp"
#include "parser/query.hpp"

namespace AST {
Source::Source(Parser::Scanner* scanner) {
  indexerEngine = new Indexer::Engine();

  // --- Types.
  parserTypes = Parser::Types(scanner);

  user = parserTypes.resolve("user").asObject();

  std::vector<std::string> typeNames = parserTypes.getTypeNames();
  std::vector<std::string>::iterator typeName;

  for (typeName = typeNames.begin(); typeName != typeNames.end(); ++typeName) {
    Type::Container type = parserTypes.resolve(*typeName);
    if (!type.isObject() || parserTypes.isBuiltIn(*typeName))
      continue;
    Type::Object* objType = type.asObject();
    this->types.push_back(objType);
    objects.add(objType);
    if (objType->is(user))
      users.add(objType);
  }

  typesArray = new Type::Array(Type::Container(&objects));

  // --- Permissions.
  std::vector<std::string> permissionNames = scanner->getPermissionNames();
  std::vector<std::string>::iterator permissionName = permissionNames.begin();

  for (; permissionName != permissionNames.end(); ++permissionName) {
    Parser::TokenVec tokens = scanner->lookupPermission(*permissionName);
    AST::Permission* permission = Parser::parsePermission(this, tokens);
    if (permission != nullptr)
      permissions.push_back(permission);
  }

  // --- Queries.
  std::vector<std::string> queryNames = scanner->getQueryNames();
  std::vector<std::string>::iterator queryName = queryNames.begin();

  for (; queryName != queryNames.end(); ++queryName) {
    Parser::TokenVec tokens = scanner->lookupQuery(*queryName);
    AST::Query* query = Parser::parseQuery(this, tokens);
    if (query != nullptr)
      queries.insert(std::pair<std::string, AST::Query*>(*queryName, query));
  }
}

bool Source::hasType(std::string name) {
  std::list<Type::Object*>::iterator it = types.begin();
  for (; it != types.end(); ++it)
    if ((*it)->getName() == name)
      return true;
  return false;
}

Type::Object* Source::getType(std::string name) {
  std::list<Type::Object*>::iterator it = types.begin();
  for (; it != types.end(); ++it)
    if ((*it)->getName() == name)
      return *it;
  assert(0);
  return nullptr;
}

Type::Array* Source::arrayOfTypes() {
  return typesArray;
}

Type::Union* Source::unionOfUsers() {
  return &users;
}

bool Source::hasPermission(std::string name) {
  std::list<Permission*>::iterator it = permissions.begin();
  for (; it != permissions.end(); ++it)
    if ((*it)->getName() == name)
      return true;
  return false;
}

Permission* Source::getPermission(std::string name) {
  std::list<Permission*>::iterator it = permissions.begin();
  for (; it != permissions.end(); ++it)
    if ((*it)->getName() == name)
      return *it;
  assert(0);
  return nullptr;
}

bool Source::hasQuery(std::string name) {
  return queries.count(name) == 1;
}

Query* Source::getQuery(std::string name) {
  std::map<std::string, Query*>::iterator it = queries.find(name);
  if (it == queries.end()) {
    assert(0);
    return nullptr;
  }
  return it->second;
}

Type::Container Source::resolveBuiltin(std::string name) {
  if (!parserTypes.isBuiltIn(name))
    return Type::Container();
  return parserTypes.resolve(name);
}

Indexer::Engine* Source::getIndexer() {
  return indexerEngine;
}

std::vector<std::string> Source::getTypeNames() {
  std::vector<std::string> names;
  std::list<Type::Object*>::iterator it = types.begin();
  for (; it != types.end(); ++it)
    names.push_back((*it)->getName());
  return names;
}

std::vector<std::string> Source::getPermissionNames() {
  std::vector<std::string> names;
  std::list<Permission*>::iterator it = permissions.begin();
  for (; it != permissions.end(); ++it)
    names.push_back((*it)->getName());
  return names;
}

std::vector<std::string> Source::getQueryNames() {
  std::vector<std::string> names;
  std::map<std::string, Query*>::iterator it = queries.begin();
  for (; it != queries.end(); ++it)
    names.push_back(it->first);
  return names;
}

bool Source::typeExists(std::string name) {
  return parserTypes.has(name);
}

Type::Container Source::queryType(std::string name) {
  return parserTypes.resolve(name);
}
}  // namespace AST