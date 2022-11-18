#include <iostream>
#include <cassert>

#include <SFML/Graphics.hpp>

#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Collision/AABB.hpp>

constexpr float PIXELS_PER_METER {32.f};

using namespace Slinky;

struct PhysicsRect
{
    sf::RectangleShape rect;

};

struct State
{
    PhysicsRect box;

    sf::RenderWindow window;
};

int main()
{
    State state;

    state.window.create(sf::VideoMode{{800, 600}}, "Example - Bounding Test");
    assert(state.window.isOpen() && "Failed to created SFML Window");

    state.box.collider.center = {400 / PIXELS_PER_METER, 300 / PIXELS_PER_METER};
    state.box.collider.hSize = {25 / PIXELS_PER_METER, 25 / PIXELS_PER_METER};
    state.box.rect.setSize({50, 50});
    state.box.rect.setFillColor(sf::Color::White);

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

        state.box.rect.setPosition({
           (state.box.collider.center.x - state.box.collider.hSize.x) * PIXELS_PER_METER,
           (state.box.collider.center.y - state.box.collider.hSize.y) * PIXELS_PER_METER,
        });

        state.window.clear();
        state.window.draw(state.box.rect);
        state.window.display();
    }

    return 0;
}