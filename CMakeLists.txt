cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(parser
    pkg/parser/parser.cpp
    pkg/parser/parser.h
)

add_library(logger
    pkg/logger/Logger.cpp
    pkg/logger/Logger.h
)

add_executable(Server
    server/main.cpp
    server/Server.cpp
)

target_link_libraries(Server
    parser
    logger
)

add_executable(Client
    client/Client.cpp
    client/main.cpp
)

target_link_libraries(Client
    parser
)