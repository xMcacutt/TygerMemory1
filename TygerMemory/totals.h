#pragma once

#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

enum TotalType {
	Level,
	Global
};

class TYGERMEM Totals
{
public:
	static int getCurrentThunderEggCount(TotalType totalType);
	static int getCurrentCogCount(TotalType totalType);
	static int getCurrentBilbyCount(TotalType totalType);
	static int getCurrentFrameCount(TotalType totalType);
	static int getCurrentOpalCount(bool thisLoad);
	static int getCurrentRangCount();
	static int getCurrentTalismanCount();

	// Sets the total amount of opals for the full game totals
	static void SetTotalOpals(int amount);
	// Sets the total amount of rainbow scales for the full game totals
	static void SetTotalRainbowScales(int amount);
	// Sets the total amount of talismans for the full game totals
	static void SetTotalTalismans(int amount);
	// Sets the total amount of golden cogs for the full game totals
	static void SetTotalCogs(int amount);
	// Sets the total amount of bilbies for the full game totals
	static void SetTotalBilbies(int amount);
	// Sets the total amount of thunder eggs for the full game totals
	static void SetTotalThunderEggs(int amount);
	// Sets the total amount of picture frames for the full game totals
	static void SetTotalPictureFrames(int amount);
};

