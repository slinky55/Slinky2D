#pragma once

#include <array>

#include "Slinky/Dynamics/Body.hpp"

namespace Slinky::Dynamics
{
    struct BodyContact
    {
        std::array<Body*, 2> bodies;

        float restitution;
        float intersection;

        Math::Vector2 normal;
    };

    inline float SeparatingVelocity(BodyContact* contact)
    {
        Math::Vector2 rel { contact->bodies[0]->linearVelocity };
        if ( contact->bodies[1] )
            rel -= contact->bodies[1]->linearVelocity;
        return rel * contact->normal;
    }
}
