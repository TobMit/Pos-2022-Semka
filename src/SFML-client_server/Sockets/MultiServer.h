#pragma once

#include "Sockets.h"
#include <list>

class ClientPacket {
public:
    sf::Packet *packet;
    long clientId;
    ClientPacket(sf::Packet *pPacket, long pId) {
        packet = pPacket;
        clientId = pId;
    }
};
/**
 * Server that can handle multiple users
 * It is not separate server like SimpleServer it is Cower class for SFML Sever
 */
class MultiServer : public Sockets {
private:
    sf::TcpListener *listener;
    sf::SocketSelector *selector;
    std::list<sf::TcpSocket*> *clients;
public:
    //! Ak bude treba tak môže beťať aj na vlákne ale zatiaľ bude to takto čiastočne obalené
    MultiServer();
    ~MultiServer();

    /**
     * Funcition bind server to the port
     * @param pPort port for client connection
     * @return  if was binding successful
     */
    bool socketInicialise(int pPort);

    /**
     * This function returns as soon as at least one socket has some data available to be received.
     * @return
     */
    bool selectorWait();

    bool listenerIsReady();

    bool socketConnect(std::string pIpAddress, int pPort) override;

    bool socketConnect();

    bool socketConnect(std::mutex *mut);

    bool socketSend(sf::Packet *pPacket) override;

    bool socketReceive(sf::Packet *pPacket) override;

    void socketDisconect() override;
private:
    bool selectorIsReady(sf::Socket &pSocket);
};

inline MultiServer::MultiServer() {
    listener = new sf::TcpListener;
    selector = new sf::SocketSelector;
}

inline MultiServer::~MultiServer() {
    delete listener;
    delete selector;

    for (auto client: *clients) {
         delete client;
    }
}

bool MultiServer::socketInicialise(int pPort) {
    if (listener->listen(pPort) == sf::Socket::Done)
    {
        selector->add(*listener);
        return true;
    }
    return false;
}

inline bool MultiServer::selectorWait() {
    return selector->wait();
}

inline bool MultiServer::listenerIsReady() {
    return selectorIsReady(*listener);
}

/**
 * Metod connect new client to the server database
 * @return every time is true
 */
inline bool MultiServer::socketConnect() {
    //! Same changes need in Thread version
    sf::TcpSocket* client = new sf::TcpSocket;
    if (listener->accept(*client) == sf::Socket::Done)
    {
        clients->push_back(client);
        selector->add(*client);
    }
    else
    {
        delete client;
    }
    return true;
}

/**
 * THREADS ONLY
 * Metod connect new client to the server database
 * @return every time is true
 */
inline bool MultiServer::socketConnect(std::mutex *mut) {
    //! Same changes need in clasic version
    sf::TcpSocket* client = new sf::TcpSocket;
    if (listener->accept(*client) == sf::Socket::Done)
    {
        {
            std::unique_lock<std::mutex> lock(*mut);
            clients->push_back(client);
        }
        selector->add(*client);
    }
    else
    {
        delete client;
    }
    return true;
}

inline bool MultiServer::socketSend(sf::Packet *pPacket) {
    return false;
}

inline bool MultiServer::socketReceive(sf::Packet *pPacket) {
    return false;
}

inline bool MultiServer::socketConnect(std::string pIpAddress, int pPort) {
    return false;
}

inline void MultiServer::socketDisconect() {
    for (auto client: *clients) {
        client->disconnect();
    }
}

bool MultiServer::selectorIsReady(sf::Socket &pSocket) {
    return selector->isReady(pSocket);
}
