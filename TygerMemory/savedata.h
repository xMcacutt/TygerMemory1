#pragma once
#include "level.h"
#include "core.h"

class LevelData;

enum class Zone {
	ZZone,
	AZone,
	BZone,
	CZone,
	DZone,
	EZone,
};

enum class FMV {
	Prologue,
	CassFindsFirstTalisman,
	SlyRevealsTyAfterTalismans,
	CassSendsSlyStopTy,
	CassRevealsPlans,
	FrogTalisman,
	CockatooTalisman,
	PlatypusTalisman,
};

enum class TyAttribute {
	LearntToSwim = 0,
	LearntToDive = 1,
	GotExtraHealth = 2,
	GotSecondRang = 3,
	GotBoomerang = 4,
	GotFrostyrang = 5,
	GotFlamerang = 6,
	GotKaboomerang = 7,
	GotDoomerang = 8,
	GotMegarang = 9,
	GotZoomerang = 10,
	GotInfrarang = 11,
	GotZappyrang = 12,
	GotAquarang = 13,
	GotMultirang = 14,
	GotChronorang = 15,
};

enum class Rang {
	Aquarang = 9,
	Boomerang = 0,
	Flamerang = 2,
	Frostyrang = 1,
	Zappyrang = 8,
	Zoomerang = 6,
	Multirang = 10,
	Infrarang = 7,
	Megarang = 5,
	Kaboomerang = 3,
	Chronorang = 11,
	Doomerang = 4
};

typedef struct LevelData {
	char TimesEntered;
	char Opals[0x25];
	char Unk;
	bool ThunderEggs[0x8];
	bool GoldenCogs[0xA];
	char Bilbies[0x5];
	int TimeAttackBestSeconds;
	int TimeAttackLastSeconds;
	short TriggerSaves[0x14];
};

typedef struct ZoneData {
	bool Unlocked;
	bool Complete;
	bool BossActive;
};

typedef struct AttributeData {
	bool LearntToSwim;
	bool LearntToDive;
	bool GotExtraHealth;
	bool GotSecondRang;
	bool GotBoomerang;
	bool GotFrostyrang;
	bool GotFlamerang;
	bool GotKaboomerang;
	bool GotDoomerang;
	bool GotMegarang;
	bool GotZoomerang;
	bool GotInfrarang;
	bool GotZappyrang;
	bool GotAquarang;
	bool GotMultirang;
	bool GotChronorang;
};

typedef struct SaveDataStruct {
	int Size;
	int Magic;
	LevelCode SavedLevel;
	char PercentageCompletion;
	char ThunderEggCount;
	bool IsHardcore;
	bool IsDevMode;
	LevelData LevelData[24];
	int Unk;
	ZoneData ZoneData[6];
	short Unk2;
	LevelCode CurrentLevel;
	LevelCode PreviousLevel;
	Zone CurrentZone;
	Rang CurrentRang;
	AttributeData AttributeData;
	bool Talismans[5];
	bool TalismansPlaced[5];
	short Unk3;
	short Lives;
	char PictureFrames[0x41];
	char FmvsWatched;
	int PlayTimeSeconds;
	int EnemiesBitten;
	int EnemiesZapped;
	int EnemiesFlamed;
	int CricketBatsBurnt;
	bool CheatsUsed;
	bool CheatsUsed2;
	bool Unk4;
	bool Unk5;
	int SkinId;
};

class SaveData {
protected:
    uintptr_t baseAddress; 
public:
	SaveDataStruct* Data = new ((void*)(*(int*)(Core::moduleBase + 0x288730)))SaveDataStruct;
	void setFmvWatched(FMV fmv, bool value);
	bool getFmvWatched(FMV fmv);
	// bool getPictureFrame(int index);
	// void setPictureFrame(int index, bool value);
};

