//
// Created by Matúš Mištrik on 28/12/2022.
//

#include "Ball.h"
#include "Constants.h"

const float Ball::ballRadius = 10.f;
const sf::Color Ball::ballColor = sf::Color::White;

Ball::Ball()
: ball(sf::CircleShape(ballRadius - constants::outline_thickness))
{
    ball.setOutlineThickness(constants::outline_thickness);
    ball.setOutlineColor(constants::outline_color);
    ball.setFillColor(ballColor);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
}
