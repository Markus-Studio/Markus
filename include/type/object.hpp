#ifndef __MARKUS_TYPE_OBJECT__
#define __MARKUS_TYPE_OBJECT__

#include <vector>
#include <string>
#include "type/uri.hpp"
#include "type/container.hpp"

namespace Type
{
// Forward declaration.
class Atomic;
class Union;

/**
 * An object field slot.
 */
struct ObjectField
{
    /**
     * The field key.
     */
    std::string key;
    /**
     * The nullable tag.
     */
    bool nullable;
    /**
     * Type container for this field's type.
     */
    Container type;
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
     * Unique id for this object, it's used for comparsion.
     */
    int uid;

    /**
     * Name of this object type.
     */
    std::string name;

    /**
     * Base types.
     */
    std::vector<Object> bases;

    /**
     * Cache of computing `getAllBases()`.
     */
    std::vector<Object> allBasesCache;

    /**
     * Whatever we're in the middle of `getAllBases()` call.
     */
    bool computingGetAllBases;

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
     * Returns the unique id for this object.
     */
    int getId();

    /**
     * Set a new field, returns false if the key already existed and fails.
     */
    bool set(std::string key, Atomic *type, bool nullable);

    /**
     * Set a new field, returns false if the key already existed and fails.
     */
    bool set(std::string key, Object *type, bool nullable);

    /**
     * Return true if the key exists in this object and not
     * the bases.
     */
    bool owns(std::string key);

    /**
     * Check if the given key exists in this type.
     */
    bool has(std::string key);

    /**
     * Check if the given uri exists in this type.
     */
    bool has(Uri uri);

    /**
     * Return all of the bases.
     */
    std::vector<Object> getBases();

    /**
     * Return all of the bases recursively.
     */
    std::vector<Object> getAllBases();

    /**
     * Query type of the field with the name.
     */
    Container query(std::string name);

    /**
     * Query type of the field with the given uri.
     */
    Container query(Uri uri);

    /**
     * Evaluates `this is obj` and returns the result.
     */
    bool is(Object obj);

    /**
     * Evaluates `this is u` and returns the result.
     */
    bool is(Union u);
};
}

#endif