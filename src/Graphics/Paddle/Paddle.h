//
// Created by Matúš Mištrik on 28/12/2022.
//

#pragma once

#include "SFML/Graphics.hpp"
#include <tuple>

class Paddle {
public:
    explicit Paddle(bool isLeft);

    inline sf::Vector2f getPosition() const { return paddle.getPosition(); }
    inline sf::Vector2f getSize() const { return paddleSize; }
    inline const sf::RectangleShape& getObject() const { return paddle; }

    inline void setPosition(sf::Vector2f position) { paddle.setPosition(position); }
    inline void setPosition(float x, float y) { paddle.setPosition(x, y); }
    inline void move(float offsetX, float offsetY) { paddle.move(offsetX, offsetY); }

private:
    static const sf::Vector2f paddleSize;
    static const std::tuple<sf::Color, sf::Color> paddleColor;
    sf::RectangleShape paddle;

};
