#include "MultiServer.h"

MultiServer::MultiServer() {
    listener = new sf::TcpListener;
    selector = new sf::SocketSelector;
    clients = new std::vector<sf::TcpSocket*>;

}

MultiServer::~MultiServer() {
    delete listener;
    delete selector;

    if (!clients->empty()) {
        for (auto client: *clients) {
            delete client;
            client = nullptr;
        }
    }

    delete clients;
}

bool MultiServer::socketInicialise(int pPort) {
    if (listener->listen(pPort) == sf::Socket::Done)
    {
        selector->add(*listener);
        return true;
    }
    return false;
}

bool MultiServer::selectorWait() {
    return selector->wait();
}

bool MultiServer::listenerIsReady() {
    return selectorIsReady(*listener);
}

/**
 * Metod connect new client to the server database
 * @return every time is true
 */
bool MultiServer::socketConnect() {
    return socketConnect(nullptr);
}

/**
 * THREADS ONLY
 * Metod connect new client to the server database
 * @return every time is true
 */
bool MultiServer::socketConnect(std::mutex *mut) {
    sf::TcpSocket* client = new sf::TcpSocket;
    if (listener->accept(*client) == sf::Socket::Done)
    {
        if  (mut != nullptr) {
            std::unique_lock<std::mutex> lock(*mut);
            clients->push_back(client);
        } else {
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

/**
 * Sent packet for every client
 * @param pPacket for sending
 * @return true false if was successful
 */
bool MultiServer::socketSend(sf::Packet *pPacket) {
    bool successful = true;
    for (auto client: *clients) {
        if (!socketSendPacket(pPacket, client)) {
            successful = false;
        }
    }
    return successful;
}

/**
 * Send packet to the specific client
 * @param id of clint for sending packet
 * @param pPacket packet for sending
 * @return true if was send successful
 */
bool MultiServer::socketSend(int id, sf::Packet *pPacket) {
    return socketSend(id, pPacket, nullptr);
}

/**
 * THREADS ONLY
 * Sent packet for every client
 * @param pPacket for sending
 * @return true false if was successful
 */
bool MultiServer::socketSend(sf::Packet *pPacket, std::mutex *mut) {
    std::unique_lock<std::mutex> lock(*mut);
    bool successful = true;
    for (auto client: *clients) {
        if (!socketSendPacket(pPacket, client)) {
            successful = false;
        }
    }
    return successful;
}

/**
 * THREADS ONLY
 * Send packet to the specific client
 * @param id of clint for sending packet
 * @param pPacket packet for sending
 * @return true if was send successful
 */
bool MultiServer::socketSend(int id, sf::Packet *pPacket, std::mutex *mut) {
    if (mut != nullptr) {
        std::unique_lock<std::mutex> lock(*mut);
        return clients->at(id)->send(*pPacket) == sf::Socket::Done;
    } else {
        return clients->at(id)->send(*pPacket) == sf::Socket::Done;
    }
}

bool MultiServer::selectorIsReady(sf::Socket &pSocket) {
    return selector->isReady(pSocket);
}

bool MultiServer::socketSendPacket(sf::Packet *pPacket, sf::TcpSocket *pSocket) {
    return pSocket->send(*pPacket) == sf::Socket::Done;
}

/**
 * Receive packet from the client
 * @param pPacket packet from client
 * @param pSocket the client
 * @return true if receiving was successful
 */
bool MultiServer::socketReceive(sf::Packet *pPacket, sf::TcpSocket *pSocket) {
    return pSocket->receive(*pPacket) == sf::Socket::Done;
}

/**
 * Get packet form client, but only for first find clients. I dont expect in same time from two clients get message.
 * In futeure need som changes
 * @param pClientPacket strore id and packet form client
 * @return true if was receiving successful
 */
bool MultiServer::socketReceive(ClientPacket *pClientPacket) {
    return socketReceive(pClientPacket, nullptr);
}

/**
 * THREADS ONLY
 * Get packet form client, but only for first find clients. I dont expect in same time from two clients get message.
 * In futeure need som changes
 * @param pClientPacket strore id and packet form client
 * @return true if was receiving successful
 */
bool MultiServer::socketReceive(ClientPacket *pClientPacket, std::mutex *mut) {
    bool successful = true;
    if (mut != nullptr) {
        std::unique_lock<std::mutex> lock(*mut);

        for (int i = 0; i < clients->size(); ++i) {
            if (selectorIsReady(*clients->at(i))) {
                pClientPacket->clientId = i;
                if (!socketReceive(pClientPacket->packet, clients->at(i))){
                    successful = false;
                }
                break;
            }
        }
    } else {
        for (int i = 0; i < clients->size(); ++i) {
            if (selectorIsReady(*clients->at(i))) {
                pClientPacket->clientId = i;
                if (!socketReceive(pClientPacket->packet, clients->at(i))){
                    successful = false;
                }
                break;
            }
        }
    }
    return successful;
}

void MultiServer::socketDisconect() {
    for (auto client: *clients) {
        client->disconnect();
    }
}

