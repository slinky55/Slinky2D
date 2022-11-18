#pragma once

#include <vector>

#include <Slinky/Collision/Body.hpp>

namespace Slinky::Core
{
    class World
    {
    public:
        World() = default;
        ~World();

        Collision::Body*    CreateBody(const Collision::BodyCfg& _cfg);
        void                DestroyBody(Collision::Body* _body);

        void Step(float _dt);

    private:
        std::vector<Collision::Body*> m_bodies;
    };
}