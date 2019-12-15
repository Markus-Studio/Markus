#include <iostream> // cout
#include <vector>
#include <string>
#include <map>
#include <set>
#include "parser/tokenizer.hpp"
#include "parser/scanner.hpp"
#include "parser/types.hpp"
#include "type/atomic.hpp"
#include "type/object.hpp"
#include "type/container.hpp"
#include "diagnostics/controller.hpp"
#include "diagnostics/error.hpp"

namespace Parser
{
using namespace Diagnostics;

Types::Types(Scanner *scanner)
{
    builtins();

    std::vector<std::string> names = scanner->getTypeNames();
    std::vector<std::string>::iterator it = names.begin();
    std::set<TokenVec *> parsed;

    for (; it != names.end(); ++it) {
        std::set<TokenVec *> seen;
        parse(scanner, scanner->lookupType(*it), &seen, &parsed);
    }

    for (it = names.begin(); it != names.end(); ++it) {
        std::set<TokenVec *> seen;
        parse(scanner, scanner->lookupType(*it), &seen, &parsed);
    }
}

void Types::add(std::string name, Type::Container *container)
{
    if (has(name))
        return Controller::report(Error::nameAlreadyInUse(name));

    types.insert(std::pair<std::string, Type::Container *>(name, container));
}

void Types::builtins()
{
    Type::Atomic *typeInt = new Type::Atomic("int");
    Type::Atomic *typeFloat = new Type::Atomic("float");
    Type::Atomic *typeString = new Type::Atomic("string");
    Type::Atomic *typeBool = new Type::Atomic("bool");

    // The base class for users.
    Type::Object *user = new Type::Object("user");
    // username and password are not legal identifiers so that
    // users will not select them on queries.
    user->set("%username", typeString, false);
    user->set("%password", typeString, false);

    // Just like in the real world, time is a mystry and exception!
    // We're absolutely not going to store all of these data about
    // a time record on the disk, but rather it's a simple API to
    // let a user work with a time record in their query.
    Type::Object *time = new Type::Object("time");
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
    Type::Object *geo = new Type::Object("geo");
    geo->set("lat", typeFloat, false);
    geo->set("lng", typeFloat, false);

    add("int", new Type::Container(typeInt));
    add("float", new Type::Container(typeFloat));
    add("string", new Type::Container(typeString));
    add("bool", new Type::Container(typeBool));
    add("user", new Type::Container(user));
    add("time", new Type::Container(time));
    add("geo", new Type::Container(geo));
}

bool Types::has(std::string name)
{
    return types.count(name) > 0;
}

void Types::parse(
    Scanner *scanner,
    TokenVec *tokens,
    std::set<TokenVec *> *seen,
    std::set<TokenVec *> *parsed)
{
    // If we've seen this before, it's a circular reference.
    if (seen->count(tokens))
    {
        seen->insert(tokens);
        return Controller::report(Error::circularBase(*seen));
    }

    // If this is already parsed simply return.
    if (parsed->count(tokens)) {
        std::cout << "ALREADY PARSED\n";
        return;
    }

    seen->insert(tokens);
    parsed->insert(tokens);
    assert(*(*tokens)[0] == "type");

    std::vector<Token *>::iterator it = ++tokens->begin();
    std::vector<Type::Object *> bases;
    Type::Container *base;
    std::string name = (*it++)->getWord();

    std::cout << "TYPE " << name << std::endl;
    std::cout << (*it)->getWord() << " o" << std::endl;

    if (**it == ":")
    {
        do
        {
            ++it;
            if (!(*it)->isIdentifier())
                return Controller::report(Error::unexpectedToken(*it));
            base = tryResolve((*it)->getWord(), scanner, seen, parsed);
            if (base->isNever())
                return Controller::report(Error::cannotResolveName(*it));
            if (!base->isObject())
                return Controller::report(Error::baseMustBeObject(*it));
            bases.push_back(base->asObject());
            ++it;
        } while (**it == ",");
    }

}

Type::Container *Types::tryResolve(
    std::string name,
    Scanner *scanner,
    std::set<TokenVec *> *seen,
    std::set<TokenVec *> *parsed)
{
    return new Type::Container();
}

} // namespace Parser