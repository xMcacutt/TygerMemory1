#include "pch.h"
#include "gamestate.h"
#include "core.h"
#include <thread>

bool GameState::onMainMenu()
{
    return !*(bool*)(Core::moduleBase + 0x286641);
}

bool GameState::onLoadScreenOrMainMenu()
{
    return *(long*)(Core::moduleBase + 0x27EBF0) == 0;
}

void GameState::displayInGameMessage(std::string message, int seconds = 0)
{
    *(char*)(Core::moduleBase + 0x286C54) = (char)0x1;
    *(char*)(Core::moduleBase + 0x289048) = (char)0x1;

    auto previousState = seconds == 0 ? PauseMenuScreen::Unpaused : PauseMenuScreen::HardDiskRemoved;
    setPauseMenuScreen(PauseMenuScreen::HardDiskRemoved);
    setPreviousPauseMenuScreen(previousState);
    
    auto addr = Core::getPointerAddress(0x293B14, { 0x4 });
    auto pointer = *(uintptr_t*)(addr) == 0;
    *(uintptr_t*)(Core::moduleBase + 0x286D18) = pointer;
    *(uintptr_t*)(Core::moduleBase + 0x287580) = pointer;

    addr = Core::getPointerAddress(0x529220, { 0x1D });
    std::string footer = seconds == 0 ? "Press ESC To Continue" : std::to_string(seconds);
    auto fullMessage = message + "\n\n" + footer + "\0";
    *(std::string*)(addr) = fullMessage;

    *(char*)(Core::moduleBase + 0x2887FC) = (char)0x0;

    if (seconds == 0)
        return;

    std::thread([seconds, addr, message]() {

        for (int t = seconds; t > 0; t--) {
            auto fullMessage = message + "\n\n" + std::to_string(t) + "\0";
            *(std::string*)(addr) = fullMessage;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        *(char*)(Core::moduleBase + 0x286C54) = (char)0x0;
        *(char*)(Core::moduleBase + 0x289048) = (char)0x0;
        }).detach();
}

void GameState::setCollectibleLinesVisibility(bool status)
{
    *(bool*)(Core::moduleBase + 0x28AB68) = status;
}

bool GameState::getCollectibleLineVisibility()
{
    return *(bool*)(Core::moduleBase + 0x28AB68);
}

void GameState::setLevelSelectMenuVisibility(bool status)
{
    auto addr = Core::getPointerAddress(0x286CB0, { 0xCA4 });
    *(bool*)(Core::moduleBase + addr) = status;
    *(bool*)(Core::moduleBase + addr + 2) = status;
}

bool GameState::getLevelSelectMenuVisibility()
{
    auto addr = Core::getPointerAddress(0x286CB0, { 0xCA4 });
    return *(bool*)(addr);
}

void GameState::setFrontEndMenuScreen(FrontEndScreen screen)
{
    *(FrontEndScreen*)(Core::moduleBase + 0x285B8C) = screen;
}

FrontEndScreen GameState::getFrontEndMenuScreen()
{
    return *(FrontEndScreen*)(Core::moduleBase + 0x285B8C);
}

void GameState::setPauseMenuScreen(PauseMenuScreen screen)
{
    *(PauseMenuScreen*)(Core::moduleBase + 0x286800) = screen;
}

PauseMenuScreen GameState::getPauseMenuScreen()
{
    return *(PauseMenuScreen*)(Core::moduleBase + 0x286800);
}

void GameState::setPreviousPauseMenuScreen(PauseMenuScreen screen)
{
    *(PauseMenuScreen*)(Core::moduleBase + 0x286804) = screen;
}

PauseMenuScreen GameState::getPreviousPauseMenuScreen()
{
    return *(PauseMenuScreen*)(Core::moduleBase + 0x286804);
}

void GameState::forceMainMenu()
{
    *(float*)(Core::moduleBase + 0x264248) = 0.01f;
    *(bool*)(Core::moduleBase + 0x286C54) = false;
    setFrontEndMenuScreen(FrontEndScreen::MainMenu);
    *(int*)(Core::moduleBase + 0x288A74) = 0x8;
}

void GameState::forcePrepNewGame(int slot)
{
    *(int*)(Core::moduleBase + 0x273838) = slot;
    *(int*)(Core::moduleBase + 0x273840) = slot;
    *(int*)(Core::moduleBase + 0x28E6C4) = slot;
    *(int*)(Core::moduleBase + 0x52F2B8) = slot;
    *(int*)(Core::moduleBase + 0x27383C) = 0x0;
    *(int*)(Core::moduleBase + 0x52F2BC) = Core::moduleBase + 0x273844;
    *(int*)(Core::moduleBase + 0x52F2A4) = 0x2;
    *(int*)(Core::moduleBase + 0x273F74) = 0x9;
}

void GameState::forceNewGameScreen()
{
    setFrontEndMenuScreen(FrontEndScreen::MainMenu);
    *(int*)(Core::moduleBase + 0x286640) = 0x1;
    *(int*)(Core::moduleBase + 0x286650) = 0x6;
}

void GameState::forceNewGame(int countdown, int saveSlot)
{
    *(int*)(Core::moduleBase + 0x2864BC) = 0x2;
}

void GameState::setNoIdle(bool status)
{
    *(bool*)(Core::moduleBase + 0x526C08) = true;
}

bool GameState::getNoIdle()
{
    return *(bool*)(Core::moduleBase + 0x526C08);
}

void GameState::setNewGameText(std::string title, std::string bottomTitle, std::string bottomSubtitle)
{
}
