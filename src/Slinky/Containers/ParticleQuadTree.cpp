#include "Slinky/Containers/ParticleQuadTree.hpp"

namespace Slinky::Containers
{
    ParticleQuadTree::ParticleQuadTree(const Collision::AABB& _bounds,
                                       std::size_t _level)
        :
        bounds{_bounds},
        level{_level}
    {}

    void ParticleQuadTree::Insert(Particle::Particle* particle)
    {
        // If the particle isn't inside this quadtree's bounds, return
        if (!bounds.Contains(particle->Position())) return;

        if (isLeaf)
        {
            // If this is the max level, add the particle to this quadtree, return
            if (level >= MAX_LEVELS)
            {
                particles.push_back(particle);
                return;
            }

            // If this quadtree is a leaf, and it has less than MAX_OBJECTS, add the particle to this quadtree, return
            if (particles.size() < MAX_OBJECTS)
            {
                particles.push_back(particle);
                return;
            }
            // If this quadtree is a leaf, and it has MAX_OBJECTS, split this quadtree into 4 sub-quadtrees, and add the particle to the appropriate sub-quadtree, return
            else
            {
                isLeaf = false;

                // Create the sub-quadtrees
                const Math::Vector2 halfSize = bounds.hSize / 2.0f;
                const Math::Vector2 center = bounds.center;

                const Collision::AABB topLeftBounds{center - halfSize, halfSize};
                const Collision::AABB topRightBounds{Math::Vector2{center.x + halfSize.x, center.y - halfSize.y}, halfSize};
                const Collision::AABB bottomLeftBounds{Math::Vector2{center.x - halfSize.x, center.y + halfSize.y}, halfSize};
                const Collision::AABB bottomRightBounds{center + halfSize, halfSize};

                topLeft = std::make_unique<ParticleQuadTree>(topLeftBounds, level + 1);
                topRight = std::make_unique<ParticleQuadTree>(topRightBounds, level + 1);
                bottomLeft = std::make_unique<ParticleQuadTree>(bottomLeftBounds, level + 1);
                bottomRight = std::make_unique<ParticleQuadTree>(bottomRightBounds, level + 1);

                // Add the particles to the appropriate sub-quadtree
                for (auto& p : particles)
                {
                    Insert(p);
                }

                // Add the new particle to the appropriate sub-quadtree
                Insert(particle);

                // Clear the particles vector
                particles.clear();
            }
        }
        else
        {
            // If this quadtree is not a leaf, add the particle to the appropriate sub-quadtree, return
            topLeft->Insert(particle);
            topRight->Insert(particle);
            bottomLeft->Insert(particle);
            bottomRight->Insert(particle);
        }
    }

    void ParticleQuadTree::GetPairs(std::vector<std::pair<Particle::Particle *, Particle::Particle *>> &pairs)
    {
        if (isLeaf)
        {
            // If this quadtree is a leaf, add all the pairs of particles in this quadtree to the pairs vector, return
            for (std::size_t i = 0; i < particles.size(); ++i)
            {
                for (std::size_t j = i + 1; j < particles.size(); ++j)
                {
                    pairs.emplace_back(particles[i], particles[j]);
                }
            }
        }
        else
        {
            // If this quadtree is not a leaf, add all the pairs of particles in the sub-quadtrees to the pairs vector, return
            topLeft->GetPairs(pairs);
            topRight->GetPairs(pairs);
            bottomLeft->GetPairs(pairs);
            bottomRight->GetPairs(pairs);
        }
    }
}