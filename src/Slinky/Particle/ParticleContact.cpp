#include "Slinky/Particle/ParticleContact.hpp"

namespace Slinky::Particle
{
    void ParticleContact::Resolve(float _dt)
    {
        ResolveImpulse(_dt);
        ResolveIntersection(_dt);
    }
    float ParticleContact::SeparatingVelocity() const
    {
        Math::Vector2 relVelocity {
            particles[1]
            ?
            (particles[0]->Velocity() - particles[1]->Velocity())
            :
            (particles[0]->Velocity())
        };

        return relVelocity * normal;
    }

    void ParticleContact::ResolveImpulse(float _dt) const
    {
        float separatingVelocity { SeparatingVelocity() };

        if (separatingVelocity > 0) return;

        float newVelocity { separatingVelocity * restitution };

        Math::Vector2 velocityFromAcc {
            particles[1]
            ?
            (particles[0]->Acceleration() - particles[1]->Acceleration())
            :
            (particles[0]->Acceleration())
        };

        if (float accSep {velocityFromAcc * normal * _dt}; accSep < 0)
        {
            newVelocity += restitution * accSep;
            if (newVelocity < 0) { newVelocity = 0; }
        }

        float deltaV { newVelocity - separatingVelocity };

        float totalInvMass {
            particles[1]
            ?
            (particles[0]->InvMass() + particles[1]->InvMass())
            :
            (particles[0]->InvMass())
        };

        if (totalInvMass < 0) return;

        float impulse { deltaV / totalInvMass };
        Math::Vector2 impulsePerInvMass { normal * impulse };

        particles[0]->SetVelocity(
        particles[0]->Velocity() + impulsePerInvMass * particles[0]->InvMass()
        );
        if (particles[1])
        {
            particles[1]->SetVelocity(
                    particles[1]->Velocity() + impulsePerInvMass * particles[1]->InvMass()
            );
        }
    }
    void ParticleContact::ResolveIntersection([[maybe_unused]] float _dt) const
    {
        if (intersection <= 0) return;

        float totalInvMass {
            particles[1]
            ?
            (particles[0]->InvMass() + particles[1]->InvMass())
            :
            (particles[0]->InvMass())
        };

        if (totalInvMass <= 0) return;

        Math::Vector2 movePerInvMass {
            normal * (-intersection / totalInvMass)
        };

        particles[0]->SetPosition(
            particles[0]->Position() + movePerInvMass * particles[0]->InvMass()
        );
        if (particles[1])
        {
            particles[1]->SetPosition(
            particles[1]->Position() + movePerInvMass * particles[1]->InvMass()
            );
        }
    }
}