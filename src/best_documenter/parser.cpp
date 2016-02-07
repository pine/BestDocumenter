#include "parser.h"

namespace best_documenter {
    Parser::Parser() {
        parser_.add<std::string>("config", 'c', "Configuration file path", true, "");
        parser_.add<int32_t>("days", 'd', "Duration days", false, 7);
    }

    Parser::~Parser() {
    }

    void Parser::parse(int argc, char* argv[]) {
        parser_.parse_check(argc, argv);
    }

    std::string Parser::getConfigFileName() {
        return parser_.get<std::string>("config");
    }

    int32_t Parser::getDurationDays() {
        return parser_.get<int32_t>("days");
    }
}
