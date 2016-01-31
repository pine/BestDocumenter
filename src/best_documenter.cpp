#include <string>
#include <memory>
#include <picojson.h>

#include "http/client.h"
#include "github/client.h"

int main(int argc, char **argv) {
    auto http = std::make_shared<http::Client>();
    http->setUserAgent("pine613/BestDocumenter");

    std::string err;
    github::Client github(http);

    auto commits = github.fetchReposCommits("pine613", "crystal-rfc5988", &err);
    if (!err.empty()) std::cout << err << std::endl;

    for (auto& commit : commits) {
        std::cout << commit.url << std::endl;
        std::cout << commit.committer.login << std::endl;
    }

    return 0;
}
