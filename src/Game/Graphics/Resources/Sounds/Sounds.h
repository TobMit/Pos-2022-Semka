//
// Created by Matúš Mištrik on 05/01/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../../../Constants/Constants.h"
#include <cstring>
#include <utility>

class Sounds {
private:
    class Sound {
    private:
        sf::Sound sound;
        bool isLoaded;
    public:
        explicit Sound(const std::string& soundPath);
        void play();
    };

    class Music {
    private:
        std::string musicPath;
        sf::Music music;
    public:
        explicit Music(std::string musicPath) : musicPath(std::move(musicPath)) {}
        void play();
        inline void stop() { music.stop(); }
    };

private:
    Music ballSound;
    Music winSound;
    Music loseSound;
    Music lobbyMusic;
    Music gameMusic;

public:
    Sounds()
    : ballSound(constants::ballSoundPath), winSound(constants::winSoundPath),
    loseSound(constants::loseSoundPath) ,lobbyMusic(constants::lobbyMusicPath),
    gameMusic(constants::gameMusicPath) {}

    inline void playBallSound() { ballSound.play(); }
    inline void playWinSound() { winSound.play(); }
    inline void playLoseSound() { loseSound.play(); }
    inline void playLobbyMusic() { lobbyMusic.play(); }
    inline void playGameMusic() { gameMusic.play(); }
    inline void stopLobbyMusic() { lobbyMusic.stop(); }
    inline void stopGameMusic() { gameMusic.stop(); }
};
