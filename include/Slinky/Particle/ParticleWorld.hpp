#pragma once

#include <vector>
#include <iostream>

#include "Slinky/Math/Vector2.hpp"

#include "Slinky/Particle/Particle.hpp"
#include "Slinky/Particle/ParticleContact.hpp"

#include "Slinky/Containers/ParticleQuadTree.hpp"

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

        [[nodiscard]] const std::vector<Particle*>& Particles() const;
    private:
        std::vector<Particle*> particles;
        std::vector<ParticleContact*> contacts;

        Math::Vector2 gravity;

        void GenerateContacts();
    };
}