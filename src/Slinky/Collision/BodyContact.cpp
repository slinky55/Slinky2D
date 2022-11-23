#include "Slinky/Collision/BodyContact.hpp"

namespace Slinky::Collision
{
    void BodyContact::Resolve(float _dt)
    {
        ResolveImpulse(_dt);
        ResolveIntersection(_dt);
    }

    float BodyContact::SeparatingVelocity() const
    {
        Math::Vector2 relVelocity {
                bodies[1]
                ?
                (bodies[0]->Velocity() - bodies[1]->Velocity())
                :
                (bodies[0]->Velocity())
        };

        return relVelocity * normal;
    }

    void BodyContact::ResolveImpulse(float _dt) const
    {
        float separatingVelocity { SeparatingVelocity() };

        if (separatingVelocity > 0) return;

        float newVelocity { -separatingVelocity * restitution };

        Math::Vector2 velocityFromAcc {
                bodies[1]
                ?
                (bodies[0]->Acceleration() - bodies[1]->Acceleration())
                :
                (bodies[0]->Acceleration())
        };

        if (float accSep {velocityFromAcc * normal * _dt}; accSep < 0)
        {
            newVelocity += restitution * accSep;
            if (newVelocity < 0) { newVelocity = 0; }
        }

        float deltaV { newVelocity - separatingVelocity };

        float totalInvMass {
                bodies[1]
                ?
                (bodies[0]->InvMass() + bodies[1]->InvMass())
                :
                (bodies[0]->InvMass())
        };

        if (totalInvMass <= 0) return;

        float impulse { deltaV / totalInvMass };
        Math::Vector2 impulsePerInvMass { normal * impulse };

        bodies[0]->SetVelocity(
                bodies[0]->Velocity() + impulsePerInvMass * bodies[0]->InvMass()
        );
        if (bodies[1])
        {
            bodies[1]->SetVelocity(
                    bodies[1]->Velocity() + impulsePerInvMass * -bodies[1]->InvMass()
            );
        }
    }

    void BodyContact::ResolveIntersection(float _dt) const
    {
        if (intersection <= 0) return;

        float totalInvMass {
                bodies[1]
                ?
                (bodies[0]->InvMass() + bodies[1]->InvMass())
                :
                (bodies[0]->InvMass())
        };

        if (totalInvMass <= 0) return;

        Math::Vector2 movePerInvMass {
                normal * (-intersection / totalInvMass)
        };

        bodies[0]->SetPosition(
            bodies[0]->Position() + movePerInvMass * bodies[0]->InvMass()
        );
        if (bodies[1])
        {
            bodies[1]->SetPosition(
                    bodies[1]->Position() + movePerInvMass * bodies[1]->InvMass()
            );
        }
    }
}