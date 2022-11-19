#include <Slinky/Core/World.hpp>

namespace Slinky::Core
{
    World::World(const Math::Vector2& _gravity)
        : m_gravity{_gravity}
    {}
    World::~World()
    {
        for (auto body : m_bodies)
        {
            delete body;
        }
    }

    Collision::Body* World::CreateBody(const Collision::BodyCfg& _cfg)
    {
        return m_bodies.emplace_back(new Collision::Body(_cfg));
    }

    void World::DestroyBody(Collision::Body *_body)
    {
        std::remove(m_bodies.begin(), m_bodies.end(), _body);
        delete _body;
        _body = nullptr;
    }


    void World::Step(float _dt) const
    {
        for (auto& body : m_bodies)
        {
            body->ApplyForce(m_gravity);

            body->Integrate(_dt);

            body->ClearForces();
        }
    }
}