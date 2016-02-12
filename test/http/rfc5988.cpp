#include <catch.hpp>
#include "../../src/http/rfc5988.h"

class Spy_RFC5988 : public http::RFC5988 {
public:
    static std::shared_ptr<std::vector<std::string>> spy_splitLinkValues(const std::string& linkHeader) {
        return RFC5988::splitLinkValues(linkHeader);
    }
};

TEST_CASE("can split RFC5988 link header values", "[RFC5988]") {
    SECTION("can split an empty string") {
        auto results = Spy_RFC5988::spy_splitLinkValues("");
        REQUIRE(results->size() == 0);
    }

    SECTION("can split a single value") {
        auto results = Spy_RFC5988::spy_splitLinkValues("<URL>");
        REQUIRE(results->size()  == 1);
        REQUIRE(results->front() == "<URL>");
    }

    SECTION("can split multi values") {
        auto results = Spy_RFC5988::spy_splitLinkValues(R"(<URL1>, <URL2>; rel="next")");
        REQUIRE(results->size()  == 2);
        REQUIRE(results->front() == "<URL1>");
        REQUIRE(results->back()  == R"(URL2>; rel="next")");
    }
}
