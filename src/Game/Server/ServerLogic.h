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
    bool roundWinPlayer1;
    bool bounce;
    int roundPause;
    /**
     * Používa sa napríklad na odpočítavanie
     */
    int time;

public:
    ServerLogic();

    void update();
    void processData(ClientData* data, bool isLeftPlayer);

    GameInfoData countdown();
    GameInfoData getClientStatus(bool isLeft) const;
    ServerResponseData getDataForClient(bool isLeft) const;

    inline void setServerStatus(int pStatus) { serverStatus = pStatus; }
    inline int getServerStatus() const { return serverStatus; }

    /**
     * Pause countdown
     * @return if is pause
     */
    bool pauseTick();
    void restGame();

private:
    void resetPositions();
};