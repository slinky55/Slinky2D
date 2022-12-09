#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <memory>
#include <map>

#include "Slinky/Math/Vector2.hpp"
#include "Slinky/Math/Mat2.hpp"

#include "Slinky/Dynamics/Body.hpp"
#include "Slinky/Collision/BodyContact.hpp"

#include "Slinky/Containers/BodyQuadTree.hpp"

#include "Slinky/Dynamics/Solvers.hpp"

namespace Slinky::Dynamics
{
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
            // Get the list of collisions
            BroadPhase();

            // Integrate velocities
            for (auto const& body : m_bodies)
            {
                if (body->invMass == 0) continue;
                body->position += body->linearVelocity * _dt;
                body->linearVelocity += (m_gravity + (body->forces * body->invMass)) * _dt;
            }
        }
    private:
        Math::Vector2 m_gravity;

        std::vector<std::unique_ptr<Body>> m_bodies;
        std::vector<std::unique_ptr<BodyContact>> m_contacts;

        std::map<ContactKey, std::unique_ptr<BodyContact>> m_contactMap;

        void BroadPhase()
        {
            for (std::size_t i { 0 }; i < m_bodies.size(); ++i)
            {
                for (std::size_t j { i + 1 }; j < m_bodies.size(); ++j)
                {
                    if (m_bodies[i]->invMass == 0 && m_bodies[j]->invMass == 0) continue;

                    if ( auto intersection { Collision::AABBvsAABB(m_bodies[i]->collider, m_bodies[j]->collider) };
                         intersection )
                    {
                        m_contacts.emplace_back(std::make_unique<BodyContact>());
                    }
                }
            }
        }
    };
}