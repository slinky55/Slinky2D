#pragma once

#include <cstdint>
#include <vector>

#include "Slinky/Collision/BodyContact.hpp"

namespace Slinky::Collision
{
    class BodyContactSolver
    {
    public:
        explicit BodyContactSolver(uint8_t _itr);

        void SetIterations(uint8_t _itr);

        void ResolveContacts(std::vector<BodyContact*>& contactArray,
                             float _dt) const;

    private:
        // Not likely (I hope) to use 255+ iterations
        uint8_t iterations;
    };
}