#include "response.h"

namespace http {
    void Response::appendBody(char* ptr, size_t n) {
        stream_.write(ptr, n);
    }
}
