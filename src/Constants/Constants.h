#pragma once

#include <SFML/Graphics.hpp>
#include <cstring>

#define EMPTY std::cout << ""
namespace constants
{
    const std::string IP_ADDRESS_LOCALHOST = "localhost";
    const std::string IP_ADDRESS_FRIOS = "frios2.fri.uniza.sk";
    const int PORT = 20000;
    const int BUFF_SIZE = 1024;

    /**
     * MOVEMENT
     */

    enum Direction {
        UP = 0,
        DOWN = 1,
        NONE = 2,
        RELEASED = 3
    };

    /**
     *  OBJECT SIZES
     */

    const float windowWidth = 800.f;
    const float windowHeight = 600.f;
    const float ballRadius = 10.f;
    const sf::Vector2f paddleSize = sf::Vector2f(25, 100);


    const int outline_thickness = 3;
    const sf::Vector2f outline_thickness_Vector2f = sf::Vector2f(outline_thickness, outline_thickness);
    const sf::Color outline_color = sf::Color::Black;
    const float paddleSpped = 7.f;
    const float ballSpeed = 5.5f;
    const float pi = 3.14159f;

    const std::string ballSoundPath = "../src/Game/Graphics/Resources/Sounds/Samples/ballHit.wav";
    const std::string loseSoundPath = "../src/Game/Graphics/Resources/Sounds/Samples/lose.wav";
    const std::string winSoundPath = "../src/Game/Graphics/Resources/Sounds/Samples/win.wav";
    const std::string gameMusicPath = "../src/Game/Graphics/Resources/Sounds/Samples/Pacific Rim.ogg";
    const std::string lobbyMusicPath = "../src/Game/Graphics/Resources/Sounds/Samples/lobyMusic.ogg";
    const int ROUNDPAUSE = 2*5;

}
