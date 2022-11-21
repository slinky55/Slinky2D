#include <random>
#include <array>

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
    std::uniform_real_distribution<float> dist(-3, 3);

    sf::RenderWindow window { sf::VideoMode{{800, 600}}, "Particles" };

    /*
     * Holds list of particles, handles integration,
     * and collision detection/resolution.
     */
    Particle::ParticleWorld world {
        {0.f, 3.2},
        8
    };

    // emitter positions
    std::vector<Math::Vector2> emitters {
        { 350.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 360.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 370.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 380.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 390.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 400.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 410.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 420.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 430.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 440.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER },
        { 450.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER }
    };


    // Define config for all particles
    Particle::ParticleCfg cfg {
        emitters[0],
        2 / PIXELS_PER_METER,
        10.f,
        0,
        0.99f,
        2.f
    };

    // Use one rectangle for all particles
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

        // Physics step
        world.Step(dt.restart().asSeconds());

        for (const auto& emitter : emitters)
        {
            for (uint32_t i {0}; i < 10; i++)
            {
                // set cfg position
                cfg.pos = emitter;

                // Create a new particle
                auto particle = world.CreateParticle(cfg);

                // Set random velocity
                particle->SetVelocity({ dist(gen), dist(gen) });
            }
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