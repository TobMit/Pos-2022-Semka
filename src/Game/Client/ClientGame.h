//
// Created by Matúš Mištrik on 30/12/2022.
//

#pragma once

#include "ClientLogic.h"
#include <iostream>
#include "../../SFML-client_server/Sockets/Client.h"


class ClientGame {

    ClientLogic game;

public:
    void run();
    void update();
    void update(ServerData data);
};

