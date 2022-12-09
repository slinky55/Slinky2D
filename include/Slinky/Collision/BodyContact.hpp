#pragma once

#include <array>

#include "Slinky/Dynamics/Body.hpp"

namespace Slinky::Collision
{
    struct ContactKey
    {
        Dynamics::Body* A;
        Dynamics::Body* B;
    };
    
    struct BodyContact
    {
        std::array<Dynamics::Body*, 2> bodies;

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
