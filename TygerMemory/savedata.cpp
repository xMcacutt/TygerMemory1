#include "pch.h"
#include "savedata.h"
#include "core.h"
#include "leveldata.h"

SaveData::SaveData(uintptr_t addr) : baseAddress(addr) {}

SaveData SaveData::getData()
{
    auto addr = Core::tryReadMemory<uintptr_t>(0x288730, true);
    return SaveData(addr);
}

LevelData SaveData::getLevelData(LevelCode levelCode)
{
    uintptr_t levelBaseAddress = baseAddress + 0x10 + (int)levelCode * 0x70;
    return LevelData(levelBaseAddress);
}

void SaveData::setHubFlag(HubFlag flag, bool value)
{
    Core::tryWriteMemory<bool>(baseAddress + 0xA94 + (int)flag, false, value);
}

bool SaveData::getHubFlag(HubFlag flag)
{
    return Core::tryReadMemory<bool>(baseAddress + 0xA94 + (int)flag, false);
}

void SaveData::setProgressFlag(ProgressFlag flag, bool value)
{
    Core::tryWriteMemory<bool>(baseAddress + 0xAC4 + (int)flag, false, value);
}

bool SaveData::getProgressFlag(ProgressFlag flag)
{
    return Core::tryReadMemory<bool>(baseAddress + 0xAC4 + (int)flag, false);
}

void SaveData::setTyAttribute(TyAttribute flag, bool value)
{
    Core::tryWriteMemory<bool>(baseAddress + 0xAB4 + (int)flag, false, value);

}

bool SaveData::getTyAttribute(TyAttribute flag)
{
    return Core::tryReadMemory<bool>(baseAddress + 0xAB4 + (int)flag, false);
}

void SaveData::setFmvWatched(FMV fmv, bool value)
{
    uint8_t fmvWatchedByte = Core::tryReadMemory<uint8_t>(baseAddress + 0xB13, false);
    uint8_t bitMask = (1 << (int)fmv);
    if (value)
        fmvWatchedByte |= bitMask;
    else
        fmvWatchedByte &= ~bitMask;
    Core::tryWriteMemory<uint8_t>(baseAddress + 0xB13, false, fmvWatchedByte);
}

bool SaveData::getFmvWatched(FMV fmv)
{
    uint8_t fmvWatchedByte = Core::tryReadMemory<uint8_t>(baseAddress + 0xB13, false);
    uint8_t bitMask = (1 << static_cast<int>(fmv));
    return (fmvWatchedByte & bitMask) != 0;
}

LevelCode SaveData::getCurrentLevel()
{
    return Core::tryReadMemory<LevelCode>(baseAddress + 0xAA4, false);
}

LevelCode SaveData::getPreviousLevel()
{
    return Core::tryReadMemory<LevelCode>(baseAddress + 0xAA8, false);
}

LevelCode SaveData::getSavedLevel()
{
    return Core::tryReadMemory<LevelCode>(baseAddress + 0x8, false);
}

int SaveData::getPercentageCompletion()
{
    return (int)Core::tryReadMemory<char>(baseAddress + 0xC, false);
}

int SaveData::getThunderEggCount()
{
    return (int)Core::tryReadMemory<char>(baseAddress + 0xD, false);
}

bool SaveData::isHardcore()
{
    return Core::tryReadMemory<bool>(baseAddress + 0xE, false);
}

Zone SaveData::getSavedZone()
{
    return Core::tryReadMemory<Zone>(baseAddress + 0xAAC, false);
}

Rang SaveData::getCurrentRang()
{
    return Core::tryReadMemory<Rang>(baseAddress + 0xAB0, false);
}

int SaveData::getLifeCount()
{
    return Core::tryReadMemory<short>(baseAddress + 0xAD0, false);
}

int SaveData::getGameTimeSeconds()
{
    return Core::tryReadMemory<int>(baseAddress + 0xB14, false);
}

void SaveData::setGameTimeSeconds(int seconds)
{
    Core::tryWriteMemory<int>(baseAddress + 0xB14, false, seconds);
}

int SaveData::getEnemiesBitten()
{
    return Core::tryReadMemory<int>(baseAddress + 0xB18, false);
}

int SaveData::getEnemiesZapped()
{
    return Core::tryReadMemory<int>(baseAddress + 0xB1C, false);
}

int SaveData::getEnemiesFlamed()
{
    return Core::tryReadMemory<int>(baseAddress + 0xB20, false);
}

int SaveData::getCricketBatsBurnt()
{
    return Core::tryReadMemory<int>(baseAddress + 0xB24, false);
}

bool SaveData::cheatsUsed()
{
    return Core::tryReadMemory<bool>(baseAddress + 0xB28, false);
}

int SaveData::getSkinId()
{
    return Core::tryReadMemory<int>(baseAddress + 0xB2C, false);
}
