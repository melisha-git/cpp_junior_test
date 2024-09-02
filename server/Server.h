#pragma once

#include "../pkg/logger/Logger.h"

class Server {
public:
    explicit Server(int port);
    void start();

    ~Server();

private:
    Logger logger;
    void handleClient(int client);
    int port_;
    
};