#pragma once
#include <string>
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

class TYGERMEM Objective
{
public:
	using ObjectiveCountIncremented = void(*)(std::string, int);
	static void addObjectiveCountIncrementedListener(ObjectiveCountIncremented callback);
	static void removeObjectiveCountIncrementedListener(ObjectiveCountIncremented callback);
private:
	friend class Hooks;
	static void installHooks();
};