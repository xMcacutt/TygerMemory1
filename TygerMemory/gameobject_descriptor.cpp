#include "pch.h"
#include "gameobject.h"
#include "core.h"
#include "logging.h"
#include "vector3f.h"
#include "gameobject_descriptor.h"

GameObjectDescriptor::GameObjectDescriptor(uintptr_t addr) { address = addr; }

int GameObjectDescriptor::getCurrentCount() {
    return *(int*)(address + 0x74);
}

const char* GameObjectDescriptor::getDescName() {
    return (const char*)(address + 0x30);
}

GameObjectDescriptor GameObjectDescriptor::getNextDesc() {
    auto newAddr = *(uintptr_t*)(address + 0x84);
    return GameObjectDescriptor(newAddr);
}

GameObjectDescriptor GameObjectDescriptor::getObjectDesc(const char* name) {
    auto desc = GameObjectDescriptor(*(uintptr_t*)(Core::moduleBase + basePtrOffset));
    while (desc.address != 0) {
        auto currentName = desc.getDescName();
        if (currentName && std::strncmp(name, currentName, 0x20) == 0)
            return desc;
        desc = desc.getNextDesc();
    }
    throw std::runtime_error("Descriptor not found");
}

GameObject GameObjectDescriptor::getFirstObject() {
    return GameObject(*(uintptr_t*)(address + 0x78), 0, this);
}

GameObject GameObjectDescriptor::getObjectByIndex(int index) {
    if (index >= getCurrentCount()) {
        Logging::log("Attempted to access object which is not loaded.");
        return GameObject(0, -1, nullptr);
    }
    auto addr = *(uintptr_t*)(address + 0x78);
    for (int i = 0; i < index; i++)
        addr = *(uintptr_t*)(addr + 0x34);
    return GameObject(addr, index, this);
}