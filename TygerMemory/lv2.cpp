#include "pch.h"
#include "lv2.h"
#include "minhook.h"

typedef void(__stdcall* FunctionType)(void);
FunctionType mergeLv2Function = nullptr;
uintptr_t mergeLv2OriginAddr;
__declspec(naked) void __stdcall mergeLv2Hook() {
	__asm {
		pushad
		pushfd
        lea eax, [ebp - 0x80]
        push eax
		call Lv2::mergeData
		add esp, 4
		popfd
		popad
		xor edi,edi
		mov [ebp-0xc4],edi
		jmp[mergeLv2OriginAddr]
	}
}

Lv2Data constructLv2Data(std::unordered_map<std::string, std::string> entries) {
    static std::string combinedText;
    combinedText.clear();
    for (auto& entry : entries)
        combinedText += entry.second + "\n";
    if (combinedText.empty())
        return Lv2Data();
    static std::vector<char> buffer;
    buffer.assign(combinedText.begin(), combinedText.end());
    Lv2Data custom = {};
    custom.pFileMem = buffer.data();
    custom.bFileMemAllocated = false;
    custom.fileSize = (int)buffer.size();
    custom.entries = nullptr;
    custom.entryCount = 0;
    custom.auxCount = 0;
    custom.unk34 = 0;
    return custom;
}

void Lv2::mergeData(Lv2Data* mainData)
{
    typedef void(__thiscall* tParseLv2)(Lv2Data* data);
    typedef void(__thiscall* tMergeLv2)(Lv2Data* dst, Lv2Data* src, int flag);
    tParseLv2 parseLv2 = (tParseLv2)(Core::moduleBase + 0x1ACA50);
    tMergeLv2 mergeLv2 = (tMergeLv2)(Core::moduleBase + 0x1AC220);
    static void* lastRaw = nullptr;
    if (mainData->pFileMem == lastRaw)
        return;
    lastRaw = mainData->pFileMem;
    auto globalCustom = constructLv2Data(globalEntries);
    if (!globalCustom.pFileMem)
        return;
    parseLv2(&globalCustom);
    if (globalCustom.entryCount > 0)
        mergeLv2(mainData, &globalCustom, 1);
    auto level = Level::stringToLevelCode[std::string(mainData->name).substr(0, 2)];
    auto levelCustom = constructLv2Data(levelEntries[level]);
    if (!levelCustom.pFileMem)
        return;
    parseLv2(&levelCustom);
    if (levelCustom.entryCount > 0)
        mergeLv2(mainData, &levelCustom, 1);
}

void Lv2::installHooks()
{
	mergeLv2OriginAddr = Core::moduleBase + 0x109f1f;
	auto addr = (char*)(Core::moduleBase + 0x109f17);
	MH_CreateHook((LPVOID)addr, &mergeLv2Hook, reinterpret_cast<LPVOID*>(&mergeLv2Function));
	MH_EnableHook(addr);
}
