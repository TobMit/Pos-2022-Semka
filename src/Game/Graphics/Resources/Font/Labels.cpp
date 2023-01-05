//
// Created by Tobias on 05/01/2023.
//

#include "Labels.h"

Labels::Labels() {
    isFontLoaded = font.loadFromFile(constants::fontPath);
    if (isFontLoaded) {
        player1Score.setFont(font);
        player2Score.setFont(font);
        message.setFont(font);

        std::vector<sf::Text*> vectorOfTexts { &player1Score, &player2Score, &message };

        std::for_each(vectorOfTexts.begin(), vectorOfTexts.end(), [](sf::Text* text) {
            text->setString("0");
            text->setFillColor(sf::Color::Black);
            text->setCharacterSize(40);
        });
    }
}

bool Labels::updatePlayersScore(int player1, int player2) {
    if (isFontLoaded) {
        player1Score.setString(std::to_string(player1));
        player2Score.setString(std::to_string(player2));
        player1Score.setOrigin(player1Score.getGlobalBounds().width / 2, player1Score.getGlobalBounds().height / 2);
        player2Score.setOrigin(player2Score.getGlobalBounds().width / 2, player2Score.getGlobalBounds().height / 2);
        player1Score.setPosition(50.f, 50.f);
        player2Score.setPosition(constants::windowWidth - 50.f, 50.f);
    } else {
        std::cout << "SCORE:" << std::endl;
        std::cout << "YOU " << player1 << " : " << player2 << " OPPONENT" << std::endl << std::endl;
    }

    return isFontLoaded;
}

bool Labels::updateMessage(MessageType messageType, int countDownValue) {
    switch (messageType) {
        case WAITING:
            if (!isFontLoaded)
                std::cout << "WAITING FOR OPPONENT" << std::endl << std::endl;
            else {
                message.setString(constants::WAITING_MESSAGE);
                //todo pozicia
            }
            return isFontLoaded;

        case COUNTDOWN:
            if (countDownValue < 0 && isFontLoaded) {
                message.setString(std::to_string(countDownValue));
                //todo pozicia
            } else if (countDownValue == 1)
                std::cout << countDownValue << std::endl << std::endl;
            else
                std::cout << countDownValue << std::endl;
            return isFontLoaded;

        case WIN:
            if (!isFontLoaded)
                std::cout << "WIN" << std::endl << std::endl;
            else {
                message.setString(constants::WIN_MESSAGE);
                //todo pozicia
            }
            return isFontLoaded;

        case LOSE:
            if (!isFontLoaded)
                std::cout << "LOSE" << std::endl << std::endl;
            else {
                message.setString(constants::LOSE_MESSAGE);
                //todo pozicia
            }
            return isFontLoaded;
    }

}