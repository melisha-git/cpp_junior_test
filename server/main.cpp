#include "../pkg/parser/parser.h"
#include "Server.h"

#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong number of arguments";
        return 1;
    }

    std::string portStr(argv[1]);

    try {
        int port = parser::parsePort(portStr);

        Server server(port);
        server.start();
    } catch (const std::exception& ex) {
        std::cerr << ex.what();
        return 1;
    }

    
}