#include <Slinky/Particle/ParticleWorld.hpp>

namespace Slinky::Particle
{
    ParticleWorld::ParticleWorld(const Math::Vector2& _grav)
        :
        gravity{_grav}
    {}

    ParticleWorld::~ParticleWorld()
    {
        for (auto& particle : particles)
        {
            delete particle;
        }
    }

    Particle* ParticleWorld::CreateParticle(const ParticleCfg &_cfg)
    {
        return particles.emplace_back(new Particle(_cfg));
    }

    void ParticleWorld::DestroyParticle(Particle* _particle)
    {
        particles.erase(
                std::remove(particles.begin(), particles.end(), _particle),
                particles.end());
    }

    void ParticleWorld::Step(float _dt)
    {
        for (auto& particle : particles)
        {
            particle->ApplyForce(gravity);
            particle->Integrate(_dt);
            particle->ClearForces();

            if (particle->Lifetime() < 0.f)
            {
                DestroyParticle(particle);
            }
        }
    }

    const std::vector<Particle*>& ParticleWorld::Particles() const
    {
        return particles;
    }
}