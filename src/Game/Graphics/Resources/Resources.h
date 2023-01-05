//
// Created by Matúš Mištrik on 05/01/2023.
//

#pragma once


#include "Sounds/Sounds.h"
#include "Font/Labels.h"

class Resources {
private:
    Sounds sounds;
    Labels labels;

public:
    Resources() = default;

    inline void playBallSound() { sounds.playBallSound(); }
    inline void playWinSound() { sounds.playWinSound(); }
    inline void playLoseSound() { sounds.playLoseSound(); }
    inline void playLobbyMusic() { sounds.playLobbyMusic(); }
    inline void playGameMusic() { sounds.playGameMusic(); }
    inline void stopLobbyMusic() { sounds.stopLobbyMusic(); }
    inline void stopGameMusic() { sounds.stopGameMusic(); }

    inline void updatePlayersScore(int player1Score, int player2Score) { labels.updatePlayersScore(player1Score, player2Score); };
    inline void updateMessage(Labels::MessageType messageType, int countDownValue = -1) { labels.updateMessage(messageType, countDownValue); };
    inline const sf::Text& player1ScoreText() const { return labels.player1ScoreText(); }
    inline const sf::Text& player2ScoreText() const { return labels.player2ScoreText(); }
    inline const sf::Text& messageText() const { return labels.messageText(); }

};
