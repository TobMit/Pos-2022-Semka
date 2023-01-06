//
// Created by Matúš Mištrik on 05/01/2023.
//

#pragma once

#include <SFML/Audio.hpp>
#include "../../../../Constants/Constants.h"

class Sounds {
private:
    class Sound {
    private:
        sf::Sound sound;
        sf::SoundBuffer buffer;
        bool isLoaded;

    public:
        explicit Sound(const std::string& soundPath);
        void play();
        void changeVolume(float toLevel);
    };

    class Music {
    private:
        std::string musicPath;
        sf::Music music;

    public:
        explicit Music(std::string musicPath) : musicPath(std::move(musicPath)) {}
        void play();
        void changeVolume(float toLevel);
        inline void stop() { music.stop(); }
    };

private:
    Sound ballSound;
    Sound winSound;
    Sound loseSound;
    Music lobbyMusic;
    Music gameMusic;

public:
    Sounds()
    : ballSound(constants::BALL_SOUND_PATH), winSound(constants::WIN_SOUND_PATH),
      loseSound(constants::LOSE_SOUND_PATH) , lobbyMusic(constants::LOBBY_MUSIC_PATH),
      gameMusic(constants::GAME_MUSIC_PATH) {}

    inline void playBallSound() { ballSound.play(); }
    inline void playWinSound() { winSound.play(); }
    inline void playLoseSound() { loseSound.play(); }
    inline void playLobbyMusic() { lobbyMusic.play(); }
    inline void playGameMusic() { gameMusic.play(); }

    inline void stopLobbyMusic() { lobbyMusic.stop(); }
    inline void stopGameMusic() { gameMusic.stop(); }

    void muteAllSounds(bool isMuted);
};
