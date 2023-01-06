#include "Sockets/Client.h"
#include <iostream>

int main() {
    std::cout << "Client started!" << std::endl;
    Client client;
    if (!client.socketConnect(constants::FRIOS_IP, constants::PORT))
    {
        std::cerr << "Error connection!" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Client is connected to the server" << std::endl;

    bool end = false;
    std::mutex mut;
    std::thread writer(&Client::consoleSendData, &client, &mut, &end);

    while (!client.isEnd(&mut, &end)) {
        std::string fromServer;
        sf::Packet packet;
        int position = -1;

        if (!client.socketReceive(&packet)) {
            client.setEnd(&mut, &end);
        }

        if (packet >> fromServer){
            std::cout << "Recieved data: " << fromServer;
            position = fromServer.find(":end", 0);
        } else {
            std::cout << "Error on recieved data!";
        }

        if (position != -1) {
            client.setEnd(&mut, &end);
        }
    }
    writer.join();
    client.socketDisconnect();
    std::cout << "Connections is aborted " << std::endl;
    return EXIT_SUCCESS;

}