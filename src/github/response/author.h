#pragma once

#include <string>
#include <picojson.h>
#include "util.h"

using namespace picojson;

namespace github {
    namespace response {
        class Author;
        using AuthorPtr       = util::Ptr<Author>;
        using AuthorArrayPtr = util::ArrayPtr<Author>;

        class Author {
        public:
            std::string login;
            int64_t id;
            std::string avatarUrl;

            // ----------------------------------------------------------------

            template<class T = Author>
            static util::Ptr<T> inflate(value val, std::string* err) {
                auto res = std::make_shared<T>();

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    if (obj["login"].is<std::string>()) {
                        res->login = obj["login"].get<std::string>();
                    }

                    if (obj["id"].is<int64_t>()) {
                        res->id = obj["id"].get<int64_t>();
                    }

                    if (obj["avatar_url"].is<std::string>()) {
                        res->avatarUrl = obj["avatar_url"].get<std::string>();
                    }
                }

                return std::move(res);
            }
        };
    }
}
