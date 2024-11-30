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
