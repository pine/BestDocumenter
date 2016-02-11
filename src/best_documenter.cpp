#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <picojson.h>

#include "best_documenter/parser.h"
#include "best_documenter/config.h"
#include "best_documenter/counter.h"
#include "github/client.h"
#include "http/client.h"
#include "http/rfc5988.h"

using namespace best_documenter;

int main(int argc, char** argv) {
    std::string err;
    Parser parser;
    parser.parse(argc, argv);

    Config loader;
    auto config = loader.load(parser.getConfigFileName(), &err);

    auto http    = std::make_shared<http::Client>();
    auto github  = std::make_shared<github::Client>(http);
    auto counter = std::make_shared<Counter>(github);
    http->setUserAgent("pine613/BestDocumenter");
    github->setAccessToken(config->getAccessToken());
    counter->setRepos(config->getRepos());

    //
    // auto result = counter->compute();

    //
    auto commits = github->fetchReposCommits("pine613", "dotfiles", &err);
    if (!err.empty()) std::cout << err << std::endl;

    auto commit = commits->front();
    std::cout << commit->committer->login << std::endl;
    std::cout << commit->sha << std::endl;
    //
    // auto commitDetail = github.fetchReposCommit("pine613", "crystal-rfc5988", commit->sha, &err);
    // if (!err.empty()) std::cout << err << std::endl;
    //
    // std::cout << commitDetail->committer->login << std::endl;
    // std::cout << commitDetail->files->front()->filename << std::endl;

    return 0;
}
