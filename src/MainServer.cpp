#include "SFML-client_server/Sockets/MultiServer/MultiServer.h"
#include "Constants/GameData.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>



int main() {
    srand(time(NULL));
    MultiServer server;

    if (!server.socketInicialise(constants::PORT)) {
        std::cerr << "ERROR listening" << std::endl;
    }
    std::cout << "Server is ready" << std::endl;
    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Clock clock;


    while (false != true) {
        timeSinceLastUpdate += clock.restart();
        if (server.selectorWait()) {
            if (server.listenerIsReady()) {
                if (server.socketConnect()) {
                    std::cout << "New client!" << std::endl;
                }
            } else {
                sf::Packet paket;
                ClientPacket clientPacket(&paket);
                if (server.socketReceive(&clientPacket)) {
                    ServerData data;
                    if (paket >> data) {
                        // ok niečo ako update a prepočítanie zo server logic
                    } else {
                        std::cerr << "Error - data receiving!" << std::endl;
                    }
                }
            }

            std::cout << "Online clients " << server.getClienSize() << std::endl;
        }

        while (timeSinceLastUpdate > timePerFrame) {
            sf::Packet packet;
            ServerData data;
            timeSinceLastUpdate -= timePerFrame;
            if (server.getClienSize() > 0) {
                data.player1PaddleY = random() % static_cast<int>(constants::windowHeight);
                packet << data;
                std::cout << "Sending data" << std::endl;
                if (!server.socketSend(&packet)) {
                    std::cerr << "Error sending" << std::endl;
                }
            }
        }

    }
    return 0;
}
