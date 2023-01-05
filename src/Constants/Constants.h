#pragma once

#include <SFML/Graphics.hpp>
#include <cstring>

#define EMPTY std::cout << ""

namespace constants
{
    const std::string LOCALHOST_IP = "localhost";
    const std::string FRIOS_IP = "frios2.fri.uniza.sk";
    const int PORT = 20000;
    const int BUFF_SIZE = 1024;

    enum Direction {
        UP = 0,
        DOWN = 1,
        NONE = 2,
        RELEASED = 3
    };

    const float WINDOW_WIDTH = 800.f;
    const float WINDOW_HEIGHT = 600.f;
    const float BALL_RADIUS = 10.f;
    const sf::Vector2f PADDLE_SIZE = sf::Vector2f(25, 100);
    const float TEXT_OFFSET = 50.f;


    const int OUTLINE_THICKNESS = 3;
    const sf::Vector2f OUTLINE_THICKNESS_VECTOR2F = sf::Vector2f(OUTLINE_THICKNESS, OUTLINE_THICKNESS);
    const sf::Color OUTLINE_COLOR = sf::Color::Black;
    const float PADDLE_SPEED = 7.f;
    const float BALL_SPEED = 5.5f;
    const float PI = 3.14159f;

    const std::string BALL_SOUND_PATH = "../src/Game/Graphics/Resources/Sounds/Samples/ballHit.wav";
    const std::string LOSE_SOUND_PATH = "../src/Game/Graphics/Resources/Sounds/Samples/lose.wav";
    const std::string WIN_SOUND_PATH = "../src/Game/Graphics/Resources/Sounds/Samples/win.wav";
    const std::string GAME_MUSIC_PATH = "../src/Game/Graphics/Resources/Sounds/Samples/Pacific Rim.ogg";
    const std::string LOBBY_MUSIC_PATH = "../src/Game/Graphics/Resources/Sounds/Samples/lobyMusic.ogg";
    const std::string FONT_PATH = "../src/Game/Graphics/Resources/Labels/Fonts/font.ttf";

    const std::string WIN_MESSAGE = "WIN";
    const std::string LOSE_MESSAGE = "LOSE";
    const std::string WAITING_MESSAGE = "Waiting for opponent";

    const int ROUND_PAUSE = 2;
}
