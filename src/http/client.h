#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <curl/curl.h>

#include "response.h"

namespace http {
    typedef std::unordered_map<std::string, std::string> GetParams;

    class Client {
    public:
        Client();
        ~Client();

        Response doGet(
                const std::string& url,
                const GetParams* params = nullptr
                );

        void setUserAgent(const std::string& userAgent);
        void setHeader(const std::string& header);

    private:
        CURL* curl_;
		struct curl_slist* slist_;

        Client(const Client&);
        Client& operator=(const Client&);

        static size_t writeCallback(char* ptr, size_t size, size_t nmemb, Response* response);
        static size_t headerCallback(char* ptr, size_t size, size_t nitems, Response* userdata);
        std::string getQueryString(const GetParams* params);

        inline std::string escape(const std::string& string) {
            return curl_easy_escape(curl_, string.c_str(), string.size());
        }
    };
}
