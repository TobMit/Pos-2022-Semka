//
// Created by Matúš Mištrik on 28/12/2022.
//

#pragma once

#include "SFML/Graphics.hpp"
#include <tuple>

class Paddle {
public:
    explicit Paddle(bool isLeft);
    inline sf::Vector2f getPosition() { return paddle.getPosition(); }
    inline void setPosition(sf::Vector2f position) { paddle.setPosition(position); }

private:
    static const sf::Vector2f paddleSize;
    static const std::tuple<sf::Color, sf::Color> paddleColor;
    sf::RectangleShape paddle;

};
