#include <Slinky/Core/World.hpp>

namespace Slinky::Core
{
    World::World(const Math::Vector2& _gravity)
        :
        gravity{_gravity}
    {}

    std::shared_ptr<Collision::Body> World::CreateBody(const Collision::BodyCfg& _cfg)
    {
        return bodies.emplace_back(std::make_shared<Collision::Body>(_cfg));
    }

    void World::DestroyBody(std::shared_ptr<Collision::Body> const& _body)
    {
        bodies.erase(
                std::remove(bodies.begin(), bodies.end(), _body),
                bodies.end());
    }

    const std::vector<std::shared_ptr<Collision::Body>>& World::Bodies() const
    {
        return bodies;
    }

    void World::Step(float _dt) const
    {
        for (auto const& body : bodies)
        {
            body->ClearForces();
            body->ApplyForce(gravity);
            body->Integrate(_dt);
        }
    }
}