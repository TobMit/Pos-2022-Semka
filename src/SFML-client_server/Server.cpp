#include <SFML/Network.hpp>
#include <iostream>
#include "../Constants.h"
#include <unistd.h>

int main() {
    std::cout << "Server start!" << std::endl;
    sf::TcpListener listener;
    if (listener.listen(constants::PORT) != sf::Socket::Done)
    {
        std::cerr << "Error - listen" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Client is found!" << std::endl;

    // accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cerr << "Error - accept" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Client is accepted!" << std::endl;
    double number = 0;
    while (number <= 10) {
        sf::Packet packet;
        packet << number;
        std::cout << "Serve is sending number: " << number << std::endl;
        client.send(packet);
        number++;
        sleep(1);
    }
    client.disconnect();
    std::cout << "Connections is aborted " << std::endl;
    return EXIT_SUCCESS;
}