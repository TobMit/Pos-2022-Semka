//
// Created by Matúš Mištrik on 29/12/2022.
//

#include "ClientLogic.h"

ClientLogic::ClientLogic()
: mainWindow(sf::VideoMode(constants::WINDOW_WIDTH , constants::WINDOW_HEIGHT, 32), "Online PONG!", sf::Style::Titlebar | sf::Style::Close),
  ball(), player1(true), player2(false) {
    mainWindow.setVerticalSyncEnabled(true);
    ball.setPosition(constants::WINDOW_WIDTH / 2, constants::WINDOW_HEIGHT / 2);
    player1.setPosition(10 + player1.getSize().x / 2, constants::WINDOW_HEIGHT / 2);
    player2.setPosition(constants::WINDOW_WIDTH - 10 - player2.getSize().x / 2, constants::WINDOW_HEIGHT / 2);
    state = GameStatus::ROUND_PAUSE;
    playerScore1 = playerScore2 = 0;
    isMutedSound = false;
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
        case GameStatus::WAITING:
            if (resources.updateMessage(Labels::WAITING))
                mainWindow.draw(resources.messageText());
            break;

        case GameStatus::COUNTDOWN:
            if (resources.updateMessage(Labels::COUNTDOWN, countDownNumber) )
                mainWindow.draw(resources.messageText());
            break;

        case GameStatus::PLAYING:
            if (resources.updatePlayersScore(playerScore1, playerScore2)) {
                mainWindow.draw(resources.player1ScoreText());
                mainWindow.draw(resources.player2ScoreText());
            }
            break;

        case GameStatus::WIN:
            if (resources.updateMessage(Labels::WIN))
                mainWindow.draw(resources.messageText());
            break;

        case GameStatus::LOSE:
            if (resources.updateMessage(Labels::LOSE))
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
            if (player1.getPosition().y < constants::WINDOW_HEIGHT) {
                return isPressed ? constants::DOWN : constants::RELEASED;
            }
            return constants::NONE;

        case sf::Keyboard::Left:
            if( player1.getPosition().y > 0) {
                return isPressed ? constants::UP : constants::RELEASED;
            }
            return constants::NONE;

        case sf::Keyboard::Right:
            if (player1.getPosition().y < constants::WINDOW_HEIGHT) {
                return isPressed ? constants::DOWN : constants::RELEASED;
            }
            return constants::NONE;

        case sf::Keyboard::M:
            if (isPressed) {
                isMutedSound = !isMutedSound;
                resources.muteAllSounds(isMutedSound);
            }

        default:
            return constants::NONE;
    }
}

void ClientLogic::win(int player1Score, int player2Score) {
    setGameScore(player1Score, player2Score);
    resources.playWinSound();
    setGameState(GameStatus::WIN);
}

void ClientLogic::lose(int player1Score, int player2Score) {
    setGameScore(player1Score, player2Score);
    resources.playLoseSound();
    setGameState(GameStatus::LOSE);
}

void ClientLogic::setGameScore(int player1Score, int player2Score) {
    playerScore1 = player1Score;
    playerScore2 = player2Score;
}

void ClientLogic::setGameState(int pState) {
    if(state != pState) {
        state = pState;
        switch (state) {
            case GameStatus::PLAYING:
                resources.stopLobbyMusic();
                resources.playGameMusic();
                break;
            case GameStatus::WAITING:
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
