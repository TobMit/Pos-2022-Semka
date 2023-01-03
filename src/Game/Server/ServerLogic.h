//
// Created by Matúš Mištrik on 02/01/2023.
//

#pragma once


#include "../../Constants/GameData.h"
#include <SFML/Graphics.hpp>

class ServerLogic {
    sf::Vector2f player1Position;
    sf::Vector2f player2Position;
    sf::Vector2f ballPosition;
    float ballAngle;
    ServerLogic();

public:
    ServerData processData(ClientData data, bool isLeftPlayer);
};