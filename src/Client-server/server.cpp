#include "definition.h"
#include "Socket/Server.h"


int main()
{
    Server server(constants::PORT);
    if (!server.createSocket()) {
        std::cerr << "Error - socket" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Server socekt created" << std::endl;
    server.setServerParameters();
    std::cout << "Server parameters are set!" << std::endl;
    if(!server.socketBind()) {
        std::cerr << "Error - bind" << std::endl;
    }
    std::cout << "Server is bined and listening!" << std::endl;
    if (!server.socketListen()) {
        std::cerr << "Error - listen" << std::endl;
        return EXIT_FAILURE;
    }
    if (!server.serverAccept()) {
        std::cerr << "Error - accept" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Client is connected!" << std::endl;

    char buffer[constants::BUFF_SIZE + 1];
    buffer[constants::BUFF_SIZE] = '\0';
    bool end = false;
    long number = 0;
    while (!end) {
        snprintf(buffer, constants::BUFF_SIZE,"%d", number);
        write(*server.getSock(), buffer, constants::BUFF_SIZE);
        printf("Server is sending: %d\n", number);
        if (number > 10) {
            end = true;
        }
        number++;
        sleep(1);
    }
    server.closeSocket();
    std::cout << "Connection was ended!"<< std::endl;
    return EXIT_SUCCESS;
}

