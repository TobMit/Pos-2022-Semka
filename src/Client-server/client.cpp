#include "Socket/Client.h"
#include "definition.h"
using namespace std;

int main()
{
    Client client(PORT);
    if (!client.createSocket()) {
        cerr << "Error - socket" << endl;
        return EXIT_FAILURE;
    }
    if (!client.setServerParameters("localhost")) {
        cerr << "Error - socket" << endl;
        return EXIT_FAILURE;
    }
    if (!client.serverConnect()) {
        cerr << "Error - connection" << endl;
        return EXIT_FAILURE;
    }
    cout << "Connection was established!"<< endl;

    char buffer[bufsize + 1];
    buffer[bufsize] = '\0';
    bool end = false;
    while (!end) {
        read(*client.getSock(), buffer, bufsize);
        int cislo;
        sscanf(buffer,"%d", &cislo);
        cout << "Server send: " << cislo << endl;
        if (cislo > 10) {
            end = true;
        }
    }
    client.closeSocket();
    cout << "Connection was ended!"<< endl;
    return EXIT_SUCCESS;
}