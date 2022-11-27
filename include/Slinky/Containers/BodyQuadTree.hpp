#pragma once

#include <vector>
#include <memory>

#include "Slinky/Dynamics/Body.hpp"
#include "Slinky/Collision/AABB.hpp"

namespace Slinky::Containers
{
    class BodyQuadTree
    {
    public:
        BodyQuadTree(const Collision::AABB& _bounds,
                     std::size_t _level);

        bool Insert(Dynamics::Body* body);

        void GetPairs(std::vector<std::pair<Dynamics::Body*, Dynamics::Body*>>& pairs);
    private:
        constexpr static std::size_t MAX_OBJECTS { 4 };
        constexpr static std::size_t MAX_LEVELS { 4 };

        Collision::AABB bounds;

        std::size_t level;

        bool isLeaf { true };

        std::vector<Dynamics::Body*> bodies;

        std::unique_ptr<BodyQuadTree> topLeft;
        std::unique_ptr<BodyQuadTree> topRight;
        std::unique_ptr<BodyQuadTree> bottomLeft;
        std::unique_ptr<BodyQuadTree> bottomRight;

        // Utility
        void Divide();
        void GetPairsInChild(std::vector<std::pair<Dynamics::Body*, Dynamics::Body*>>& pairs,
                             Dynamics::Body* body,
                             BodyQuadTree* child);
    };
}