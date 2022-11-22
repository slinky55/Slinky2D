#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

#include "Slinky/Collision/Body.hpp"
#include "Slinky/Collision/BodyContact.hpp"

namespace Slinky::Core
{
    class World
    {
    public:
        explicit World(const Math::Vector2& _gravity);
        ~World() = default;

        std::shared_ptr<Collision::Body>    CreateBody(const Collision::BodyCfg& _cfg);
        void                                DestroyBody(std::shared_ptr<Collision::Body> const& _body);

        void Step(float _dt) const;

        [[nodiscard]] const std::vector<std::shared_ptr<Collision::Body>>& Bodies() const;
    private:
        std::vector<std::shared_ptr<Collision::Body>> bodies;
        std::vector<std::shared_ptr<Collision::BodyContact>> contacts;

        Math::Vector2 gravity;
    };
}