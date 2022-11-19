#pragma once

#include <vector>
#include <algorithm>

#include <Slinky/Collision/Body.hpp>

namespace Slinky::Core
{
    class World
    {
    public:
        explicit World(const Math::Vector2& _gravity);
        ~World();

        Collision::Body*    CreateBody(const Collision::BodyCfg& _cfg);
        void                DestroyBody(Collision::Body* _body);

        void Step(float _dt) const;

    private:
        std::vector<Collision::Body*> m_bodies;

        Math::Vector2 m_gravity;
    };
}