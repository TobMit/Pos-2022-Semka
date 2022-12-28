#include "Socket/Client.h"
#include "definition.h"


int main()
{
    Client client(constants::PORT);
    if (!client.createSocket()) {
        std::cerr << "Error - socket" << std::endl;
        return EXIT_FAILURE;
    }
    if (!client.setServerParameters("localhost")) {
        std::cerr << "Error - socket" << std::endl;
        return EXIT_FAILURE;
    }
    if (!client.serverConnect()) {
        std::cerr << "Error - connection" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Connection was established!"<< std::endl;

    char buffer[constants::BUFF_SIZE + 1];
    buffer[constants::BUFF_SIZE] = '\0';
    bool end = false;
    while (!end) {
        read(*client.getSock(), buffer, constants::BUFF_SIZE);
        int cislo;
        sscanf(buffer,"%d", &cislo);
        std::cout << "Received data: " << cislo << std::endl;
        if (cislo > 10) {
            end = true;
        }
    }
    std::cout << "Connection was ended!"<< std::endl;
    client.closeSocket();
    return EXIT_SUCCESS;
}