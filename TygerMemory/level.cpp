#include "pch.h"
#include "level.h"
#include "core.h"

LevelCode Level::getCurrentLevel()
{
    return *(LevelCode*)(Core::moduleBase + 0x280594);
}

void Level::changeLevel(LevelCode level)
{
    *(float*)(Core::moduleBase + 0x264248) = 0.01f;
    *(char*)(Core::moduleBase + 0x286C54) = (char)0x0;
    *(int*)(Core::moduleBase + 0x289028) = (int)level;
    *(char*)(Core::moduleBase + 0x289050) = (char)0x1;
}
