//
// Created by Matúš Mištrik on 30/12/2022.
//

#pragma once

#include "ClientLogic.h"
#include <iostream>
#include "../../SFML-client_server/Sockets/Client.h"


class ClientGame {
private:
    ClientLogic game;
    Client client;

public:
    void run();
    void update();
    void update(ServerResponseData data);

    void processPacket(sf::Packet *packet);
};

