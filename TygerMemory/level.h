#pragma once
#include <string>

class Level
{
public:
	static int getCurrentLevelId();
	static int getPreviousLevelId();
};

struct LevelData
{
public:
	int id;
	std::string code;
};
