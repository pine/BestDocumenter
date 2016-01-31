#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <picojson.h>
#include "model/config.h"
#include "model/result.h"

namespace best_documenter {
    class Config {
    public:
        Config();
        ~Config();

        std::shared_ptr<model::Config> load(
                const std::string& filename,
                std::string* err
                );

    private:
        std::string filename_;
    };
}
