#pragma once

#include <memory>
#include <vector>
#include <picojson.h>

#include "../http/client.h"
#include "../http/rfc5988.h"
#include "response/github_commit.h"
#include "response/util.h"

namespace github {
    class Client {
    public:
        static const char* ENDPOINT;

        Client(std::shared_ptr<http::Client> http);
        ~Client();

        void setAccessToken(const std::string& accessToken);

        response::GitHubCommitArrayPtr fetchReposCommits(
                const std::string& owner,
                const std::string& repo,
                std::string* err,
                const http::GetParams* opts = nullptr
                );

        response::GitHubCommitPtr fetchReposCommit(
                const std::string& owner,
                const std::string& repo,
                const std::string& sha,
                std::string* err
                );

    private:
        std::shared_ptr<http::Client> http_;

        std::string getNextUrl(http::HeaderMap& header);
    };
}
