#pragma once

#include <vector>

#include "Slinky/Collision/Body.hpp"
#include "Slinky/Collision/AABB.hpp"

namespace Slinky::Containers
{
    class BodyQuadTree
    {
    public:
        BodyQuadTree(const Collision::AABB& _bounds,
                     std::size_t _level);

        bool Insert(Collision::Body* body);

        void GetPairs(std::vector<std::pair<Collision::Body*, Collision::Body*>>& pairs);
    private:
        constexpr static std::size_t MAX_OBJECTS { 4 };
        constexpr static std::size_t MAX_LEVELS { 4 };

        Collision::AABB bounds;

        std::size_t level;

        bool isLeaf { true };

        std::vector<Collision::Body*> bodies;

        std::unique_ptr<BodyQuadTree> topLeft;
        std::unique_ptr<BodyQuadTree> topRight;
        std::unique_ptr<BodyQuadTree> bottomLeft;
        std::unique_ptr<BodyQuadTree> bottomRight;

        // Utility
        void Divide();
        void GetPairsInChild(std::vector<std::pair<Collision::Body*, Collision::Body*>>& pairs,
                             Collision::Body* body,
                             BodyQuadTree* child);
    };
}