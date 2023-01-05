//
// Created by Matúš Mištrik on 05/01/2023.
//

#include "Sounds.h"
#include <iostream>

Sounds::Sound::Sound(const std::string& soundPath) {
    sf::SoundBuffer soundBuffer;
    isLoaded = soundBuffer.loadFromFile(soundPath);
    sound.setBuffer(soundBuffer);
}

void Sounds::Sound::play() {
    if (isLoaded) {
        sound.play();
        std::cerr << "Error Music" << std::endl;
    }
}

void Sounds::Sound::changeVolume(float toLevel) {
    sound.setVolume(toLevel);
}

void Sounds::Music::play() {
    if (music.openFromFile(musicPath))
        music.play();
}

void Sounds::Music::changeVolume(float toLevel) {
    music.setVolume(toLevel);
}

void Sounds::muteAllsounds(bool isMuted) {
    ballSound.changeVolume(isMuted ? 0.f : 100.f);
    winSound.changeVolume(isMuted ? 0.f : 100.f);
    loseSound.changeVolume(isMuted ? 0.f : 100.f);
    lobbyMusic.changeVolume(isMuted ? 0.f : 100.f);
    gameMusic.changeVolume(isMuted ? 0.f : 100.f);
}
