//
// Created by Matúš Mištrik on 28/12/2022.
//

#include "Paddle.h"

const std::tuple<sf::Color, sf::Color> Paddle::paddleColor = std::tuple<sf::Color, sf::Color>(sf::Color::Red, sf::Color::Blue);

Paddle::Paddle(bool isLeft)
: paddle(constants::PADDLE_SIZE - constants::OUTLINE_THICKNESS_VECTOR2F)
{
    paddle.setOutlineThickness(constants::OUTLINE_THICKNESS);
    paddle.setOutlineColor(constants::OUTLINE_COLOR);
    paddle.setFillColor(isLeft ? std::get<0>(paddleColor) : std::get<1>(paddleColor));
    paddle.setOrigin(constants::PADDLE_SIZE / 2.f);
}
