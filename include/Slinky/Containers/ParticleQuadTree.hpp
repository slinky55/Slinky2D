
#include <vector>

#include "Slinky/Math/Vector2.hpp"
#include "Slinky/Collision/AABB.hpp"

#include "Slinky/Particle/Particle.hpp"

namespace Slinky::Containers
{
    class ParticleQuadTree
    {
    public:
        ParticleQuadTree(const Collision::AABB& _bounds,
                         std::size_t _level);

        void Insert(Particle::Particle* particle);

        void GetPairs(std::vector<std::pair<Particle::Particle*, Particle::Particle*>>& pairs);
    private:
        constexpr static std::size_t MAX_OBJECTS { 4 };
        constexpr static std::size_t MAX_LEVELS { 4 };

        Collision::AABB bounds;

        std::size_t level;

        bool isLeaf { true };

        std::vector<Particle::Particle*> particles;

        std::unique_ptr<ParticleQuadTree> topLeft;
        std::unique_ptr<ParticleQuadTree> topRight;
        std::unique_ptr<ParticleQuadTree> bottomLeft;
        std::unique_ptr<ParticleQuadTree> bottomRight;
    };
}