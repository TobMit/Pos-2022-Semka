//
// Created by Matúš Mištrik on 27/12/2022.
//

#include <cmath>
#include "Game.h"
#include "../Graphics/Constants/Constants.h"



const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);
const float Game::windowHeight = 600;
const float Game::windowWidth = 800;

Game::Game()
: mainWindow(sf::VideoMode(windowWidth ,windowHeight, 32),"Online PONG!",sf::Style::Titlebar | sf::Style::Close),
  ball(), player1(true), player2(false) {
//    mainWindow.setVerticalSyncEnabled(true);
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
    sf::Clock loopClock;
    loopClock.restart();
//    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mainWindow.isOpen()) {
//        timeSinceLastUpdate += loopClock.restart();
//
//        while (timeSinceLastUpdate > timePerFrame) {
//            timeSinceLastUpdate -= timePerFrame;
            processEvents(&loopClock);
            update(timePerFrame);
//        }

        render();
    }
}

void Game::processEvents(sf::Clock* clock) {
    sf::Event event;

    while(mainWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInputs(event.key.code, clock);
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
// TODO
}

void Game::render() {
    mainWindow.clear(sf::Color::White);

    mainWindow.draw(ball.getObject());
    mainWindow.draw(player1.getObject());
    mainWindow.draw(player2.getObject());

    mainWindow.display();
}

void Game::handlePlayerInputs(sf::Keyboard::Key key, sf::Clock* clock) {
    float deltaTime = clock->restart().asSeconds();
    switch (key) {
        case sf::Keyboard::Up:
            if (player2.getPosition().y - player2.getSize().y / 2 > 5.f)
                player2.move(0.f, -10.f);
            break;

        case sf::Keyboard::Down:
            if (player2.getPosition().y + player2.getSize().y / 2 < windowHeight - 5.f)
                player2.move(0.f, 10.f);
            break;
        default:
            break;
    }
}