#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include <unordered_map>
#include <string>
#include "core.h"
#include "level.h"

struct Lv2Data
{
    char  name[0x20];
    char* pFileMem;
    bool  bFileMemAllocated;
    char  pad25[0x03];
    int   fileSize;
    void* entries;
    int   entryCount;
    int   unk34;
    int   auxCount;
};

class TYGERMEM Lv2 {
public:
    static void addGlobalEntry(const std::string& identifier, const std::string& data) {
		globalEntries[identifier] = data;
    }
    static void removeGlobalEntry(const std::string& identifier) {
		while (globalEntries.find(identifier) != globalEntries.end())
    		globalEntries.erase(identifier);
    }
    static void addLevelEntry(LevelCode level, const std::string& identifier, std::string& data) {
        levelEntries[level][identifier] = data;
    }
    static void removeLevelEntry(LevelCode level, const std::string& identifier) {
        while (levelEntries[level].find(identifier) != levelEntries[level].end())
            levelEntries[level].erase(identifier);
    }
private:
    static inline std::unordered_map<LevelCode, std::unordered_map<std::string, std::string>> levelEntries;
    static inline std::unordered_map<std::string, std::string> globalEntries;
    friend class Hooks;
	static void mergeData(Lv2Data* mainData);
    static void installHooks();
};
