#include <random>

#include <SFML/Graphics.hpp>

#include <Slinky/Core/World.hpp>

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
    std::uniform_real_distribution<float> yRange(100, 500);

    // Set up SFML
    sf::RenderWindow window;
    window.create(sf::VideoMode{{800, 600}}, "Example - Falling Box");
    if (!window.isOpen())
    {
        std::cout << "Failed to create SFML Window\n";
        return -1;
    }

    // Create physics world
    Core::World world { {0, 9.81f} };

    // Box Config
    Collision::BodyCfg cfg {
            {0, 0},
            { 32.f / PIXELS_PER_METER, 32.f / PIXELS_PER_METER },
            70.f,
            0.3f,
            0.9f
    };

    // Create physics body for ground
    world.CreateBody({
        { 400.f / PIXELS_PER_METER, (600.f - 16) / PIXELS_PER_METER },
        { 800.f / PIXELS_PER_METER, 32.f / PIXELS_PER_METER },
        0.f,
        0.3f,
        0.f
    });

    // Rect used for drawing, will use same rect for box and floor
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);

    for (std::size_t i {0}; i < (std::stoi(argv[1])); i++)
    {
        cfg.pos = { xRange(gen) / PIXELS_PER_METER, yRange(gen) / PIXELS_PER_METER };
        world.CreateBody(cfg);
    }

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // Step physics world
        world.Step(dt.restart().asSeconds());

        // Draw code
        window.clear();
        for (auto const& body : world.Bodies())
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
