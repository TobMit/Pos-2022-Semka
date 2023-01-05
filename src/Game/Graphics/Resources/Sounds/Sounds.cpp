//
// Created by Matúš Mištrik on 05/01/2023.
//

#include "Sounds.h"

Sounds::Sound::Sound(const std::string& soundPath) {
    isLoaded = buffer.loadFromFile(soundPath);
    sound.setBuffer(buffer);
}

void Sounds::Sound::play() {
    if (isLoaded)
        sound.play();
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

void Sounds::muteAllSounds(bool isMuted) {
    ballSound.changeVolume(isMuted ? 0.f : 100.f);
    winSound.changeVolume(isMuted ? 0.f : 100.f);
    loseSound.changeVolume(isMuted ? 0.f : 100.f);
    lobbyMusic.changeVolume(isMuted ? 0.f : 100.f);
    gameMusic.changeVolume(isMuted ? 0.f : 100.f);
}
