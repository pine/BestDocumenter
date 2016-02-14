#pragma once

#include <memory>
#include <string>
#include <map>
#include <picojson.h>

using namespace picojson;

namespace best_documenter {
    namespace model {
        class Result {
        public:
            std::map<std::string, int32_t> changes;
            std::map<std::string, int32_t> additions;
            std::map<std::string, int32_t> deletions;
        };
    }
}
