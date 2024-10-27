#include "pch.h"
#include "logging.h"

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
	if (logger_) {
		logger_(message, level);
	}
}