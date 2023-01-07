//
// Created by Matúš Mištrik on 05/01/2023.
//

#pragma once


#include "Sounds/Sounds.h"
#include "Labels/Labels.h"

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

    inline void muteAllSounds(bool isMuted) { sounds.muteAllSounds(isMuted); }

    inline bool updatePlayersScore(int player1Score, int player2Score) { return labels.updatePlayersScore(player1Score, player2Score); };
    inline bool updateMessage(Labels::MessageType messageType, int countDownValue = -1, int lastPlayerScore = 0) { return labels.updateMessage(messageType, countDownValue, lastPlayerScore); };
    inline const sf::Text& player1ScoreText() const { return labels.player1ScoreText(); }
    inline const sf::Text& player2ScoreText() const { return labels.player2ScoreText(); }
    inline const sf::Text& lastScoreText() const { return labels.lastScoreText(); }
    inline const sf::Text& messageText() const { return labels.messageText(); }

};
