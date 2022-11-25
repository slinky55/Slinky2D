//#include "Slinky/Containers/BodyQuadTree.hpp"
//
//namespace Slinky::Containers {
//    BodyQuadTree::BodyQuadTree(const Collision::AABB &_bounds,
//                               std::size_t _level)
//            :
//            bounds{_bounds},
//            level{_level} {}
//
//    bool BodyQuadTree::Insert(Collision::Body *body)
//    {
//        if (!bounds.Contains(body->Collider())) return false;
//
//        if (isLeaf)
//        {
//            bodies.push_back(body);
//
//            if (bodies.size() > MAX_OBJECTS && level < MAX_LEVELS)
//            {
//                Divide();
//            }
//
//            return true;
//        }
//        else
//        {
//            if (topLeft->Insert(body)) return true;
//            if (topRight->Insert(body)) return true;
//            if (bottomLeft->Insert(body)) return true;
//            if (bottomRight->Insert(body)) return true;
//            bodies.push_back(body);
//            return true;
//        }
//    }
//
//    void BodyQuadTree::GetPairs(std::vector<std::pair<Collision::Body *, Collision::Body *>> &pairs)
//    {
//        for (std::size_t i {0}; i < bodies.size(); ++i)
//        {
//            for (std::size_t j {i + 1}; j < bodies.size(); ++j)
//            {
//                pairs.emplace_back(bodies[i], bodies[j]);
//            }
//
//            if (!isLeaf)
//            {
//                GetPairsInChild(pairs, bodies[i], topLeft.get());
//                GetPairsInChild(pairs, bodies[i], topRight.get());
//                GetPairsInChild(pairs, bodies[i], bottomLeft.get());
//                GetPairsInChild(pairs, bodies[i], bottomRight.get());
//            }
//        }
//
//        if (!isLeaf)
//        {
//            topLeft->GetPairs(pairs);
//            topRight->GetPairs(pairs);
//            bottomLeft->GetPairs(pairs);
//            bottomRight->GetPairs(pairs);
//        }
//    }
//
//    void BodyQuadTree::Divide()
//    {
//        isLeaf = false;
//
//        const Math::Vector2 center { bounds.center };
//        const Math::Vector2 halfSize { bounds.hSize };
//
//        topLeft = std::make_unique<BodyQuadTree>(
//                Collision::AABB{{center - (halfSize / 2.f)}, {halfSize / 2.f}},
//                level + 1
//        );
//        topRight = std::make_unique<BodyQuadTree>(
//                Collision::AABB{{center.x + (halfSize / 2.f).x,
//                                 center.y - (halfSize / 2.f).y}, {halfSize / 2.f}},
//                level + 1
//        );
//        bottomLeft = std::make_unique<BodyQuadTree>(
//                Collision::AABB{{center.x - (halfSize / 2.f).x,
//                                 center.y + (halfSize / 2.f).y}, {halfSize / 2.f}},
//                level + 1
//        );
//        bottomRight = std::make_unique<BodyQuadTree>(
//                Collision::AABB{{center + (halfSize / 2.f)}, {halfSize / 2.f}},
//                level + 1
//        );
//
//        std::vector<Collision::Body*> temp{};
//        for (auto body : bodies)
//        {
//            if (topLeft->Insert(body)) continue;
//            if (topRight->Insert(body)) continue;
//            if (bottomLeft->Insert(body)) continue;
//            if (bottomRight->Insert(body)) continue;
//            temp.push_back(body);
//        }
//        bodies.clear();
//        std::move(temp.begin(), temp.end(), std::back_inserter(bodies));
//    }
//
//    void BodyQuadTree::GetPairsInChild(std::vector<std::pair<Collision::Body *, Collision::Body *>> &pairs,
//                                       Collision::Body *body,
//                                       BodyQuadTree* child)
//    {
//        for (auto childBody : child->bodies)
//        {
//            pairs.emplace_back(body, childBody);
//        }
//
//        if (!child->isLeaf)
//        {
//            GetPairsInChild(pairs, body, child->topLeft.get());
//            GetPairsInChild(pairs, body, child->topRight.get());
//            GetPairsInChild(pairs, body, child->bottomLeft.get());
//            GetPairsInChild(pairs, body, child->bottomRight.get());
//        }
//    }
//}