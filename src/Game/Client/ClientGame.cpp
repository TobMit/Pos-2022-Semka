//
// Created by Matúš Mištrik on 30/12/2022.
//

//todo keď podržím šipku tak to zaváha a potom sa rozbehne, pravdepodobne niekde je sa zle odchytáva event
//todo doriešiť konečne tú logiku aby už aj prepočítavalo a odrážalo ball

#include "ClientGame.h"

void ClientGame::run() {
    Client client;
    if (!client.socketConnect(constants::IP_ADDRESS_LOCALHOST, constants::PORT)) {
        std::cerr << "Error - connection" << std::endl;
        return;
    }
    std::cout << "Client is connected to the server" << std::endl;
    //long long cislo = 0;
    //float oldData = 0;
    while (game.isRunning()) {
        if (client.selectorChange()) {
            auto movement = game.processEvents();
            // musí tam byť overenie či bola klávesa zmačknutá lebo inak to robili dvojkliky
            if (movement.direction != constants::NONE && movement.isPressed) {
                sf::Packet packet;
                ClientData data(movement.direction);
//            std::cout << data.direction << " " << data.packet_id << std::endl;
                //! najskôr sa pošle typ a potom samotný paket chcelo by to nejak zautomatizovať
                if(packet << static_cast<float>(packetType::CLIENT_UPDATE) << data) {
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
            if (client.socketReceive(&packet)) {
                //! Zistím typ paketu a podľa toho reagujem
                float typPaketu;
                if (packet >> typPaketu) {
                    //! Switchujem podla typu paketu
                    switch (static_cast<int>(typPaketu)) {
                        case packetType::SERVER_RESPONSE :{
                            ServerResponseData responseData;
                            packet >> responseData;
                            update(responseData);
                            break;
                        }
                        case packetType::NETWORK_MSG : {
                            NetworkData networkData;
                            packet >> networkData;
                            if (networkData.netMsg == packetType::DISCONECT) {
                                client.socketDisconnect();
                                game.closeWindow();
                            }
                            break;
                        }
                    }
                }
            } else {
                std::cerr << "ERROR - data receiving" << std::endl;
            }
        }
//        std::cout << "Koniec loopu" << std::endl;
        //game.render();

    }
    //TODO paket inicializuje disconect
    client.socketDisconnect();
}

void ClientGame::update(ServerResponseData data) {
    game.update(data);
    game.render();
}

void ClientGame::update() {
    game.render();
}
