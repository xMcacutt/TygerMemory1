#pragma once

#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

#include <functional>
#include <string>
#include <mutex>

enum class MemLogLevel {
	INFO,
	WARN,
	ERR
};

using LoggerFunction = void(*)(const std::string&, MemLogLevel);

class TYGERMEM Logging {
private:
	Logging() = default; // Private constructor
	Logging(const Logging&) = delete; // Prevent copying
	Logging& operator=(const Logging&) = delete; // Prevent assignment

	std::function<void(const std::string&, MemLogLevel)> logger_; // User-defined logger
	std::mutex mutex_; // For thread safety
public:
    static Logging& getInstance();
    void setLogger(std::function<void(const std::string&, MemLogLevel)> logger);
    void log(const std::string& message, MemLogLevel level = MemLogLevel::INFO);
};
