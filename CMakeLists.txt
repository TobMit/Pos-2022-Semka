cmake_minimum_required(VERSION 3.18.4)
project(Pos_2022_Semka)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        Pos_2022_Semka
        src/main.cpp
)
add_executable(
        Grafika
        src/Graphics/Main_Game.cpp
        src/Graphics/Game.cpp
        src/Graphics/Game.h
        src/Graphics/Ball/Ball.cpp
        src/Graphics/Ball/Ball.h
        src/Graphics/Constants/Constants.h
        src/Graphics/Paddle/Paddle.cpp
        src/Graphics/Paddle/Paddle.h
)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Grafika sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(Pos_2022_Semka sfml-system sfml-network)

add_executable(Server
        src/SFML-client_server/Server.cpp
        src/SFML-client_server/Sockets/Sockets.cpp
        src/SFML-client_server/Sockets/Sockets.h
        src/SFML-client_server/Sockets/MultiServer/MultiServer.h
        src/SFML-client_server/Sockets/MultiServer/MultiServer.cpp)


add_executable(SimpleServer
        src/SFML-client_server/Sockets/Sockets.cpp
        src/SFML-client_server/Sockets/Sockets.h
        src/SFML-client_server/Sockets/SimpleServer.h
        src/SFML-client_server/ServerTest.cpp)

add_executable(Client
        src/SFML-client_server/ClientTest.cpp
        src/SFML-client_server/Sockets/Sockets.cpp
        src/SFML-client_server/Sockets/Sockets.h
        src/SFML-client_server/Sockets/Client.h
        src/Constants.h)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Server sfml-network pthread)
target_link_libraries(SimpleServer sfml-network)
target_link_libraries(Client sfml-network pthread)
