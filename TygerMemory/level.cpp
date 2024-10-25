#include "pch.h"
#include "level.h"
#include "core.h"

LevelCode Level::getCurrentLevel()
{
    return (LevelCode)Core::tryReadMemory<int>(0x280594, true);
}

void Level::changeLevel(LevelCode level)
{
    Core::tryWriteMemory<float>(0x264248, true, 0.01f);
    Core::tryWriteMemory<char>(0x286C54, true, { 0x1 });
    Core::tryWriteMemory<int>(0x289028, true, (int)level);
    Core::tryWriteMemory<char>(0x289050, true, { 0x1 });
}
