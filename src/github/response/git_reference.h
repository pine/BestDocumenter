#pragma once

#include <string>
#include <picojson.h>
#include "user.h"

using namespace picojson;

namespace github {
    namespace response {
        struct GitReference {
        public:
            std::string url;
            std::string label;
            std::string ref;
            std::string sha;
            User user;

            // ----------------------------------------------------------------

            template<class T = GitReference>
            static T inflate(picojson::value val, std::string* err) {
                T res;

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    res.url   = obj["url"].to_str();
                    res.ref   = obj["ref"].to_str();
                    res.label = obj["label"].to_str();
                    res.sha   = obj["sha"].to_str();

                    res.user = User::inflate(obj["user"], err);
                    if (!err->empty()) { return std::move(res); }
                }

                return std::move(res);
            }
        };
    }
}
