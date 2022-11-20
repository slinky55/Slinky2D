#pragma once

#include "Slinky/Particle/Particle.hpp"

namespace Slinky::Particle
{
    class ParticleContact
    {
    public:
        Particle* particles[2];

        float restitution;
        float intersection;

        Math::Vector2 normal;

    protected:
        void Resolve(float _dt);
        [[nodiscard]] float SeparatingVelocity() const;

    private:
        void ResolveImpulse(float _dt);
        void ResolveIntersection(float _dt);
    };
}