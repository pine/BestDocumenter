#pragma once

#include <string>
#include <sstream>

namespace http {
    class Client;

    class Response {
    friend Client;

    public:
        inline long getStatusCode() { return statusCode_; }
        inline std::string getBody() { return stream_.str(); }

    private:
        inline void setStatusCode(long code) { statusCode_ = code; }

        void appendBody(char* ptr, size_t n);

        long statusCode_;
        std::stringstream stream_;
    };
}
