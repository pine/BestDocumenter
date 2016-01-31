#pragma once

#include <string>
#include <picojson.h>
#include "util.h"

using namespace picojson;

namespace github {
    namespace response {
        struct Author {
        public:
            std::string login;
            int64_t id;
            std::string avatarUrl;

            // ----------------------------------------------------------------

            template<class T = Author>
            static T inflate(value val, std::string* err) {
                T res;

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    if (obj["login"].is<std::string>()) {
                        res.login = obj["login"].get<std::string>();
                    }

                    if (obj["id"].is<int64_t>()) {
                        res.id = obj["id"].get<int64_t>();
                    }

                    if (obj["avatar_url"].is<std::string>()) {
                        res.avatarUrl = obj["avatar_url"].get<std::string>();
                    }
                }

                return std::move(res);
            }

            template<class T = Author>
            static std::vector<T> inflateArray(value val, std::string* err) {
                return util::inflateArray<T>(val, err);
            }
        };
    }
}
