cmake_minimum_required(VERSION 3.18.4)
project(Pos_2022_Semka)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})


add_executable(GameClient
        src/MainClient.cpp
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
        src/Game/Server/ServerLogic.h
        src/Game/Graphics/Resources/Resources.h
        src/Game/Graphics/Resources/Sounds/Sounds.cpp
        src/Game/Graphics/Resources/Sounds/Sounds.h
        src/Game/Graphics/Resources/Labels/Labels.cpp
        src/Game/Graphics/Resources/Labels/Labels.h)

add_executable(GameServer
        src/MainServer.cpp
        src/Sockets/Sockets.cpp
        src/Sockets/Sockets.h
        src/Sockets/MultiServer/MultiServer.h
        src/Sockets/MultiServer/MultiServer.cpp
        src/Constants/Constants.h
        src/Constants/GameData.h
        src/Game/Server/ServerLogic.cpp
        src/Game/Server/ServerLogic.h
        src/Game/Server/ServerGame.cpp
        src/Game/Server/ServerGame.h)

target_link_libraries(GameServer sfml-network sfml-graphics pthread)
target_link_libraries(GameClient sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

