#include "pch.h"
#include "gamestate.h"

bool GameState::onMainMenu()
{
    return false;
}

bool GameState::onLoadScreenOrMainMenu()
{
    return false;
}

void GameState::displayInGameMessage(std::string message)
{
}

void GameState::setCollectibleLinesVisibility(bool status)
{
}

bool GameState::getCollectibleLineVisibility()
{
    return false;
}

void GameState::setLevelSelectMenuVisibility(bool status)
{
}

bool GameState::getLevelSelectMenuVisibility()
{
    return false;
}

void GameState::forceMainMenu()
{
}

void GameState::forcePrepNewGame()
{
}

void GameState::forceNewGameScreen()
{
}

void GameState::forceNewGame(int countdown, int saveSlot)
{
}

void GameState::setNoIdle(bool status)
{
}

bool GameState::getNoIdle()
{
    return false;
}

void GameState::setNewGameText(std::string title, std::string bottomTitle, std::string bottomSubtitle)
{
}
