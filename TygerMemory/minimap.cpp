#include "pch.h"
#include "minimap.h"
#include "core.h"

MapTransform* Minimap::GetMapTransform(LevelCode level)
{
    return (MapTransform*)((Core::moduleBase + 0x261f50) + (0x30 * (int)level));
}

void Minimap::SetMapTransform(LevelCode level, MapTransform* transform)
{
    memcpy((MapTransform*)(Core::moduleBase + 0x261f50 + (0x30 * (int)level)), transform, sizeof(MapTransform));
}

void Minimap::SetDisabledMapLevel(char levelIndex)
{
    Core::WriteHardcodedValue((BYTE*)(Core::moduleBase + 0xEA136), &levelIndex, 1);
}
