#pragma once

#include <array>

#include "Slinky/Collision/Body.hpp"

namespace Slinky::Collision
{
    class BodyContact
    {
    public:
        std::array<Body*, 2> bodies;

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
