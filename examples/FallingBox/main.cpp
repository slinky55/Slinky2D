#include <random>

#include <SFML/Graphics.hpp>

#include <Slinky/Dynamics/World.hpp>

// Needed for Slinky2D to work in meters
constexpr float PIXELS_PER_METER {32.f};

using namespace Slinky;

int main(int argc, char** argv)
{
    // For random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xRange(100, 700);
    std::uniform_real_distribution<float> yRange(50, 200);

    // Set up SFML
    sf::RenderWindow window;
    window.create(sf::VideoMode{{800, 600}}, "Example - Falling Boxes");
    if (!window.isOpen())
    {
        std::cout << "Failed to create SFML Window\n";
        return -1;
    }

    // One rect to draw all physics objects
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);

    // Create physics world
    Dynamics::DWorld world { {0, 10.f} };
    // Create a large box
    world.CreateBody({
        { xRange(gen) / PIXELS_PER_METER,
        yRange(gen) / PIXELS_PER_METER },
        0.f,
        { 50 / PIXELS_PER_METER, 50 / PIXELS_PER_METER },
        70.f,
        0.3f,
        0.9f,
        0.1f
    });

    // Create ground body
    world.CreateBody({
        { 400.f / PIXELS_PER_METER, (600.f - 16.f) / PIXELS_PER_METER },
        0.f,
        { 800.f / PIXELS_PER_METER, 32.f / PIXELS_PER_METER },
        0.f,
        0.3f,
        0.0f,
        0.0f
    });

    sf::Clock dt;

    while (window.isOpen())
    {
        // Event handling
        sf::Event e {};
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        world.Step(dt.restart().asSeconds());

        // Draw code
        window.clear();
        for (auto const& body : world.Bodies())
        {
            rect.setOrigin({body->halfSize.x * PIXELS_PER_METER, body->halfSize.y * PIXELS_PER_METER});
            rect.setPosition({body->position.x * PIXELS_PER_METER, body->position.y * PIXELS_PER_METER});
            rect.setSize({body->size.x * PIXELS_PER_METER, body->size.y * PIXELS_PER_METER});
            //rect.setRotation(sf::radians(body->orientation));
            window.draw(rect);
        }
        window.display();
    }

    return 0;
}
