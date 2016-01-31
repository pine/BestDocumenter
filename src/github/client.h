#pragma once

#include <memory>
#include <vector>
#include <picojson.h>

#include "../http/client.h"
#include "response/github_commit.h"

namespace github {
    class Client {
    public:
        static const char* ENDPOINT;

        Client(std::shared_ptr<http::Client> http);
        ~Client();

        std::vector<response::GitHubCommit> fetchReposCommits(
                const std::string& owner,
                const std::string& repo,
                std::string* err
                );

        response::GitHubCommit fetchReposCommit(
                const std::string& owner,
                const std::string& repo,
                const std::string& sha,
                std::string* err
                );

    private:
        std::shared_ptr<http::Client> http_;
    };
}
