#include "pch.h"
#include "hooks.h"
#include "minhook.h"

void Hooks::installAllHooks() {
	MH_Initialize();
	Level::installHooks();
	Hero::installHooks();
	GameState::installHooks();
	Collectable::installHooks();
	Objective::installHooks();
	Lv2::installHooks();
}