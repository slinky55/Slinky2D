#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include <Slinky/Collision/Body.hpp>
#include "Slinky/Collision/BodyContactSolver.hpp"
#include "Slinky/Collision/BodyContact.hpp"

namespace Slinky::Core
{
    class World
    {
    public:
        World(const Math::Vector2& _gravity,
              uint8_t _itr);
        ~World();

        Collision::Body*    CreateBody(const Collision::BodyCfg& _cfg);
        void                DestroyBody(Collision::Body* _body);

        void Step(float _dt);

        std::vector<Collision::Body*>& Bodies();
    private:
        std::vector<Collision::Body*> bodies;
        std::vector<Collision::BodyContact*> contacts;

        Collision::BodyContactSolver solver;

        Math::Vector2 gravity;

        void GenerateContacts();
    };
}