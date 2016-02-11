#pragma once

#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

namespace http {
    using HeaderMap = std::unordered_map<std::string, std::string>;

    class Header {
    public:
        static std::shared_ptr<HeaderMap> parse(const std::string& rawHeader) {
            auto headers = std::make_shared<HeaderMap>();
            std::stringstream ss(rawHeader);

            std::string line;
            while (std::getline(ss, line)) {
                auto pos = line.find(':');

                if (pos != std::string::npos) {
                    auto name  = line.substr(0, pos);
                    auto value = line.substr(pos + 2);

                    if (!name.empty() && !value.empty()) {
                        (*headers)[name] = value;
                    }
                }
            }

            return std::move(headers);
        }
    };
}
