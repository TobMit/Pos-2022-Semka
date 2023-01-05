//
// Created by Tobias on 04/01/2023.
//
#pragma once
#include "../../SFML-client_server/Sockets/MultiServer/MultiServer.h"
#include "../../Constants/GameData.h"
#include "ServerLogic.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

class ServerGame {
private:
    MultiServer server;
    ServerLogic serverLogic;

    std::mutex mut;
    std::condition_variable writeToBuff;
    std::vector<std::string> buffer;

    sf::Time timePerFrame;
public:
    ServerGame();
    bool serverInicialise();
    void run();
private:
    void processConsole(bool *end);
    void processPacket(sf::Packet *packet, ClientPacket *clientPacket);
    void setSpeedToCountDown();
    void setSpeedToGame();
    void setSpeedToWait();
    void serverTick();
};

