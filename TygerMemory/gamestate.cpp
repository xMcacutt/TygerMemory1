#include "pch.h"
#include "gamestate.h"
#include "core.h"

bool GameState::onMainMenu()
{
    return !Core::tryReadMemory<bool>(0x286641, true);
}

bool GameState::onLoadScreenOrMainMenu()
{
    return Core::tryReadMemory<long>(0x27EBF0, true) == 0;
}

void GameState::displayInGameMessage(std::string message, int seconds = 0)
{
    Core::tryWriteMemory<char>(0x286C54, true, (char)0x1);
    Core::tryWriteMemory<char>(0x289048, true, (char)0x1);

    auto previousState = seconds == 0 ? PauseMenuScreen::Unpaused : PauseMenuScreen::HardDiskRemoved;
    setPauseMenuScreen(PauseMenuScreen::HardDiskRemoved);
    setPreviousPauseMenuScreen(previousState);
    
    auto addr = Core::getPointerAddress(0x293B14, { 0x4 });
    auto pointer = Core::tryReadMemory<uintptr_t>(addr, false);
    Core::tryWriteMemory<uintptr_t>(0x286D18, true, pointer);
    Core::tryWriteMemory<uintptr_t>(0x287580, true, pointer);

    addr = Core::getPointerAddress(0x529220, { 0x1D });
    std::string footer = seconds == 0 ? "Press ESC To Continue" : std::to_string(seconds);
    auto fullMessage = message + "\n\n" + footer + "\0";
    Core::tryWriteMemory<std::string>(addr, false, fullMessage);

    Core::tryWriteMemory<char>(0x2887FC, true, (char)0x0);

    if (seconds == 0)
        return;

    std::thread([seconds, addr, message]() {

        for (int t = seconds; t > 0; t--) {
            auto fullMessage = message + "\n\n" + std::to_string(t) + "\0";
            Core::tryWriteMemory<std::string>(addr, false, fullMessage);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        Core::tryWriteMemory<char>(0x286C54, true, (char)0x0);
        Core::tryWriteMemory<char>(0x289048, true, (char)0x0);
        }).detach();
}

void GameState::setCollectibleLinesVisibility(bool status)
{
    Core::tryWriteMemory<bool>(0x28AB68, true, status);
}

bool GameState::getCollectibleLineVisibility()
{
    return Core::tryReadMemory<bool>(0x28AB68, true);
}

void GameState::setLevelSelectMenuVisibility(bool status)
{
    auto addr = Core::getPointerAddress(0x286CB0, { 0xCA4 });
    Core::tryWriteMemory<bool>(addr, false, status);
    Core::tryWriteMemory<bool>(addr + 2, false, status);
}

bool GameState::getLevelSelectMenuVisibility()
{
    auto addr = Core::getPointerAddress(0x286CB0, { 0xCA4 });
    return Core::tryReadMemory<bool>(addr, true);
}

void GameState::setFrontEndMenuScreen(FrontEndScreen screen)
{
    Core::tryWriteMemory<FrontEndScreen>(0x285B8C, true, screen);
}

FrontEndScreen GameState::getFrontEndMenuScreen()
{
    return Core::tryReadMemory<FrontEndScreen>(0x285B8C, true);
}

void GameState::setPauseMenuScreen(PauseMenuScreen screen)
{
    Core::tryWriteMemory<PauseMenuScreen>(0x286800, true, screen);
}

PauseMenuScreen GameState::getPauseMenuScreen()
{
    return Core::tryReadMemory<PauseMenuScreen>(0x286800, true);
}

void GameState::setPreviousPauseMenuScreen(PauseMenuScreen screen)
{
    Core::tryWriteMemory<PauseMenuScreen>(0x286804, true, screen);
}

PauseMenuScreen GameState::getPreviousPauseMenuScreen()
{
    return Core::tryReadMemory<PauseMenuScreen>(0x286804, true);
}

void GameState::forceMainMenu()
{
    Core::tryWriteMemory<float>(0x264248, true, 0.01f);
    Core::tryWriteMemory<bool>(0x286C54, true, true);
    setFrontEndMenuScreen(FrontEndScreen::MainMenu);
    Core::tryWriteMemory<int>(0x288A74, true, 0x8);
}

void GameState::forcePrepNewGame(int slot)
{
    Core::tryWriteMemory<int>(0x273838, true, slot);
    Core::tryWriteMemory<int>(0x273840, true, slot);
    Core::tryWriteMemory<int>(0x28E6C4, true, slot);
    Core::tryWriteMemory<int>(0x52F2B8, true, slot);
    Core::tryWriteMemory<int>(0x27383C, true, 0x0);
    Core::tryWriteMemory<int>(0x52F2BC, true, Core::moduleBase + 0x273844);
    Core::tryWriteMemory<int>(0x52F2A4, true, 0x2);
    Core::tryWriteMemory<int>(0x273F74, true, 0x9);
}

void GameState::forceNewGameScreen()
{
    setFrontEndMenuScreen(FrontEndScreen::MainMenu);
    // Force select new game
    Core::tryWriteMemory(0x286640, true, 0x1);
    // Force enter new game screen
    Core::tryWriteMemory(0x286650, true, 0x6);
}

void GameState::forceNewGame(int countdown, int saveSlot)
{
    Core::tryWriteMemory(0x2864BC, true, 0x2);
}

void GameState::setNoIdle(bool status)
{
    Core::tryWriteMemory<bool>(0x526C08, true, true);
}

bool GameState::getNoIdle()
{
    return Core::tryReadMemory<bool>(0x526C08, true);
}

void GameState::setNewGameText(std::string title, std::string bottomTitle, std::string bottomSubtitle)
{
}
