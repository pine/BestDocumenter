#include "client.h"

using namespace picojson;

namespace github {
    const char* Client::ENDPOINT = "https://api.github.com/";

    Client::Client(std::shared_ptr<http::Client> http) {
        http_ = http;
        http_->setHeader("Accept: application/vnd.github.v3+json");
    }

    Client::~Client() {
    }

    void Client::setAccessToken(const std::string& accessToken) {
        http_->setHeader("Authorization: token " + accessToken);
    }

    response::GitHubCommitArrayPtr Client::fetchReposCommits(
            const std::string& owner,
            const std::string& repo,
            std::string* err,
            const http::GetParams* opts
            )
    {
        std::stringstream path;
        path << ENDPOINT << "repos" << "/" << owner << "/" << repo << "/commits";

        http::GetParams params = { { "page", "1" }, { "per_page", "100" } };
        if (opts) { params.insert(opts->begin(), opts->end()); }

        auto  response = http_->doGet(path.str(), &params);
        auto  body     = response.getBody();
        auto& header   = *response.getParsedHeader();

        value out;
        parse(out, body.begin(), body.end(), err);

        if (!err->empty()) {
            return response::GitHubCommitArrayPtr();
        }

        return response::GitHubCommit::inflateArray(out, err);
    }

    response::GitHubCommitPtr Client::fetchReposCommit(
            const std::string& owner,
            const std::string& repo,
            const std::string& sha,
            std::string* err
            )
    {
        std::stringstream path;
        path << ENDPOINT;
        path << "repos" << "/" << owner << "/" << repo << "/commits/" << sha;

        auto response = http_->doGet(path.str());
        auto body     = response.getBody();

        std::cout << body << std::endl;

        value out;
        parse(out, body.begin(), body.end(), err);

        if (!err->empty()) {
            return response::GitHubCommitPtr();
        }

        return response::GitHubCommit::inflate(out, err);
    }
}
