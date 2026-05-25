#pragma once
#include "core.h"
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

class TYGERMEM Cheats
{
public:
	static void invincibility();
	static void elementalRangs();
	static void technoRangs();
	static void levelMenu();
	static void collectibleLines();
};

