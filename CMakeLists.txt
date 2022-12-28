cmake_minimum_required(VERSION 3.18)
project(Pos_2022_Semka)

set(CMAKE_CXX_STANDARD 11)

add_executable(Pos_2022_Semka
        src/main.cpp)
add_executable(Server
        "src/Client-server/server.cpp"
        src/Client-server/Socket/Server.h
        src/Client-server/Socket/Socket.cpp
        src/Client-server/Socket/Server.h)

add_executable(Client
        src/Client-server/client.cpp
        src/Client-server/definition.h
        src/Client-server/Socket/Socket.h
        src/Client-server/Socket/Socket.cpp
        src/Client-server/Socket/Server.h
        src/Client-server/Socket/Client.h)
