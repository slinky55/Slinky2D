#include <random>

#include <SFML/Graphics.hpp>

#include <Slinky/Particle/Particle.hpp>
#include <Slinky/Particle/ParticleWorld.hpp>
#include <Slinky/Math/Vector2.hpp>

constexpr float PIXELS_PER_METER {30.f};

using namespace Slinky;

int main()
{
    // For creating random numbers in a range
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-20.f, 20.f);

    sf::RenderWindow window { sf::VideoMode{{800, 600}}, "Particles" };

    /*
     * Holds list of particles, handles integration,
     * and collision detection/resolution.
     */
    Particle::ParticleWorld world {
        {0.f, 3.2},
        8
    };

    // Position of the particle emitter
    Math::Vector2 emitterPosition { 400.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER };

    // Define config for all particles
    Particle::ParticleCfg cfg {
        emitterPosition,
        2 / PIXELS_PER_METER,
        10.f,
        0,
        0.99f,
        2.f
    };

    // Use one rectangle for all particles
    sf::RectangleShape particleShape;
    particleShape.setFillColor(sf::Color::White);
    particleShape.setSize({ 4.f, 4.f});

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

        // Physics step
        world.Step(dt.restart().asSeconds());

        // Generate new particles
        for (uint32_t i {0}; i < 10; i++)
        {
            Particle::Particle* particle = world.CreateParticle(cfg);

            // Randomize initial velocity
            particle->SetVelocity({dist(gen), dist(gen)});
        }

        // Draw all particles
        window.clear();
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