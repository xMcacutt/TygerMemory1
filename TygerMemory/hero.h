#pragma once
#include "HeroState.h"

class hero
{
public:
	static void setHeroState(HeroState state);
	static void setHeroState(BullState state);
	static int getHeroState();
};

