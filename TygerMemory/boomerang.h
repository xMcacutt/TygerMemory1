#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

class TYGERMEM Boomerang
{
public:
	// Sets how long crates will burn for after being hit with a flamerang.
	// A value of 60 seems to be roughly 1 second
	// Default value is 120. 
	static void SetCrateBurnTime(int burnTime = 120);
};

