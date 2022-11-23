#pragma once

#include "Slinky/Particle/Particle.hpp"

namespace Slinky::Particle
{
    class ParticleForceGen
    {
    public:

        virtual void updateForce(Particle* _particle,
                                 float _dt) = 0;
    };
}