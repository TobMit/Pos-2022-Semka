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
    if (isLeftPlayer) {
//        switch (data.movement) {
//
//        }
    }
    return ServerData();
}