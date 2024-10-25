#include "pch.h"
#include "instance.h"
#include "gameobject.h"
#include "logging.h"
#include "core.h"

Instance::Instance(uintptr_t addr, int idx, GameObject* object) : address(addr), index(idx), objectData(object) {}

Instance Instance::getNext()
{
    if (index + 1 >= objectData->getCurrentCount())
    {
        Logging::getInstance().log(LogLevel::WARN, "Attempted to access an object which isn't loaded.");
        return *this;
    }
    return objectData->getByIndex(index + 1);
}

Instance Instance::getPrevious()
{
    if (index == 0) {
        Logging::getInstance().log(LogLevel::WARN, "Attempted to access an object which isn't loaded.");
        return *this;
    }
    return objectData->getByIndex(index - 1);
}

void Instance::setPosition(Vector3f position) {
    auto addr = Core::tryReadMemory<uintptr_t>(address + 0x8, false);
    Core::tryWriteMemory<Vector3f>(addr + 0x74, false, position);
}

Vector3f Instance::getPosition() {
    auto addr = Core::tryReadMemory<uintptr_t>(address + 0x8, false);
    return Core::tryReadMemory<Vector3f>(addr + 0x74, false);
}