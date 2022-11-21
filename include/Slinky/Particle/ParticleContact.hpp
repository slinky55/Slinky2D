#pragma once

#include <array>

#include "Slinky/Particle/Particle.hpp"

namespace Slinky::Particle
{
    class ParticleContact
    {
    public:
        std::array<Particle*, 2> particles;

        float restitution;
        float intersection;

        Math::Vector2 normal;

        void Resolve(float _dt);
        [[nodiscard]] float SeparatingVelocity() const;
    private:
        void ResolveImpulse(float _dt) const;
        void ResolveIntersection(float _dt) const;
    };
}