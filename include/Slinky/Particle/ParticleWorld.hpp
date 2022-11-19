#pragma once

#include <vector>

#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Particle/Particle.hpp>

namespace Slinky::Particle
{
    class ParticleWorld
    {
    public:
        explicit ParticleWorld(const Math::Vector2& _grav);
        ~ParticleWorld();

        Particle* CreateParticle(const ParticleCfg& _cfg);
        void DestroyParticle(Particle* _particle);

        void Step(float _dt);

        const std::vector<Particle*>& Particles() const;
    private:
        std::vector<Particle*> particles;

        Math::Vector2 gravity;
    };
}