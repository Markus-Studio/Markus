#ifndef __MARKUS_TYPE_OBJECT__
#define __MARKUS_TYPE_OBJECT__

#include <vector>
#include <string>
#include "type/uri.hpp"

namespace Type
{

/**
 * An object type is any type with a set of typed fields,
 * each object type can have zero or multiple base types which
 * are also objects.
 */
class Object
{
private:
    /**
     * Name of this object type.
     */
    std::string name;

    /**
     * Base types.
     */
    std::vector<Object> bases;

public:
    /**
     * Constructs a new object with the given name and no base object.
     */
    Object(std::string name);

    /**
     * Constructs a new object type with the given data.
     */
    Object(std::string name, std::vector<Object> bases);

    /**
     * Set a new field, returns false if the key already existed and fails.
     */
    bool set(std::string key, AtomicType type, bool nullable);

    /**
     * Set a new field, returns false if the key already existed and fails.
     */
    bool set(std::string key, ObjectType type, bool nullable);

    /**
     * Check if the given key exists in this type.
     */
    has(std::string key);

    /**
     * Check if the given uri exists in this type.
     */
    has(Uri uri);

    /**
     * Return true if the key exists in this object and not
     * the bases.
     */
    owns(std::string key);

    /**
     * Return all of the fields on this object.
     */
    std::vector<Uri> getAllUris();

    /**
     * Return all of the bases.
     */
    std::vector<Object> getBases();

    // Container query(Uri uri);
};
}

#endif