#pragma once
#include <string>

enum class LevelCode {
	Z1,
	Z2,
	Z3,
	Z4,
	A1,
	A2,
	A3,
	A4,
	B1,
	B2,
	B3,
	B4,
	C1,
	C2,
	C3,
	C4,
	D1,
	D2,
	D3,
	D4,
	E1,
	E2,
	E3,
	E4,
};

class Level
{
public:
	static LevelCode getCurrentLevel();
	static void changeLevel(LevelCode code);
};

