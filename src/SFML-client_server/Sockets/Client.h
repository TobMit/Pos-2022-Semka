#pragma once
#include "Sockets.h"

class Client : public Sockets {
private:
    sf::TcpSocket *socket;
public:
    Client();
    ~Client();
    bool socketSend(sf::Packet *pPacket) override;

    bool socketReceive(sf::Packet *pPacket) override;

    bool socketConnect(std::string pIpAddress, int pPort) override;

    void socketDisconnect() override;

};

/**
 * Simple clinet for socket
 */
inline Client::Client() {
    socket = new sf::TcpSocket;
}


inline bool Client::socketSend(sf::Packet *pPacket) {
    return socket->send(*pPacket) == sf::Socket::Done;
}

inline bool Client::socketReceive(sf::Packet *pPacket) {
    return socket->receive(*pPacket) == sf::Socket::Done;
}

inline bool Client::socketConnect(std::string pIpAddress, int pPort) {
    sf::Socket::Status status = socket->connect(pIpAddress, pPort);
    return status == sf::Socket::Done;
}


inline void Client::socketDisconnect() {
    socket->disconnect();
}

inline Client::~Client() {
    socketDisconnect();
    delete socket;
}
