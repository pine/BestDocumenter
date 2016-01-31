#pragma once

#include <memory>
#include <string>
#include <picojson.h>

using namespace picojson;

namespace github {
    namespace response {
        namespace util {
            template <class T>
            using Ptr = std::shared_ptr<T>;

            template <class T>
            using Array = std::vector<Ptr<T>>;

            template <class T>
            using ArrayPtr = std::shared_ptr<Array<T>>;

            template <class T>
            static ArrayPtr<T> inflateArray(value val, std::string* err) {
                auto res = std::make_shared<Array<T>>();

                if (val.is<value::array>()) {
                    auto& ary = val.get<array>();
                    for (auto& obj : ary) {
                        res->push_back(std::move(T::inflate(obj, err)));
                        if (!err->empty()) { return std::move(res); }
                    }
                }

                return std::move(res);
            }
        }
    }
}

