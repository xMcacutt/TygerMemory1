#include "pch.h"
#include "logging.h"
#include <mutex>

Logging& Logging::getInstance()
{
	static Logging instance;
	return instance;
}

void Logging::setLogger(std::function<void(LogLevel, const std::string&)> logger)
{
	logger_ = logger;
}

void Logging::log(LogLevel level, const std::string& message) {
	std::lock_guard<std::mutex> lock(mutex_); // Ensure thread safety
	if (logger_) {
		logger_(level, message);
	}
}