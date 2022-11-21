#include "Slinky/Collision/BodyContactSolver.hpp"

namespace Slinky::Collision
{
    BodyContactSolver::BodyContactSolver(uint8_t _itr)
            :
            iterations{_itr}
    {}

    void BodyContactSolver::SetIterations(uint8_t _itr)
    {
        iterations = _itr;
    }

    void BodyContactSolver::ResolveContacts(std::vector<BodyContact*>& contactArray,
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
