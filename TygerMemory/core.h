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
	static uintptr_t getModuleBaseAddress(HANDLE hProcess, std::string& moduleName);
public:
	static uintptr_t moduleBase;
	static bool initialize(HWND hWnd, std::function<void(LogLevel, const std::string&)> loggerFunction);
	static uintptr_t getPointerAddress(uintptr_t baseAddress, const std::vector<int>& offsets);
	static std::string tryReadString(uintptr_t address, bool addBase, size_t length, bool& success);
	static std::string tryReadString(uintptr_t address, bool addBase, size_t length);

	template<typename T>
	static T tryReadMemory(uintptr_t address, bool addBase, bool& success) {
		T result{};
		try {
			if (addBase)
				address += moduleBase;
			SIZE_T bytesRead = 0;
			if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), &result, sizeof(T), &bytesRead))
				success = (bytesRead == sizeof(T));
			else
				success = false;
		}
		catch (const std::exception& ex) {
			Logging::getInstance().log(LogLevel::ERR, ex.what());
			success = false;
		}
		return success ? result : T();
	}

	template<typename T>
	static T tryReadMemory(uintptr_t address, bool addBase) {
		T result{};
		bool success;
		try {
			if (addBase)
				address += moduleBase;
			SIZE_T bytesRead = 0;
			if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), &result, sizeof(T), &bytesRead))
				success = (bytesRead == sizeof(T));
			else
				success = false;
		}
		catch (const std::exception& ex) {
			Logging::getInstance().log(LogLevel::ERR, ex.what());
			success = false;
		}
		return success ? result : T();
	}

	template <typename T>
	static bool tryWriteMemory(uintptr_t address, bool addBase, T value) {
		if (addBase)
			address += moduleBase;
		SIZE_T bytesWritten = 0;
		if (WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), &value, sizeof(T), &bytesWritten)) {
			return bytesWritten == sizeof(T);
		}
		return false;
	}

	template <typename T>
	static bool UnprotectMemory(LPVOID address) {
		DWORD oldProtect;
		return VirtualProtectEx(hProcess, address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
	}

	static bool tryWriteMemory(uintptr_t address, bool addBase, const std::vector<char>& bytes);
};