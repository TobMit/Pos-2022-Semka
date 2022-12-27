//
// Created by Matúš Mištrik on 27/12/2022.
//

#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const int Game::windowHeight = 600;
const int Game::windowWidth = 800;

Game::Game()
: mainWindow(sf::VideoMode(windowWidth ,windowHeight, 32),
             "Online PONG!", sf::Style::Titlebar | sf::Style::Close) {
    mainWindow.setVerticalSyncEnabled(true);
}

void Game::Run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mainWindow.isOpen()) {
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event{};

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
// TODO
}

void Game::render() {
    mainWindow.clear();
    // TODO
    mainWindow.display();
}

void Game::handlePlayerInputs(sf::Keyboard::Key key, bool isPressed) {

}
