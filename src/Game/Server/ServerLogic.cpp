//
// Created by Matúš Mištrik on 02/01/2023.
//

#include "ServerLogic.h"

ServerLogic::ServerLogic() {
    resetPositions();
    serverStatus = GameStatus::WAITING;
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
    if (serverStatus != GameStatus::PLAYING) {
        return;
    }
    bounce = false;


    switch (player1Direction) {
        case constants::UP:
            player1Position.y -= player1Position.y > 0 ? constants::PADDLE_SPEED : 0.f;
            break;

        case constants::DOWN:
            player1Position.y += player1Position.y > constants::WINDOW_HEIGHT ? constants::PADDLE_SPEED : 0.f;
            break;

        default:
            break;
    }

    switch (player2Direction) {
        case constants::UP:
            player2Position.y -= player2Position.y > 0 ? constants::PADDLE_SPEED : 0.f;
            break;

        case constants::DOWN:
            player2Position.y += player2Position.y > 0 ? constants::PADDLE_SPEED : 0.f;
            break;

        default:
            break;
    }

    ballPosition.x += std::cos(ballAngle) * constants::BALL_SPEED;
    ballPosition.y += std::sin(ballAngle) * constants::BALL_SPEED;

    //boundries collisions checking
    if (ballPosition.x - constants::BALL_RADIUS < 0.f) {
        scorePlayer2++;
        setServerStatus(GameStatus::COLLISION);
        resetPositions();
        roundWinPlayer1 = false;
    }
    if (ballPosition.x + constants::BALL_RADIUS > constants::WINDOW_WIDTH) {
        scorePlayer1++;
        setServerStatus(GameStatus::COLLISION);
        resetPositions();
        roundWinPlayer1 = true;
    }
    if (ballPosition.y - constants::BALL_RADIUS < 0.f) {
        ballAngle = -ballAngle;
        ballPosition.y = constants::BALL_RADIUS + 0.1f;
    }
    if (ballPosition.y + constants::BALL_RADIUS > constants::WINDOW_HEIGHT) {
        ballAngle = -ballAngle;
        ballPosition.y = constants::WINDOW_HEIGHT - constants::BALL_RADIUS - 0.1f;
    }

    //player1 pad collisions checking

    if (ballPosition.x - constants::BALL_RADIUS < player1Position.x + constants::PADDLE_SIZE.x / 2 &&
        ballPosition.x - constants::BALL_RADIUS > player1Position.x &&
        ballPosition.y - constants::BALL_RADIUS <= player1Position.y + constants::PADDLE_SIZE.y / 2 &&
        ballPosition.y + constants::BALL_RADIUS >= player1Position.y - constants::PADDLE_SIZE.y / 2) {
        if (ballPosition.y > player1Position.y)
            ballAngle = constants::PI - ballAngle + (std::rand() % 20) * constants::PI / 180;
        else
            ballAngle = constants::PI - ballAngle - (std::rand() % 20) * constants::PI / 180;

        ballPosition.x = player1Position.x + constants::BALL_RADIUS + constants::PADDLE_SIZE.x / 2 + 0.1f;
        bounce = true;
    }

    //player2 pad collisions checking

    if (ballPosition.x + constants::BALL_RADIUS > player2Position.x - constants::PADDLE_SIZE.x / 2 &&
        ballPosition.x + constants::BALL_RADIUS < player2Position.x &&
        ballPosition.y - constants::BALL_RADIUS <= player2Position.y + constants::PADDLE_SIZE.y / 2 &&
        ballPosition.y + constants::BALL_RADIUS >= player2Position.y - constants::PADDLE_SIZE.y / 2) {
        if (ballPosition.y > player2Position.y)
            ballAngle = constants::PI - ballAngle + (std::rand() % 20) * constants::PI / 180;
        else
            ballAngle = constants::PI - ballAngle - (std::rand() % 20) * constants::PI / 180;

        ballPosition.x = player2Position.x - constants::BALL_RADIUS - constants::PADDLE_SIZE.x / 2 - 0.1f;
        bounce = true;
    }

}

ServerResponseData ServerLogic::getDataForClient(bool isLeft) const {
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
        responseData.ballX = constants::WINDOW_WIDTH + tmp;
        responseData.ballY = ballPosition.y;
    }
    responseData.bounce = bounce;
    return responseData;
}

void ServerLogic::resetPositions() {
    player1Position.x = 10 + constants::PADDLE_SIZE.x / 2;
    player1Position.y = constants::WINDOW_HEIGHT / 2;
    player2Position.x = constants::WINDOW_WIDTH - 10 - constants::PADDLE_SIZE.x / 2;
    player2Position.y = constants::WINDOW_HEIGHT / 2;
    player1Direction = constants::NONE;
    player2Direction = constants::NONE;
    ballPosition.x = constants::WINDOW_WIDTH / 2;
    ballPosition.y = constants::WINDOW_HEIGHT / 2;
    do
    {
        ballAngle = (random() % 360) * 2 * constants::PI / 360;
    }
    while (std::abs(std::cos(ballAngle)) < 0.7f);
}

GameInfoData ServerLogic::countdown() {
    GameInfoData data;
    if (time > 0) {
        data.msg = GameStatus::COUNTDOWN;
        data.other = time--;
    } else {
        data.msg = GameStatus::PLAYING;
        setServerStatus(GameStatus::PLAYING);
        time = 3;
    }
    return data;
}

GameInfoData ServerLogic::getClientStatus(bool isLeft) const {
    GameInfoData data;
    if (isLeft) {
        data.scoreP1 = scorePlayer1;
        data.scoreP2 = scorePlayer2;
        if (roundWinPlayer1) {
            data.msg = GameStatus::WIN;
        } else {
            data.msg = GameStatus::LOSE;
        }
    } else {
        data.scoreP1 = scorePlayer2;
        data.scoreP2 = scorePlayer1;
        if (roundWinPlayer1) {
            data.msg = GameStatus::LOSE;
        } else {
            data.msg = GameStatus::WIN;
        }
    }
    return data;
}

bool ServerLogic::pauseTick() {
    roundPause--;
    if (roundPause <= 0) {
        roundPause = constants::ROUND_PAUSE;
        setServerStatus(GameStatus::PLAYING);
        return false;
    }
    return true;

}

void ServerLogic::restGame() {
    resetPositions();
    scorePlayer1 = 0;
    scorePlayer2 = 0;

}
