#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include "vector4f.h"
#include "sharedEnums.h"

struct MapTransform {
	Vector4f Scale;
	Vector4f Position;
	// In radians
	Vector4f Rotation;
};

class TYGERMEM Minimap
{
public:
	/// <summary>
	/// Gets the minimap transform for the specified level
	/// <para> For the rotation X rotates vertically across the center position</para>
	/// <para> Y spins around the center position</para>
	/// <para> Z rotates it horizontally across the center position</para>
	/// </summary>
	/// <returns></returns>
	static MapTransform* GetMapTransform(LevelCode level);
	/// <summary>
	/// Sets the minimap transform for the specified level
	/// </summary>
	/// <param name="transform"></param>
	static void SetMapTransform(LevelCode level, MapTransform* transform);
	/// <summary>
	/// Changes which level that the minimap won't update the positon of Ty moving around (usually set to the final cutscene level where you won't move anyways)
	/// <para> If you don't want any level to be disabled then just set it to something like -1 or something like 24 or higher </para>
	/// </summary>
	/// <param name="levelIndex"></param>
	static void SetDisabledMapLevel(char levelIndex);
};

