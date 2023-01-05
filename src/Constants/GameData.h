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
    DISCONECT = 3,

    /**
     * Server to client about game
     */
    GAME_INFO = 4

};

enum gameStatus{
    WAITING = 0,
    COUNTDOWN = 1,
    PLAYING = 2,
    WIN = 3,
    LOSE = 4,
    /**
     * Only for server
     */
    COLLISION = 5,
    /**
     * Pusa between rounds
     */
    ROUNDPAUSE = 6
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
    bool bounce;
    ServerResponseData() {
      id = packetType::SERVER_RESPONSE;
    };
    ServerResponseData(float player1PaddleY, float player2PaddleY, float ballX, float ballY, bool bounce)
    : player1PaddleY(player1PaddleY), player2PaddleY(player2PaddleY), ballX(ballX), ballY(ballY), bounce(bounce) {
        id = packetType::SERVER_RESPONSE;
    }
};

/**
 * Client to server.
 * Information about paddle
 */
class ClientData : public PacketData { // sending client to server
public:
    constants::Direction direction;
    ClientData(){
        id = packetType::CLIENT_UPDATE;
    };
    ClientData( constants::Direction direction)
    : direction(direction) {
        id = packetType::CLIENT_UPDATE;
    }
};

/**
 * Network information
 */
class NetworkData : public PacketData {
public:
    int netMsg;
    NetworkData(){
        id = packetType::NETWORK_MSG;
    };
    NetworkData(int pNetMsg) : netMsg(pNetMsg) {
        id = packetType::NETWORK_MSG;
    };
};

class GameInfoData : public PacketData {
public:
    /**
     * Pre identifikáciu typu GameInfoSpravy
     */
    int msg;
    int scoreP1;
    int scoreP2;
    int other;
    GameInfoData(){
        id = packetType::GAME_INFO;
    };
    GameInfoData(int msg, int other) : msg(msg), other(other) {
        id = packetType::GAME_INFO;
    }
    GameInfoData(int msg, int scoreP1, int scoreP2, int other) : msg(msg), scoreP1(scoreP1), scoreP2(scoreP2), other(other) {
        id = packetType::GAME_INFO;
    }
};


inline sf::Packet& operator <<(sf::Packet& packet, const ServerResponseData& data) {
    return packet << static_cast<float>(data.id) << data.player1PaddleY << data.player2PaddleY << data.ballX << data.ballY << data.bounce;
}

inline sf::Packet& operator >>(sf::Packet& packet, ServerResponseData& data) {
    return packet >> data.player1PaddleY >> data.player2PaddleY >> data.ballX >> data.ballY >> data.bounce;
}

inline sf::Packet& operator <<(sf::Packet& packet, const ClientData& data) {
    return packet << static_cast<float>(data.id) << static_cast<float>(data.direction);
}

//! Nemusí to detekovať zlý paket
inline sf::Packet& operator >>(sf::Packet& packet, ClientData& data) {
    float direction;
    packet >> direction;
    data.direction = static_cast<constants::Direction>(direction);
    return packet;
}

inline sf::Packet& operator <<(sf::Packet& packet, const NetworkData& data) {
    return packet << static_cast<float>(data.id) << static_cast<float>(data.netMsg);
}

inline sf::Packet& operator >>(sf::Packet& packet, NetworkData& data) {
    float netMsg;
    packet >> netMsg;
    data.netMsg = static_cast<int >(netMsg);
    return packet;
}

inline sf::Packet& operator <<(sf::Packet& packet, const GameInfoData& data) {
    return packet << static_cast<float>(data.id) << static_cast<float>(data.msg) << static_cast<float>(data.scoreP1) << static_cast<float>(data.scoreP2) << static_cast<float>(data.other);
}

inline sf::Packet& operator >>(sf::Packet& packet, GameInfoData& data) {
    float msg, score1, score2, other;
    packet >> msg;
    packet >> score1;
    packet >> score2;
    packet >> other;
    data.msg = static_cast<int >(msg);
    data.scoreP1 = static_cast<int >(score1);
    data.scoreP2 = static_cast<int >(score2);
    data.other = static_cast<int >(other);
    return packet;
}
