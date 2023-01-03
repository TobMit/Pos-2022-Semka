//
// Created by Matúš Mištrik on 29/12/2022.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../../Constants/GameData.h"
#include "../Graphics/Paddle/Paddle.h"
#include "../Graphics/Ball/Ball.h"

class ClientLogic {

    sf::RenderWindow mainWindow;
    Ball ball;
    Paddle player1;
    Paddle player2;

    static constants::Movement handlePlayerInputs(sf::Keyboard::Key key, bool isPressed);

public:
    ClientLogic();
    inline bool isRunning() { return mainWindow.isOpen(); }
    constants::Movement processEvents();
    void update(ServerData data);
    void render();

};