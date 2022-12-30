//
// Created by Matúš Mištrik on 30/12/2022.
//

#pragma once

#include "ClientLogic.h"


class ClientGame {

    ClientLogic game;

public:
    void run();
    void update(ServerData data);
};

