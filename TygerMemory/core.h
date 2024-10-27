// core.h

#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include <vector>
#include <string>
#include <functional>
#include "logging.h"
//For stuff like DWORD, HANDLE, HWND
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

typedef void (*LoggerFunction)(const std::string&, MemLogLevel);

class TYGERMEM Core
{
private:
	static DWORD processId;
	static HANDLE hProcess;
	static uintptr_t getModuleBaseAddress(HANDLE hProcess);
public:
	static uintptr_t moduleBase;
	static bool initialize(HWND hWnd, std::function<void(const std::string&, MemLogLevel)> loggerFunction);
	static uintptr_t getPointerAddress(uintptr_t baseAddress, const std::vector<int>& offsets);

	template <typename T>
	static bool unprotectMemory(LPVOID address) {
		DWORD oldProtect;
		return VirtualProtectEx(hProcess, address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
	}
};