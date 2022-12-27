//
// Created by Matúš Mištrik on 27/12/2022.
//

#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void Run();

private:
    static const sf::Time TimePerFrame;
    static const int windowHeight;
    static const int windowWidth;
    sf::RenderWindow mainWindow;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInputs(sf::Keyboard::Key key, bool isPressed);
};