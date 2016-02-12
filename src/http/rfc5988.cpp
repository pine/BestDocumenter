#include "rfc5988.h"

namespace http {
    std::shared_ptr<std::vector<std::string>> RFC5988::splitLinkValues(const std::string& linkHeader) {
        const std::regex ex(R"(,\s*<)");
        auto values = std::make_shared<std::vector<std::string>>();

        std::sregex_token_iterator begin(linkHeader.begin(), linkHeader.end(), ex, -1);
        std::sregex_token_iterator end;

        for (auto itr = begin; itr != end; ++itr) {
            std::string matched = *itr;

            if (matched.size() > 0) {
                values->push_back(std::move(matched));
            }
        }

        return std::move(values);
    }
}
