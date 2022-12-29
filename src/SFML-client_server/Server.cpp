#include <SFML/Network.hpp>
#include <iostream>
#include "../Constants.h"
#include <unistd.h>
#include <list>

int main() {
    std::cout << "Server start!" << std::endl;
    sf::TcpListener listener;
    if (listener.listen(constants::PORT) != sf::Socket::Done)
    {
        std::cerr << "Error - listen" << std::endl;
        return EXIT_FAILURE;
    }
    //std::cout << "Client is found!" << std::endl;

    // accept a new connection
    //sf::TcpSocket client;
    // list of clients
    std::list<sf::TcpSocket*> clients;
    sf::SocketSelector selector;
    selector.add(listener);
    /*
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cerr << "Error - accept" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Client is accepted!" << std::endl;*/

    //double number = 0;
    bool run = true;
    while (run) {/*
        sf::Packet packet;
        packet << number;
        std::cout << "Serve is sending number: " << number << std::endl;
        client.send(packet);
        number++;*/
        if (selector.wait()) {
            // test the listener
            if (selector.isReady(listener)) {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    // Add the new client to the clients list
                    clients.push_back(client);
                    // Add the new client to the selector so that we will
                    // be notified when he sends something
                    selector.add(*client);
                }
                else
                {
                    // Error, we won't get a new connection, delete the socket
                    delete client;
                }
            } else {
                // The listener socket is not ready, test all other sockets (the clients)
                for (auto it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it;
                    if (selector.isReady(client))
                    {
                        // The client has sent some data, we can receive it
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Done)
                        {
                            std::string message;
                            packet >> message;
                            std::cout << message << std::endl;
                            int position =  message.find(":end",0);
                            if (position != -1) {
                                run = false;
                            }
                        }
                    }
                }
            }

        }

    }
    for (auto client: clients) {
        client->disconnect();
    }
    clients.clear();
    //client.disconnect();
    std::cout << "Connections is aborted " << std::endl;
    return EXIT_SUCCESS;
}