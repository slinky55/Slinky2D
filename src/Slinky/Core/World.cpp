#include <Slinky/Core/World.hpp>

namespace Slinky::Core
{
    World::World(const Math::Vector2& _gravity,
                 uint8_t _itr)
        :
            solver{_itr},
            gravity{_gravity}
    {}
    World::~World()
    {
        bodies.erase(
            std::remove_if(bodies.begin(), bodies.end(), [](Collision::Body* _body)
            {
                delete _body;
                return true;
            }),
            bodies.end());
    }

    Collision::Body* World::CreateBody(const Collision::BodyCfg& _cfg)
    {
        return bodies.emplace_back(new Collision::Body(_cfg));
    }

    void World::DestroyBody(Collision::Body *_body)
    {
        bodies.erase(
                std::remove(bodies.begin(), bodies.end(), _body), bodies.end());
    }

    std::vector<Collision::Body*>& World::Bodies()
    {
        return bodies;
    }

    void World::Step(float _dt)
    {
        for (auto& body : bodies)
        {
            body->ApplyForce(gravity);
        }

        for (auto& body : bodies)
        {
            body->Integrate(_dt);
        }

        GenerateContacts();

        if (!contacts.empty())
            solver.ResolveContacts(contacts,
                                   _dt);

        for (auto& contact : contacts)
        {
            delete contact;
            contact = nullptr;
        }
        contacts.clear();

        for (auto& body : bodies)
        {
            body->ClearForces();
        }
    }

    void World::GenerateContacts()
    {
        for (auto& A : bodies)
        {
            for (auto& B : bodies) {
                //if (A == B) return;

                if (A->collider.Intersects(B->collider))
                {
                    auto& contact { contacts.emplace_back(new Collision::BodyContact) };

                    contact->bodies[0] = A;
                    contact->bodies[1] = B;

                    contact->normal = (B->pos - A->pos).Normal();

                    Math::Vector2 totalHSize { A->collider.hSize + B->collider.hSize };
                    Math::Vector2 dist { std::fabsf(B->pos.x - A->pos.x), std::fabsf(B->pos.y - A->pos.y) };

                    contact->intersection = (totalHSize - dist) * contact->normal;

                    contact->restitution = std::min(A->restitution, B->restitution);

                    std::cout << "Contact!\n";
                }
            }
        }
    }
}