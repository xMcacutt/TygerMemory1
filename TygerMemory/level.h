#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include <string>
#include "sharedEnums.h"
#include "core.h"
#include "event.h"
#include "gamestate.h"

class TYGERMEM Level
{
public:
	using LevelLoadedCallback = void(*)(LevelCode);
	static void addLevelLoadedListener(LevelLoadedCallback callback);
	static void removeLevelLoadedListener(LevelLoadedCallback callback);
	using LevelChangedCallback = void(*)(LevelCode);
	static void addLevelChangedListener(LevelChangedCallback callback);
	static void removeLevelChangedListener(LevelChangedCallback callback);
	static inline std::unordered_map<std::string, LevelCode> stringToLevelCode{
		{"a1", LevelCode::A1},
		{"a2", LevelCode::A2},
		{"a3", LevelCode::A3},
		{"a4", LevelCode::A4},
		{"b1", LevelCode::B1},
		{"b2", LevelCode::B2},
		{"b3", LevelCode::B3},
		{"b4", LevelCode::B4},
		{"c1", LevelCode::C1},
		{"c2", LevelCode::C2},
		{"c3", LevelCode::C3},
		{"c4", LevelCode::C4},
		{"d1", LevelCode::D1},
		{"d2", LevelCode::D2},
		{"d3", LevelCode::D3},
		{"d4", LevelCode::D4},
		{"e1", LevelCode::E1},
		{"e2", LevelCode::E2},
		{"e3", LevelCode::E3},
		{"e4", LevelCode::E4},
		{"z1", LevelCode::Z1},
		{"z2", LevelCode::Z2},
		{"z3", LevelCode::Z3},
		{"z4", LevelCode::Z4},
	};

	/// <summary>
	///		Gets the current level.
	/// </summary>
	/// <returns>
	///		The level code of the current level.
	/// </returns>
	static LevelCode getCurrentLevel();

	/// <summary>
	///		Warps the player directly to a given level.
	///		<para>Note* this only works if the player is not on the main menu or an fmv cutscene</para>
	/// </summary>
	/// <param name="code:">
	///		<para>The LevelCode of the level to warp to.</para>
	/// </param>
	static void changeLevel(LevelCode code);
private:
	friend class Hooks;
	static void installHooks();
};

