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
    state = gameStatus::WAITING;
}

constants::Movement ClientLogic::processEvents() {
    sf::Event event{};

    while(mainWindow.pollEvent(event) && state == gameStatus::PLAYNG) {
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
    return constants::Movement {.direction = constants::NONE, .isPressed = false};
}

void ClientLogic::update(ServerResponseData data) {
    player1.setPosition(player1.getPosition().x, data.player1PaddleY);
    player2.setPosition(player2.getPosition().x, data.player2PaddleY);
    ball.setPosition(data.ballX, data.ballY);
}

void ClientLogic::render() {
    mainWindow.clear(sf::Color::White);

    mainWindow.draw(ball.getObject());
    mainWindow.draw(player1.getObject());
    mainWindow.draw(player2.getObject());

    switch (state) {
        case gameStatus::WAITING:
            //todo nejaký nápis ako waiting for players
            //todo hudba lobyMusic.waw
            break;
        case gameStatus::COUNT_DOWM:
            //todo zobrazí cislo countDownNumber;
            break;
        case gameStatus::WIN:
            //todo nejaká hlaška round win
            //todo hudba success
            break;
        case gameStatus::LOSE:
            //todo nejaká hláška round lose
            //todo hudba hit
            break;
    }

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

void ClientLogic::win(int player1, int player2) {
    setGameScore(player1, player2);
    state = gameStatus::WIN;
}

void ClientLogic::lose(int player1, int player2) {
    setGameScore(player1, player2);
    state = gameStatus::LOSE;
}

void ClientLogic::setGameScore(int player1, int player2) {
    playerScore1 = player1;
    playerScore2 = player2;
}
