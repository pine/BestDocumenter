#include "counter.h"

namespace best_documenter {
    Counter::Counter(std::shared_ptr<github::Client> github) {
        github_ = github;
    }

    Counter::~Counter() {
    }

    std::shared_ptr<model::Result> Counter::compute() {
        auto result = std::make_shared<model::Result>();
        std::string err;

        for (auto& repo : repos_) {
            auto commits = github_->fetchReposCommits("pine613", "dotfiles", &err);
            if (!err.empty()) {
                std::cout << err << std::endl;
                return result;
            }
        }

        return std::move(result);
    }

    GitHubCommitArrayPtr Counter::fetchReposCommits(
            const std::string& repo,
            std::string* err
            )
    {
        auto slashPos = repo.find('/');

        if (slashPos == std::string::npos) {
            *err = "Invalid repository name";
            return GitHubCommitArrayPtr();
        }

        auto owner   = repo.substr(0, repo.find('/'));
        auto name    = repo.substr(repo.find('/') + 1);
        auto commits = github_->fetchReposCommits(
                std::move(owner),
                std::move(name),
                err);

        return std::move(commits);
    }
}
