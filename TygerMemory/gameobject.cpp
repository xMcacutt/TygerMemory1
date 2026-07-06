#include "gameobject.h"
#include "core.h"
#include "gameobject_descriptor.h"
#include "logging.h"
#include "pch.h"


GameObject::GameObject(uintptr_t addr, int idx, GameObjectDescriptor *object)
    : address(addr), index(idx), objectData(object) {}

GameObject GameObject::getNext() {
  if (index + 1 >= objectData->getCurrentCount()) {
    Logging::log("Attempted to access an object which isn't loaded.");
    return *this;
  }
  return objectData->getObjectByIndex(index + 1);
}

GameObject GameObject::getPrevious() {
  if (index == 0) {
    Logging::log("Attempted to access an object which isn't loaded.");
    return *this;
  }
  return objectData->getObjectByIndex(index - 1);
}

void GameObject::setPosition(Vector3f position) {
  auto addr = *(uintptr_t *)(address + 0x8);
  *(Vector3f *)(addr + 0x74) = position;
}

Vector3f GameObject::getPosition() {
  auto addr = *(uintptr_t *)(address + 0x8);
  return *(Vector3f *)(addr + 0x74);
}

uintptr_t GameObject::getAddr() { return address; }
