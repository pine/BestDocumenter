#include <string>
#include <cmdline.h>

namespace best_documenter {
    class Parser {
    public:
        Parser();
        ~Parser();

        void parse(int argc, char** argv);
        std::string getConfigFileName();

    private:
        cmdline::parser parser_;
    };
}
