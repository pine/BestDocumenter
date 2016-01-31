#include "counter.h"

namespace best_documenter {
    Counter::Counter(std::shared_ptr<github::Client> github) {
        github_ = github;
    }

    Counter::~Counter() {
    }

    std::shared_ptr<model::Result> Counter::compute() {
        auto result = std::make_shared<model::Result>();

        return result;
    }
}
