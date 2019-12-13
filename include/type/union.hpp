#ifndef __MARKUS_TYPE_UNION__
#define __MARKUS_TYPE_UNION__

#include <list>

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
    std::list<Atomic> atomicMembers;

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
    void add(Atomic type);

    /**
     * Check if type is a member of this union.
     */
    bool has(Atomic type);

    /**
     * Copies members of another union to this one.
     */
    void add(Union type);
};
} // namespace Type

#endif