#include <iostream>
#include <cassert>

#include <SFML/Graphics.hpp>

#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Collision/AABB.h>

constexpr float PIXELS_PER_METER {32.f};

using namespace Slinky;

struct PhysicsRect
{
    sf::RectangleShape rect;
    Collision::AABB collider;
};

struct State
{
    PhysicsRect rect1;
    PhysicsRect rect2;

    sf::RenderWindow window;
};

int main()
{
    State state;

    state.window.create(sf::VideoMode{{800, 600}}, "Example - Bounding Test");
    assert(state.window.isOpen() && "Failed to created SFML Window");

    state.rect1.collider.center = {400 / PIXELS_PER_METER, 300 / PIXELS_PER_METER};
    state.rect1.collider.hSize = {100 / PIXELS_PER_METER, 25 / PIXELS_PER_METER};
    state.rect1.rect.setSize({200, 50});
    state.rect1.rect.setFillColor(sf::Color::White);
    state.rect1.rect.setPosition({300, 300});

    while (state.window.isOpen())
    {
        sf::Event e {};
        while (state.window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                state.window.close();
            }
        }

        state.window.clear();
        state.window.draw(state.rect1.rect);
        state.window.display();
    }

    return 0;
}