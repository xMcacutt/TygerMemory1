#include "pch.h"
#include "logging.h"
#include <mutex>

Logging& Logging::getInstance()
{
	static Logging instance;
	return instance;
}

void Logging::setLogger(std::function<void(const std::string&, MemLogLevel)> logger)
{
	logger_ = logger;
}

void Logging::log(const std::string& message, MemLogLevel level) {
	std::lock_guard<std::mutex> lock(mutex_); // Ensure thread safety
	if (logger_) {
		logger_(message, level);
	}
}