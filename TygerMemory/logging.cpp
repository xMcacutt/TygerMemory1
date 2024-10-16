#include "pch.h"
#include "logging.h"
#include <mutex>

logging& logging::getInstance()
{
    static logging instance;
    return instance;
}

void logging::setLogger(std::function<void(LogLevel, const std::string&)> logger)
{
	logger_ = logger;
}

void logging::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_); // Ensure thread safety
    if (logger_) {
        logger_(level, message);
    }
}