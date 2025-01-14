#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include <string>
#include "sharedEnums.h"

class TYGERMEM Level
{
public:

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
};

