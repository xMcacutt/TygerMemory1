#pragma once
#include <string>

class Level
{
public:
	static int getCurrentLevelId();
	static int getPreviousLevelId();
	static void changeLevel();
};

struct LevelData
{
public:
	int id;
	std::string code;
	std::string defaultName;
};