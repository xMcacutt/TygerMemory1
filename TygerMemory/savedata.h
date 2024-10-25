#pragma once
#include "level.h"
#include "leveldata.h"

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

enum class HubFlag {
	AZoneMachineHidden,
	AZoneBossActivated,
	IceWallDestroyed,
	BZoneMachineHidden, 
	BZoneBossActivated,
	FlamingLogsDestroyed,
	CZoneMachineHidden,
	CZoneBossActivated,
	SmashRockDestroyed,
	DZoneMachineHidden,
	DZoneBossActivated,
	GeneratorActivated
};

enum class ProgressFlag {
	GotTalismanA,
	GotTalismanB,
	GotTalismanC,
	GotTalismanD,
	GotTalismanE,
	AZoneBossComplete,
	BZoneBossComplete,
	CZoneBossComplete,
	DZoneBossComplete,
	EZoneBossComplete
};

enum class TyAttribute {
	GotExtraHealth = 2,
	LearntToSwim = 0,
	LearntToDive = 1,
	GotAquarang = 13,
	GotBoomerang = 4,
	GotSecondRang = 3,
	GotFlamerang = 6,
	GotFrostyrang = 5,
	GotZappyrang = 12,
	GotZoomerang = 10,
	GotMultirang = 14,
	GotInfrarang = 11,
	GotMegarang = 9,
	GotKaboomerang = 7,
	GotChronorang = 15,
	GotDoomerang = 8
};

enum class Rang {
	GotAquarang = 9,
	GotBoomerang = 0,
	GotFlamerang = 2,
	GotFrostyrang = 1,
	GotZappyrang = 8,
	GotZoomerang = 6,
	GotMultirang = 10,
	GotInfrarang = 7,
	GotMegarang = 5,
	GotKaboomerang = 3,
	GotChronorang = 11,
	GotDoomerang = 4
};

class SaveData {
protected:
    uintptr_t baseAddress; 
public:
	SaveData(uintptr_t baseAddress);
    static SaveData getData();
	LevelData getLevelData(LevelCode levelCode);
	void setHubFlag(HubFlag flag, bool value);
	bool getHubFlag(HubFlag flag);
	void setProgressFlag(ProgressFlag flag, bool value);
	bool getProgressFlag(ProgressFlag flag);
	void setTyAttribute(TyAttribute flag, bool value);
	bool getTyAttribute(TyAttribute flag);
	void setFmvWatched(FMV fmv, bool value);
	bool getFmvWatched(FMV fmv);
	LevelCode getCurrentLevel();
	LevelCode getPreviousLevel();
	LevelCode getSavedLevel();
	int getPercentageCompletion();
	int getThunderEggCount();
	bool isHardcore();
	Zone getSavedZone();
	Rang getCurrentRang();
	int getLifeCount();
	// bool getPictureFrame(int index);
	// void setPictureFrame(int index, bool value);
	int getGameTimeSeconds();
	void setGameTimeSeconds(int seconds);
	int getEnemiesBitten();
	int getEnemiesZapped();
	int getEnemiesFlamed();
	int getCricketBatsBurnt();
	bool cheatsUsed();
	int getSkinId();
};

