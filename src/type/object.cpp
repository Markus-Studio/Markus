#include <string>
#include <vector>
#include "type/uri.hpp"
#include "type/atomic.hpp"
#include "type/object.hpp"
#include "type/container.hpp"

namespace Type
{
Object::Object(std::string name)
{
    this->name = name;
}

Object::Object(std::string name, std::vector<Object> bases)
{
    this->name = name;
    this->bases.assign(bases.begin(), bases.end());
}

std::string Object::getName()
{
    return name;
}

bool Object::set(std::string key, Atomic *type, bool nullable)
{
    if (has(key))
        return false;
    struct ObjectField field = {key, nullable, Container(type)};
    fields.push_back(field);
    return true;
}

bool Object::set(std::string key, Object *type, bool nullable)
{
    if (has(key))
        return false;
    struct ObjectField field = {key, nullable, Container(type)};
    fields.push_back(field);
    return true;
}

bool Object::owns(std::string key)
{
    std::vector<struct ObjectField>::iterator it;
    for (it = fields.begin(); it != fields.end(); ++it)
        if (it->key == key)
            return true;
    return false;
}

bool Object::has(std::string key)
{
    if (owns(key))
        return true;

    std::vector<Object>::iterator it;
    for (it = bases.begin(); it != bases.end(); ++it)
        if (it->has(key))
            return true;

    return false;
}

bool Object::has(Uri uri)
{
    if (uri.size() == 1)
        return has(uri.getFirstUnit());

    Container container = query(uri);
    return !container.isNever();
}

std::vector<Object> Object::getBases()
{
    std::vector<Object> temp;
    temp.assign(bases.begin(), bases.end());
    temp.shrink_to_fit();
    return temp;
}

Container Object::query(std::string name)
{
    Container container;

    std::vector<struct ObjectField>::iterator it;
    for (it = fields.begin(); it != fields.end(); ++it)
        if (it->key == name)
            return it->type;

    std::vector<Object>::iterator bIt;
    for (bIt = bases.begin(); bIt != bases.end(); ++bIt)
        if (!(container = bIt->query(name)).isNever())
            return container;

    return container;
}

Container Object::query(Uri uri)
{
    if (uri.isEmpty())
        return Container(this);

    if (uri.size() == 1)
        return query(uri.getFirstUnit());
    
    Container container = query(uri.getFirstUnit());
    uri = uri.popFirst();

    if (container.isNever())
        return container;
    
    if (container.isObject())
        return container.asObject()->query(uri);
    
    return Container();
}

} // namespace Type