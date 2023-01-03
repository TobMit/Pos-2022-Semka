//
// Created by Matúš Mištrik on 02/01/2023.
//

#pragma once


#include "../../Constants/GameData.h"
#include <SFML/Graphics.hpp>

class ServerLogic {
private:
    sf::Vector2f player1Position;
    sf::Vector2f player2Position;
    sf::Vector2f ballPosition;
    float ballAngle;
public:
    ServerLogic();
    float processData(ClientData* data, bool isLeftPlayer);
    ServerData update();
};