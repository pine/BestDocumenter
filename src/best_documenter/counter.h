#include <memory>
#include <string>
#include "../github/client.h"
#include "model/result.h"

namespace best_documenter {
    class Counter {
    public:
        Counter(std::shared_ptr<github::Client> github);
        ~Counter();

        void setAccessToken(const std::string& accessToken) { accessToken_ = accessToken; }
        void setRepos(const std::vector<std::string>& repos) { repos_ = repos; }

        std::shared_ptr<model::Result> compute();

    private:
        std::shared_ptr<github::Client> github_;
        std::string                     accessToken_;
        std::vector<std::string>        repos_;
    };
}
