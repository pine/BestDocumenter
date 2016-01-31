#pragma once

#include <memory>
#include <string>
#include <picojson.h>
#include "util.h"

using namespace picojson;

namespace github {
    namespace response {
        class Account;
        using AccountPtr      = util::Ptr<Account>;
        using AccountArrayPtr = util::ArrayPtr<Account>;

        class Account {
        public:
            std::string avatarUrl;
            std::string bio;
            std::string blog;
            int64_t     collaborators;
            std::string name;

            // ----------------------------------------------------------------

            template<class T = Account>
            static util::Ptr<T> inflate(value val, std::string* err) {
                auto res = std::make_shared<T>();

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    res->avatarUrl = obj["avatarUrl"].to_str();
                    res->bio       = obj["bio"].to_str();
                    res->blog      = obj["blog"].to_str();
                    res->name      = obj["name"].to_str();

                    if (obj["collaborators"].is<int64_t>()) {
                        res->collaborators = obj["collaborators"].get<int64_t>();
                    }
                }

                return std::move(res);
            }
        };
    }
}
