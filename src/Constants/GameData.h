//
// Created by Matúš Mištrik on 29/12/2022.
//

#pragma once

#include <SFML/Network/Packet.hpp>
#include "Constants.h"

enum packetType {
    /**
     * Client to server
     */
    CLIENT_UPDATE = 0,
    /**
     * Server to client
     */
    SERVER_RESPONSE = 1,
    /**
     * Network info
     */
    NETWORK_MSG = 2,

    //! ak bude treba vlastný enum
    DISCONECT = 3

};

/**
 * Basic class for identify data exchange
 */
class PacketData {
public:
    int id;
    PacketData() = default;
    PacketData(int pId) : id(pId) {};
};

/**
 * Server send data for client
 * Every information for render canvas
 */
class ServerResponseData : public PacketData { // sending server to client
public:
    float player1PaddleY;
    float player2PaddleY;
    float ballX;
    float ballY;
    ServerResponseData() = default;
    ServerResponseData(float player1PaddleY, float player2PaddleY, float ballX, float ballY)
    : player1PaddleY(player1PaddleY), player2PaddleY(player2PaddleY), ballX(ballX), ballY(ballY) {}
};

/**
 * Client to server.
 * Information about paddle
 */
class ClientData : public PacketData { // sending client to server
public:
    constants::Direction direction;
    ClientData() = default;
    ClientData( constants::Direction direction)
    : direction(direction) {}
};

/**
 * Network information
 */
class NetworkData : public PacketData {
public:
    int netMsg;
    NetworkData() = default;
    NetworkData(int pNetMsg) : netMsg(pNetMsg) {};
};


inline sf::Packet& operator <<(sf::Packet& packet, const ServerResponseData& data) {
    return packet << data.player1PaddleY << data.player2PaddleY << data.ballX << data.ballY;
}

inline sf::Packet& operator >>(sf::Packet& packet, ServerResponseData& data) {
    return packet >> data.player1PaddleY >> data.player2PaddleY >> data.ballX >> data.ballY;
}

inline sf::Packet& operator <<(sf::Packet& packet, const ClientData& data) {
    return packet << static_cast<float>(data.direction);
}

//! Nemusí to detekovať zlý paket
inline sf::Packet& operator >>(sf::Packet& packet, ClientData& data) {
    float direction;
    packet >> direction;
    data.direction = static_cast<constants::Direction>(direction);
    return packet;
}

inline sf::Packet& operator <<(sf::Packet& packet, const NetworkData& data) {
    return packet << static_cast<float>(data.netMsg);
}

inline sf::Packet& operator >>(sf::Packet& packet, NetworkData& data) {
    float netMsg;
    packet >> netMsg;
    data.netMsg = static_cast<int >(netMsg);
    return packet;
}
