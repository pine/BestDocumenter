#include <memory>
#include <string>

#include "../github/client.h"
#include "model/result.h"

namespace best_documenter {
    using GitHubCommitArrayPtr = github::response::GitHubCommitArrayPtr;

    class Counter {
    public:
        Counter(std::shared_ptr<github::Client> github);
        ~Counter();

        void setRepos(const std::vector<std::string>& repos) { repos_ = repos; }

        std::shared_ptr<model::Result> compute();

    private:
        std::shared_ptr<github::Client> github_;
        std::vector<std::string>        repos_;

        GitHubCommitArrayPtr fetchReposCommits(
                const std::string& repo,
                std::string* err
                );

    };
}
