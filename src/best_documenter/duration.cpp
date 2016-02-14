#include "duration.h"

namespace best_documenter {
    const char* Duration::TIME_FORMAT = "%Y-%m-%dT%H:%M:%SZ";

    Duration Duration::fromDays(int32_t days) {
        auto hours        = std::chrono::hours(days * 24);
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(hours);
        return Duration(milliseconds);
    }

    Duration::Duration(const std::chrono::milliseconds& milliseconds) {
        milliseconds_ = milliseconds;
    }

    Duration::~Duration() {
    }

    std::string Duration::fetchSince() const {
        auto nowPoint   = std::chrono::system_clock::now();
        auto untilPoint = nowPoint - milliseconds_;
        auto timer      = std::chrono::system_clock::to_time_t(untilPoint);
        return format(&timer);
    }

    std::string Duration::fetchUntil() const {
        auto timer = std::time(nullptr);
        return format(&timer);
    }

    std::string Duration::format(const std::time_t* timer) const {
        auto tm = std::gmtime(timer);

        std::array<char, TIME_BUFF> buf;
        std::strftime(buf.data(), buf.size(), TIME_FORMAT, tm);

        return std::string(buf.data());
    }
}
