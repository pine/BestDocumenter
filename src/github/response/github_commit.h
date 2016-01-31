#pragma once

#include <memory>
#include <string>
#include <picojson.h>
#include "author.h"
#include "git_reference.h"
#include "github_commit_file.h"
#include "util.h"

using namespace picojson;

namespace github {
    namespace response {
        class GitHubCommit;
        using GitHubCommitPtr      = util::Ptr<GitHubCommit>;
        using GitHubCommitArrayPtr = util::ArrayPtr<GitHubCommit>;

        class GitHubCommit : public GitReference {
        public:
            AuthorPtr                author;
            std::string              commentsUrl;
            AuthorPtr                committer;
            std::string              htmlUrl;
            GitHubCommitFileArrayPtr files;

            // ----------------------------------------------------------------

            template<class T = GitHubCommit>
            static util::Ptr<T> inflate(value val, std::string* err) {
                auto res = GitReference::inflate<T>(val, err);
                if (!err->empty()) { return res; }

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    res->author = Author::inflate(obj["author"], err);
                    if (!err->empty()) { return std::move(res); }

                    if (obj["comments_url"].is<std::string>()) {
                        res->commentsUrl = obj["comments_url"].get<std::string>();
                    }

                    res->committer = Author::inflate(obj["committer"], err);
                    if (!err->empty()) { return std::move(res); }

                    if (obj["html_url"].is<std::string>()) {
                        res->htmlUrl = obj["html_url"].get<std::string>();
                    }

                    if (obj["files"].is<array>()) {
                        res->files = util::inflateArray<GitHubCommitFile>(obj["files"], err);
                        if (!err->empty()) { return std::move(res); }
                    }
                }

                return std::move(res);
            }

            template<class T = GitHubCommit>
            static util::ArrayPtr<T> inflateArray(value val, std::string* err) {
                return util::inflateArray<T>(val, err);
            }
        };
    }
}
