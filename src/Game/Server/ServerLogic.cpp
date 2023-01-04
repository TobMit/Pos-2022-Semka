//
// Created by Matúš Mištrik on 02/01/2023.
//

#include "ServerLogic.h"

ServerLogic::ServerLogic() {
    resetPositions();
    isStarted = false;
    scorePlayer1 = 0;
    scorePlayer2 = 0;
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

void ServerLogic::update() {
    if (!isStarted) {
        return;
    }

    ballPosition.x += std::cos(ballAngle) * constants::ballSpeed;
    ballPosition.y += std::sin(ballAngle) * constants::ballSpeed;

    //boundries collisions checking

    if (ballPosition.x - constants::ballRadius / 2 < 0.f) {
        //prehral player1
        resetPositions();
    }
    if (ballPosition.x + constants::ballRadius / 2 > constants::windowWidth) {
        //prehral player2
        resetPositions();
    }
    if (ballPosition.y - constants::ballRadius / 2 < 0.f) {
        ballAngle = -ballAngle;
        ballPosition.y = constants::ballRadius + 0.1f;
    }
    if (ballPosition.y + constants::ballRadius / 2 > constants::windowHeight) {
        ballAngle = -ballAngle;
        ballPosition.y = constants::windowHeight - constants::ballRadius - 0.1f;
    }

    //player1 pad collisions checking

    if (ballPosition.x - constants::ballRadius / 2 < player1Position.x + constants::paddleSize.x / 2 &&
        ballPosition.x - constants::ballRadius / 2 > player1Position.x - constants::paddleSize.x / 2 &&
        ballPosition.y - constants::ballRadius / 2 <= player1Position.y + constants::paddleSize.y / 2 &&
        ballPosition.y + constants::ballRadius / 2 >= player1Position.y - constants::paddleSize.y / 2) {
        if (ballPosition.y > player1Position.y)
            ballAngle = constants::pi - ballAngle + (std::rand() % 20) * constants::pi / 180;
        else
            ballAngle = constants::pi - ballAngle - (std::rand() % 20) * constants::pi / 180;

        ballPosition.x = player1Position.x + constants::ballRadius / 2 + constants::paddleSize.x / 2 + 0.1f;
    }

    //player2 pad collisions checking

    if (ballPosition.x + constants::ballRadius / 2 > player2Position.x - constants::paddleSize.x / 2 &&
        ballPosition.x + constants::ballRadius / 2 < player2Position.x + constants::paddleSize.x / 2 &&
        ballPosition.y - constants::ballRadius / 2 <= player2Position.y + constants::paddleSize.y / 2 &&
        ballPosition.y + constants::ballRadius / 2 >= player2Position.y - constants::paddleSize.y / 2) {
        if (ballPosition.y > player2Position.y)
            ballAngle = constants::pi - ballAngle + (std::rand() % 20) * constants::pi / 180;
        else
            ballAngle = constants::pi - ballAngle - (std::rand() % 20) * constants::pi / 180;

        ballPosition.x = player2Position.x - constants::ballRadius / 2 - constants::paddleSize.x / 2 - 0.1f;
    }


}

ServerResponseData ServerLogic::getDataForClient(bool isLeft) {
    ServerResponseData responseData;
    if (isLeft) {
        responseData.player1PaddleY = player1Position.y;
        responseData.player2PaddleY = player2Position.y;
        responseData.ballX = ballPosition.x;
        responseData.ballY = ballPosition.y;
    } else {
        responseData.player1PaddleY = player2Position.y;
        responseData.player2PaddleY = player1Position.y;
        float tmp = ballPosition.x * -1;
        responseData.ballX = constants::windowWidth + tmp;
        responseData.ballY = ballPosition.y;
    }
    return responseData;
}

void ServerLogic::resetPositions() {
    player1Position.x = 10 + constants::paddleSize.x / 2;
    player1Position.y = constants::windowHeight / 2;
    player2Position.x = constants::windowWidth - 10 - constants::paddleSize.x /2;
    player2Position.y = constants::windowHeight / 2;
    ballPosition.x = constants::windowWidth / 2;
    ballPosition.y = constants::windowHeight / 2;
    do
    {
        ballAngle = (random() % 360) * 2 * constants::pi / 360;
    }
    while (std::abs(std::cos(ballAngle)) < 0.7f);
}
