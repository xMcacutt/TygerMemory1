#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include "vector3f.h"

class TYGERMEM GameObjectDescriptor;

class TYGERMEM GameObject {

private:
    uintptr_t address;
    int index;
    GameObjectDescriptor* objectData;
    GameObject(uintptr_t addr, int index, GameObjectDescriptor* objectData);
public:
    friend class GameObjectDescriptor;

    

    /// <summary>
    /// Gets the next instance with the same type as this instance.
    /// </summary>
    /// <returns>
    /// The next instance of this instance's type.
    /// <para>If this instance is the last, returns this instance.</para>
    /// </returns>
    GameObject getNext();

    /// <summary>
    /// Gets the previous instance with the same type as this instance.
    /// </summary>
    /// <returns>
    /// The previous instance of this instance's type.
    /// <para>If this instance is the first, returns this instance.</para>
    /// </returns>
    GameObject getPrevious();

    /// <summary>
    /// Gets the GameObject data for the type of this instance.
    /// </summary>
    /// <returns>
    /// The GameObject data which owns the instance.
    /// </returns>
    GameObjectDescriptor* getOwner() const { return objectData; }

    /// <summary>
    /// Gets the index of this instance.
    /// </summary>
    /// <returns>
    /// The index of this instance.
    /// </returns>
    int getIndex() const { return index; }

    /// <summary>
    /// Attempts to set the position of this instance.
    /// </summary>
    /// <param name="position:">
    /// The position to move the instance to.
    /// </param>
    virtual void setPosition(Vector3f position);

    /// <summary>
    /// Attempts to get the position of this instance.
    /// </summary>
    /// <returns>
    /// A 3-float vector class containing the position of the instance.
    /// </returns>
    virtual Vector3f getPosition();

    /// <summary>
    /// Attempts to get the address of this instance.
    /// </summary>
    /// <returns>
    /// A uintptr_t to the address of the instance.
    /// </returns>
    virtual uintptr_t getAddr();
};

