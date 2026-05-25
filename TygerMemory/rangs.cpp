#include "pch.h"
#include "rangs.h"
#include "core.h"

typedef Boomerangs(__thiscall* SetCurrentRang_t)(void* boomerangManager, Boomerangs newRang);
SetCurrentRang_t Original_SetCurrentRang;

Boomerangs Rangs::GetCurrentRang()
{
	return *(Boomerangs*)(Core::moduleBase + 0x2719A0);
}

void Rangs::SetCrateBurnTime(int burnTime)
{
	Core::SetReadOnlyValue((void*)(Core::moduleBase + 0x5E66f), &burnTime, 4);
}