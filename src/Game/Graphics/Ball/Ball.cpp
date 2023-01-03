//
// Created by Matúš Mištrik on 28/12/2022.
//

#include "Ball.h"
#include "../../../Constants/Constants.h"

const sf::Color Ball::ballColor = sf::Color::White;

Ball::Ball()
: ball(constants::ballRadius - constants::outline_thickness)
{
    ball.setOutlineThickness(constants::outline_thickness);
    ball.setOutlineColor(constants::outline_color);
    ball.setFillColor(ballColor);
    ball.setOrigin(constants::ballRadius / 2, constants::ballRadius / 2);
}
