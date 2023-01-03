#include "SFML-client_server/Sockets/MultiServer/MultiServer.h"
#include "Constants/GameData.h"
#include "Game/Server/ServerLogic.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>



int main() {
    srand(time(NULL));
    MultiServer server;
    ServerLogic serverLogic;

    if (!server.socketInicialise(constants::PORT)) {
        std::cerr << "ERROR listening" << std::endl;
    }
    std::cout << "Server is ready" << std::endl;
    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Clock clock;

    std::mutex mut;
    std::condition_variable writeToBuff;
    bool end = false;
    float position = constants::windowHeight / 2;
    float oldPosition = 0;

    //long long cislo = 0;

    //std::thread console(&MultiServer::consoleSendData, &server, &mut, &end, &writeToBuff);

    while (!server.isEnd(&mut, &end)) {
        if (server.selectorWait()) {

            if (server.listenerIsReady()) {
                server.socketConnect(&mut) ? std::cout << "New client!" << std::endl : EMPTY; //! no krása
                /*
                if (server.socketConnect(&mut)) {
                    std::cout << "New client!" << std::endl;
                }
                 */
            } else {
                sf::Packet packet;
                ClientPacket clientPacket(&packet);
                if (server.socketReceive(&clientPacket, &mut)) {
                    ClientData data;

                    if (packet >> data) {
                        position = serverLogic.processData(&data, true);
                        //std::cout << cislo++ << " Processing data"<< std::endl;
                    }
                    else
                        std::cerr << "Error - data receiving!" << std::endl;
                }
            }
            //std::cout << "Online clients " << server.getClienSize() << std::endl;
        }

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame) {
            //std::cout << "tick" << std::endl;
            sf::Packet packet;
            ServerData data;
            timeSinceLastUpdate -= timePerFrame;
            if (server.getClienSize() > 0) {
                data.player1PaddleY = position;
                data.player2PaddleY = rand() % static_cast<int>(constants::windowHeight);
                packet << data;/*
                if (position != oldPosition) {
                    std::cout << data.player1PaddleY << " Sending data" << std::endl;
                    oldPosition = position;
                }*/
                //std::cout << "Sending data" << std::endl;
                if (!server.socketSend(&packet, &mut)) {
                    std::cerr << "Error sending" << std::endl;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
