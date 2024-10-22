#pragma once
#include "pch.h"
#include <string>

class GameState
{
public:
	static bool onMainMenu();
	static bool onLoadScreenOrMainMenu();
	static void displayInGameMessage(std::string message);
	static void setCollectibleLinesVisibility(bool status);
	static bool getCollectibleLineVisibility();
	static void setLevelSelectMenuVisibility(bool status);
	static bool getLevelSelectMenuVisibility();
	static void forceMainMenu();
	static void forcePrepNewGame();
	static void forceNewGameScreen();
	static void forceNewGame(int countdown, int saveSlot);
	static void setNoIdle(bool status);
	static bool getNoIdle();
	static void setNewGameText(std::string title, std::string bottomTitle, std::string bottomSubtitle);
};

