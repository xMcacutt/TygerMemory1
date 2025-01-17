#include "pch.h"
#include "totals.h"
#include "savedata.h"
#include "level.h"
#include <algorithm>
#include <vector>

int Totals::getCurrentThunderEggCount(TotalType totalType)
{
    auto saveData = SaveData::GetData()->LevelData;
    if (totalType == TotalType::Level) {
        auto levelData = saveData[(int)Level::getCurrentLevel()];
        return std::count(levelData.ThunderEggs, levelData.ThunderEggs + 8, true);
    }
    int count = 0;
    for (size_t i = 0; i < 24; ++i)
        count += std::count(saveData[i].ThunderEggs, saveData[i].ThunderEggs + 8, true);
    return count;

}

int Totals::getCurrentCogCount(TotalType totalType)
{
    if (totalType == TotalType::Level)
        return *(int*)(Core::moduleBase + 0x265260);
    auto saveData = SaveData::GetData()->LevelData;
    int count = 0;
    for (size_t i = 0; i < 24; ++i)
        count += std::count(saveData[i].GoldenCogs, saveData[i].GoldenCogs + 10, true);
    return count;
}

int Totals::getCurrentBilbyCount(TotalType totalType)
{
    if (totalType == TotalType::Level)
        return *(int*)(Core::moduleBase + 0x2651AC);
    auto saveData = SaveData::GetData()->LevelData;
    int count = 0;
    for (size_t i = 0; i < 24; ++i)
        count += std::count_if(saveData[i].Bilbies, saveData[i].Bilbies + 5, [](int bilby) { return bilby != 0; });
    return count;
}

int Totals::getCurrentFrameCount(TotalType totalType)
{
    auto frameData = SaveData::GetData()->PictureFrames;
    
    if (totalType == TotalType::Level) {

        int levelOffset = 0xC * (int)Level::getCurrentLevel();
        int levelIdsStart = *(int*)(Core::moduleBase + 0x288610 + levelOffset);
        int levelIdsEnd = *(int*)(Core::moduleBase + 0x288614 + levelOffset);

        std::vector<int> frameIndices;
        for (int addr = levelIdsStart; addr < levelIdsEnd; addr += sizeof(int)) {
            int frameIndex = *(int*)addr;
            frameIndices.push_back(frameIndex);
        }
        int collectedCount = 0;
        for (int index : frameIndices) {
            int byteIndex = index / 8;
            int bitOffset = index % 8;
            if (frameData[byteIndex] & (1 << bitOffset)) {
                collectedCount++;
            }
        }
        return collectedCount;
    }

    int totalCollectedCount = 0;
    for (int i = 0; i < 64; ++i) {
        uint8_t byte = frameData[i];
        for (int bit = 0; bit < 8; ++bit) {
            if (byte & (1 << bit)) {
                totalCollectedCount++;
            }
        }
    }
    return totalCollectedCount;
}

int Totals::getCurrentOpalCount(bool thisLoad)
{
    return thisLoad ? *(int*)(Core::moduleBase + 0x2888B4) : *(int*)(Core::moduleBase + 0x2888B0);
}

int Totals::getCurrentRangCount()
{
    auto saveData = SaveData::GetData();
    int count = 0;
    count += saveData->AttributeData.GotAquarang;
    count += saveData->AttributeData.GotBoomerang;
    count += saveData->AttributeData.GotFlamerang;
    count += saveData->AttributeData.GotFrostyrang;
    count += saveData->AttributeData.GotZappyrang;
    count += saveData->AttributeData.GotZoomerang;
    count += saveData->AttributeData.GotMultirang;
    count += saveData->AttributeData.GotInfrarang;
    count += saveData->AttributeData.GotMegarang;
    count += saveData->AttributeData.GotKaboomerang;
    count += saveData->AttributeData.GotChronorang;
    count += saveData->AttributeData.GotDoomerang;
    return count;
}

int Totals::getCurrentTalismanCount()
{
    auto saveData = SaveData::GetData();
    return std::count(saveData->Talismans, saveData->Talismans + 5, true);
}

void Totals::SetTotalOpals(int amount)
{
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xE7691), &amount, 4);
}

void Totals::SetTotalRainbowScales(int amount)
{
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xE76B6), &amount, 4);
}

void Totals::SetTotalTalismans(int amount)
{
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xE76CF), &amount, 4);
}

void Totals::SetTotalCogs(int amount)
{
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xE76E8), &amount, 4);
}

void Totals::SetTotalBilbies(int amount)
{
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xE7701), &amount, 4);
}

void Totals::SetTotalThunderEggs(int amount)
{
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xE771A), &amount, 4);
}

void Totals::SetTotalPictureFrames(int amount)
{
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xE7733), &amount, 4);
}

int Totals::GameInfoLevelCount = 0;
int* Totals::GameInfoLevelIndexArrayPtr = nullptr;

void Totals::SetGameInfoLevels(int levels[], int levelCount)
{
    int* oldArrayPtr = GameInfoLevelIndexArrayPtr;

    GameInfoLevelIndexArrayPtr = new int[levelCount];
    memcpy(GameInfoLevelIndexArrayPtr, levels, levelCount * 4);
    int levelsPtr = (int)GameInfoLevelIndexArrayPtr;

    //Level array
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe55c3), &levelsPtr, 4);

    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5747), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe57d3), &levelsPtr, 4);

    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5a27), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5a48), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5af3), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5b20), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5b85), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5bc4), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5caf), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5cc3), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5d77), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5dfc), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5e29), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5e98), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5ebc), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5f2a), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5f51), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe5fa1), &levelsPtr, 4);

    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe6015), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe603f), &levelsPtr, 4);

    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe66ef), &levelsPtr, 4);
    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe67d7), &levelsPtr, 4);

    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe69fd), &levelsPtr, 4);

    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe6a43), &levelsPtr, 4);

    Core::SetReadOnlyValue((int*)(Core::moduleBase + 0xe6a9c), &levelsPtr, 4);

    //Level count
    *(int*)(Core::moduleBase + 0x26164c) = levelCount;

    // Delete/Unallocate the old allocated memory if it had previously been allocated
    // Deleting it after the new one has been set everywhere in the code, 
    // just incase so the game doesn't try to potentially access random memory
    if (oldArrayPtr)
        delete[] oldArrayPtr;
}
