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
 * It is not separate server like SimpleServer it is Cower class for SFML Sever
 */
class MultiServer : public Sockets {
private:
    sf::TcpListener *listener;
    sf::SocketSelector *selector;
    std::vector<sf::TcpSocket*> *clients;
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

    /**
     * Return allways false bacause this is server
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
     * Count of clints
     * @return count of clients in list
     */
    int getClienSize(){
        return clients->size();
    };

    bool socketReceive(sf::Packet *pPacket) override {
        return false;
    };

    bool socketReceive(ClientPacket *pClientPacket);

    bool socketReceive(ClientPacket *pClientPacket, std::mutex *mut);

    void socketDisconect() override;

    void disconectClient(int id);
private:
    bool selectorIsReady(sf::Socket &pSocket);

    bool socketSendPacket(sf::Packet *pPacket, sf::TcpSocket *pSocket, sf::Socket::Status *status);

    bool socketReceive(sf::Packet *pPacket, sf::TcpSocket *pSocket, sf::Socket::Status *status);
};
