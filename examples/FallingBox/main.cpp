#include <iostream>
#include <cassert>

#include <SFML/Graphics.hpp>

#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Collision/Body.hpp>
#include <Slinky/Core/World.hpp>

constexpr float PIXELS_PER_METER {32.f};

using namespace Slinky;

struct PhysicsRect
{
    sf::RectangleShape rect;
    Collision::Body *body {nullptr};
};

int main()
{
    sf::RenderWindow window;

    Core::World world {{0, 10.f}};

    PhysicsRect box;

    window.create(sf::VideoMode{{800, 600}}, "Example - Bounding Test");
    assert(window.isOpen() && "Failed to created SFML Window");

    box.body = world.CreateBody({
        {400 / PIXELS_PER_METER, 100 / PIXELS_PER_METER},
        { 20 / PIXELS_PER_METER, 20 / PIXELS_PER_METER},
        70,
        .5f,
        .9f
    });

    box.rect.setSize({20, 20});
    box.rect.setFillColor(sf::Color::White);

    sf::Clock dt;
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

        world.Step(dt.restart().asSeconds());

        box.rect.setPosition({
            (box.body->Position().x - box.body->HalfSize().x) * PIXELS_PER_METER,
            (box.body->Position().y - box.body->HalfSize().y) * PIXELS_PER_METER,
        });

        window.clear();
        window.draw(box.rect);
        window.display();
    }

    return 0;
}