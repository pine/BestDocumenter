#include "rfc5988.h"

namespace http {
    std::shared_ptr<std::vector<rfc5988::Model>> RFC5988::parse(const std::string& header) {
        auto results = std::make_shared<std::vector<rfc5988::Model>>();
        auto values  = splitLinkValues(header);

        for (auto& value : *values) {
            auto parts = splitLinkValue(value);

            if (parts->size() >= 1) {
                auto uri = parts->front();
                parts->erase(parts->begin());
                chompUriReference(uri);

                auto params = std::make_shared<rfc5988::Params>();
                for (auto& part : *parts) {
                    auto param = splitLinkParam(part);
                    (*params)[param->first] = param->second;
                }

                results->push_back(rfc5988::Model(uri, params));
            }
        }

        return std::move(results);
    }

    std::shared_ptr<std::vector<std::string>> RFC5988::split(
            const std::string& str,
            const std::regex& ex
            )
    {
        auto values = std::make_shared<std::vector<std::string>>();

        std::sregex_token_iterator begin(str.begin(), str.end(), ex, -1);
        std::sregex_token_iterator end;

        for (auto itr = begin; itr != end; ++itr) {
            std::string matched = *itr;

            if (matched.size() > 0) {
                values->push_back(std::move(matched));
            }
        }

        return std::move(values);
    }

    std::shared_ptr<std::vector<std::string>> RFC5988::splitLinkValues(const std::string& header)
    {
        const std::regex ex(R"(,\s*<)");
        return split(header, ex);
    }

    std::shared_ptr<std::vector<std::string>> RFC5988::splitLinkValue(const std::string& value)
    {
        const std::regex ex(";");
        return split(value, ex);
    }

    std::shared_ptr<std::pair<std::string, std::string>> RFC5988::splitLinkParam(const std::string& param)
    {
        const std::regex ex("\\s*(.+)\\s*=\\s*\"?([^\"]+)\"?");
        std::smatch match;

        if (std::regex_search(param, match, ex)) {
            if (match.size() == 3) {
                return std::make_shared<std::pair<std::string, std::string>>(match[1], match[2]);
            }
        }

        return std::shared_ptr<std::pair<std::string, std::string>>();
    }

    void RFC5988::chompUriReference(std::string& str) {
        size_t pos;

        while ((pos = str.find("<")) == 0) {
            str.erase(pos, 1);
        }

        while (!str.empty() && (pos = str.find(">")) == str.size() - 1) {
            str.erase(pos, 1);
        }
    }
}
