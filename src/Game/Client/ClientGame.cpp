//
// Created by Matúš Mištrik on 30/12/2022.
//

#include "ClientGame.h"

void ClientGame::run() {
    if (!client.socketConnect(constants::LOCALHOST_IP, constants::PORT)) {
        std::cerr << "Error - connection" << std::endl;
        return;
    }
    std::cout << "Client is connected to the server" << std::endl;

    while (game.isRunning()) {
        if (client.selectorChange()) {
            auto direction = game.processEvents();
            if (direction != constants::NONE) {
                sf::Packet packet;
                ClientData data(direction);
                if(packet << data) {
                    if (!client.socketSend(&packet)) {
                        std::cerr << "Error - sending data" << std::endl;
                    }
                } else {
                    std::cerr << "Error - compressing data" << std::endl;
                }
            }

            sf::Packet packet;
            if (client.socketReceive(&packet)) {
                processPacket(&packet);
            } else {
                std::cerr << "ERROR - data receiving" << std::endl;
            }
        }
    }
    sf::Packet packet;
    NetworkData networkData(DISCONECT);
    packet << networkData;
    client.socketSend(&packet);
    client.socketDisconnect();
}

void ClientGame::processPacket(sf::Packet *packet) {
//! Zistím typ paketu a podľa toho reagujem
    float typPaketu;
    if (*packet >> typPaketu) {
        //! Switchujem podla typu paketu
        switch (static_cast<int>(typPaketu)) {
            case SERVER_RESPONSE :{
                ServerResponseData responseData;
                *packet >> responseData;
                update(responseData);
                break;
            }
            case NETWORK_MSG : {
                NetworkData networkData;
                *packet >> networkData;
                if (networkData.netMsg == DISCONECT) {
                    client.socketDisconnect();
                    game.closeWindow();
                }
                break;
            }
            case GAME_INFO : {
                GameInfoData gameInfoData;
                *packet >> gameInfoData;
                switch (gameInfoData.msg) {
                    case GameStatus::WAITING:
                        game.setGameState(GameStatus::WAITING);
                        game.setGameScore(gameInfoData.scoreP1, gameInfoData.scoreP2);
                        break;

                    case GameStatus::WIN:
                        game.win(gameInfoData.scoreP1, gameInfoData.scoreP2);
                        break;

                    case GameStatus::LOSE:
                        game.lose(gameInfoData.scoreP1, gameInfoData.scoreP2);
                        break;

                    case GameStatus::COUNTDOWN:
                        game.setGameState(GameStatus::COUNTDOWN);
                        game.showNumber(gameInfoData.other);
                        break;

                    case GameStatus::PLAYING:
                        game.setGameState(GameStatus::PLAYING);
                        break;
                }

                update();
            }
        }
    }
}

void ClientGame::update(ServerResponseData data) {
    game.update(data);
    game.render();
}

void ClientGame::update() {
    game.render();
}
