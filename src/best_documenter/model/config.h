#pragma once

#include <memory>
#include <string>
#include <picojson.h>

using namespace picojson;

namespace best_documenter {
    namespace model {
        class Config {
        public:
            inline std::string getAccessToken() { return access_token_; }
            inline std::vector<std::string> getRepos() { return repos_; }

            // ----------------------------------------------------------------

            static std::shared_ptr<Config> inflate(picojson::value val, std::string* err) {
                auto config = std::make_shared<Config>();

                if (val.is<value::object>()) {

                    auto& obj = val.get<value::object>();

                    if (obj["github"].is<value::object>()) {
                        auto& github = obj["github"].get<value::object>();

                        if (github["access_token"].is<std::string>()) {
                            config->access_token_ = github["access_token"].get<std::string>();
                        }
                    }

                    if (obj["repos"].is<value::array>()) {
                        auto& repos = obj["repos"].get<value::array>();

                        for (auto& repo : repos) {
                            if (repo.is<std::string>()) {
                                config->repos_.push_back(repo.get<std::string>());
                            }
                        }
                    }
                }

                return config;
            }

        private:
            std::string              access_token_;
            std::vector<std::string> repos_;
        };
    }
}
