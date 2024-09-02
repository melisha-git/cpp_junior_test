#include "Client.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>


Client::Client(const std::string& name, int port, int64_t connectionPeriod) 
        : name_(name), port_(port), connectionPeriod_(connectionPeriod) {}

void Client::connectToServer() {
    if (socket_ = socket(AF_INET, SOCK_STREAM, 0); socket_ < 0) {
        throw std::logic_error("Error create socket");
    }

    struct sockaddr_in serverCreds;
    serverCreds.sin_family = AF_INET;
    serverCreds.sin_port = htons(port_);

    if (inet_pton(AF_INET, "127.0.0.1", &serverCreds.sin_addr) <= 0) {
        throw std::logic_error("Invalid address or port");
    }
        
    int flags = fcntl(socket_, F_GETFL, 0);
    fcntl(socket_, F_SETFL, flags | O_NONBLOCK);

    if (connect(socket_, reinterpret_cast<struct sockaddr *>(&serverCreds), sizeof(serverCreds)) < 0 && errno != EINPROGRESS) {
        throw std::logic_error("Connection error");
    }
        
    fd_set set;
    struct timeval timeout {connectionPeriod_, 0};
    FD_ZERO(&set);
    FD_SET(socket_, &set);
        
    auto result = select(socket_ + 1, nullptr, &set, nullptr, &timeout);
    if (result < 0) {
        throw std::logic_error("Connection error");
    }
    if (result == 0) {
        throw std::logic_error("Connection timeout");
    }
        
    int errors = 0;
    socklen_t len = sizeof(errors);
    getsockopt(socket_, SOL_SOCKET, SO_ERROR, &errors, &len);
        
    if (errors != 0) {
        throw std::logic_error("Connection error");
    }

    fcntl(socket_, F_SETFL, flags);
}

void Client::disconnect() {
    if (keepAlive()) {
        close(socket_);
    }
}

bool Client::keepAlive() {
    struct sockaddr_in peer;
    socklen_t perrLen = sizeof(peer);
    if (getpeername(socket_, reinterpret_cast<struct sockaddr *>(&peer), &perrLen) == -1) {
        return false;
    }
    return true;
}

void Client::sendToServer(const std::string& message) {
    send(socket_, message.c_str(), message.size(), 0);
}

Client::~Client() {
    disconnect(); 
}