#pragma once
#include "Socket.h"

class Server : public Socket{
private:
    int clientSoc;
public:
    bool setServerParameters() override;
    int *getSock() override;
    bool socketBind();
    bool serverAccept();

};

inline bool Server::setServerParameters() {
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_addr.s_addr = INADDR_ANY;
    serverAdd.sin_port = htons(Socket::port);
    return true;
}

inline bool Server::socketBind() {
    int overenie = bind(sock, (struct sockaddr *)&serverAdd, sizeof(serverAdd));
    return overenie < 0 ? false : true;
}

inline bool Server::serverAccept() {
    struct sockaddr_in clientAdd;
    socklen_t clientAddLength = sizeof (clientAdd);
    int overenie = accept(sock,(struct sockaddr *)&clientAdd, &clientAddLength);
    closeSocket(sock); //! môže spôsobovať chybu
    return overenie < 0 ? false : true;
}

int *Server::getSock() {
    return &clientSoc;
}
