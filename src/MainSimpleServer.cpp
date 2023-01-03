#include "SFML-client_server/Sockets/SimpleServer.h"
#include "Constants/GameData.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>



int main() {
    srand(time(NULL));
    SimpleServer server;

    if (!server.socketInicialise(constants::PORT)) {
        std::cerr << "ERROR listening" << std::endl;
    }
    std::cout << "Server started and wait for client" << std::endl;
    if (!server.socketConnect()) {
        std::cerr << "ERROR connecting client" << std::endl;
    }

    std::cout << "Server is ready" << std::endl;
    sf::Time timePerFrame = sf::seconds(1.f/120.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Clock clock;


    while (false != true) {
        sf::Packet packet;
        ServerData data;

//        while (mainWindow.isOpen()) {
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            //processEvents();
            //update(timePerFrame);// -> send;
            //server.socketSend(serverlogi.updater(reP));


            //server.socketSend()
            data.player1PaddleY = random() % static_cast<int>(constants::windowHeight);
            packet << data;
            std::cout << "Sending data" << std::endl;
            if (!server.socketSend(&packet)) {
                std::cerr << "Error sending" << std::endl;
            }
        }
    }
    return 0;
}
