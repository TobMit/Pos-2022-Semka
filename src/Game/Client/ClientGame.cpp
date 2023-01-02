//
// Created by Matúš Mištrik on 30/12/2022.
//

#include "ClientGame.h"

void ClientGame::run() {
    Client client;
    if (!client.socketConnect("localhost", constants::PORT)) {
        std::cerr << "Error - cennection" << std::endl;
        return;
    }
    std::cout << "Client is connected to the server" << std::endl;
    while (game.isRunning()) {
        std::cout << "why the fuck" << std::endl;
        game.processEvents();
        std::cout << "why the heck" << std::endl;
        if (client.selectorChange()) {
            std::cout << "nieco"<< std::endl;
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
        std::cout << "Koniec loopu" << std::endl;

    }
    //TODO paket inicializuje disconect
    client.socketDisconnect();
}

void ClientGame::update(ServerData data) {
    game.update(data);
    game.render();
}
