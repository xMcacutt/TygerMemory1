#pragma once
#include "vector3f.h"

class GameObject;

class Instance {
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

