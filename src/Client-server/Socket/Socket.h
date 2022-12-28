#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>



class Socket {
protected:
    int port;
    struct hostent *ipAdr;
    int sock;
    int sockClient;
    struct sockaddr_in serverAdd;
public:
    Socket(int pPort);
    bool createSocket();
    virtual bool setServerParameters(){
        return false;
    };
    virtual bool setServerParameters(char *ipAddress) {
        return false;
    };

    virtual int * getSock(){
        return &sock;
    };
    void closeSocket();
    ~Socket();
protected:
    void closeSocket(int pSocket);
};
