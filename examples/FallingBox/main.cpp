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
    // Set up physics objects

    Core::World world {{0, 10.f}, 8 };

    // Box
    world.CreateBody({
        {400 / PIXELS_PER_METER, 100 / PIXELS_PER_METER},
        { 20 / PIXELS_PER_METER, 20 / PIXELS_PER_METER},
        70,
        .5f,
        .9f
    });

    // Ground
    world.CreateBody({
         {400 / PIXELS_PER_METER,  (600 - 16) / PIXELS_PER_METER},
         { 800 / PIXELS_PER_METER, 32 / PIXELS_PER_METER},
         0,
         .5f,
         .9f
    });

    // Set up SFML

    sf::RenderWindow window;

    window.create(sf::VideoMode{{800, 600}}, "Example - Bounding Test");
    assert(window.isOpen() && "Failed to created SFML Window");

    // Rect used for drawing, will use same rect for box and floor
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);

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

        window.clear();
        for (auto& body : world.Bodies())
        {
            rect.setPosition({
                (body->Position().x - body->HalfSize().x) * PIXELS_PER_METER,
                (body->Position().y - body->HalfSize().y) * PIXELS_PER_METER
            });
            rect.setSize({body->Size().x * PIXELS_PER_METER,
                          body->Size().y * PIXELS_PER_METER});
            window.draw(rect);
        }
        window.display();
    }

    return 0;
}