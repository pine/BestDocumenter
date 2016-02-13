#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <regex>
#include <utility>
#include <vector>
#include "rfc5988/model.h"

namespace http {
    class RFC5988 {
    public:
        static std::shared_ptr<std::vector<rfc5988::Model>> parse(const std::string& header);

    private:
        static std::shared_ptr<std::vector<std::string>> split(
                const std::string& str,
                const std::regex& ex
                );

        static std::shared_ptr<std::vector<std::string>> splitLinkValues(const std::string& linkHeader);
        static std::shared_ptr<std::vector<std::string>> splitLinkValue(const std::string& value);
        static std::shared_ptr<std::pair<std::string, std::string>> splitLinkParam(const std::string& param);
        static void chompUriReference(std::string& str);
    };
}
