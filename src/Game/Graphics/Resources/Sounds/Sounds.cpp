//
// Created by Matúš Mištrik on 05/01/2023.
//

#include "Sounds.h"

Sounds::Sound::Sound(const std::string& soundPath) {
    sf::SoundBuffer soundBuffer;
    isLoaded = soundBuffer.loadFromFile(soundPath);
    sound = sf::Sound(soundBuffer);
}

void Sounds::Sound::play() {
    if (isLoaded)
        sound.play();
}

void Sounds::Music::play() {
    if (music.openFromFile(musicPath))
        music.play();
}