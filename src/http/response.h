#pragma once

#include <memory>
#include <string>
#include <sstream>
#include "header.h"

namespace http {
    class Client;

    class Response {
    friend Client;

    public:
        Response();
        ~Response();

        inline long getStatusCode() { return statusCode_; }
        inline std::string getBody() { return body_->str(); }
        inline std::string getRawHeader() { return header_->str(); }

        std::shared_ptr<HeaderMap> getParsedHeader();

    private:
        inline void setStatusCode(long code) { statusCode_ = code; }

        void appendBody(char* ptr, size_t n);
        void appendHeader(char* ptr, size_t n);

        long statusCode_;
        std::shared_ptr<std::stringstream> body_;
        std::shared_ptr<std::stringstream> header_;
        std::shared_ptr<HeaderMap> parsedHeader_;
    };
}
