#pragma once

#include <cinttypes>
#include <memory>
#include <string>
#include <vector>
#include <picojson.h>
#include "util.h"
#include "git_reference.h"

using namespace picojson;

namespace github {
    namespace response {
        class GitHubCommitFile;
        using GitHubCommitFilePtr      = util::Ptr<GitHubCommitFile>;
        using GitHubCommitFileArrayPtr = util::ArrayPtr<GitHubCommitFile>;

        class GitHubCommitFile : public GitReference {

        public:
            std::string filename;
            int64_t     additions;
            int64_t     deletions;
            int64_t     changes;
            std::string status;
            std::string blobUrl;
            std::string contentsUrl;
            std::string rawUrl;

            // ----------------------------------------------------------------

            template<class T = GitHubCommitFile>
            static util::Ptr<GitHubCommitFile> inflate(value val, std::string* err) {
                auto res = GitReference::inflate<T>(val, err);
                if (!err->empty()) { return res; }

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    if (obj["filename"].is<std::string>()) {
                        res->filename = obj["filename"].get<std::string>();
                    }

                    if (obj["additions"].is<int64_t>()) {
                        res->additions = obj["additions"].get<int64_t>();
                    }

                    if (obj["deletions"].is<int64_t>()) {
                        res->deletions = obj["deletions"].get<int64_t>();
                    }

                    if (obj["changes"].is<int64_t>()) {
                        res->changes = obj["changes"].get<int64_t>();
                    }

                    if (obj["status"].is<std::string>()) {
                        res->status = obj["status"].get<std::string>();
                    }

                    if (obj["blob_url"].is<std::string>()) {
                        res->blobUrl = obj["blob_url"].get<std::string>();
                    }

                    if (obj["contents_url"].is<std::string>()) {
                        res->contentsUrl = obj["contents_url"].get<std::string>();
                    }

                    if (obj["raw_url"].is<std::string>()) {
                        res->rawUrl = obj["raw_url"].get<std::string>();
                    }
                }

                return std::move(res);
            }
        };
    }
}
