#pragma once

#include <vector>
#include <memory>

#include "Slinky/Dynamics/BodyContact.hpp"

namespace Slinky::Dynamics
{
    inline void SolveImpulse(BodyContact* contact)
    {
        Math::Vector2 relativeVelocity {
            contact->bodies[1]->linearVelocity - contact->bodies[0]->linearVelocity
        };

        float normalVelocity { relativeVelocity * contact->normal };
        if (normalVelocity <= 0) return;

        float e { std::min(contact->bodies[0]->restitution, contact->bodies[1]->restitution) };
        float totalInvMass { contact->bodies[0]->invMass + contact->bodies[1]->invMass };

        float j { -(1.0f + e) * normalVelocity / totalInvMass };

        Math::Vector2 impulse { contact->normal * j };
        contact->bodies[0]->linearVelocity -= impulse * contact->bodies[0]->invMass;
        contact->bodies[1]->linearVelocity += impulse * contact->bodies[1]->invMass;
    }

    inline void SolvePositionSmooth(BodyContact* contact)
    {
        constexpr float slop { 0.01f };
        constexpr float percent { 0.8f };

        Math::Vector2 correction {
            contact->normal * percent * std::max(contact->intersection - slop, 0.0f) /
            (contact->bodies[0]->invMass + contact->bodies[1]->invMass)
        };

        contact->bodies[0]->position -= correction * contact->bodies[0]->invMass;
        contact->bodies[1]->position += correction * contact->bodies[1]->invMass;
    }
}