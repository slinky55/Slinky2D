#include <random>

#include <SFML/Graphics.hpp>

#include <Slinky/Particle/Particle.hpp>
#include <Slinky/Particle/ParticleWorld.hpp>
#include <Slinky/Math/Vector2.hpp>

constexpr float PIXELS_PER_METER {32.f};

using namespace Slinky;

int main()
{
    // For creating random numbers in a range
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-3, 3);

    sf::RenderWindow window { sf::VideoMode{{800, 600}}, "Particles" };
    window.setFramerateLimit(60);

    /*
     * Holds list of particles, handles integration,
     * and collision detection/resolution.
     */
    Particle::ParticleWorld world {
        {0.f, 9.8f}
    };

    std::array<Math::Vector2, 3> emitters {
            Math::Vector2 { 400.f / PIXELS_PER_METER, 200.f / PIXELS_PER_METER },
            Math::Vector2 { 250.f / PIXELS_PER_METER, 150.f / PIXELS_PER_METER },
            Math::Vector2 { 550.f / PIXELS_PER_METER, 150.f / PIXELS_PER_METER }
    };

    // Define config for all particles
    Particle::ParticleCfg cfg {
        {0, 0},
        .5f / PIXELS_PER_METER,
        10.f,
        0.9f,
        0.9f,
        5.f
    };

    // Use one circle for all particles
    sf::CircleShape particleShape;
    particleShape.setPointCount(100);
    particleShape.setFillColor(sf::Color::Cyan);
    particleShape.setRadius(2);

    sf::Clock dt;
    while (window.isOpen())
    {
        // Poll events
        sf::Event e {};
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        for (auto const& emitter : emitters)
        {
            // Set position of config
            cfg.pos = emitter;
            for (uint32_t i {0}; i < 10; i++)
            {
                // Create a new particle
                auto particle { world.CreateParticle(cfg) };

                // Set random velocity
                particle->SetVelocity({ dist(gen), dist(gen) });
            }
        }

        // Physics step
        if (dt.getElapsedTime().asSeconds() >= 1.f / 60.f)
        {
            world.Step(dt.restart().asSeconds());
        }

        // Draw all particles
        window.clear();

        particleShape.setRadius(cfg.radius * PIXELS_PER_METER);
        for (auto const& particle : world.Particles())
        {
            particleShape.setPosition({particle->Position().x * PIXELS_PER_METER,
                                       particle->Position().y * PIXELS_PER_METER});
            window.draw(particleShape);
        }

        window.display();
    }

    return 0;
}