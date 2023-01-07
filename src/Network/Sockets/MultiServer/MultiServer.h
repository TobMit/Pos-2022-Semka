#pragma once

#include "../Sockets.h"
#include <vector>

class ClientPacket {
public:
    sf::Packet *packet;
    long clientId;
    ClientPacket() = default;
    ClientPacket(sf::Packet *pPacket) {
        packet = pPacket;
    }
    ClientPacket(sf::Packet *pPacket, long pId) {
        packet = pPacket;
        clientId = pId;
    }
};
/**
 * Server that can handle multiple users
 * It is not separate server like SimpleServer it is wrapper class for SFML Server
 */
class MultiServer : public Sockets {
private:
    sf::TcpListener *listener;
    sf::SocketSelector *selector;
    std::vector<sf::TcpSocket*> *clients;
public:
    MultiServer();
    ~MultiServer();

    /**
     * Function bind server to the port
     * @param pPort port for client connection
     * @return  if was binding successful
     */
    bool socketInitialize(int pPort);

    /**
     * This function returns as soon as at least one socket has some data available to be received.
     * @return
     */
    bool selectorWait();

    bool listenerIsReady();

    /**
     * Return always false because this is server
     */
    bool socketConnect(std::string pIpAddress, int pPort) override{
        return false;
    };

    bool socketConnect();

    bool socketConnect(std::mutex *mut);

    bool socketSend(sf::Packet *pPacket) override;

    bool socketSend(int id, sf::Packet *pPacket);

    bool socketSend(sf::Packet *pPacket, std::mutex *mut);

    bool socketSend(int id, sf::Packet *pPacket, std::mutex *mut);

    /**
     * Count of clients
     * @return count of clients in list
     */
    int getClientSize(){
        return clients->size();
    };

    bool socketReceive(sf::Packet *pPacket) override {
        return false;
    };

    bool socketReceive(ClientPacket *pClientPacket);

    bool socketReceive(ClientPacket *pClientPacket, std::mutex *mut);

    void socketDisconnect() override;

    void clientDisconnect(int id);
private:
    bool selectorIsReady(sf::Socket &pSocket);

    bool socketSendPacket(sf::Packet *pPacket, sf::TcpSocket *pSocket, sf::Socket::Status *status);

    bool socketReceive(sf::Packet *pPacket, sf::TcpSocket *pSocket, sf::Socket::Status *status);
};
