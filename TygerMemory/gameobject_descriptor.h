#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include <iostream>
#include "vector3f.h"
#include "gameobject.h"
#include <string>

class TYGERMEM GameObjectDescriptor {
private:
    GameObjectDescriptor(uintptr_t addr);
    static inline uintptr_t basePtrOffset = 0x288738;
public:
    uintptr_t address;
    friend class GameObject;

    /// <summary>
    ///     <para>Gets the GameObjectDescriptor for the given type.</para>
    /// </summary>
    /// <param name="type:">
    ///     Name of the descriptor of the game object to retrieve data for.
    /// </param>
    static GameObjectDescriptor getObjectDesc(const char* name);

    /// <summary>
    ///     <para>Gets the next linked GameObjectDescriptor.</para>
    /// </summary>
    /// <returns></returns>
    GameObjectDescriptor getNextDesc();

    const char* getDescName();

    /// <summary>
    ///     Gets the number of objects of this type currently loaded.
    /// </summary>
    /// <returns>
    ///     The number of objects loaded.
    /// </returns>
    int getCurrentCount();

    /// <summary>
    ///     Gets the first object of this type.
    /// </summary>
    /// <returns>
    ///     <para>The first object of this type.</para>
    ///     <para>Used to access data about the instance.</para>
    /// </returns>
    GameObject getFirstObject();

    /// <summary>
    ///     Gets the object of this type at the given index.
    /// </summary>
    /// <param name="index">
    ///     The index of the instance to get the data for.
    /// </param>
    /// <returns>
    ///     <para>The object of this type at the given index.</para>
    ///     <para>Used to access data about the instance.</para>
    /// </returns>
    GameObject getObjectByIndex(int index);

};
