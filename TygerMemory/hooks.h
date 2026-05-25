#pragma once
#include "level.h"
#include "hero.h"
#include "collectable.h"
#include "objective.h"
#include "lv2.h"

class Hooks {
private:
	friend class Core;
	static void installAllHooks();
};