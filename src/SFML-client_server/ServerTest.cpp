#include "Sockets/SimpleServer.h"
#include "../Constants.h"
#include <iostream>

int main() {
    SimpleServer server;
    if (!server.socketInicialise(constants::PORT)) {
        std::cerr << "ERROR listening" << std::endl;
    }
    std::cout << "Server started and wait for client" << std::endl;
    if (!server.socketConnect()) {
        std::cerr << "ERROR connecting client" << std::endl;
    }

    std::cout << "Server is ready" << std::endl;

    for (float i = 0; i < 10; ++i) {
        sf::Packet packet;
        std::string test = std::to_string(i);
        test += "\n";
        packet << test;
        if (!server.socketSend(&packet)) {
            std::cerr << "Error sending data" << std::endl;
        }
        sleep(1);
    }
    server.socketDisconect();
    std::cout << "Connection aborted" << std::endl;
    return EXIT_SUCCESS;

}