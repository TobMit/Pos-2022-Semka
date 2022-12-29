//
// Created by Matúš Mištrik on 28/12/2022.
//

#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball();

    inline sf::Vector2f getPosition() const { return ball.getPosition(); }
    inline const sf::CircleShape& getObject() const { return ball; }

    inline void setPosition(sf::Vector2f position) { ball.setPosition(position); }
    inline void setPosition(float x, float y) { ball.setPosition(x, y); }
    inline void move(float offsetX, float offsetY) { ball.move(offsetX, offsetY); }

private:
    static const float ballRadius;
    static const sf::Color ballColor;
    sf::CircleShape ball;
};
