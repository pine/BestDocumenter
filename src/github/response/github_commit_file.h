#pragma once

#include <string>
#include <picojson.h>

using namespace picojson;

namespace github {
    namespace response {
        struct GitHubCommitFile {
        public:
            std::string filename;

            // ----------------------------------------------------------------

            static inline std::vector<GitHubCommit>
            getEmptyArray() { return std::vector<GitHubCommit>(); }

            template<class T = GitHubCommitFile>
            static T inflate(value val, std::string* err) {
                auto res = GitReference::inflate<T>(val, err);
                if (!err->empty()) { return res; }

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    res.author = Author::inflate(obj["author"], err);
                    if (!err->empty()) { return std::move(res); }

                    if (obj["filename"].is<std::string>()) {
                        res.filename = obj["filename"].get<std::string>();
                    }
                }

                return std::move(res);
            }
        };
    }
}
