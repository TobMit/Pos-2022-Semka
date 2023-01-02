//
// Created by Matúš Mištrik on 28/12/2022.
//

#include "Paddle.h"

const std::tuple<sf::Color, sf::Color> Paddle::paddleColor = std::tuple<sf::Color, sf::Color>(sf::Color::Red, sf::Color::Blue);

Paddle::Paddle(bool isLeft)
: paddle(constants::paddleSize - constants::outline_thickness_Vector2f)
{
    paddle.setOutlineThickness(constants::outline_thickness);
    paddle.setOutlineColor(constants::outline_color);
    paddle.setFillColor(isLeft ? std::get<0>(paddleColor) : std::get<1>(paddleColor));
    paddle.setOrigin(constants::paddleSize / 2.f);
}
