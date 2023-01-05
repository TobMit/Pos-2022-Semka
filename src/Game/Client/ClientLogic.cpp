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
    state = gameStatus::ROUNDPAUSE;
}

constants::Direction ClientLogic::processEvents() {
    sf::Event event{};

    while(mainWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                return state == gameStatus::PLAYING ? handlePlayerInputs(event.key.code, true) :  constants::NONE;

            case sf::Event::KeyReleased:
                return state == gameStatus::PLAYING ? handlePlayerInputs(event.key.code, false) :  constants::NONE;

            case sf::Event::Closed:
                mainWindow.close();

            default:
                break;
        }
    }
    return constants::NONE;
}

void ClientLogic::update(ServerResponseData data) {
    player1.setPosition(player1.getPosition().x, data.player1PaddleY);
    player2.setPosition(player2.getPosition().x, data.player2PaddleY);
    ball.setPosition(data.ballX, data.ballY);
    if (data.bounce) {
        resources.playBallSound();
    }
}

void ClientLogic::render() {
    mainWindow.clear(sf::Color::White);

    switch (state) {
        case gameStatus::WAITING:
            //todo nejaký nápis ako waiting for players
            //todo hudba lobyMusic.waw
//            resources.updateMessage(Labels::WAITING);
//            mainWindow.draw(resources.messageText());
            break;
        case gameStatus::COUNTDOWN:
            //todo zobrazí cislo countDownNumber;
//            resources.updateMessage(Labels::COUNTDOWN, countDownNumber);
//            mainWindow.draw(resources.messageText());
            break;
        case gameStatus::PLAYING:
            //todo score
            resources.updatePlayersScore(playerScore1, playerScore2);
            mainWindow.draw(resources.player1ScoreText());
            mainWindow.draw(resources.player2ScoreText());

            break;
        case gameStatus::WIN:
            //todo nejaká hlaška round win
            //todo hudba succes
            resources.updateMessage(Labels::WIN);
            mainWindow.draw(resources.messageText());
            break;
        case gameStatus::LOSE:
            //todo nejaká hláška round lose
            //todo hudba hit
            resources.updateMessage(Labels::LOSE);
            mainWindow.draw(resources.messageText());
            break;
    }

    mainWindow.draw(ball.getObject());
    mainWindow.draw(player1.getObject());
    mainWindow.draw(player2.getObject());

    mainWindow.display();
}

constants::Direction ClientLogic::handlePlayerInputs(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
        case sf::Keyboard::Up:
            if( player1.getPosition().y > 0) {
                return isPressed ? constants::UP : constants::RELEASED;
            }
            return constants::NONE;

        case sf::Keyboard::Down:
            if (player1.getPosition().y < constants::windowHeight) {
                return isPressed ? constants::DOWN : constants::RELEASED;
            }
            return constants::NONE;

        case sf::Keyboard::Left:
            if( player1.getPosition().y > 0) {
                return isPressed ? constants::UP : constants::RELEASED;
            }
            return constants::NONE;

        case sf::Keyboard::Right:
            if (player1.getPosition().y < constants::windowHeight) {
                return isPressed ? constants::DOWN : constants::RELEASED;
            }
            return constants::NONE;

        case sf::Keyboard::M:
            return isPressed ? constants::MUTE : constants::RELEASED;

        default:
            return constants::NONE;
    }
}

void ClientLogic::win(int player1, int player2) {
    setGameScore(player1, player2);
    resources.playWinSound();
    setGameState(gameStatus::WIN);
}

void ClientLogic::lose(int player1, int player2) {
    setGameScore(player1, player2);
    resources.playLoseSound();
    setGameState(gameStatus::LOSE);
}

void ClientLogic::setGameScore(int player1, int player2) {
    playerScore1 = player1;
    playerScore2 = player2;
}

void ClientLogic::setGameState(int pState) {
    if(state != pState) {
        state = pState;
        switch (state) {
            case gameStatus::PLAYING:
                resources.stopLobbyMusic();
                resources.playGameMusic();
                break;
            case gameStatus::WAITING:
                resources.stopGameMusic();
                resources.playLobbyMusic();
                break;
            default:
                resources.stopLobbyMusic();
                resources.stopGameMusic();
                break;
        }
    }
}
