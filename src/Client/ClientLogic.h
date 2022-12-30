//
// Created by Matúš Mištrik on 29/12/2022.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../Constants/Constants.h"
#include "../Constants/GameData.h"
#include "../Graphics/Ball/Ball.h"
#include "../Graphics/Paddle/Paddle.h"

class ClientLogic {

    static const float windowHeight;
    static const float windowWidth;

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