//
// Created by Matúš Mištrik on 28/12/2022.
//

#include "Ball.h"
#include "../../../Constants/Constants.h"

const sf::Color Ball::ballColor = sf::Color::White;

Ball::Ball()
: ball(constants::BALL_RADIUS - constants::OUTLINE_THICKNESS)
{
    ball.setOutlineThickness(constants::OUTLINE_THICKNESS);
    ball.setOutlineColor(constants::OUTLINE_COLOR);
    ball.setFillColor(ballColor);
    ball.setOrigin(constants::BALL_RADIUS / 2, constants::BALL_RADIUS / 2);
}
