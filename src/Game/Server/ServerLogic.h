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
    float ballAngle;
    bool isStarted;
    int scorePlayer1;
    int scorePlayer2;

public:
    ServerLogic();
    float processData(ClientData* data, bool isLeftPlayer);
    void update();
    ServerResponseData getDataForClient(bool isLeft);
    void setStart(bool start) {
        isStarted = start;
    }

private:
    void resetPositions();
};