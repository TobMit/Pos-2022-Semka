//
// Created by Matúš Mištrik on 29/12/2022.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../Graphics/Ball/Ball.h"
#include "../Graphics/Paddle/Paddle.h"

class ClientGame {
    inline bool isRunning() { return mainWindow.isOpen(); }
    static const float windowHeight;
    static const float windowWidth;
    float ballAngle;

    sf::RenderWindow mainWindow;
    Ball ball;
    Paddle player1;
    Paddle player2;

public:
    ClientGame();
    void processEvents();
    void update();
    void render();
};