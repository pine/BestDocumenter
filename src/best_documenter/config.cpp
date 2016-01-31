#include "config.h"

namespace best_documenter {
    Config::Config() {
    }

    Config::~Config() {
    }

    std::shared_ptr<model::Config> Config::load(
            const std::string& filename,
            std::string* err
            )
    {
        std::ifstream ifs;
        ifs.open(filename);

        std::stringstream ss;
        ss << ifs.rdbuf();
        std::string str = ss.str();

        value out;
        parse(out, str.begin(), str.end(), err);
        if (!err->empty()) { return std::shared_ptr<model::Config>(); }

        return model::Config::inflate(out, err);
    }
}
