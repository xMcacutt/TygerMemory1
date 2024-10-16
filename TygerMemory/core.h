#pragma once
#include <vector>

class core
{
private:
	static DWORD processId;
	static HANDLE hProcess;
	static uintptr_t moduleBase;
	static uintptr_t GetModuleBaseAddress(HANDLE hProcess, std::string& moduleName);
public:
	static bool Initialize(HWND hWnd, std::function<void(LogLevel, const std::string&)> loggerFunction);
	static int GetPointerAddress(uintptr_t baseAddress, const std::vector<int>& offsets);
	template <typename T>
	static bool TryReadMemory(uintptr_t address, T& result, bool addBase);
	template<typename T>
	static bool TryWriteMemory(uintptr_t address, bool addBase, T& value);
	static bool TryWriteMemory(uintptr_t address, bool addBase, const std::vector<char>& bytes);
};

