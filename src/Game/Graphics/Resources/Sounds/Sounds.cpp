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

void Sounds::Music::play() {
    if (music.openFromFile(musicPath))
        music.play();
}