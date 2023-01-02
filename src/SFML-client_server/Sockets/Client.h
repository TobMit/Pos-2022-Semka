#pragma once
#include "Sockets.h"

class Client : public Sockets {
private:
    sf::TcpSocket *socket;
    sf::SocketSelector *selector;
public:
    Client();
    ~Client();
    bool socketSend(sf::Packet *pPacket) override;

    bool socketReceive(sf::Packet *pPacket) override;

    bool socketConnect(std::string pIpAddress, int pPort) override;

    void socketDisconnect() override;

    bool selectorChange();

};

/**
 * Simple clinet for socket
 */
inline Client::Client() {
    socket = new sf::TcpSocket;
    selector = new sf::SocketSelector;
}


inline bool Client::socketSend(sf::Packet *pPacket) {
    return socket->send(*pPacket) == sf::Socket::Done;
}

inline bool Client::socketReceive(sf::Packet *pPacket) {
    return socket->receive(*pPacket) == sf::Socket::Done;
}

inline bool Client::socketConnect(std::string pIpAddress, int pPort) {
    sf::Socket::Status status = socket->connect(pIpAddress, pPort);
    if (status == sf::Socket::Done) {
        selector->add(*socket);
        return true;
    }
    return false;
}


inline void Client::socketDisconnect() {
    socket->disconnect();
    selector->remove(*socket);
}

inline Client::~Client() {
    socketDisconnect();
    delete socket;
    delete selector;
}

inline bool Client::selectorChange() {
    if (selector->wait()) {
        std::cout << "SELEKTOR HEKTOR" << std::endl;
        return selector->isReady(*socket);
    }
    return false;
}
