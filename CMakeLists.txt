cmake_minimum_required(VERSION 3.18.4)
project(Pos_2022_Semka)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})


add_executable(Grafika
        src/Game/Main_Game.cpp
        src/Game/Game.cpp
        src/Game/Game.h
        src/Game/Graphics/Ball/Ball.cpp
        src/Game/Graphics/Ball/Ball.h
        src/Game/Graphics/Paddle/Paddle.cpp
        src/Game/Graphics/Paddle/Paddle.h
        src/Constants/GameData.h
        src/Game/Client/ClientLogic.cpp
        src/Game/Client/ClientLogic.h
        src/Game/Client/ClientGame.cpp
        src/Game/Client/ClientGame.h
        src/Game/Server/ServerLogic.cpp
        src/Game/Server/ServerLogic.h)

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
        src/Constants/Constants.h)

add_executable(GameServer
        src/MainServer.cpp
        src/SFML-client_server/Sockets/Sockets.cpp
        src/SFML-client_server/Sockets/Sockets.h
        src/SFML-client_server/Sockets/MultiServer/MultiServer.h
        src/SFML-client_server/Sockets/MultiServer/MultiServer.cpp
        src/Constants/Constants.h
        src/Constants/GameData.h
        src/Game/Server/ServerLogic.cpp
        src/Game/Server/ServerLogic.h
        src/Game/Server/ServerGame.cpp
        src/Game/Server/ServerGame.h)
target_link_libraries(Server sfml-network pthread sfml-graphics)
target_link_libraries(SimpleServer sfml-network sfml-graphics)
target_link_libraries(GameServer sfml-network sfml-graphics pthread)
target_link_libraries(Client sfml-network pthread sfml-graphics)
target_link_libraries(Grafika sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

