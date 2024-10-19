#pragma once
#include <iostream>

class GameObject {
protected:
	const uintptr_t baseAddr;
	const std::string objectName;
	GameObject(std::string name, uintptr_t addr);
public:
	uintptr_t getFirst();
	int getCount();
	uintptr_t getByIndex(int index);
	std::string getFullName();

	virtual ~GameObject();
};