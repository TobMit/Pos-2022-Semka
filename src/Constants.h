#pragma once

#include <SFML/Graphics.hpp>

namespace constants
{
    const int PORT = 15000;
    const int BUFF_SIZE = 1024;

    /**
     * MOVEMENT
     */

    enum Direction { UP, DOWN, NONE };

    struct Movement {

        Direction direction;
        bool isPressed;

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
    const float paddleSpeed = 400.f;
    const float ballSpeed = 400.f;
    const float pi = 3.14159f;
}
