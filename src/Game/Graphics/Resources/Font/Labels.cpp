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
        player1Score.setPosition(constants::messageBorderOffset, constants::messageBorderOffset);
        player2Score.setPosition(constants::windowWidth - constants::messageBorderOffset, constants::messageBorderOffset);
    } else {
        std::cout << "SCORE:" << std::endl;
        std::cout << "YOU " << player1 << " : " << player2 << " OPPONENT" << std::endl << std::endl;
    }

    return isFontLoaded;
}

bool Labels::updateMessage(MessageType messageType, int countDownValue) {
    switch (messageType) {
        case WAITING:
            setupMessage(constants::WAITING_MESSAGE);
            break;

        case COUNTDOWN:
            setupMessage(std::to_string(countDownValue), true);
            break;

        case WIN:
            setupMessage(constants::WIN_MESSAGE);
            break;

        case LOSE:
            setupMessage(constants::LOSE_MESSAGE);
            break;
    }
    message.setOrigin(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2);
    message.setPosition(constants::windowWidth / 2, constants::messageBorderOffset);

    return isFontLoaded;

}

void Labels::setupMessage(const std::string& text, bool isCountdown) {
    if (isCountdown) {
        int intValue = std::stoi(text);
        if (intValue > 0 && isFontLoaded) {
            message.setString(text);
        } else if (intValue == 1)
            std::cout << text << std::endl << std::endl;
        else
            std::cout << text << std::endl;
    } else {
        if (!isFontLoaded)
            std::cout << text << std::endl << std::endl;
        else {
            message.setString(text);
        }
    }
}
