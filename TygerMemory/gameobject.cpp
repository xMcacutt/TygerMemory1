#include "pch.h"
#include "gameobject.h"
#include "core.h"
#include "logging.h"
#include "vector3f.h"
#include "GameObject.h"

GameObject::GameObject(uintptr_t addr) : address(addr) {}

int GameObject::getCurrentCount() {
    return *(int*)(Core::moduleBase + address + 0x44);
}

GameObject GameObject::getObject(ObjectType type) {
    return GameObject(Core::moduleBase + (int)type);
}

Instance GameObject::getFirst() {
    return Instance(*(uintptr_t*)(Core::moduleBase + address + 0x48), 0, this);
}

Instance GameObject::getByIndex(int index) {
    if (index >= getCurrentCount()) {
        Logging::log("Attempted to access object which is not loaded.");
        return Instance(0, -1, nullptr);
    }
    auto addr = *(uintptr_t*)(Core::moduleBase + address + 0x48);
    for (int i = 0; i < index; i++)
        addr = *(uintptr_t*)(addr + 0x34);
    return Instance(addr, index, this);
}