//
// Created by Tobias on 04/01/2023.
//

#include "ServerGame.h"

ServerGame::ServerGame() {
    srand(time(NULL));
    //todo dokoncovanie nastavovanie rychlosti
    timePerFrame = sf::seconds(1.f/50.f);
}

bool ServerGame::serverInitialize() {
    if (!server.socketInicialise(constants::PORT)) {
        std::cerr << "ERROR listening" << std::endl;
        return false;
    }
    return true;
}

void ServerGame::run() {
    std::cout << "Server is ready" << std::endl;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Clock clock;
    bool end = false;

    std::thread console(&MultiServer::consoleToBuffer, &server, &mut, &end, std::ref(buffer), &writeToBuff);

    while (!server.isEnd(&mut, &end)) {
        if (server.selectorWait()) {

            if (server.listenerIsReady()) {
                server.socketConnect(&mut) ? std::cout << "New client!" << std::endl : EMPTY; //! no krása

                std::cout << "Online clients " << server.getClienSize() << std::endl;
                server.getClienSize() > 1 ? serverLogic.setServerStatus(GameStatus::COUNTDOWN) : serverLogic.setServerStatus(GameStatus::WAITING);
            } else {
                sf::Packet packet;
                ClientPacket clientPacket(&packet);
                if (server.socketReceive(&clientPacket, &mut)) {
                    processPacket(&packet, &clientPacket);
                }
            }
        }

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame) {
            //std::cout << "tick" << std::endl;
            timeSinceLastUpdate -= timePerFrame;
            if (server.getClienSize() < 2) {
                serverLogic.setServerStatus(GameStatus::WAITING);
                serverLogic.restGame();
            }
            serverTick();
        }
        processConsole(&end);

    }
    console.join();

    server.socketDisconnect();
    std::cout << "Server shut down!" << std::endl;
}

void ServerGame::serverTick() {
    switch (serverLogic.getServerStatus()) {
        case GameStatus::WAITING: {
            setGameSpeed(WAITING);
            GameInfoData data;
            data.msg = GameStatus::WAITING;
            sf::Packet packet;
            packet << data;
            server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            packet.clear();
            packet << serverLogic.getDataForClient(true);
            server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            break;
        }
        case GameStatus::COUNTDOWN: {
            setGameSpeed(COUNTDOWN);
            GameInfoData data = serverLogic.countdown();
            sf::Packet packet;
            packet << data;
            server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            packet.clear();
            packet << serverLogic.getDataForClient(true);
            server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            break;
        }
        case GameStatus::PLAYING: {
            setGameSpeed(PLAYING);
            serverLogic.update();
            sf::Packet packet;
            packet << serverLogic.getDataForClient(true);
            server.socketSend(0, &packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            packet.clear();
            packet << serverLogic.getDataForClient(false);
            server.socketSend(1, &packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            break;
        }
        case GameStatus::COLLISION: {
            setGameSpeed(COLLISION);
            sf::Packet packet;
            packet << serverLogic.getDataForClient(true);
            server.socketSend(&packet, &mut);
            packet.clear();
            packet << serverLogic.getClientStatus(true);
            server.socketSend(0, &packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            packet.clear();
            packet << serverLogic.getClientStatus(false);
            server.socketSend(1, &packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            serverLogic.setServerStatus(GameStatus::ROUND_PAUSE);
            break;
        }
        case GameStatus::ROUND_PAUSE:
            setGameSpeed(ROUND_PAUSE);
            if(!serverLogic.pauseTick()) {
                GameInfoData data;
                data.msg = GameStatus::PLAYING;
                sf::Packet packet;
                packet << data;
                server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            }
            break;
    }
}

void ServerGame::processPacket(sf::Packet *packet, ClientPacket *clientPacket) {//! Zistím typ paketu a podľa toho reagujem
    float typPaketu;
    if (*packet >> typPaketu) {
        //! Switchujem podla typu paketu
        switch (static_cast<int>(typPaketu)) {
            case CLIENT_UPDATE : {
                ClientData clientData;
                *packet >> clientData;
                serverLogic.processData(&clientData, clientPacket->clientId == 0);
                break;
            }
            case NETWORK_MSG : {
                NetworkData networkData;
                *packet >> networkData;
                if (networkData.netMsg == DISCONECT) {
                    server.clientDisconnect(clientPacket->clientId);

                }
                break;
            }
            default:
                std::cout << "wrong" << std::endl;
                break;
        }
    }
}

void ServerGame::processConsole(bool *end) {
    std::string commandFromBuffer;
    {
        std::unique_lock<std::mutex> lock(mut);
        if (!buffer.empty()) {
            commandFromBuffer = buffer.at(buffer.size() - 1);
            buffer.pop_back();
            writeToBuff.notify_one();
        }
    }

    if (commandFromBuffer.size() != 0) {
        if (commandFromBuffer.find(":end", 0) != -1) {
            sf::Packet packet;
            NetworkData networkData(DISCONECT);
            packet << networkData;
            server.socketSend(&packet, &mut);
            server.setEnd(&mut, end);
        } else if (commandFromBuffer.find(":cend 1", 0) != -1 && server.getClienSize()>= 1) {
            std::cout << "Disconect 2. client!" << std::endl;
            sf::Packet packet;
            NetworkData networkData(DISCONECT);
            packet << networkData;
            if (server.getClienSize() > 0) {
                if(!server.socketSend(0, &packet, &mut)){
                    server.clientDisconnect(0);
                }
            }
        } else if (commandFromBuffer.find(":cend 2", 0) != -1 && server.getClienSize()>= 2) {
            std::cout << "Disconect 2. client!" << std::endl;;
            sf::Packet packet;
            NetworkData networkData(DISCONECT);
            packet << networkData;
            if (server.getClienSize() > 0) {
                if(!server.socketSend(1, &packet, &mut)) {
                    server.clientDisconnect(0);
                }
            }
        } else if (commandFromBuffer.find(":stat", 0) != -1) {
            switch (serverLogic.getServerStatus()) {
                case GameStatus::WAITING:
                    std::cout << "Online players: " << server.getClienSize() << std::endl;
                    std::cout << "Game is WAITING for players!" << std::endl;
                    break;
                case GameStatus::PLAYING: {
                    std::cout << "Game is RUNNING!" << std::endl;
                    GameInfoData data = serverLogic.getClientStatus(true);
                    std::cout << "Score:\n\tPlayer 1: " << data.scoreP1 << "\n\tPlayer 2: " << data.scoreP2 << std::endl;;
                }
                default:
                    std::cout << "Online players: " << server.getClienSize() << std::endl;
                    break;
            }
        } else if (commandFromBuffer.find(":restart", 0) != -1 && server.getClienSize()>= 2) {
            std::cout << "Restarting game!" << std::endl;;
            serverLogic.setServerStatus(GameStatus::WAITING);
            serverLogic.restGame();
        } else {
            std::cerr << "Unknow command!" << std::endl;
        }
    }
}

void ServerGame::setGameSpeed(GameStatus status) {
    switch (status) {
        case WAITING:
        case ROUND_PAUSE:
        case COLLISION:
            timePerFrame = sf::seconds(1.f/2.f);
            break;

        case COUNTDOWN:
            timePerFrame = sf::seconds(1.f/1.f);
            break;

        default:
            timePerFrame = sf::seconds(1.f/50.f);
            break;
    }
}
