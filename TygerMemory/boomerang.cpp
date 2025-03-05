#include "pch.h"
#include "boomerang.h"
#include "core.h"

void Boomerang::SetCrateBurnTime(int burnTime)
{
	Core::SetReadOnlyValue((void*)(Core::moduleBase + 0x5E66f), &burnTime, 4);
}
