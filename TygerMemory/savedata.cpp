#include "pch.h"
#include "savedata.h"
#include "core.h"

void SaveData::setFmvWatched(FMV fmv, bool value)
{
    uint8_t fmvWatchedByte = SaveData::Data->FmvsWatched;
    uint8_t bitMask = (1 << (int)fmv);
    if (value)
        fmvWatchedByte |= bitMask;
    else
        fmvWatchedByte &= ~bitMask;
    SaveData::Data->FmvsWatched = fmvWatchedByte;
}

bool SaveData::getFmvWatched(FMV fmv)
{
    uint8_t fmvWatchedByte = SaveData::Data->FmvsWatched;
    uint8_t bitMask = (1 << static_cast<int>(fmv));
    return (fmvWatchedByte & bitMask) != 0;
}
