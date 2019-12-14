#ifndef __MARKUS_TYPE_CONTAINER__
#define __MARKUS_TYPE_CONTAINER__

namespace Type
{
// Forward declaration.
class Object;
class Atomic;
class Union;

enum TypeKind {
    TYPE_KIND_NEVER,
    TYPE_KIND_ATOMIC,
    TYPE_KIND_UNION,
    TYPE_KIND_OBJECT
};

/**
 * A container is wrapper class around any other type.
 */
class Container
{
private:
    /**
     * Kind of this type.
     */
    enum TypeKind kind;

    /**
     * The type in this container.
     */
    void *type;

public:
    /**
     * Returns the kind of type this container is containing.
     */
    enum TypeKind getKind();

    /**
     * Default constructor that contains a `never` type.
     */
    Container();

    /**
     * Returns true if the contained type is a never type.
     */
    bool isNever();

    /**
     * Construct a new container from an atomic type.
     */
    Container(Atomic *type);

    /**
     * Returns the contained type as an atomic.
     */
    Atomic *asAtomic();

    /**
     * Check if the container is containing an atomic type.
     */
    bool isAtomic();

    /**
     * Constructs a new container from an union type.
     */
    Container(Union *type);

    /**
     * Returns the contained type as an union.
     */
    Union *asUnion();

    /**
     * Check if the container is containing an union type.
     */
    bool isUnion();

    /**
     * Constructs a new container from an object type.
     */
    Container(Object *type);

    /**
     * Returns the contained type as an array.
     */
    Object *asObject();

    /**
     * Check if the container is containing an object type.
     */
    bool isObject();
};

}

#endif