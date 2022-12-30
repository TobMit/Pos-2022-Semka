#include <SFML/Network.hpp>
#include <istream>
#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#include "../Constants.h"

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

void writeToBuffer(std::mutex *mut, sf::TcpSocket *socket, bool *end)
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
                    if (socket->send(packet) != sf::Socket::Done) {
                        setEnd(mut, end);
                    }
                }

            }
        }
        if (position != -1) {
            setEnd(mut, end);
        }
    }
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) & ~O_NONBLOCK);

}

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
    //std::list<std::string> buffer;
    std::mutex mut;
    std::condition_variable writeToBuff, readFromBuff;
    std::thread writer(writeToBuffer, &mut, &socket, &end);

    while (!isEnd(&mut, &end)) {
        std::string fromServer;
        sf::Packet packet;
        int position = -1;

        if (socket.receive(packet) != sf::Socket::Done) {
            setEnd(&mut, &end);
        }

        if (packet >> fromServer){
            std::cout << "Recieved data: " << fromServer;
            position = fromServer.find(":end", 0);
        } else {
            std::cout << "Error on recieved data!";
        }

        if (position != -1) {
            setEnd(&mut, &end);
        }
    }
    writer.join();
    socket.disconnect();
    std::cout << "Connections is aborted " << std::endl;
    return EXIT_SUCCESS;

}