#pragma once

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string& fileName);

    void log(const std::string& message);

    ~Logger();
private:
    std::ofstream file_;
};