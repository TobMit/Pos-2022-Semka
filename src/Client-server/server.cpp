#include "definition.h"
#include "Socket/Server.h"
using namespace std;

int main()
{
    Server server(constants::PORT);
    if (!server.createSocket()) {
        cerr << "Error - socket" << endl;
        return EXIT_FAILURE;
    }
    cout << "Server socekt created" << endl;
    server.setServerParameters();
    cout << "Server parameters are set" << endl;
    server.socketBind();
    cout << "Server is bined and listening! asi" << endl;
    if (!server.socketListen()) {
        cerr << "Error - listen" << endl;
        return EXIT_FAILURE;
    }
    if (!server.serverAccept()) {
        cerr << "Error - accept" << endl;
        return EXIT_FAILURE;
    }

    cout << "Client is connected!" << endl;

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
    cout << "Connection was ended!"<< endl;
    return EXIT_SUCCESS;
}

