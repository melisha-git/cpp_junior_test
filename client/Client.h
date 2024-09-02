#pragma once

#include <string>

class Client {
public:
    Client(const std::string& name, int port, int64_t connectionPeriod);
    
    void connectToServer();
    void disconnect();
    bool keepAlive();
    
    void sendToServer(const std::string& message);

    ~Client();
private:
    int socket_;
    std::string name_;
    int port_;
    int64_t connectionPeriod_;
};