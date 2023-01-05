//
// Created by Matúš Mištrik on 05/01/2023.
//

#pragma once


#include "Sounds/Sounds.h"

class Resources {
private:
    Sounds sounds;

public:
    Resources() = default;

    inline void playBallSound() { sounds.playBallSound(); }
    inline void playWinSound() { sounds.playWinSound(); }
    inline void playLoseSound() { sounds.playLoseSound(); }
    inline void playLobbyMusic() { sounds.playLobbyMusic(); }
    inline void playGameMusic() { sounds.playGameMusic(); }
    inline void stopLobbyMusic() { sounds.stopLobbyMusic(); }
    inline void stopGameMusic() { sounds.stopGameMusic(); }
};
