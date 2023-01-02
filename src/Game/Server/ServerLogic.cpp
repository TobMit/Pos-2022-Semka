//
// Created by Matúš Mištrik on 02/01/2023.
//

#include "ServerLogic.h"

ServerLogic::ServerLogic()
: player1Position(10 + constants::paddleSize.x / 2, constants::windowHeight / 2),
  player2Position()
{

}

ServerData ServerLogic::processData(ClientData data, bool isLeftPlayer) {
//    switch (data.movement.direction) {
//        case constants::UP:
//            break;
//
//        case constants::DOWN:
//            break;
//    }
    return ServerData();
}