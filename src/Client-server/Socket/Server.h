
#include "Socket.h"

class Server : public Socket{
public:
    void setServerParameters() override;
    bool socketBind();
    bool serverAccept

};

inline void Server::setServerParameters() {
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_addr.s_addr = INADDR_ANY;
    serverAdd.sin_port = htons(Socket::port);
}

inline bool Server::socketBind() {
    int overenie = bind(sock, (struct sockaddr *)&serverAdd, sizeof(serverAdd));
    return overenie < 0 ? false : true;
}

inline bool serverAccept() {
    int overenie = accept()
}