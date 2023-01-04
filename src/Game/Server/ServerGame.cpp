//
// Created by Tobias on 04/01/2023.
//

#include "ServerGame.h"

ServerGame::ServerGame() {
    srand(time(NULL));
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
                /*
                if (server.socketConnect(&mut)) {
                    std::cout << "New client!" << std::endl;
                }
                 */
                std::cout << "Online clients " << server.getClienSize() << std::endl;
                server.getClienSize() > 1 ? serverLogic.setStart(true) : serverLogic.setStart(false);
            } else {
                sf::Packet packet;
                ClientPacket clientPacket(&packet);
                if (server.socketReceive(&clientPacket, &mut)) {
                    //! Zistím typ paketu a podľa toho reagujem
                    float typPaketu;
                    if (packet >> typPaketu) {
                        //! Switchujem podla typu paketu
                        switch (static_cast<int>(typPaketu)) {
                            case packetType::CLIENT_UPDATE :{
                                ClientData clientData;
                                packet >> clientData;
                                serverLogic.processData(&clientData, clientPacket.clientId == 0 ? true : false);
                                break;
                            }
                            case packetType::NETWORK_MSG : {
                                NetworkData networkData;
                                packet >> networkData;
                                if (networkData.netMsg == packetType::DISCONECT) {
                                    server.clientDisconnect(clientPacket.clientId);
                                    server.clientDisconnect(0);
                                    //alebo
                                    server.clientDisconnect(1);

                                }
                                break;
                            }
                            default:
                                std::cout << "wrong" << std::endl;
                                break;
                        }
                    }
                }
            }
        }

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame) {
            //std::cout << "tick" << std::endl;
            timeSinceLastUpdate -= timePerFrame;
            if (server.getClienSize() > 1) {
                serverLogic.update();
            }
            if (server.getClienSize() > 0) {
                sf::Packet packet;
                packet << serverLogic.getDataForClient(true);
                if (!server.socketSend(0, &packet, &mut)) {
                    std::cerr << "Error sending" << std::endl;
                }
                if (server.getClienSize() > 1) {
                    packet.clear();
                    packet << serverLogic.getDataForClient(false);
                    if (!server.socketSend(1, &packet, &mut)) {
                        std::cerr << "Error sending" << std::endl;
                    }
                }
            }
        }

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
                NetworkData networkData(packetType::DISCONECT);
                packet << networkData;
                server.socketSend(&packet, &mut);
                server.setEnd(&mut, &end);
            } else if (commandFromBuffer.find(":cend", 0) != -1) {
                std::cout << "Disconect zatial prvého klienta " << commandFromBuffer;
                sf::Packet packet;
                NetworkData networkData(packetType::DISCONECT);
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

    console.join();

    server.socketDisconnect();
    std::cout << "Server shut down!" << std::endl;
}
