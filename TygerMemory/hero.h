#pragma once
#include "HeroState.h"
#include <variant>
#include "vector3f.h"

class Hero
{
public:
	static void setState(int state);
	static int getState();
	static Vector3f getPosition();
	static void setPosition(Vector3f coords);
	static bool isBull();
};

