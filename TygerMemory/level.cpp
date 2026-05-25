#include "pch.h"
#include "level.h"
#include "minhook.h"

using LoadLevelFunc = void(__cdecl*)(int levelId);
using LevelChangedFunc = void(__thiscall*)(void* thisPtr, int levelId);
LevelChangedFunc levelChangedOrigin = nullptr;
static Event<LevelCode> g_onLevelChanged;

using UnkFinishLoadLevelFunc = void(__cdecl*)(float unk);
UnkFinishLoadLevelFunc levelLoadedOrigin = nullptr;
static Event<LevelCode> g_onLevelLoaded;

LevelCode Level::getCurrentLevel()
{
    return *(LevelCode*)(Core::moduleBase + 0x280594);
}

void Level::changeLevel(LevelCode level)
{
    auto loadLevel = ((LoadLevelFunc)(Core::moduleBase + 0x14EDE0));
    loadLevel((int)level);
}

void Level::addLevelLoadedListener(LevelChangedCallback callback)
{
    g_onLevelLoaded.subscribe(callback);
}

void Level::removeLevelLoadedListener(LevelChangedCallback callback)
{
    g_onLevelLoaded.unsubscribe(callback);
}

void Level::addLevelChangedListener(LevelChangedCallback callback)
{
    g_onLevelChanged.subscribe(callback);
}

void Level::removeLevelChangedListener(LevelChangedCallback callback)
{
    g_onLevelChanged.unsubscribe(callback);
}

void __fastcall levelChangedHook(void* thisPtr, void* edx, int levelId)
{
    g_onLevelChanged.invoke((LevelCode)levelId);
    levelChangedOrigin(thisPtr, levelId);
}

void __cdecl levelLoadedHook(float unk) {
    g_onLevelLoaded.invoke(SaveData::GetData()->CurrentLevel);
    levelLoadedOrigin(unk);
}

void Level::installHooks()
{
    void* target = (void*)(Core::moduleBase + 0xf7dd0);
    MH_CreateHook(target, &levelChangedHook, reinterpret_cast<void**>(&levelChangedOrigin));
	MH_EnableHook(target);
    target = (void*)(Core::moduleBase + 0x1c08f0);
    MH_CreateHook(target, &levelLoadedHook, reinterpret_cast<void**>(&levelLoadedOrigin));
    MH_EnableHook(target);
}