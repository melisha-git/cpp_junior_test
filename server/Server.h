#pragma once

#include "../pkg/logger/Logger.h"
#include <mutex>

class Server {
public:
    explicit Server(int port);
    void start();

    ~Server();

private:
    Logger logger_;
    void handleClient(int client);
    int port_;
    std::mutex loggerMutex_;
};
