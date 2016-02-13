#include <memory>
#include <string>
#include <unordered_map>

namespace http {
    namespace rfc5988 {
        using Params = std::unordered_map<std::string, std::string>;

        class Model {
        public:
            Model(const std::string& url, const std::shared_ptr<Params>& params);
            ~Model();

            inline std::string getUrl() { return url_; }
            inline std::shared_ptr<Params> getParams() { return params_; }

        private:
            std::shared_ptr<Params> params_;
            std::string url_;
        };
    }
}
