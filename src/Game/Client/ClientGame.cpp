//
// Created by Matúš Mištrik on 30/12/2022.
//

#include "ClientGame.h"

void ClientGame::run() {
    Client client;
    if (!client.socketConnect(constants::IP_ADDRESS_LOCALHOST, constants::PORT)) {
        std::cerr << "Error - cennection" << std::endl;
        return;
    }
    std::cout << "Client is connected to the server" << std::endl;
    //long long cislo = 0;
    while (game.isRunning()) {
        if (client.selectorChange()) {
            auto movement = game.processEvents();
            if (movement.direction != constants::NONE) {
                sf::Packet packet;
                ClientData data(CLIENT_UPDATE, movement.direction);
//            std::cout << data.direction << " " << data.packet_id << std::endl;
                if(packet << data) {
                    if (!client.socketSend(&packet)) {
                        std::cerr << "Error - sending data" << std::endl;
                    } else {
                        //std::cout << cislo++ << " Sending data" << std::endl;
                    }
                } else {
                    std::cerr << "Error - compressing data" << std::endl;
                }

            }
            sf::Packet packet;
            ServerData serverData;
            if (client.socketReceive(&packet)) {
                if (packet >> serverData) {
                    update(serverData);
                }
            } else {
                std::cerr << "ERROR - data receiving" << std::endl;
            }
        }
//        std::cout << "Koniec loopu" << std::endl;

    }
    //TODO paket inicializuje disconect
    client.socketDisconnect();
}

void ClientGame::update(ServerData data) {
    game.update(data);
    game.render();
}
