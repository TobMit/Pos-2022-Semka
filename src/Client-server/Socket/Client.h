#pragma once

#include "Socket.h"

class Client : public Socket {
public:
    bool setServerParameters(char *ipAddress) override;
    bool serverConnect();
};

inline bool Client::setServerParameters(char *ipAddress) {
    ipAdr = gethostbyname(ipAddress);
    if (ipAdr == NULL) {
        cerr << "Wrong ip add!" << endl;
        return false;
    }
    bzero((char *)&serverAdd, sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    bcopy((char *)ipAdr->h_addr, (char *)&serverAdd.sin_addr.s_addr, ipAdr->h_length);
    serverAdd.sin_port = htons(port);
    return true;
}


inline bool Client::serverConnect() {
    int test = connect(sock,(struct sockaddr *)&serverAdd, sizeof(serverAdd));
    return test < 0 ? false : true;
}