#ifndef __MARKUS_TYPE_UNION__
#define __MARKUS_TYPE_UNION__

#include <list>
#include "type/object.hpp"

namespace Type
{
// Forward declaration.
class Atomic;

/**
 * An union type is a markus type that is the union of different
 * types such as a set of atomics and objects.
 */
class Union
{
private:
    /**
     * Set of all atomic members that are in this union.
     */
    std::list<Atomic *> atomicMembers;

    /**
     * Set of all object members that are in this union.
     */
    std::list<Object *> objectMembers;

public:
    /**
     * Constructs a new empty union.
     */
    Union();

    /**
     * Clone the current union type and returns the new one.
     */
    Union clone();

    /**
     * Adds a new atomic type to this union.
     */
    void add(Atomic *type);

    /**
     * Check if type is a member of this union.
     */
    bool has(Atomic *type);

    /**
     * Copies members of another union to this one.
     */
    void add(Union *type);

    /**
     * Adds a new object type to this union.
     */
    void add(Object *object);

    /**
     * Check if the given object is a member of this union.
     */
    bool has(Object *object);

    /**
     * Return whatever this union is empty or not.
     */
    bool isEmpty();

    /**
     * Evaluates the result of `this is type`, in another word it
     * checks if this type is subset of the other union.
     */
    bool is(Union &type);

    friend class Object;
};
} // namespace Type

#endif