#pragma once

#include <array>
#include <chrono>
#include <cinttypes>
#include <ctime>
#include <string>

namespace best_documenter {
    class Duration {
    public:
        static const std::size_t TIME_BUFF = 256;
        static const char*       TIME_FORMAT;
        static Duration fromDays(int32_t days);

        Duration(const std::chrono::milliseconds& milliseconds);
        ~Duration();

        std::string fetchSince() const;
        std::string fetchUntil() const;

    private:
        std::chrono::milliseconds milliseconds_;

        std::string format(const std::time_t* timer) const;
    };
}
