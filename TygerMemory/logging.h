#pragma once

#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

#include <functional>
#include <string>

enum class MemLogLevel {
	INFO,
	WARN,
	ERR
};

using LoggerFunction = void(*)(const std::string&, MemLogLevel);

class TYGERMEM Logging {
private:
	Logging() = default;
	Logging(const Logging&) = delete;
	Logging& operator=(const Logging&) = delete;

	std::function<void(const std::string&, MemLogLevel)> logger_;
public:
    static Logging& getInstance();
    void setLogger(std::function<void(const std::string&, MemLogLevel)> logger);
    void log(const std::string& message, MemLogLevel level = MemLogLevel::INFO);
};
