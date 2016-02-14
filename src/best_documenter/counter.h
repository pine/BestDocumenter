#include <memory>
#include <string>

#include "../github/client.h"
#include "../http/client.h"
#include "model/result.h"
#include "duration.h"

namespace best_documenter {
    using GitHubCommitArrayPtr = github::response::GitHubCommitArrayPtr;
    using GitHubCommitPtr      = github::response::GitHubCommitPtr;

    class Counter {
    public:
        Counter(std::shared_ptr<github::Client> github);
        ~Counter();

        void setRepos(const std::vector<std::string>& repos) { repos_ = repos; }

        std::shared_ptr<model::Result> compute(const Duration& duration);

    private:
        std::shared_ptr<github::Client> github_;
        std::vector<std::string>        repos_;

        GitHubCommitArrayPtr fetchReposCommits(
                const std::string& repo,
                const Duration& duration,
                std::string* err
                );

        GitHubCommitPtr fetchReposCommit(
                const std::string& repo,
                const std::string& sha,
                std::string* err
                );
    };
}
