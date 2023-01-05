//
// Created by Matúš Mištrik on 30/12/2022.
//

#include "ClientGame.h"

void ClientGame::run() {
    if (!client.socketConnect(constants::IP_ADDRESS_FRIOS, constants::PORT)) {
        std::cerr << "Error - connection" << std::endl;
        return;
    }
    std::cout << "Client is connected to the server" << std::endl;

    while (game.isRunning()) {
        if (client.selectorChange()) {
            auto direction = game.processEvents();
            // musí tam byť overenie či bola klávesa zmačknutá lebo inak to robili dvojkliky
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

        //game.render();

    }
    //TODO paket inicializuje disconect ked sa zvrie okno
    client.socketDisconnect();
}

void ClientGame::processPacket(sf::Packet *packet) {//! Zistím typ paketu a podľa toho reagujem
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
                //todo upratať
                switch (gameInfoData.msg) {
                    case gameStatus::WAITING:
                        game.setGameState(gameStatus::WAITING);
                        std::cout << "Waiting for players" << std::endl;
                        break;
                    case gameStatus::WIN:
                        game.win(gameInfoData.scoreP1, gameInfoData.scoreP2);
                        std::cout << "Round win" << std::endl;
                        break;
                    case gameStatus::LOSE:
                        game.lose(gameInfoData.scoreP1, gameInfoData.scoreP2);
                        std::cout << "Round lose" << std::endl;
                        break;
                    case gameStatus::COUNTDOWN:
                        game.setGameState(gameStatus::COUNTDOWN);
                        game.showNumber(gameInfoData.other);
                        std::cout << gameInfoData.other << std::endl;
                        break;
                    case gameStatus::PLAYING:
                        game.setGameState(gameStatus::PLAYING);
                        break;
                }
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
