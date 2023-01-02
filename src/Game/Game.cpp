//
// Created by Matúš Mištrik on 27/12/2022.
//

#include <cmath>
#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f/120.f);
const float Game::windowHeight = 600;
const float Game::windowWidth = 800;

Game::Game()
: mainWindow(sf::VideoMode(windowWidth ,windowHeight, 32),"Online PONG!",sf::Style::Titlebar | sf::Style::Close),
  ball(), player1(true), player2(false) {
    mainWindow.setVerticalSyncEnabled(true);
    ball.setPosition(windowWidth / 2, windowHeight / 2);
    player1.setPosition(10 + player1.getSize().x / 2, windowHeight / 2);
    player2.setPosition(windowWidth - 10 - player2.getSize().x / 2, windowHeight / 2);
    do
    {
        ballAngle = (std::rand() % 360) * 2 * constants::pi / 360;
    }
    while (std::abs(std::cos(ballAngle)) < 0.7f);
}

void Game::Run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mainWindow.isOpen()) {
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;

    while(mainWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInputs(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInputs(event.key.code, false);
                break;

            case sf::Event::Closed:
                mainWindow.close();
                break;

            default:
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    float movementY = 0.f;

    if (isMovingUP)
        movementY -= playerSpeed;
    if (isMovingDOWN)
        movementY += playerSpeed;

    player2.move(0.f, movementY * deltaTime.asSeconds());
}

void Game::render() {
    mainWindow.clear(sf::Color::White);

    mainWindow.draw(ball.getObject());
    mainWindow.draw(player1.getObject());
    mainWindow.draw(player2.getObject());

    mainWindow.display();
}

void Game::handlePlayerInputs(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
        case sf::Keyboard::Up:
            isMovingUP = isPressed;
            break;

        case sf::Keyboard::Down:
            isMovingDOWN = isPressed;
            break;

        default:
            break;
    }
}