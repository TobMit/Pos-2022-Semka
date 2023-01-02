//
// Created by Matúš Mištrik on 29/12/2022.
//

#include "ClientLogic.h"

ClientLogic::ClientLogic()
: mainWindow(sf::VideoMode(constants::windowWidth ,constants::windowHeight, 32),"Online PONG!",sf::Style::Titlebar | sf::Style::Close),
  ball(), player1(true), player2(false) {
    mainWindow.setVerticalSyncEnabled(true);
    ball.setPosition(constants::windowWidth / 2, constants::windowHeight / 2);
    player1.setPosition(10 + player1.getSize().x / 2, constants::windowHeight / 2);
    player2.setPosition(constants::windowWidth - 10 - player2.getSize().x / 2, constants::windowHeight / 2);
//    do
//    {
//        ballAngle = (std::rand() % 360) * 2 * constants::pi / 360;
//    }
//    while (std::abs(std::cos(ballAngle)) < 0.7f);
}

constants::Movement ClientLogic::processEvents() {
    sf::Event event{};

    while(mainWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                return handlePlayerInputs(event.key.code, true);

            case sf::Event::KeyReleased:
                return handlePlayerInputs(event.key.code, false);

            case sf::Event::Closed:
                mainWindow.close();

            default:
                break;
        }
    }
    return constants::Movement {.direction = constants::DOWN, .isPressed = false};
}

void ClientLogic::update(ServerData data) {
    
}

void ClientLogic::render() {
    mainWindow.clear(sf::Color::White);

    mainWindow.draw(ball.getObject());
    mainWindow.draw(player1.getObject());
    mainWindow.draw(player2.getObject());

    mainWindow.display();
}

constants::Movement ClientLogic::handlePlayerInputs(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
        case sf::Keyboard::Up:
            return constants::Movement {.direction = constants::UP, .isPressed = isPressed};

        case sf::Keyboard::Down:
            return constants::Movement {.direction = constants::DOWN, .isPressed = isPressed};

        default:
            return constants::Movement {.direction = constants::NONE, .isPressed = isPressed};
    }
}
