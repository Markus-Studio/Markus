#ifndef __MARKUS_TYPE_OBJECT__
#define __MARKUS_TYPE_OBJECT__

#include <vector>
#include <string>
#include "type/uri.hpp"

namespace Type
{
// Forward declaration.
class Atomic;

struct ObjectField
{
    std::string key;
    bool nullable;
    // Container type.
};

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

    /**
     * Fields in this object.
     * (Yes, we will move to a hash-table in the future when not using it
     *  becomes a bottleneck.)
     */
    std::vector<struct ObjectField> fields;

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
     * Returns name of this object.
     */
    std::string getName();

    /**
     * Set a new field, returns false if the key already existed and fails.
     */
    bool set(std::string key, Atomic type, bool nullable);

    /**
     * Set a new field, returns false if the key already existed and fails.
     */
    bool set(std::string key, Object type, bool nullable);

    /**
     * Check if the given key exists in this type.
     */
    bool has(std::string key);

    /**
     * Check if the given uri exists in this type.
     */
    bool has(Uri uri);

    /**
     * Return true if the key exists in this object and not
     * the bases.
     */
    bool owns(std::string key);

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