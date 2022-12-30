//
// Created by Matúš Mištrik on 29/12/2022.
//

#include "ClientGame.h"

const float ClientGame::windowHeight = 600;
const float ClientGame::windowWidth = 800;

ClientGame::ClientGame()
: mainWindow(sf::VideoMode(windowWidth ,windowHeight, 32),"Online PONG!",sf::Style::Titlebar | sf::Style::Close),
  ball(), player1(true), player2(false)
{
}