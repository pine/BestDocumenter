#pragma once

#include <string>
#include <picojson.h>
#include "account.h"

using namespace picojson;

namespace github {
    namespace response {
        struct User : public Account {
        public:
            bool siteAdmin;

            // ----------------------------------------------------------------

            template<class T = User>
            static T inflate(picojson::value val, std::string* err) {
                auto res = Account::inflate<User>(val, err);
                if (!err->empty()) { return res; }

                if (val.is<value::object>()) {
                    auto& obj = val.get<object>();

                    if (val.is<bool>()) {
                        res.siteAdmin = val.get<bool>();
                    }
                }

                return std::move(res);
            }
        };
    }
}
