#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include "HeroState.h"
#include <variant>
#include "vector3f.h"
#include "sharedEnums.h"

class TYGERMEM Hero
{
public:
	static void setState(int state);
	static void setState(BullState state);
	static void setState(TyState state);
	static int getState();
	static Vector3f getPosition();
	static void setPosition(Vector3f coords);
	static int getHealth();
	static void setHealth(int health);
	static int getBreath();
	static void setBreath(int breath);
	static float getSwimSpeed();
	static void setSwimSpeed(float speed);
	static float getRunSpeed();
	static void setRunSpeed(float speed);
	static float getGravity();
	static void setGravity(float gravity);
	static float getAirSpeed();
	static void setAirSpeed(float speed);
	static float getDoubleJumpHeight();
	static void setDoubleJumpHeight(float height);
	static float getJumpHeight();
	static void setJumpHeight(float height);
	static float getLedgeGrabTolerance();
	static void setLedgeGrabTolerance(float tolerance);
	static float getGlideSpeed();
	static void setGlideSpeed(float speed);
	static bool getInvincibility();
	static void setInvincibility(bool status);
	static void kill();
	static void setMainSkin(int index);
	static void resetValues();
	static bool isBull();
	static bool isChargeBiting();

	/// <summary>
	/// Sets the level everywhere in the code that are hard coded to only make Bull spawn in outback.
	/// <para> This also requires editing the lv2 for the level you want bull to spawn in and changing Ty to the BushPig </para>
	/// </summary>
	static void SetBullHardCodeLevel(LevelCode level);
};
