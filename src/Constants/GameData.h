//
// Created by Matúš Mištrik on 29/12/2022.
//

#pragma once

#include <SFML/Network/Packet.hpp>
#include "Constants.h"

enum packetType {
    CLIENT_UPDATE = 0,
    SERVER_RESPONSE = 1,
    CLIENT_DISCONNECT = 2,
    SERVER_DISCONNECT = 3

};

class ServerData {
public:
    float player1PaddleY;
    float player2PaddleY;
    float ballX;
    float ballY;
    ServerData() = default;
    ServerData(float player1PaddleY, float player2PaddleY, float ballX, float ballY)
    : player1PaddleY(player1PaddleY), player2PaddleY(player2PaddleY), ballX(ballX), ballY(ballY) {}
};

class ClientData {
public:
    int packet_id;
    constants::Direction direction;
    //    bool isPressed;
    ClientData() = default;
    ClientData(int packet_id, constants::Direction direction)
    : packet_id(packet_id), direction(direction) {}
};

inline sf::Packet& operator <<(sf::Packet& packet, const ServerData& data) {
    return packet << data.player1PaddleY << data.player2PaddleY << data.ballX << data.ballY;
}

inline sf::Packet& operator >>(sf::Packet& packet, ServerData& data) {
    return packet >> data.player1PaddleY >> data.player2PaddleY >> data.ballX >> data.ballY;
}

inline sf::Packet& operator <<(sf::Packet& packet, const ClientData& data) {
    return packet << static_cast<float>(data.packet_id) << static_cast<float>(data.direction);
}

inline sf::Packet& operator >>(sf::Packet& packet, ClientData& data) {
    float id, direction;
    packet >> id;
    packet >> direction;
    data.packet_id = static_cast<int>(id);
    data.direction = static_cast<constants::Direction>(direction);
    return packet;
}