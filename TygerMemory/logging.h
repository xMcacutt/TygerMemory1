#pragma once
#include <functional>
#include <string>

class logging
{
public:
    static logging& getInstance();
    void setLogger(std::function<void(LogLevel, const std::string&)> logger);
	void log(LogLevel level, const std::string& message);
private:
    logging() = default; // Private constructor
    logging(const logging&) = delete; // Prevent copying
    logging& operator=(const logging&) = delete; // Prevent assignment

    std::function<void(LogLevel, const std::string&)> logger_; // User-defined logger
    std::mutex mutex_; // For thread safety
};

enum class LogLevel {
    INFO,
    WARN,
    ERR
};

