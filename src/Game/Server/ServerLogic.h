//
// Created by Matúš Mištrik on 02/01/2023.
//

#pragma once


#include "../../Constants/GameData.h"
#include <cmath>
#include <SFML/Graphics.hpp>

class ServerLogic {
private:
    sf::Vector2f player1Position;
    sf::Vector2f player2Position;
    sf::Vector2f ballPosition;
    constants::Direction player1Direction;
    constants::Direction player2Direction;
    float ballAngle;
    int serverStatus;
    int scorePlayer1;
    int scorePlayer2;
    /**
     * Používa sa napríklad na odpočítavanie
     */
    int time;
    bool roundWinPlayer1;
    int roundPause;

public:
    ServerLogic();
    void processData(ClientData* data, bool isLeftPlayer);
    void update();
    ServerResponseData getDataForClient(bool isLeft);
    void setServerStatus(int pStatus) {
        serverStatus = pStatus;
    }
    int getServerStatus() {
        return serverStatus;
    }
    GameInfoData coundDown();

    GameInfoData getClientStatus(bool isLeft);

    /**
     * Pause countdown
     * @return if is pause
     */
    bool puseTick();

    void restGame();

private:
    void resetPositions();
};