#include "Client.h"
#include "../pkg/parser/parser.h"

#include <iostream>
#include <string>

#include <chrono>
#include <iomanip>
#include <sstream>

std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");

    oss << '.' << std::setw(3) << std::setfill('0') << ms.count();

    return oss.str();
}

int main(int argc, char* argv[]) {
    
    if (argc != 4) {
        std::cerr << "Wrong number of arguments";
        return 1;
    }

    std::string clientName(argv[1]);
    std::string portStr(argv[2]);
    std::string timeStr(argv[3]);

    try {
        int port = parser::parsePort(portStr);
        int64_t time = parser::parseTime(timeStr);

        Client client (clientName, port, time);
        client.connectToServer();
        client.sendToServer("[" + getCurrentDateTime() + "] \"" + clientName + "\"");
    } catch (const std::exception& ex) {
        std::cerr << ex.what();
        return 1;
    }
    
    return 0;
}
