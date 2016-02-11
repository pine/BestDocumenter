#include "client.h"

namespace http {

    Client::Client() {
        curl_ = curl_easy_init();
        slist_ = nullptr;

        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &Client::writeCallback);
        curl_easy_setopt(curl_, CURLOPT_HEADERFUNCTION, &Client::headerCallback);
    }

    Client::~Client() {
        curl_slist_free_all(slist_);
        curl_easy_cleanup(curl_);
        slist_ = nullptr;
        curl_ = nullptr;
    }

    Response Client::doGet(
            const std::string& url,
            const GetParams* params
            )
    {
        Response response;

        curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, slist_);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl_, CURLOPT_HEADERDATA, &response);
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        curl_easy_perform(curl_);

        int statusCode;
        curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &statusCode);
        response.setStatusCode(std::move(statusCode));

        return std::move(response);
    }

    void Client::setUserAgent(const std::string& userAgent) {
        curl_easy_setopt(curl_, CURLOPT_USERAGENT, userAgent.c_str());
    }

    void Client::setHeader(const std::string& header) {
        slist_ = curl_slist_append(slist_, header.c_str());
    }

    size_t Client::writeCallback(char* ptr, size_t size, size_t nmemb, Response* response) {
        size_t dataLength = size * nmemb;
        response->appendBody(ptr, dataLength);
        return dataLength;
    }

    size_t Client::headerCallback(char* buffer, size_t size, size_t nitems, Response* response) {
        size_t dataLength = size * nitems;
        response->appendHeader(buffer, dataLength);
        return dataLength;
    }

    std::string Client::getQueryString(const GetParams* params) {
        if (params == nullptr) { return ""; }

        std::stringstream queryStream;
        for (auto &param : *params) {
            queryStream << escape(param.first) << '=' << escape(param.second);
            queryStream << '&';
        }

        std::string queryString = queryStream.str();

        if (!queryString.empty()) {
            queryString.pop_back();
        }

        return std::move(queryString);
    }
}
