#include "Logger.h"

Logger::Logger(const std::string& fileName) {
    file_.open(fileName, std::ios::app);
}

void Logger::log(const std::string& message) {
    file_ << message << std::endl;
}

Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
}