#include "pch.h"
#include "core.h"
#include "hero.h"
#include <variant>
#include "vector3f.h"

void Hero::setState(int state)
{
    uintptr_t addr = isBull() ? 0x254564 : 0x271590;
    Core::tryWriteMemory(addr, true, state);
}

int Hero::getState() {
    uintptr_t addr = isBull() ? 0x254564 : 0x271590;
    return Core::tryReadMemory<int>(addr, true);
}

void Hero::setPosition(Vector3f coords) {
    uintptr_t addr = isBull() ? 0x254268 : 0x270B78;
    Core::tryWriteMemory<Vector3f>(0x270B78, true, coords);
}

Vector3f Hero::getPosition() {
    uintptr_t addr = isBull() ? 0x254268 : 0x270B78;
    return Core::tryReadMemory<Vector3f>(addr, true);
}

bool Hero::isBull()
{
	return Core::tryReadMemory<bool>(0x27E544, true);
}
