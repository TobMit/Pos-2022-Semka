//
// Created by Matúš Mištrik on 29/12/2022.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../../Constants/GameData.h"
#include "../Graphics/Paddle/Paddle.h"
#include "../Graphics/Ball/Ball.h"
#include "../Graphics/Resources/Resources.h"

class ClientLogic {
private:
    sf::RenderWindow mainWindow;
    Ball ball;
    Paddle player1;
    Paddle player2;
    int state;
    int playerScore1;
    int playerScore2;
    int countDownNumber;
    Resources resources;

    constants::Direction handlePlayerInputs(sf::Keyboard::Key key, bool isPressed);

public:
    ClientLogic();
    inline bool isRunning() { return mainWindow.isOpen(); }
    constants::Direction processEvents();
    void update(ServerResponseData data);
    void render();
    void closeWindow(){ mainWindow.close();}
    void setGameState(int pState);
    void win(int player1, int player2);
    void lose(int player1, int player2);
    void showNumber(int number) {
        countDownNumber = number;
    };


private:
    void setGameScore(int player1, int player2);
};