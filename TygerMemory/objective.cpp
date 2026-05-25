#include "pch.h"
#include "event.h"
#include "Objective.h"
#include "MinHook.h"
#include "core.h"

using ObjectiveIncrementFunction = void(__thiscall*)(uintptr_t thisPtr);
ObjectiveIncrementFunction objectiveIncrementFunctionOrigin = nullptr;
Event<std::string, int> g_onObjectiveCountIncrementedCollected;

void Objective::addObjectiveCountIncrementedListener(ObjectiveCountIncremented callback)
{
	g_onObjectiveCountIncrementedCollected.subscribe(callback);
}

void Objective::removeObjectiveCountIncrementedListener(ObjectiveCountIncremented callback)
{
	g_onObjectiveCountIncrementedCollected.unsubscribe(callback);
}

void __fastcall objectiveCountIncrementedHook(uintptr_t thisPtr, void* edx)
{
	auto descriptor = *(uintptr_t*)(thisPtr + 0x4);
	const char* namePtr = (const char*)(descriptor + 0x2c);
	std::string objectiveName(namePtr, strnlen(namePtr, 0x20));
	int count = *(int*)(thisPtr + 0x70) + 1;
	g_onObjectiveCountIncrementedCollected.invoke(objectiveName, count);
	objectiveIncrementFunctionOrigin(thisPtr);
}

void Objective::installHooks()
{
	void* target = (void*)(Core::moduleBase + 0x106a80);
	MH_CreateHook(target, &objectiveCountIncrementedHook, reinterpret_cast<void**>(&objectiveIncrementFunctionOrigin));
	MH_EnableHook(target);
}
