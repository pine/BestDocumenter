#pragma once

#include <memory>
#include <string>
#include <regex>
#include <utility>
#include <vector>

namespace http {
    class RFC5988 {
        // static void parse(const std::string& linkHeader) {
        //     std::cout << linkHeader << std::endl;
        // }

        static std::shared_ptr<std::vector<std::string>> splitLinkValues(const std::string& linkHeader) {
            const std::regex ex(R"(,\s*<)");
            auto values = std::make_shared<std::vector<std::string>>();

            std::sregex_token_iterator begin(linkHeader.begin(), linkHeader.end(), ex, -1);
            std::sregex_token_iterator end;

            for (auto itr = begin; itr != end; ++itr) {
                values->push_back(*itr);
            }

            return std::move(values);
        }
    };
}
