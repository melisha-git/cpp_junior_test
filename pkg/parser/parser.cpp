#include "parser.h"

#include <iostream>
#include <climits>

namespace parser
{
    int parsePort(const std::string& portStr) {
        int port = std::stoi(portStr);
        if (port < 0 || port > USHRT_MAX) {
            std::cerr << "Port is invalid. Max port number - " + std::to_string(USHRT_MAX);
            return 1;
        }
        return port;
    }

    int64_t parseTime(const std::string& timeStr) {
        int64_t time = std::stoll(timeStr);
        if (time < 0) {
            std::cerr << "Time is invalid";
            return 1;
        }
        return time;
    }
}
