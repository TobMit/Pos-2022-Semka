//
// Created by Matúš Mištrik on 28/12/2022.
//

#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball();
    inline sf::Vector2f getPosition() { return ball.getPosition(); }
    inline void setPosition(sf::Vector2f position) { ball.setPosition(position); }

private:
    static const float ballRadius;
    static const sf::Color ballColor;
    sf::CircleShape ball;
};
