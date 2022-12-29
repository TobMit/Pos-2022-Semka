#include <SFML/Network.hpp>
#include <iostream>
#include "../Constants.h"

int main() {
    std::cout << "Client is started!" << std::endl;
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("localhost", constants::PORT);
    if (status != sf::Socket::Done)
    {
        std::cerr << "Error connection!" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Client is connected to the server" << std::endl;
    bool end = false;
    while (!end) {
        sf::Packet packet;
        if (socket.receive(packet) != sf::Socket::Done) {
            end = true;
        }

        double number;
        if (packet >> number){
            std::cout << "Recieved data: " << number << std::endl;
        } else {
            std::cout << "Error receiving data: " << number << std::endl;
        }
        if (number >= 10) {
            end = true;
        }
    }
    socket.disconnect();
    std::cout << "Connections is aborted " << std::endl;
    return EXIT_SUCCESS;

}