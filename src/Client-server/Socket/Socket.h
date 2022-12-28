#pragma once
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

class Socket {
protected:
    int port;
    struct hosten *ipAdr;
    int sock;
    int sockClient;
    struct sockaddr_in serverAdd;
public:
    Socket(int pPort);
    bool createSocket();
    virtual void setServerParameters();
    virtual void setServerParameters(char *ipAddress);

    virtual int * getSock();
    void closeSocket();
    ~Socket();
protected:
    void closeSocket(int pSocket);
};
