#include <catch.hpp>
#include "../../src/http/header.h"

TEST_CASE("can parse HTTP headers", "[Header]") {
    SECTION("can parse an empty string") {
        auto results = http::Header::parse("");
        REQUIRE(results->size() == 0);
    }

    SECTION("can parse a single line header") {
        auto results = http::Header::parse("Content-Type: text/html");
        REQUIRE(results->size() == 1);

        auto& first = *results->begin();
        REQUIRE(first.first == "Content-Type");
        REQUIRE(first.second == "text/html");
    }

    SECTION("can parse multi line headers") {
        auto results = http::Header::parse(R"(
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 10
)");

        REQUIRE(results->size() == 2);
        REQUIRE((*results)["Content-Type"] == "text/html");
        REQUIRE((*results)["Content-Length"] == "10");
    }
}
