#include "Slinky/Particle/ParticleContactSolver.hpp"

namespace Slinky::Particle
{
    ParticleContactSolver::ParticleContactSolver(uint8_t _itr)
    :
    iterations{_itr}
    {}

    void ParticleContactSolver::SetIterations(uint8_t _itr)
    {
        iterations = _itr;
    }

    void ParticleContactSolver::ResolveContacts(std::vector<ParticleContact*>& contactArray,
                                                float _dt) const
    {
        for (uint8_t itr {0}; itr < iterations; itr++)
        {
            float max {0};

            std::size_t maxI { contactArray.size() };

            for (std::size_t i {0}; i < contactArray.size(); i++)
            {
                if (float sepVelocity { contactArray[i]->SeparatingVelocity() };
                    sepVelocity < max)
                {
                    max = sepVelocity;
                    maxI = i;
                }
            }

            contactArray[maxI]->Resolve(_dt);
        }
    }
}