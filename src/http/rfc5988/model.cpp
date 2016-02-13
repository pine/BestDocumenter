#include "model.h"

namespace http {
    namespace rfc5988 {
        Model::Model(const std::string& url, const std::shared_ptr<Params>& params) {
            url_ = url;
            params_ = params;
        }

        Model::~Model() {
        }
    }
}
