//
// Created by Matúš Mištrik on 02/01/2023.
//

#include "ServerLogic.h"

ServerLogic::ServerLogic() {
    resetPositions();
    serverStatus = gameStatus::WAITING;
    scorePlayer1 = 0;
    scorePlayer2 = 0;
    time = 3;
    roundPause = 3;
    bounce = false;
}

void ServerLogic::processData(ClientData* data, bool isLeftPlayer) {
    isLeftPlayer ? player1Direction = data->direction : player2Direction = data->direction;
}

void ServerLogic::update() {
    if (serverStatus != gameStatus::PLAYING) {
        return;
    }
    bounce = false;


    switch (player1Direction) {
        case constants::UP:
            player1Position.y -= constants::paddleSpped;
            break;

        case constants::DOWN:
            player1Position.y += constants::paddleSpped;
            break;

        default:
            break;
    }

    switch (player2Direction) {
        case constants::UP:
            player2Position.y -= constants::paddleSpped;
            break;

        case constants::DOWN:
            player2Position.y += constants::paddleSpped;
            break;

        default:
            break;
    }

    ballPosition.x += std::cos(ballAngle) * constants::ballSpeed;
    ballPosition.y += std::sin(ballAngle) * constants::ballSpeed;

    //boundries collisions checking
    if (ballPosition.x - constants::ballRadius / 2 < 0.f) {
        scorePlayer2++;
        setServerStatus(gameStatus::COLLISION);
        resetPositions();
        roundWinPlayer1 = false;
    }
    if (ballPosition.x + constants::ballRadius / 2 > constants::windowWidth) {
        scorePlayer1++;
        setServerStatus(gameStatus::COLLISION);
        resetPositions();
        roundWinPlayer1 = true;
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
        bounce = true;
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
        bounce = true;
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
    responseData.bounce = bounce;
    return responseData;
}

void ServerLogic::resetPositions() {
    player1Position.x = 10 + constants::paddleSize.x / 2;
    player1Position.y = constants::windowHeight / 2;
    player2Position.x = constants::windowWidth - 10 - constants::paddleSize.x /2;
    player2Position.y = constants::windowHeight / 2;
    player1Direction = constants::NONE;
    player2Direction = constants::NONE;
    ballPosition.x = constants::windowWidth / 2;
    ballPosition.y = constants::windowHeight / 2;
    do
    {
        ballAngle = (random() % 360) * 2 * constants::pi / 360;
    }
    while (std::abs(std::cos(ballAngle)) < 0.7f);
}

GameInfoData ServerLogic::coundDown() {
    GameInfoData data;
    if (time > 0) {
        data.msg = gameStatus::COUNTDOWN;
        data.other = time--;
    } else {
        data.msg = gameStatus::PLAYING;
        setServerStatus(gameStatus::PLAYING);
        time = 3;
    }
    return data;
}

GameInfoData ServerLogic::getClientStatus(bool isLeft) {
    GameInfoData data;
    if (isLeft) {
        data.scoreP1 = scorePlayer1;
        data.scoreP2 = scorePlayer2;
        if (roundWinPlayer1) {
            data.msg = gameStatus::WIN;
        } else {
            data.msg = gameStatus::LOSE;
        }
    } else {
        data.scoreP1 = scorePlayer2;
        data.scoreP2 = scorePlayer1;
        if (roundWinPlayer1) {
            data.msg = gameStatus::LOSE;
        } else {
            data.msg = gameStatus::WIN;
        }
    }
    return data;
}

bool ServerLogic::puseTick() {
    roundPause--;
    if (roundPause <= 0) {
        roundPause = constants::ROUNDPAUSE;
        setServerStatus(gameStatus::PLAYING);
        return false;
    }
    return true;

}

void ServerLogic::restGame() {
    resetPositions();
    scorePlayer1 = 0;
    scorePlayer2 = 0;

}
