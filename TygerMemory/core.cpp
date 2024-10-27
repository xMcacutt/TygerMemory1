#include "pch.h"
#include "core.h"
#include <iostream>
#include <psapi.h>
#include <windows.h>
#include "logging.h"
#include <tchar.h>

DWORD Core::processId = 0;
HANDLE Core::hProcess = 0;
uintptr_t Core::moduleBase = 0;

bool Core::initialize(HMODULE hModule)
{
	Logging::del();
	Logging::log("TygerMemory Initializing...");
	moduleBase = (uintptr_t)hModule;
	if (moduleBase == 0) {
		Logging::log("Failed to load .exe module.");
		return false;
	}
	Logging::log("TygerMemory Initialized.");
	return true;
}

uintptr_t Core::getPointerAddress(uintptr_t baseAddr, const std::vector<int>& offsets)
{
	uintptr_t currentAddr = baseAddr;
	for (size_t i = 0; i < offsets.size(); i++) {
		uintptr_t* pointer = reinterpret_cast<uintptr_t*>(currentAddr);
		currentAddr = *pointer;
		if (currentAddr == 0)
			return 0; 
		currentAddr += offsets[i];
	}
	return currentAddr;
}