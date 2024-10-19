#include "pch.h"
#include "gameobject.h"
#include "core.h"
#include "logging.h"

GameObject::GameObject(std::string name, uintptr_t addr) : objectName(name), baseAddr(addr) {}

uintptr_t GameObject::getFirst()
{
	return Core::tryReadMemory<uintptr_t>(baseAddr + 0x48, true);
}

int GameObject::getCount()
{
	return Core::tryReadMemory<int>(baseAddr + 0x44, true);
}

uintptr_t GameObject::getByIndex(int index)
{
	int count = getCount();

	if (index < 0 || index >= count) {
		Logging::getInstance().log(LogLevel::WARN, "Invalid index specified for gameobject: " + objectName);
		return 0;
	}

	auto currentAddr = getFirst();

	for (int i = 0; i < index; ++i)
		currentAddr = Core::tryReadMemory<uintptr_t>(currentAddr + 0x30, false);

	return currentAddr;
}

std::string GameObject::getFullName()
{
	return Core::tryReadString(baseAddr + 0x20, true, 0x20);
}

GameObject::~GameObject() {}