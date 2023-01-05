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

        sf::Text *arrayOfTexts[3] { &player1Score, &player2Score, &message };

        std::for_each(arrayOfTexts[0], arrayOfTexts[1], [](sf::Text& text) {
            text.setString("0");
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(40);
        });
    }
}

bool Labels::updatePlayersScore(int player1, int player2) {
    if (isFontLoaded) {
        player1Score.setString(std::to_string(player1));
        player2Score.setString(std::to_string(player2));
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
            }
            return isFontLoaded;

        case COUNTDOWN:
            if (countDownValue < 0 && isFontLoaded) {
                message.setString(std::to_string(countDownValue));
            } else if (countDownValue == 1)
                std::cout << countDownValue << std::endl << std::endl;

            return isFontLoaded;

        case WIN:
            message.setString(constants::WIN_MESSAGE);
            break;

        case LOSE:
            message.setString(constants::LOSE_MESSAGE);
            break;
    }

}