#include <random>

#include <SFML/Graphics.hpp>

#include "Slinky/Dynamics/World.hpp"

// Needed for Slinky2D to work in meters
constexpr float PIXELS_PER_METER {32.f};

using namespace Slinky;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <box count>\n";
        return -1;
    }

    // For random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xRange(100, 700);
    std::uniform_real_distribution<float> yRange(50, 200);

    // Set up SFML
    sf::RenderWindow window;
    window.create(sf::VideoMode{{800, 600}}, "Example - Falling Box");
    if (!window.isOpen())
    {
        std::cout << "Failed to create SFML Window\n";
        return -1;
    }
    window.setFramerateLimit(60);

    // Create physics world
    Dynamics::DWorld world { {0, 9.81f} };

    // Create physics box
    auto* box { world.CreateBody({
        { xRange(gen) / PIXELS_PER_METER,
          yRange(gen) / PIXELS_PER_METER },
        0.f,
        { 32.f / PIXELS_PER_METER, 32.f / PIXELS_PER_METER },
        70.f,
        0.3f,
        0.9f,
        0.1f
    })};

    // Rect used for drawing, will use same rect for box and floor
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);
    rect.setOrigin({box->halfSize.x * PIXELS_PER_METER, box->halfSize.y * PIXELS_PER_METER});
    rect.setPosition({box->position.x * PIXELS_PER_METER, box->position.y * PIXELS_PER_METER});
    rect.setSize({box->size.x * PIXELS_PER_METER, box->size.y * PIXELS_PER_METER});
    rect.setRotation(sf::radians(box->orientation));

    sf::Clock dt;

    // Prevent applying too much rotational force
    bool spinning { false };

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spinning)
        {
            Dynamics::ApplyForceToPoint(box, {-1.f, 0.5f}, {20.f, 0.f});
            spinning = true;
        }

        world.Step(dt.restart().asSeconds());

        // Draw code
        window.clear();
        rect.setPosition({box->position.x * PIXELS_PER_METER, box->position.y * PIXELS_PER_METER});
        rect.setRotation(sf::radians(box->orientation));
        window.draw(rect);
        window.display();
    }

    return 0;
}
