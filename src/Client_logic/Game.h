//
// Created by Matúš Mištrik on 27/12/2022.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../Graphics/Ball/Ball.h"
#include "../Graphics/Paddle/Paddle.h"

class Game {
public:
    Game();
    void Run();

private:
    static const sf::Time timePerFrame;
    static const float windowHeight;
    static const float windowWidth;

    sf::RenderWindow mainWindow;
    Ball ball;
    Paddle player1;
    Paddle player2;
    bool isMovingUP = false;
    bool isMovingDOWN = false;

    float ballAngle;
    float playerSpeed = 400.f;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInputs(sf::Keyboard::Key key, bool isPressed);
};