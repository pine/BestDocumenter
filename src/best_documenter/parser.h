#include <cinttypes>
#include <string>
#include <cmdline.h>

namespace best_documenter {
    class Parser {
    public:
        Parser();
        ~Parser();

        void parse(int argc, char** argv);

        std::string getConfigFileName();
        int32_t getDurationDays();

    private:
        cmdline::parser parser_;
    };
}
