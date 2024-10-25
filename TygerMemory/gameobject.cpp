#include "pch.h"
#include "gameobject.h"
#include "core.h"
#include "logging.h"
#include "vector3f.h"
#include "GameObject.h"

GameObject::GameObject(uintptr_t addr) : address(addr) {}

int GameObject::getCurrentCount() {
    return Core::tryReadMemory<int>(address + 0x44, true);
}

GameObject GameObject::getObject(ObjectType type) {
    return GameObject(Core::moduleBase + (int)type);
}

Instance GameObject::getFirst() {
    return Instance(Core::tryReadMemory<uintptr_t>(address + 0x48, true), 0, this);
}

Instance GameObject::getByIndex(int index) {
    if (index >= getCurrentCount()) {
        Logging::getInstance().log(LogLevel::WARN, "Attempted to access object which is not loaded.");
        return Instance(0, -1, nullptr);
    }
    auto addr = Core::tryReadMemory<uintptr_t>(address + 0x48, true);
    for (int i = 0; i < index; i++) {
        addr = Core::tryReadMemory<uintptr_t>(addr + 0x34, false);
    }
    return Instance(addr, index, this);
}