cmake_minimum_required(VERSION 3.18)
project(Pos_2022_Semka CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(Pos_2022_Semka
        src/main.cpp)
add_executable(Server
        "src/Client-server/server.cpp")
add_executable(Client
        src/Client-server/client.cpp)
