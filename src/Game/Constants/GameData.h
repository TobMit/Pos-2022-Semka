//
// Created by Matúš Mištrik on 29/12/2022.
//

#pragma once
#include "../../Constants.h"

struct ServerData {

    float player1PaddleY;
    float player2PaddleY;
    float ballX;
    float ballY;

};

struct ClientData {

    constants::Movement movement;

};
