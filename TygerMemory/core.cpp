#include "pch.h"
#include "core.h"
#include <iostream>
#include <psapi.h>
#include <windows.h>
#include "logging.h"

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

    std::string moduleName = "TY.exe";
    moduleBase = getModuleBaseAddress(hProcess, moduleName);
    if (moduleBase == 0) {
        Logging::getInstance().log(LogLevel::ERR, "Failed to find TY.exe module.");
        return false;
    }

    Logging::getInstance().log(LogLevel::INFO, "TygerMemory Initialized.");
    return true;
}

uintptr_t Core::getModuleBaseAddress(HANDLE hProcess, std::string& moduleName) {
    HMODULE hMods[1024];
    DWORD cbNeeded;
    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            char szModName[MAX_PATH];
            if (GetModuleFileNameExA(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(char))) {
                if (moduleName == szModName || moduleName == szModName + std::string(".exe")) {
                    return reinterpret_cast<uintptr_t>(hMods[i]);
                }
            }
        }
    }
    return 0;
}

uintptr_t Core::getPointerAddress(uintptr_t baseAddr, const std::vector<int>& offsets)
{
    uintptr_t currentAddr = baseAddr;
    uintptr_t result;
    bool success;
    for (int iOffset = 0; iOffset < offsets.size(); iOffset++) {
        result = tryReadMemory<bool>(currentAddr, iOffset == 0, success);
        if (!success)
            return 0;
        currentAddr = result + offsets[iOffset];
    }
    return currentAddr;
}

bool Core::tryWriteMemory(uintptr_t address, bool addBase, const std::vector<char>& bytes) {
    if (addBase)
        address += moduleBase;
    SIZE_T bytesWritten = 0;
    if (WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), bytes.data(), bytes.size(), &bytesWritten))
        return bytesWritten == bytes.size();
    return false;
}
