#include <SFML/Network.hpp>
#include <iostream>
#include "../Constants.h"
#include <unistd.h>
#include <list>
#include <sys/select.h>
#include <fcntl.h>
#include <thread>
#include <mutex>
#include <condition_variable>

bool isEnd(std::mutex *mut, bool *pEnd) {
    bool end;
    {
        std::unique_lock<std::mutex> lock(*mut);
        end = *pEnd;
    }
    return end;
}

void setEnd(std::mutex *mut, bool *pEnd) {
    std::unique_lock<std::mutex> lock(*mut);
    *pEnd = true;
}

void writeToBuffer(std::mutex *mut, std::list<sf::TcpSocket*> &clients, bool *end)
{
    char buffer[constants::BUFF_SIZE + 1];
    buffer[constants::BUFF_SIZE] = '\0';

    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
    fd_set inputs;
    FD_ZERO(&inputs);
    struct timeval tv;
    tv.tv_usec = 0;
    while (!isEnd(mut, end)) {
        int position = -1;
        tv.tv_sec = 1;
        FD_SET(STDIN_FILENO, &inputs);
        select(STDIN_FILENO + 1, &inputs, NULL, NULL, &tv);

        if (FD_ISSET(STDIN_FILENO, &inputs)) {
            char *testStart = buffer;

            while (fgets(testStart, constants::BUFF_SIZE-1, stdin)!= nullptr) {
                std::string inputFromConsole = testStart;
                position = inputFromConsole.find(":end",0);
                //std::cout << testStart << std::endl;
                {
                    std::unique_lock<std::mutex> lock(*mut);
                    sf::Packet packet;
                    packet << inputFromConsole;
                    for (auto client: clients) {
                        client->send(packet);
                    }
                    if (position != -1) {
                        *end = true;
                    }
                }
            }
        }
    }
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) & ~O_NONBLOCK);

}

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
    bool end = false;
    std::mutex mut;
    std::condition_variable writeToBuff, readFromBuff;
    std::thread writer(writeToBuffer, &mut, std::ref(clients), &end);
    while (!isEnd(&mut, &end)) {/*
        sf::Packet packet;
        packet << number;
        std::cout << "Serve is sending number: " << number << std::endl;
        client.send(packet);
        number++;*/
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    {
                        std::unique_lock<std::mutex> lock(mut);
                        clients.push_back(client);
                    }
                    selector.add(*client);
                }
                else
                {
                    delete client;
                }
            } else {
                {
                    std::unique_lock<std::mutex> lock(mut);

                    for (auto it = clients.begin(); it != clients.end(); ++it) {
                        sf::TcpSocket &client = **it;
                        if (selector.isReady(client)) {
                            // The client has sent some data, we can receive it
                            sf::Packet packet;
                            if (client.receive(packet) == sf::Socket::Done) {
                                std::string message;
                                packet >> message;
                                std::cout << message;

                            }
                        }
                    }
                }
            }

        }

    }
    writer.join();
    for (auto client: clients) {
        client->disconnect();
        delete client;
    }
    //client.disconnect();
    std::cout << "Connections is aborted " << std::endl;
    return EXIT_SUCCESS;
}