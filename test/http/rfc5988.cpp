#include <catch.hpp>
#include "../../src/http/rfc5988.h"

TEST_CASE("can parse RFC5988 link header", "[RFC5988]") {
    SECTION("can parse an empty string") {
        auto results = http::RFC5988::parse("");
        REQUIRE(results->size() == 0);
    }

    SECTION("can parse multi values") {
        auto results = http::RFC5988::parse(R"(<URL1>, <URL2>; rel="next")");
        REQUIRE(results->size() == 2);
        REQUIRE(results->front().getUrl() == "URL1");
        REQUIRE(results->front().getParams()->size() == 0);
        REQUIRE(results->back().getUrl() == "URL2");
        REQUIRE(results->back().getParams()->size() == 1);
        REQUIRE(results->back().getParams()->at("rel") == "next");
    }
}

TEST_CASE("can split RFC5988 link header values", "[RFC5988]") {
    SECTION("can split an empty string") {
        auto results = http::RFC5988::splitLinkValues("");
        REQUIRE(results->size() == 0);
    }

    SECTION("can split a single value") {
        auto results = http::RFC5988::splitLinkValues("<URL>");
        REQUIRE(results->size()  == 1);
        REQUIRE(results->front() == "<URL>");
    }

    SECTION("can split multi values") {
        auto results = http::RFC5988::splitLinkValues(R"(<URL1>, <URL2>; rel="next")");
        REQUIRE(results->size()  == 2);
        REQUIRE(results->front() == "<URL1>");
        REQUIRE(results->back()  == R"(URL2>; rel="next")");
    }
}

TEST_CASE("can split RFC5988 link header value", "[RFC5988]") {
    SECTION("can split an empty string") {
        auto results = http::RFC5988::splitLinkValue("");
        REQUIRE(results->size() == 0);
    }

    SECTION("can split a value") {
        auto results = http::RFC5988::splitLinkValue("A;B;C");
        REQUIRE(results->size()  == 3);
        REQUIRE(results->at(0) == "A");
        REQUIRE(results->at(1) == "B");
        REQUIRE(results->at(2) == "C");
    }
}

TEST_CASE("can split RFC5988 link header param", "[RFC5988]") {
    SECTION("can split an empty string") {
        auto pair = http::RFC5988::splitLinkParam("");
        REQUIRE(!pair);
    }

    SECTION("can split a param") {
        auto pair = http::RFC5988::splitLinkParam("rel=next");
        REQUIRE(pair->first == "rel");
        REQUIRE(pair->second == "next");
    }

    SECTION("can split a param with quote") {
        auto pair = http::RFC5988::splitLinkParam("rel=\"next\"");
        REQUIRE(pair->first == "rel");
        REQUIRE(pair->second == "next");
    }
}

TEST_CASE("can chomp URL reference", "[RFC5988]") {
    SECTION("can chomp empty URL reference") {
        std::string s("");
        http::RFC5988::chompUriReference(s);
        REQUIRE(s == "");
    }

    SECTION("can chomp URL reference (right)") {
        std::string s("URL>");
        http::RFC5988::chompUriReference(s);
        REQUIRE(s == "URL");
    }

    SECTION("can chomp URL reference") {
        std::string s("<URL>");
        http::RFC5988::chompUriReference(s);
        REQUIRE(s == "URL");
    }
}
