//
// Created by Tobias on 04/01/2023.
//

#include "ServerGame.h"

ServerGame::ServerGame() {
    srand(time(NULL));
    //todo dokoncovanie nastavovanie rychlosti
    timePerFrame = sf::seconds(1.f/50.f);
}

bool ServerGame::serverInicialise() {
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
                server.getClienSize() > 1 ? serverLogic.setServerStatus(gameStatus::COUNTDOWN) : serverLogic.setServerStatus(gameStatus::WAITING);
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
                serverLogic.setServerStatus(gameStatus::WAITING);
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
        case gameStatus::WAITING: {
            setSpeedToWait();
            GameInfoData data;
            data.msg = gameStatus::WAITING;
            sf::Packet packet;
            packet << data;
            server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            packet.clear();
            packet << serverLogic.getDataForClient(true);
            server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            break;
        }
        case gameStatus::COUNTDOWN: {
            setSpeedToCountDown();
            GameInfoData data = serverLogic.coundDown();
            sf::Packet packet;
            packet << data;
            server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            packet.clear();
            packet << serverLogic.getDataForClient(true);
            server.socketSend(&packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            break;
        }
        case gameStatus::PLAYING: {
            setSpeedToGame();
            serverLogic.update();
            sf::Packet packet;
            packet << serverLogic.getDataForClient(true);
            server.socketSend(0, &packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            packet.clear();
            packet << serverLogic.getDataForClient(false);
            server.socketSend(1, &packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            break;
        }
        case gameStatus::COLLISION: {
            setSpeedToWait();
            sf::Packet packet;
            packet << serverLogic.getDataForClient(true);
            server.socketSend(&packet, &mut);
            packet.clear();
            packet << serverLogic.getClientStatus(true);
            server.socketSend(0, &packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            packet.clear();
            packet << serverLogic.getClientStatus(false);
            server.socketSend(1, &packet, &mut) ? EMPTY : std::cerr << "Error sending" << std::endl;
            serverLogic.setServerStatus(gameStatus::ROUNDPAUSE);
            break;
        }
        case gameStatus::ROUNDPAUSE:
            setSpeedToWait();
            if(!serverLogic.puseTick()) {
                GameInfoData data;
                data.msg = gameStatus::PLAYING;
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
                serverLogic.processData(&clientData, clientPacket->clientId == 0 ? true : false);
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
        } else if (commandFromBuffer.find(":cend", 0) != -1) {
            std::cout << "Disconect zatial prvého klienta " << commandFromBuffer;
            sf::Packet packet;
            NetworkData networkData(DISCONECT);
            packet << networkData;
            if (server.getClienSize() > 0) {
                if(!server.socketSend(0, &packet, &mut)){
                    server.clientDisconnect(0);
                }
            }
        } else {
            std::cout << "Z konzoli ha " << commandFromBuffer;
        }
    }
}

void ServerGame::setSpeedToCountDown() {
    timePerFrame = sf::seconds(1.f/1.f);
}

void ServerGame::setSpeedToGame() {
    timePerFrame = sf::seconds(1.f/50.f);
}

void ServerGame::setSpeedToWait() {
    timePerFrame = sf::seconds(1.f/2.f);
}
