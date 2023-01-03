//
// Created by Matúš Mištrik on 02/01/2023.
//

#include "ServerLogic.h"

ServerLogic::ServerLogic()
: player1Position(10 + constants::paddleSize.x / 2, constants::windowHeight / 2),
  player2Position()
{
//    do
//    {
//        ballAngle = (random() % 360) * 2 * constants::pi / 360;
//    }
//    while (std::abs(std::cos(ballAngle)) < 0.7f);
}

float ServerLogic::processData(ClientData* data, bool isLeftPlayer) {
    switch (data->direction) {
        case constants::UP:
            isLeftPlayer ? player1Position.y -= constants::paddleSpped : player2Position.y -= constants::paddleSpped;
            break;

        case constants::DOWN:
            isLeftPlayer ? player1Position.y += constants::paddleSpped : player2Position.y += constants::paddleSpped;
            break;

        default:
            break;
    }
    return isLeftPlayer ? player1Position.y : player2Position.y;
}

ServerData ServerLogic::update() {
    return ServerData();
}
