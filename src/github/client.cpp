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

        std::string url = path.str();
        auto results = std::make_shared<response::util::Array<response::GitHubCommit>>();

        while (!url.empty()) {
            auto  response = http_->doGet(url, &params);
            auto  body     = response.getBody();
            auto& header   = *response.getParsedHeader();

            if (response.getStatusCode() != 200) {
                *err = body;
                return response::GitHubCommitArrayPtr();
            }

            value out;
            parse(out, body.begin(), body.end(), err);

            if (!err->empty()) {
                return response::GitHubCommitArrayPtr();
            }

            auto fragments = response::GitHubCommit::inflateArray(out, err);
            for (auto& fragment : *fragments) {
                results->push_back(fragment);
            }

            url = getNextUrl(header);
        }

        return results;
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

    std::string Client::getNextUrl(http::HeaderMap& header) {
        if (header.count("Link") > 0) {
            auto links = http::RFC5988::parse(header["Link"]);
            for (auto& link : *links) {
                if (link.getParams()->count("rel") && link.getParams()->at("rel") == "next") {
                    auto uri = link.getUrl();
                    if (!uri.empty()) return uri;
                }
            }
        }

        return "";
    }
}
