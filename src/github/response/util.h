#pragma once

#include <string>
#include <picojson.h>

using namespace picojson;

namespace github {
    namespace response {
        namespace util {
            template <class T>
            static inline std::vector<T> getEmptyArray() { return std::vector<T>(); }

            template <class T>
            static std::vector<T> inflateArray(value val, std::string* err) {
                auto res = getEmptyArray<T>();

                if (val.is<value::array>()) {
                    auto& ary = val.get<array>();
                    for (auto& obj : ary) {
                        res.push_back(std::move(T::inflate(obj, err)));
                        if (!err->empty()) { return std::move(res); }
                    }
                }

                return std::move(res);
            }
        }
    }
}

