#pragma once
#include <functional>
#include <string>
#include <mutex>

enum class LogLevel {
    INFO,
    WARN,
    ERR
};

class Logging
{
public:
    static Logging& getInstance();
    void setLogger(std::function<void(LogLevel level, const std::string&)> logger);
	void log(LogLevel level, const std::string& message);
private:
    Logging() = default; // Private constructor
    Logging(const Logging&) = delete; // Prevent copying
    Logging& operator=(const Logging&) = delete; // Prevent assignment

    std::function<void(LogLevel, const std::string&)> logger_; // User-defined logger
    std::mutex mutex_; // For thread safety
};
