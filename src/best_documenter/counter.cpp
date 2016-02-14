#include "counter.h"

namespace best_documenter {
    Counter::Counter(std::shared_ptr<github::Client> github) {
        github_ = github;
    }

    Counter::~Counter() {
    }

    // FIXME: 分割
    std::shared_ptr<model::Result> Counter::compute(const Duration& duration) {
        auto result = std::make_shared<model::Result>();
        std::vector<GitHubCommitPtr> allCommits;
        std::string err;

        for (auto& repo : repos_) {
            std::cout << "Counting " << repo << " commits ... " << std::flush;
            auto commits = fetchReposCommits(repo, duration, &err);
            if (!err.empty()) {
                std::cout << err << std::endl;
                return result;
            }
            std::cout << commits->size() << " commits found" << std::endl;

            std::cout << "Collectiong " << repo << " commits " << std::endl;
            for (auto& commit : *commits) {
                std::cout << "." << std::flush;

                auto& sha         = commit->sha;
                auto githubCommit = fetchReposCommit(repo, sha, &err);
                if (!err.empty()) {
                    std::cout << err << std::endl;
                    return result;
                }

                allCommits.push_back(githubCommit);
            }
            std::cout << std::endl << std::endl;
        }

        auto itr = allCommits.begin();
        while (itr != allCommits.end()) {
            auto& commit = *itr;
            auto& files  = commit->files;
            bool documentFound = false;

            for (auto&  file : *files) {
                auto extPos = file->filename.find_last_of('.');

                if (extPos != std::string::npos) {
                    auto ext = file->filename.substr(extPos + 1);

                    if (ext == "md") { // FIXME: hard coding
                        auto& login = commit->author->login;

                        result->changes[login]   += file->changes;
                        result->additions[login] += file->additions;
                        result->deletions[login] += file->deletions;
                    }
                }
            }

            if (documentFound) {
                ++itr;
            }
            else {
                itr = allCommits.erase(itr);
            }
        }

        return result;
    }

    GitHubCommitArrayPtr Counter::fetchReposCommits(
            const std::string& repo,
            const Duration& duration,
            std::string* err
            )
    {
        auto slashPos = repo.find('/');

        if (slashPos == std::string::npos) {
            *err = "Invalid repository name";
            return GitHubCommitArrayPtr();
        }

        http::GetParams params;
        params["since"] = duration.fetchSince();
        params["until"] = duration.fetchUntil();

        auto owner   = repo.substr(0, repo.find('/'));
        auto name    = repo.substr(repo.find('/') + 1);
        auto commits = github_->fetchReposCommits(
                std::move(owner),
                std::move(name),
                err,
                &params);

        return std::move(commits);
    }

    GitHubCommitPtr Counter::fetchReposCommit(
            const std::string& repo,
            const std::string& sha,
            std::string* err
            )
    {
        auto slashPos = repo.find('/');

        if (slashPos == std::string::npos) {
            *err = "Invalid repository name";
            return GitHubCommitPtr();
        }

        auto owner  = repo.substr(0, repo.find('/'));
        auto name   = repo.substr(repo.find('/') + 1);
        auto commit = github_->fetchReposCommit(
                std::move(owner),
                std::move(name),
                sha,
                err);

        return std::move(commit);
    }
}
