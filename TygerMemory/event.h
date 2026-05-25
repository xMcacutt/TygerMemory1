#pragma once
#include <functional>
#include <vector>

template<typename... Args>
class Event {
public:
    using Handler = void(*)(Args...);
    void subscribe(Handler handler) {
        handlers.push_back(handler);
    }
    void unsubscribe(Handler handler) {
        handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
    }
    void invoke(Args... args) {
        for (auto handler : handlers)
            handler(args...);
    }
private:
    std::vector<Handler> handlers;
};