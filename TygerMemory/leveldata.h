#pragma once
#include "pch.h"
#include "savedata.h"

class LevelData {
protected:
	uintptr_t baseAddress;
public:
	LevelData(uintptr_t addr);
	void setBilby(int bilbyIndex, bool value, bool isFinal);
	bool getBilby(int bilbyIndex);
	void setThunderEgg(int eggIndex, bool value);
	bool getThunderEgg(int eggIndex);
	void setCog(int cogIndex, bool value);
	bool getCog(int cogIndex);
	// void setOpal(int opalIndex, bool value);
	// bool getOpal(int opalIndex);
	int getTimesEntered();
};