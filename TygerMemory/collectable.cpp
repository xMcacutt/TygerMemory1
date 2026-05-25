#include "pch.h"
#include "collectable.h"
#include "core.h"
#include "minhook.h"

using ThunderEggCollectedFunction = void(__thiscall*)(void* thisPtr, int id);
ThunderEggCollectedFunction thunderEggCollectedOrigin = nullptr;
Event<int> g_onThunderEggCollected;

using GoldenCogCollectedFunction = void(__thiscall*)(void* thisPtr, int id);
GoldenCogCollectedFunction goldenCogCollectedOrigin = nullptr;
Event<int> g_onGoldenCogCollected;

using BilbyCollectedFunction = void(__thiscall*)(void* thisPtr, int id);
BilbyCollectedFunction bilbyCollectedOrigin = nullptr;
Event<int> g_onBilbyCollected;

using PictureFrameCollectedFunction = void(__thiscall*)(void* thisPtr, int id);
PictureFrameCollectedFunction pictureFrameCollectedOrigin = nullptr;
Event<int> g_onPictureFrameCollected;

using OpalCollectedFunction = void(__cdecl*)(uintptr_t opalPtr);
OpalCollectedFunction opalCollectedOrigin = nullptr;
Event<int> g_onOpalCollected;

using TalismanCollectedFunction = void(__thiscall*)(void* thisPtr, int id, void* arg);
TalismanCollectedFunction talismanCollectedOrigin = nullptr;
Event<int> g_onTalismanCollected;

LevelInfo* Collectable::GetLevelInfoArray()
{
    return (LevelInfo*)(Core::moduleBase + 0x26F6D0);
}

RGBA* Collectable::GetThunderEggParticleColours()
{
    return (RGBA*)(Core::moduleBase + 0x2701B0);
}

void Collectable::SetGoldenCogParticleColours(RGBA colour)
{
    Core::SetReadOnlyValue((void*)(Core::moduleBase + 0x209C60), &colour, sizeof(RGBA));
}

void Collectable::addThunderEggCollectedListener(ThunderEggCollected callback)
{
    g_onThunderEggCollected.subscribe(callback);
}

void Collectable::removeThunderEggCollectedListener(ThunderEggCollected callback)
{
    g_onThunderEggCollected.unsubscribe(callback);
}

void Collectable::addGoldenCogCollectedListener(GoldenCogCollected callback)
{
    g_onGoldenCogCollected.subscribe(callback);
}

void Collectable::removeGoldenCogCollectedListener(GoldenCogCollected callback)
{
    g_onGoldenCogCollected.unsubscribe(callback);
}

void Collectable::addBilbyCollectedListener(BilbyCollected callback)
{
    g_onBilbyCollected.subscribe(callback);
}

void Collectable::removeBilbyCollectedListener(BilbyCollected callback)
{
    g_onBilbyCollected.unsubscribe(callback);
}

void Collectable::addPictureFrameCollectedListener(PictureFrameCollected callback)
{
    g_onPictureFrameCollected.subscribe(callback);
}

void Collectable::removePictureFrameCollectedListener(PictureFrameCollected callback)
{
    g_onPictureFrameCollected.unsubscribe(callback);
}

void Collectable::addOpalCollectedListener(OpalCollected callback)
{
    g_onOpalCollected.subscribe(callback);
}

void Collectable::removeOpalCollectedListener(OpalCollected callback)
{
    g_onOpalCollected.unsubscribe(callback);
}

void Collectable::addTalismanCollectedListener(TalismanCollected callback)
{
    g_onTalismanCollected.subscribe(callback);
}

void Collectable::removeTalismanCollectedListener(TalismanCollected callback)
{
    g_onTalismanCollected.unsubscribe(callback);
}

void __fastcall pictureFrameCollectedHook(void* thisPtr, void* edx, int id)
{
    g_onPictureFrameCollected.invoke(id);
    pictureFrameCollectedOrigin(thisPtr, id);
}

void __fastcall bilbyCollectedHook(void* thisPtr, void* edx, int id)
{
    g_onBilbyCollected.invoke(id);
    bilbyCollectedOrigin(thisPtr, id);
}

void __fastcall goldenCogCollectedHook(void* thisPtr, void* edx, int id)
{
    g_onGoldenCogCollected.invoke(id);
    goldenCogCollectedOrigin(thisPtr, id);
}

void __fastcall thunderEggCollectedHook(void* thisPtr, void* edx, int id)
{
    g_onThunderEggCollected.invoke(id);
    thunderEggCollectedOrigin(thisPtr, id);
}

void __cdecl opalCollectedHook(uintptr_t opalPtr)
{
    uintptr_t* opals = *(uintptr_t**)(Core::moduleBase + 0x28ab7c);
    for (int opalIndex = 0; opalIndex < 300; opalIndex++) {
        if (opals[opalIndex] == opalPtr - 0x44) {
            g_onOpalCollected.invoke(opalIndex);
            break;
		}
    }
    opalCollectedOrigin(opalPtr);
}

void __fastcall talismanCollectedHook(void* thisPtr, void* edx, int id, void* arg)
{
    int level = (int)SaveData::GetData()->CurrentLevel;
    int* table = (int*)(Core::moduleBase + 0x26F6DC);
    int index = *(int*)((char*)table + level * 20);
    g_onTalismanCollected.invoke(index);
    if (index == 4)
		GameState::onGameComplete();
    talismanCollectedOrigin(thisPtr, id, arg);
}

void Collectable::installHooks()
{
    void* target = (void*)(Core::moduleBase + 0xf7f00);
    MH_CreateHook(target, &pictureFrameCollectedHook, reinterpret_cast<void**>(&pictureFrameCollectedOrigin));
    MH_EnableHook(target);
	target = (void*)(Core::moduleBase + 0xf7ac0);
    MH_CreateHook(target, &bilbyCollectedHook, reinterpret_cast<void**>(&bilbyCollectedOrigin));
	MH_EnableHook(target);
    target = (void*)(Core::moduleBase + 0xf6cc0);
	MH_CreateHook(target, &goldenCogCollectedHook, reinterpret_cast<void**>(&goldenCogCollectedOrigin));
	MH_EnableHook(target);
    target = (void*)(Core::moduleBase + 0xf6e80);
    MH_CreateHook(target, &thunderEggCollectedHook, reinterpret_cast<void**>(&thunderEggCollectedOrigin));
	MH_EnableHook(target);
    target = (void*)(Core::moduleBase + 0x12e8c0);
    MH_CreateHook(target, &opalCollectedHook, reinterpret_cast<void**>(&opalCollectedOrigin));
	MH_EnableHook(target);
    target = (void*)(Core::moduleBase + 0xf7c90);
	MH_CreateHook(target, &talismanCollectedHook, reinterpret_cast<void**>(&talismanCollectedOrigin));
	MH_EnableHook(target);
}