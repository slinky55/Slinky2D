#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <memory>

#include "Slinky/Dynamics/Body.hpp"
#include "Slinky/Dynamics/BodyContact.hpp"

#include "Slinky/Containers/BodyQuadTree.hpp"

#include "Slinky/Dynamics/Solvers.hpp"

namespace Slinky::Dynamics
{
    using BroadPhaseList = std::vector<std::pair<Body*, Body*>>;
    using NarrowPhaseList = std::vector<std::unique_ptr<BodyContact>>;

    class DWorld
    {
    public:
        explicit DWorld(const Math::Vector2& _grav)
            :
            m_gravity{_grav}
        {}
        ~DWorld() = default;

        /*
         * @return Newly created body
         * @param _body Body to copy
         */
        Body* CreateBody(const Body& _body)
        {
            return m_bodies.emplace_back(std::make_unique<Body>(_body)).get();
        }

        /*
         * @return The list of bodies in the world
         */
        [[nodiscard]] const std::vector<std::unique_ptr<Body>>& Bodies() const { return m_bodies; }

        /*
         * Step the physics world
         * @param _dt The time step
         */
        void Step(float _dt)
        {
            Containers::BodyQuadTree tree {
                    {{0.f, 0.f}, {800.f / 32.f, 600.f / 32.f}},
                    0
            };

            for (auto const& body : m_bodies)
            {
                ApplyForceToCM(body.get(), m_gravity * body->mass);
                IntegrateBody(body.get(), _dt);

                tree.Insert(body.get());
            }

            BroadPhaseList broadList;
            tree.GetPairs(broadList);

            NarrowPhaseList narrowList;
            for (auto const& [A, B] : broadList)
            {
                if (auto intersection { Collision::AABBvsAABB(A->collider, B->collider) };
                    intersection)
                {

                    auto const& contact { narrowList.emplace_back(std::make_unique<BodyContact>()) };

                    contact->bodies[0] = A;
                    contact->bodies[1] = B;

                    if (intersection->x < intersection->y)
                    {
                        if (A->position.x < B->position.x)
                        {
                            contact->normal = {-1.f, 0.f};
                        }
                        else
                        {
                            contact->normal = {1.f, 0.f};
                        }
                        contact->intersection = intersection->x;
                    }
                    else if (intersection->x > intersection->y)
                    {
                        if (A->position.y < B->position.y)
                        {
                            contact->normal = {0.f, -1.f};
                        }
                        else
                        {
                            contact->normal = {0.f, 1.f};
                        }
                        contact->intersection = intersection->y;
                    }
                    else
                    {
                        contact->normal = intersection->Normal();
                        contact->intersection = intersection->Magnitude();
                    }

                    contact->restitution = std::min(A->restitution, B->restitution);
                }

            }

            for (std::size_t itr {0}; itr < narrowList.size() * 2; itr++)
            {
                float max {0};
                std::size_t maxI { narrowList.size() };
                for (std::size_t i {0}; i < narrowList.size(); i++)
                {
                    float sepVelocity { Dynamics::SeparatingVelocity(narrowList[i].get()) };
                    if (sepVelocity < max)
                    {
                        max = sepVelocity;
                        maxI = i;
                    }
                }

                SolveImpulse(narrowList[maxI].get());
                SolvePositionSmooth(narrowList[maxI].get());
            }

            for (auto const& body : m_bodies)
            {
                ClearForces(body.get());
            }
        }
    private:
        Math::Vector2 m_gravity;

        std::vector<std::unique_ptr<Body>> m_bodies;
    };
}