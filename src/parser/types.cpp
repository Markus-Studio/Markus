#include "parser/types.hpp"

#include <assert.h>

#include <map>
#include <set>
#include <string>
#include <vector>

#include "diagnostics/controller.hpp"
#include "diagnostics/error.hpp"
#include "parser/scanner.hpp"
#include "parser/tokenizer.hpp"
#include "type/atomic.hpp"
#include "type/container.hpp"
#include "type/object.hpp"

namespace Parser {
using namespace Diagnostics;
Types::Types() {}

Types::Types(Scanner* scanner) {
  builtins();

  std::vector<std::string> names = scanner->getTypeNames();
  std::vector<std::string>::iterator it = names.begin();
  std::set<std::string>* parsed = new std::set<std::string>();

  for (; it != names.end(); ++it) {
    std::set<std::string>* seen = new std::set<std::string>();
    parse(scanner, scanner->lookupType(*it), seen, parsed);
    delete seen;
  }

  delete parsed;
}

void Types::add(std::string name, Type::Container container) {
  if (has(name))
    return Controller::report(Error::nameAlreadyInUse(name));

  types.insert(std::pair<std::string, Type::Container>(name, container));
}

void Types::builtins() {
  Type::Atomic* typeInt = new Type::Atomic("int");
  Type::Atomic* typeFloat = new Type::Atomic("float");
  Type::Atomic* typeString = new Type::Atomic("string");
  Type::Atomic* typeBool = new Type::Atomic("bool");

  // The base class for users.
  Type::Object* user = new Type::Object("user");
  // username and password are not legal identifiers so that
  // users will not select them on queries.
  user->set("%username", typeString, false);
  user->set("%password", typeString, false);

  // Just like in the real world, time is a mystry and exception!
  // We're absolutely not going to store all of these data about
  // a time record on the disk, but rather it's a simple API to
  // let a user work with a time record in their query.
  Type::Object* time = new Type::Object("time");
  time->set("stamp", typeInt, false);
  time->set("weekday", new Type::Atomic("weekday"), false);
  time->set("hour", new Type::Atomic("hour"), false);
  time->set("day", new Type::Atomic("day"), false);
  time->set("week", new Type::Atomic("week"), false);
  time->set("month", new Type::Atomic("month"), false);
  time->set("year", new Type::Atomic("year"), false);
  // Date formats in string.
  time->set("date", typeString, false);
  time->set("date_year", typeString, false);
  time->set("date_year_month", typeString, false);
  time->set("date_year_month_day", typeString, false);
  time->set("date_year_month_day_hour", typeString, false);
  time->set("date_month", typeString, false);
  time->set("date_month_day", typeString, false);
  time->set("date_month_day_hour", typeString, false);
  time->set("date_day", typeString, false);
  time->set("date_day_hour", typeString, false);
  time->set("date_hour", typeString, false);

  // Geo type can be used to store locations.
  Type::Object* geo = new Type::Object("geo");
  geo->set("lat", typeFloat, false);
  geo->set("long", typeFloat, false);

  add("int", Type::Container(typeInt));
  add("float", Type::Container(typeFloat));
  add("string", Type::Container(typeString));
  add("bool", Type::Container(typeBool));
  add("user", Type::Container(user));
  add("time", Type::Container(time));
  add("geo", Type::Container(geo));
}

bool Types::has(std::string name) {
  return types.count(name) > 0;
}

// Utility function to check a seen set by type name.
bool checkSeenByName(std::set<std::string>* seen, std::string name) {
  return seen->count(name) > 0;
}

void Types::parse(Scanner* scanner,
                  TokenVec tokens,
                  std::set<std::string>* seen,
                  std::set<std::string>* parsed) {
  // Name of the token.
  std::string name = tokens[1].getWord();

  // If we've seen this before, it's a circular reference.
  if (seen->count(name))
    return Controller::report(Error::circularBase(*seen, name));

  // If this is already parsed simply return.
  if (parsed->count(name))
    return;

  seen->insert(name);
  parsed->insert(name);
  assert((tokens)[0] == "type");

  std::vector<Token>::iterator it = ++tokens.begin();
  it++;  // Eat name.
  Type::Container base;

  Type::Object* obj = new Type::Object(name);
  add(name, Type::Container(obj));

  if (*it == ":") {
    do {
      ++it;
      if (!(it)->isIdentifier())
        return Controller::report(Error::unexpectedToken(*it, "identifier"));
      base = tryResolve((it)->getWord(), scanner, seen, parsed);
      if (base.isNever())
        return Controller::report(Error::cannotResolveName(*it));
      if (!base.isObject())
        return Controller::report(Error::baseMustBeObject(*it));
      obj->addBase(base.asObject());
      ++it;
    } while (*it == ",");
  }

  if (*it++ != "{")
    return Controller::report(Error::unexpectedToken(*it, "{"));

  while (*it != "}") {
    std::string typeName, name;
    Type::Container type;
    Token nameToken;
    bool nullable = false;
    bool result = false;

    if (!(it)->isIdentifier())
      return Controller::report(Error::unexpectedToken(*it, "type name"));

    typeName = (it++)->getWord();

    if (*it == "?") {
      nullable = true;
      it++;
    }

    if (!(it)->isIdentifier())
      return Controller::report(Error::unexpectedToken(*it, "identifier"));

    nameToken = *it;
    name = (it++)->getWord();

    if ((*it++) != ";")
      return Controller::report(Error::unexpectedToken(*it, ";"));

    type = tryResolve(typeName, scanner, seen, parsed);

    if (type.isNever())
      return Controller::report(Error::cannotResolveName(*it));

    if (type.isObject())
      result = obj->set(name, type.asObject(), nullable);
    else if (type.isAtomic())
      result = obj->set(name, type.asAtomic(), nullable);

    if (!result)
      return Controller::report(Error::nameAlreadyInUse(nameToken));

    if (!nullable && checkSeenByName(seen, typeName))
      return Controller::report(Error::circularField(obj->getName(), name));
  }
}

Type::Container Types::tryResolve(std::string name,
                                  Scanner* scanner,
                                  std::set<std::string>* seen,
                                  std::set<std::string>* parsed) {
  if (has(name))
    return resolve(name);

  if (!scanner->hasType(name))
    return Type::Container();

  parse(scanner, scanner->lookupType(name), seen, parsed);
  return resolve(name);
}

Type::Container Types::resolve(std::string name) {
  std::map<std::string, Type::Container>::iterator it;
  it = types.find(name);
  if (it == types.end())
    return Type::Container();
  return it->second;
}

std::vector<std::string> Types::getTypeNames() {
  std::map<std::string, Type::Container>::iterator it;
  std::vector<std::string> keys;
  keys.reserve(types.size());

  for (it = types.begin(); it != types.end(); ++it)
    keys.push_back(it->first);

  return keys;
}

bool Types::isBuiltIn(std::string name) {
  return (name == "int" || name == "geo" || name == "user" || name == "bool" ||
          name == "time" || name == "float" || name == "string");
}

}  // namespace Parser