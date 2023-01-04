//
// Created by Matúš Mištrik on 02/01/2023.
//

#include "ServerLogic.h"

ServerLogic::ServerLogic()
: player1Position(10 + constants::paddleSize.x / 2, constants::windowHeight / 2),
  player2Position(constants::windowWidth - 10 - constants::paddleSize.x /2, constants::windowHeight / 2),
  ballPosition(constants::windowWidth / 2, constants::windowHeight / 2)
{
    do
    {
        ballAngle = (random() % 360) * 2 * constants::pi / 360;
    }
    while (std::abs(std::cos(ballAngle)) < 0.7f);
}

float ServerLogic::processData(ClientData* data, bool isLeftPlayer) {
    switch (data->direction) {
        case constants::UP:
            isLeftPlayer ? player1Position.y -= constants::paddleSpped : player2Position.y -= constants::paddleSpped;
            break;

        case constants::DOWN:
            isLeftPlayer ? player1Position.y += constants::paddleSpped : player2Position.y += constants::paddleSpped;
            break;//Matúúš makaj iks Dé         som zvedavý kedy si to všimneš potom sa ohlás - sak ja makam jako srob, len zrovna na inom projekte :D :D

        default:
            break;
    }
    return isLeftPlayer ? player1Position.y : player2Position.y;
}

ServerResponseData ServerLogic::update() {

    return ServerResponseData();
}
