#pragma once

#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

#include <string>


class TYGERMEM Logging {
public:
    static void del();
    static void log(const std::string& message);
};
