#include "parser.h"

namespace best_documenter {
    Parser::Parser() {
        parser_.add<std::string>("config-file", 'c', "Configuration file path", true, "");
    }

    Parser::~Parser() {
    }

    void Parser::parse(int argc, char* argv[]) {
        parser_.parse_check(argc, argv);
    }

    std::string Parser::getConfigFileName() {
        return parser_.get<std::string>("config-file");
    }
}
