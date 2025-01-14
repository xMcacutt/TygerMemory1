#include "pch.h"
#include "sound.h"
#include "core.h"

TyPlaySoundByIndex_t Sound::GetTySoundFunction()
{
    return (TyPlaySoundByIndex_t)(Core::moduleBase + 0x153dd0);
}

UINT* Sound::PlayTySoundByIndex(int soundIndex)
{
    return GetTySoundFunction()(soundIndex, nullptr, 0.0f);
}
