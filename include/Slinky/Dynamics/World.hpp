#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

#include "Slinky/Dynamics/Body.hpp"

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
            for (auto const& body : m_bodies)
            {
                ApplyForceToCM(body.get(), m_gravity * body->mass);
                IntegrateBody(body.get(), _dt);
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