#include "Server.h"

#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(int port) : port_(port), logger("log.txt") {}

void Server::start() {
    int server = 0, client = 0;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        close(server);
        throw std::logic_error("Error creation socket");
    }

    int opt = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        close(server);
        throw std::logic_error("Error init socket");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    if (bind(server, (struct sockaddr *)&address, sizeof(address)) < 0) {
        throw std::logic_error("Error init socket");
    }

    if (listen(server, 3) < 0) {
        throw std::logic_error("Listen error");
    }

    while (true) {
        if ((client = accept(server, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            close(server);
            throw std::logic_error("Accepting error");
        }

        std::thread(&Server::handleClient, this, client).detach();
    }
}

Server::~Server() {

}

void Server::handleClient(int client) {
    char buffer[1024];
    int valread;

    while ((valread = read(client, buffer, 1024)) > 0) {
        buffer[valread] = '\0';
        logger.log(buffer);
    }

    close(client);
}
