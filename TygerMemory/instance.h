#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include "vector3f.h"

class TYGERMEM GameObject;

class TYGERMEM Instance {
protected:
    uintptr_t address;
    int index;
    GameObject* objectData;
public:
    Instance(uintptr_t addr, int index, GameObject* objectData);
    Instance getNext();
    Instance getPrevious();
    GameObject* getOwner() const { return objectData; }
    int getIndex() const { return index; }

    virtual void setPosition(Vector3f);
    virtual Vector3f getPosition();
};

