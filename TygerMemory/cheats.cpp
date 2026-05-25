#include "pch.h"
#include "Cheats.h"

typedef void (*CheatFunction)();

void Cheats::invincibility()
{
	((CheatFunction)(Core::moduleBase + 0x10A850))();
}

void Cheats::elementalRangs()
{
	((CheatFunction)(Core::moduleBase + 0x10A7A0))();
}

void Cheats::technoRangs()
{
	((CheatFunction)(Core::moduleBase + 0x10A710))();
}

void Cheats::levelMenu()
{
	((CheatFunction)(Core::moduleBase + 0xE5050))();
}

void Cheats::collectibleLines()
{
	((CheatFunction)(Core::moduleBase + 0x10A820))();
}
