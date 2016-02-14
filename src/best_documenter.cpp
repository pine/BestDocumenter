#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <chrono>
#include <picojson.h>

#include "best_documenter/parser.h"
#include "best_documenter/config.h"
#include "best_documenter/counter.h"
#include "best_documenter/duration.h"
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

    auto duration = Duration::fromDays(parser.getDurationDays());
    auto result   = counter->compute(duration);

    // FIXME: 切り出し
    std::cout << std::endl;
    std::cout << "BestDocumenter v0.1.0" << std::endl;
    std::cout << "BEGIN: " << duration.fetchSince() << std::endl;
    std::cout << "END  : " << duration.fetchUntil() << std::endl;
    std::cout << std::endl;

    for (auto& change : result->changes) {
        if (change.first.empty()) continue;

        std::cout << change.first << ": " << change.second << " changes ";
        std::cout << "( +";
        std::cout << result->additions[change.first] << " / -";
        std::cout << result->deletions[change.first];
        std::cout << " )" << std::endl;
    }

    return 0;
}
