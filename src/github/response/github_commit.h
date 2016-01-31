#pragma once

#include <string>
#include <picojson.h>
#include "author.h"
#include "git_reference.h"

using namespace picojson;

namespace github {
    namespace response {
        struct GitHubCommit : GitReference {
        public:
            Author author;
            std::string commentsUrl;
            Author committer;
            std::string htmlUrl;

            // ----------------------------------------------------------------

            template<class T = GitHubCommit>
            static T inflate(value val, std::string* err) {
                auto res = GitReference::inflate<T>(val, err);
                if (!err->empty()) { return res; }

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    res.author = Author::inflate(obj["author"], err);
                    if (!err->empty()) { return std::move(res); }

                    if (obj["comments_url"].is<std::string>()) {
                        res.commentsUrl = obj["comments_url"].get<std::string>();
                    }

                    res.committer = Author::inflate(obj["committer"], err);
                    if (!err->empty()) { return std::move(res); }

                    if (obj["html_url"].is<std::string>()) {
                        res.htmlUrl = obj["html_url"].get<std::string>();
                    }
                }

                return std::move(res);
            }

            template<class T = GitHubCommit>
            static std::vector<T> inflateArray(value val, std::string* err) {
                return util::inflateArray<T>(val, err);
            }
        };
    }
}
