#pragma once

#include <iostream>
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

    protected:
        static std::shared_ptr<std::vector<std::string>> splitLinkValues(const std::string& linkHeader);
    };
}
