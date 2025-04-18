#include "pch.h"
#include "sound.h"
#include "core.h"

TyPlaySoundByIndex_t Sound::GetTySoundFunction()
{
    return (TyPlaySoundByIndex_t)(Core::moduleBase + 0x153dd0);
}

UINT* Sound::PlayTySoundByIndex(GlobalSound soundIndex, Vector4f* soundLocation, int materialFlags)
{
    //Just always make w 1, seems to be what it usually is in the game
    if (soundLocation)
        soundLocation->w = 1.0f;
    return GetTySoundFunction()(soundIndex, soundLocation, materialFlags);
}
