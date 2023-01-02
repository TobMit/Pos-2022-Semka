//
// Created by Matúš Mištrik on 29/12/2022.
//

#pragma once

#include <SFML/Network/Packet.hpp>
#include "../../Constants.h"

struct ServerData {

    float player1PaddleY;
    float player2PaddleY;
    float ballX;
    float ballY;

};

struct ClientData {

    int id;
    constants::Direction direction;
    bool isPressed;

};

inline sf::Packet& operator <<(sf::Packet& packet, const ServerData& data) {
    return packet << data.player1PaddleY << data.player2PaddleY << data.ballX << data.ballY;
}

inline sf::Packet& operator >>(sf::Packet& packet, ServerData& data) {
    return packet >> data.player1PaddleY >> data.player2PaddleY >> data.ballX >> data.ballY;
}

//sf::Packet& operator <<(sf::Packet& packet, const ClientData& data) {
//    return packet << static_cast<float>(data.id) << static_cast<float>data.direction << data.isPressed;
//}
//
//sf::Packet& operator >>(sf::Packet& packet, ClientData& data) {
//    return packet >>  >> data.direction >> data.isPressed;
//}