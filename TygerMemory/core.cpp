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

bool Core::initialize(HWND hWnd, std::function<void(LogLevel, const std::string&)> loggerFunction)
{
	Logging::getInstance().setLogger(loggerFunction);
	Logging::getInstance().log(LogLevel::INFO, "TygerMemory Initializing...");

	GetWindowThreadProcessId(hWnd, &processId);
	if (processId == 0) {
		Logging::getInstance().log(LogLevel::ERR, "Failed to get process id.");
		return false;
	};

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (hProcess == nullptr) {
		Logging::getInstance().log(LogLevel::ERR, "Failed to open process.");
		return false;
	}

	moduleBase = getModuleBaseAddress(hProcess);
	if (moduleBase == 0) {
		Logging::getInstance().log(LogLevel::ERR, "Failed to find .exe module.");
		return false;
	}

	Logging::getInstance().log(LogLevel::INFO, "TygerMemory Initialized.");
	return true;
}

uintptr_t Core::getModuleBaseAddress(HANDLE hProcess) {
	HMODULE hModules[1024];
	DWORD cbNeeded;

	if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(hProcess, hModules[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
				if (_tcslen(szModName) > 4 && _tcscmp(szModName + _tcslen(szModName) - 4, _T(".exe")) == 0) {
					return (DWORD)hModules[i]; 
				}
			}
		}
	}
	return 0; 
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