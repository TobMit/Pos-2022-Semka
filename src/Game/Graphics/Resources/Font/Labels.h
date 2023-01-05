//
// Created by Tobias on 05/01/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../../../../Constants/Constants.h"
#include <cstring>
#include <iostream>

class Labels {
public:
    enum MessageType { WAITING, COUNTDOWN, WIN, LOSE };

private:
    sf::Font font;
    sf::Text player1Score;
    sf::Text player2Score;
    sf::Text message;
    bool isFontLoaded;

public:
    Labels();
    bool updatePlayersScore(int player1Score, int player2Score);
    bool updateMessage(MessageType messageType, int countDownValue);

    inline const sf::Text& player1ScoreText() const { return player1Score; }
    inline const sf::Text& player2ScoreText() const { return player1Score; }
    inline const sf::Text& messageText() const { return player1Score; }
};
