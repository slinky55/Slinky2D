#include <iostream>
#include <cassert>

#include <SFML/Graphics.hpp>

#include <Slinky/Math/Vector2.hpp>

using namespace Slinky;

int main()
{
    sf::RenderWindow window { sf::VideoMode{{800, 600}}, "Example - Test" };
    assert(window.isOpen());

    sf::RectangleShape rect;
    rect.setSize({50, 50});
    rect.setFillColor(sf::Color::White);
    rect.setPosition({100, 100});

    while (window.isOpen())
    {
        sf::Event e {};

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}