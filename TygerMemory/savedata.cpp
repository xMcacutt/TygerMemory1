#include "pch.h"
#include "savedata.h"
#include "core.h"

SaveDataStruct* SaveData::Data = nullptr;

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

SaveDataStruct* SaveData::GetData() {
    if (!Data) { // Initialize only if Data hasn't been set
        uintptr_t address = Core::moduleBase + 0x288730;
        Data = reinterpret_cast<SaveDataStruct*>(*reinterpret_cast<int*>(address));
    }
    return Data;
}