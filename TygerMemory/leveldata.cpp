#include "pch.h"
#include "leveldata.h"
#include "core.h"

LevelData::LevelData(uintptr_t levelBaseAddress) : baseAddress(levelBaseAddress) { }

void LevelData::setBilby(int bilbyIndex, bool value, bool isFinal = false) {
	if (bilbyIndex > 4)	{
		Logging::getInstance().log(LogLevel::WARN, "Attempted to access bilby out of range.");
		return;
	}
	char valueToSet = isFinal && value ? 0x3 : value ? 0x1 : 0x0;
	Core::tryWriteMemory<char>(baseAddress + 0x3A + bilbyIndex, false, valueToSet);
}

bool LevelData::getBilby(int bilbyIndex) {
	if (bilbyIndex > 4) {
		Logging::getInstance().log(LogLevel::WARN, "Attempted to access bilby out of range.");
		return false;
	}
	return Core::tryReadMemory<int>(baseAddress + 0x3A + bilbyIndex, false) != 0;
}

void LevelData::setThunderEgg(int eggIndex, bool value) {
	if (eggIndex > 7) {
		Logging::getInstance().log(LogLevel::WARN, "Attempted to access thunder egg out of range.");
		return;
	}
	Core::tryWriteMemory<bool>(baseAddress + 0x28 + eggIndex, false, value);
}

bool LevelData::getThunderEgg(int eggIndex) {
	if (eggIndex > 7) {
		Logging::getInstance().log(LogLevel::WARN, "Attempted to access thunder egg out of range.");
		return false;
	}
	return Core::tryReadMemory<bool>(baseAddress + 0x28 + eggIndex, false);
}

void LevelData::setCog(int cogIndex, bool value) {
	if (cogIndex > 7) {
		Logging::getInstance().log(LogLevel::WARN, "Attempted to access cog out of range.");
		return;
	}
	Core::tryWriteMemory<bool>(baseAddress + 0x28 + cogIndex, false, value);
}

bool LevelData::getCog(int cogIndex) {
	if (cogIndex > 7) {
		Logging::getInstance().log(LogLevel::WARN, "Attempted to access cog out of range.");
		return false;
	}
	return Core::tryReadMemory<bool>(baseAddress + 0x28 + cogIndex, false);
}

int LevelData::getTimesEntered() {
	return Core::tryReadMemory<char>(baseAddress, false);
}