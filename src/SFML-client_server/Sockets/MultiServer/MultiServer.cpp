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
    return selector->wait(sf::microseconds(1)); //! keď nebude server stíhať zmeniť na nanoseconds
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
 * If is client disconnected this can detect and remove client
 * @param pPacket for sending
 * @return true false if was successful
 */
bool MultiServer::socketSend(sf::Packet *pPacket) {
    bool successful = true;
    sf::Socket::Status status;
    for (int i = 0; i < clients->size(); ++i) {
        if (!socketSendPacket(pPacket, clients->at(i), &status)) {
            successful = false;
            if (status == sf::Socket::Disconnected) {
                clientDisconnect(i);
            }
        }
    }
    return successful;
}

/**
 * Send packet to the specific client
 * If was client disconected, this will detect it and remove it from server
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
 * If is client disconnected this can detect and remove client
 * @param pPacket for sending
 * @return true false if was successful
 */
bool MultiServer::socketSend(sf::Packet *pPacket, std::mutex *mut) {
    bool success = true;
    sf::Socket::Status status;
    if (mut != nullptr) {
        std::unique_lock<std::mutex> lock(*mut);
        //! Tuto to tak musí byť, aby som vedel že celkove posielanie nebolo uspesne
        for (int i = 0; i < clients->size(); ++i) {
            if (!socketSendPacket(pPacket, clients->at(i), &status)) {
                success = false;
                if (status == sf::Socket::Disconnected) {
                    clientDisconnect(i);
                }
            }
        }
    } else {
        //! Tuto to tak musí byť, aby som vedel že celkove posielanie nebolo uspesne
        for (int i = 0; i < clients->size(); ++i) {
            if (!socketSendPacket(pPacket, clients->at(i), &status)) {
                success = false;
                if (status == sf::Socket::Disconnected) {
                    clientDisconnect(i);
                }
            }
        }
    }
    return success;
}

/**
 * THREADS ONLY
 * Send packet to the specific client.
 * If was client disconected, this will detect it and remove it from server
 * @param id of clint for sending packet
 * @param pPacket packet for sending
 * @return true if was send successful
 */
bool MultiServer::socketSend(int id, sf::Packet *pPacket, std::mutex *mut) {
    sf::Socket::Status status;
    bool success = true;
    if (mut != nullptr) {
        std::unique_lock<std::mutex> lock(*mut);
        success = socketSendPacket(pPacket, clients->at(id), &status);
        if (status == sf::Socket::Disconnected) {
            clientDisconnect(id);
        }
    } else {
        success = socketSendPacket(pPacket, clients->at(id), &status);
        if (status == sf::Socket::Disconnected) {
            clientDisconnect(id);
        }
    }
    return success;
}

bool MultiServer::selectorIsReady(sf::Socket &pSocket) {
    return selector->isReady(pSocket);
}

bool MultiServer::socketSendPacket(sf::Packet *pPacket, sf::TcpSocket *pSocket, sf::Socket::Status *status) {
    *status = pSocket->send(*pPacket);
    return *status == sf::Socket::Done;
}

/**
 * Receive packet from the client
 * @param pPacket packet from client
 * @param pSocket the client
 * @param status status of receiving
 * @return true if receiving was successful
 */
bool MultiServer::socketReceive(sf::Packet *pPacket, sf::TcpSocket *pSocket, sf::Socket::Status *status) {
    *status = pSocket->receive(*pPacket);
    return *status == sf::Socket::Done;
    //return pSocket->receive(*pPacket) == sf::Socket::Done;
}

/**
 * Get packet form client, but only for first find clients. I dont expect in same time from two clients get message.
 * If is client disconnected this can detect and remove client
 * @param pClientPacket strore id and packet form client
 * @return true if was receiving successful
 */
bool MultiServer::socketReceive(ClientPacket *pClientPacket) {
    return socketReceive(pClientPacket, nullptr);
}

/**
 * THREADS ONLY
 * Get packet form client, but only for first find clients. I dont expect in same time from two clients get message.
 * If is client disconnected this can detect and remove client
 * @param pClientPacket strore id and packet form client
 * @return true if was receiving successful
 */
bool MultiServer::socketReceive(ClientPacket *pClientPacket, std::mutex *mut) {
    bool successful = true;
    sf::Socket::Status status;
    if (mut != nullptr) {
        std::unique_lock<std::mutex> lock(*mut);
        for (int i = 0; i < clients->size(); ++i) {
            if (selectorIsReady(*clients->at(i))) {
                pClientPacket->clientId = i;
                if (!socketReceive(pClientPacket->packet, clients->at(i), &status)){
                    successful = false;
                }
                // if was client disconnected
                if (status == sf::Socket::Disconnected) {
                    clientDisconnect(i);
                }
                break;
            }
        }
    } else {
        for (int i = 0; i < clients->size(); ++i) {
            if (selectorIsReady(*clients->at(i))) {
                pClientPacket->clientId = i;
                if (!socketReceive(pClientPacket->packet, clients->at(i), &status)){
                    successful = false;
                }
                // if was client disconnected
                if (status == sf::Socket::Disconnected) {
                    clientDisconnect(i);
                }
                break;
            }
        }
    }
    return successful;
}

void MultiServer::socketDisconnect() {
    for (auto client: *clients) {
        client->disconnect();
    }
}

void MultiServer::clientDisconnect(int id) {
    selector->remove(*clients->at(id));
    clients->at(id)->disconnect();
    delete clients->at(id);
    clients->erase(clients->begin() + id);

}