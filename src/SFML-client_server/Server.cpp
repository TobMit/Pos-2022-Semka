#include <iostream>
#include "Sockets/MultiServer/MultiServer.h"
#include "../Constants.h"

int main() {

    std::cout << "Server start!" << std::endl;
    MultiServer multiServer;
    if (!multiServer.socketInicialise(constants::PORT))
    {
        std::cerr << "Error - listen" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Server is ready!" << std::endl;
    std::cout << "Online clients: "<< multiServer.getClienSize() << std::endl;

    bool end = false;
    std::mutex mut;
    std::thread writer(&MultiServer::consoleSendData, &multiServer, &mut, &end);
    while (!multiServer.isEnd(&mut, &end)) {
        if (multiServer.selectorWait()) {
            std::cout << "1" << std::endl;

            if (multiServer.listenerIsReady()) {
                std::cout << "2" << std::endl;
                if (multiServer.socketConnect(&mut)){
                    std::cout << "New client is connected!" << std::endl;
                }
            } else {
                std::cout << "3" << std::endl;
                sf::Packet packet;
                ClientPacket clientPacket(&packet);
                if (multiServer.socketReceive(&clientPacket, &mut)) {
                    std::cout << "4" << std::endl;
                    std::string messageFromClient;
                    *clientPacket.packet >> messageFromClient;
                    std::cout << "Client " << clientPacket.clientId << ". send: " << messageFromClient;
                }
            }
            std::cout << "Online clients " << multiServer.getClienSize() << std::endl;
        }

    }
    writer.join();
    multiServer.socketDisconect();
    std::cout << "Connections is aborted " << std::endl;
    return EXIT_SUCCESS;
}