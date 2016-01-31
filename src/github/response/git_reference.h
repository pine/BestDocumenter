#pragma once

#include <memory>
#include <string>
#include <picojson.h>
#include "util.h"
#include "user.h"

using namespace picojson;

namespace github {
    namespace response {
        class GitReference;
        using GitReferencePtr      = util::Ptr<GitReference>;
        using GitReferenceArrayPtr = util::ArrayPtr<GitReference>;

        class GitReference {
        public:
            std::string url;
            std::string label;
            std::string ref;
            std::string sha;
            UserPtr     user;

            // ----------------------------------------------------------------

            template<class T = GitReference>
            static std::shared_ptr<T> inflate(picojson::value val, std::string* err) {
                auto res = std::make_shared<T>();

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    res->url   = obj["url"].to_str();
                    res->ref   = obj["ref"].to_str();
                    res->label = obj["label"].to_str();
                    res->sha   = obj["sha"].to_str();

                    res->user = User::inflate(obj["user"], err);
                    if (!err->empty()) { return std::move(res); }
                }

                return std::move(res);
            }
        };
    }
}
