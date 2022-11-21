#pragma once

#include <cstdint>
#include <cstdlib>
#include <vector>

#include "Slinky/Particle/ParticleContact.hpp"

namespace Slinky::Particle
{
    class ParticleContactSolver
    {
    public:
        explicit ParticleContactSolver(uint8_t _itr);

        void SetIterations(uint8_t _itr);

        void ResolveContacts(std::vector<ParticleContact*>& contactArray,
                             float _dt) const;

    private:
        // Not likely (I hope) to use 255+ iterations
        uint8_t iterations;
    };
}
