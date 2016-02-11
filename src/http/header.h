#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

namespace http {
    using HeaderMap = std::unordered_map<std::string, std::string>;

    class Header {
    public:
        static std::shared_ptr<HeaderMap> parse(const std::string& rawHeader);
    };
}
