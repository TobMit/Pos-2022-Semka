#pragma once
#include "Sockets.h"

/**
 * Simple SFML synchronous server
 */
class SimpleServer : public Sockets {
private:
    sf::TcpListener *listener;
    sf::TcpSocket *client;
public:
    SimpleServer();
    ~SimpleServer();
    bool socketSend(sf::Packet *pPacket) override;

    bool socketReceive(sf::Packet *pPacket) override;

    bool socketConnect(std::string pIpAddress, int pPort) override;
    /**
     * Funcition wait for client to connect
     * @return  if was connection successful
     */
    bool socketConnect();
    /**
     * Funcition bind server to the port
     * @param pPort port for client connection
     * @return  if was binding successful
     */
    bool socketInicialise(int pPort);

    void socketDisconect() override;
};

inline SimpleServer::SimpleServer() {
    listener = new sf::TcpListener;
}

inline SimpleServer::~SimpleServer() {
    delete listener;
    this->socketDisconect();
    delete client;
}

inline bool SimpleServer::socketSend(sf::Packet *pPacket) {
    return client->send(*pPacket) == sf::Socket::Done;
}

inline bool SimpleServer::socketReceive(sf::Packet *pPacket) {
    return client->receive(*pPacket) == sf::Socket::Done;
}

inline bool SimpleServer::socketConnect(std::string pIpAddress, int pPort) {
    return false;
}

bool SimpleServer::socketConnect() {
    return listener->accept(*client) == sf::Socket::Done;
}

bool SimpleServer::socketInicialise(int pPort) {
    if (listener->listen(pPort) == sf::Socket::Done)
    {
        client = new sf::TcpSocket;
        return true;
    }
    return false;
}

inline void SimpleServer::socketDisconect() {
    client->disconnect();
}
