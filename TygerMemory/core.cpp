#include "pch.h"
#include "core.h"
#include <iostream>
#include <psapi.h>
#include <windows.h>
#include "logging.h"

bool core::Initialize(HWND hWnd, std::function<void(LogLevel, const std::string&)> loggerFunction)
{
    logging::getInstance().setLogger(loggerFunction);
    logging::getInstance().log(LogLevel::INFO, "TygerMemory Initializing...");

    GetWindowThreadProcessId(hWnd, &processId);
    if (processId == 0) {
        
        logging::getInstance().log(LogLevel::ERR, "Failed to get process id.");
        return false;
    };

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (hProcess == nullptr) {
        logging::getInstance().log(LogLevel::ERR, "Failed to open process.");
        return false;
    }

    std::string moduleName = "TY.exe";
    moduleBase = GetModuleBaseAddress(hProcess, moduleName);
    if (moduleBase == 0) {
        logging::getInstance().log(LogLevel::ERR, "Failed to find TY.exe module.");
        return false;
    }

    logging::getInstance().log(LogLevel::INFO, "TygerMemory Initialized.");
    return true;
}

uintptr_t core::GetModuleBaseAddress(HANDLE hProcess, std::string& moduleName) {
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

int core::GetPointerAddress(uintptr_t baseAddr, const std::vector<int>& offsets)
{
    uintptr_t currentAddr = baseAddr;
    uintptr_t result;
    for (int iOffset = 0; iOffset < offsets.size(); iOffset++) {
        if (!TryReadMemory(currentAddr, result, iOffset == 0))
            return 0;
        currentAddr = result + offsets[iOffset];
    }
    return currentAddr;
}

template <typename T>
bool core::TryReadMemory(uintptr_t address, T & result, bool addBase) {
    try {
        if (addBase)
            address += moduleBase;
        SIZE_T bytesRead = 0;
        if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), &result, sizeof(T), &bytesRead)) {
            return bytesRead == sizeof(T);
        }
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        result = T();
        return false;
    }
}

bool core::TryWriteMemory(uintptr_t address, bool addBase, const std::vector<char>& bytes) {
    if (addBase)
        address += moduleBase;
    SIZE_T bytesWritten = 0;
    if (WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), bytes.data(), bytes.size(), &bytesWritten)) {
        return bytesWritten == bytes.size();
    }
    return false;
}

template <typename T>
bool core::TryWriteMemory(uintptr_t address, bool addBase, T& value) {
    if (addBase)
        address += moduleBase;
    SIZE_T bytesWritten = 0;
    if (WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), &value, sizeof(T), &bytesWritten)) {
        return bytesWritten == sizeof(T);
    }
    return false;
}



