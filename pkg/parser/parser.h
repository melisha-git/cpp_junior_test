#pragma once

#include <string>

namespace parser
{
    int parsePort(const std::string& portStr);
    int64_t parseTime(const std::string& timeStr);
}
