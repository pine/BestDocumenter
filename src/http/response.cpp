#include "response.h"

namespace http {
    Response::Response() {
        body_ = std::make_shared<std::stringstream>();
        header_ = std::make_shared<std::stringstream>();
    }

    Response::~Response() {
    }

    std::shared_ptr<HeaderMap> Response::getParsedHeader() {
        if (!parsedHeader_) {
            parsedHeader_ = Header::parse(getRawHeader());
        }

        return parsedHeader_;
    }

    void Response::appendBody(char* ptr, size_t n) {
        body_->write(ptr, n);
    }

    void Response::appendHeader(char* ptr, size_t n) {
        header_->write(ptr, n);
    }
}
