#include "IR/program.hpp"
#include <assets.hpp>

namespace IR {
Program::Program(Parser::Types* types) {
  user = types->resolve("user")->asObject();

  std::vector<std::string> typeNames = types->getTypeNames();
  std::vector<std::string>::iterator typeName;

  for (typeName = typeNames.begin(); typeName != typeNames.end(); ++typeName) {
    Type::Container* type = types->resolve(*typeName);
    if (!type->isObject() || !types->isBuiltIn(*typeName))
      continue;
    Type::Object* objType = type->asObject();
    this->types.push_back(objType);
    objects.add(objType);
    if (objType->is(user))
      users.add(objType);
  }

  typesArray = new Type::Array(new Type::Container(&objects));
}

Type::Object* Program::getType(std::string name) {
  std::list<Type::Object*>::iterator it = types.begin();
  for (; it != types.end(); ++it)
    if ((*it)->getName() == name)
      return *it;
  assert(0);
}

Type::Array* Program::arrayOfTypes() {
  return typesArray;
}

Type::Union* Program::unionOfUsers() {
  return &users;
}

}  // namespace IR