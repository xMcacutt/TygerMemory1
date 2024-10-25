// core.h

#pragma once
#include <vector>
#include <string>
#include <functional>
#include "logging.h"

class Core
{
private:
	static DWORD processId;
	static HANDLE hProcess;
	static uintptr_t getModuleBaseAddress(HANDLE hProcess);
public:
	static uintptr_t moduleBase;
	static bool initialize(HWND hWnd, std::function<void(LogLevel, const std::string&)> loggerFunction);
	static uintptr_t getPointerAddress(uintptr_t baseAddress, const std::vector<int>& offsets);

	template <typename T>
	static bool unprotectMemory(LPVOID address) {
		DWORD oldProtect;
		return VirtualProtectEx(hProcess, address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
	}
};