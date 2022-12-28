#pragma once
#include "Socket.h"

class Server : public Socket{
public:
    Server(int pPort) : Socket(pPort)
    {
    };
    bool setServerParameters() override;
    int *getSock() override;
    bool socketBind();
    bool socketListen();
    bool serverAccept();


};

inline bool Server::setServerParameters() {
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_addr.s_addr = INADDR_ANY;
    serverAdd.sin_port = htons(Socket::port);
    return true;
}

inline bool Server::socketBind() {
    int test = bind(sock, (struct sockaddr *)&serverAdd, sizeof(serverAdd));
    return test < 0 ? false : true;
}

inline bool Server::socketListen() {
    int test = listen(sock, 10);
    return test < 0 ? false : true;
}

inline bool Server::serverAccept() {
    struct sockaddr_in clientAdd;
    socklen_t clientAddLength = sizeof (clientAdd);
    sockClient = accept(sock,(struct sockaddr *)&clientAdd, &clientAddLength);
    closeSocket(sock); //! môže spôsobovať chybu
    return sockClient < 0 ? false : true;
}

inline int *Server::getSock() {
    return &sockClient;
}
