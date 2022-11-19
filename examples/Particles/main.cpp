#include <random>

#include <cstdint>

#include <SFML/Graphics.hpp>

#include <Slinky/Particle/Particle.hpp>
#include <Slinky/Particle/ParticleWorld.hpp>
#include <Slinky/Math/Vector2.hpp>

constexpr float PIXELS_PER_METER {30.f};

using namespace Slinky;

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-20.f, 20.f);

    sf::RenderWindow window { sf::VideoMode{{800, 600}}, "Particles" };

    Particle::ParticleWorld world {{0.f, 10.f}};

    Math::Vector2 emitterPosition { 400.f / PIXELS_PER_METER, 300.f / PIXELS_PER_METER };

    std::vector<Particle::Particle*> particles;
    Particle::ParticleCfg cfg {
        emitterPosition,
        2 / PIXELS_PER_METER,
        10.f,
        0,
        0.99f,
        .5f
    };

    sf::RectangleShape particleShape;
    particleShape.setFillColor(sf::Color::White);
    particleShape.setSize({ 4.f, 4.f});

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

        world.CreateParticle(cfg)->SetVelocity({dist(gen), dist(gen)});

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