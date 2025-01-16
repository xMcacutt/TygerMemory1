#include "pch.h"
#include "collectable.h"
#include "core.h"

LevelInfo* Collectable::GetLevelInfoArray()
{
    return (LevelInfo*)(Core::moduleBase + 0x26F6D0);
}

FloatRGBA* Collectable::GetThunderEggParticleColours()
{
    return (FloatRGBA*)(Core::moduleBase + 0x2701B0);
}

void Collectable::SetGoldenCogParticleColours(FloatRGBA colour)
{
    Core::SetReadOnlyValue((void*)(Core::moduleBase + 0x209C60), &colour, sizeof(FloatRGBA));
}
