//
// Created by Matúš Mištrik on 27/12/2022.
//

#include <SFML/Graphics.hpp>

using namespace std;
int main() {
    sf::RenderWindow window(
            sf::VideoMode(640, 480),
            "Hello World");
    sf::CircleShape shape(200);

    while (window.isOpen())
    {
        sf::Event event;
        while (
                window.pollEvent(event))
            if (event.type ==
                sf::Event::Closed)
                window.close();

        window.clear();
        window.draw(shape);
        window.display();
    }
}