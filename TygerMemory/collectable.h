#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include "sharedEnums.h"
#include "colour.h"

struct LevelInfo
{
	char* LevelIDStr;
	Element Element;
	Zone Zone;
	Talisman Talisman;
	bool ShowExtendedTotals;
	bool ShowOpal;
	short PaddingMaybe;
};

class TYGERMEM Collectable
{
public:
	/// <summary>
	/// All the info used for the collectables and level select
	/// </summary>
	/// <returns>Returns a array with 24 elements, use the level code enum for the index</returns>
	static LevelInfo* GetLevelInfoArray();

	/// <summary>
	/// Gets a array to the the thunder egg particle colours. 
	/// <para>You can access and set each thunder egg particle colour element like: </para>
	/// <para>ParticleColourVar[Element:Fire] = RGBA{ 0.8f, 0.8f, 0.0f, 1.0f } </para>
	/// <para>or one specific colour channel ParticleColourVar[Element:Ice].R = 0.8f.</para>
	/// </summary>
	/// <returns></returns>
	static RGBA* GetThunderEggParticleColours();

	/// <summary>
	/// Sets the read only memory golden cog particle colour
	/// </summary>
	static void SetGoldenCogParticleColours(RGBA colour);
};

