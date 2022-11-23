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

    void World::Step(float _dt)
    {
        for (auto const& body : bodies)
        {
            body->ApplyForce(gravity * body->Mass());
        }

        for (auto const& body : bodies)
        {
            body->Integrate(_dt);
        }

        Containers::BodyQuadTree quadTree {
                {{0, 0}, { 800 / 32.f, 600 / 32.f }},   // Temporary to test the quad tree
                0
        };

        for (auto const& body : bodies)
        {
            quadTree.Insert(body.get());
        }

        std::vector<std::pair<Collision::Body*, Collision::Body*>> pairs;
        quadTree.GetPairs(pairs);

        for (auto& [A, B] : pairs)
        {
            if (A->Collider().Intersects(B->Collider()))
            {
                auto const& contact {
                        contacts.emplace_back(std::make_shared<Collision::BodyContact>())
                };

                contact->bodies[0] = A;
                contact->bodies[1] = B;

                // Calculate the intersection
                const Math::Vector2 intersection {
                        (A->HalfSize().x + B->HalfSize().x) - std::fabsf(A->Position().x - B->Position().x),
                        (A->HalfSize().y + B->HalfSize().y) - std::fabsf(A->Position().y - B->Position().y)
                };

                // Find the collision normal
                if (intersection.x < intersection.y)
                {
                    if (A->Position().x < B->Position().x)
                    {
                        contact->normal = {-1.f, 0.f};
                    }
                    else
                    {
                        contact->normal = {1.f, 0.f};
                    }
                }
                else if (intersection.x > intersection.y)
                {
                    if (A->Position().y < B->Position().y)
                    {
                        contact->normal = {0.f, -1.f};
                    }
                    else
                    {
                        contact->normal = {0.f, 1.f};
                    }
                    contact->intersection = intersection.y;
                }
                else
                {
                    contact->normal = intersection.Normal();
                }

                contact->intersection = contact->normal * intersection;

                contact->restitution = std::fminf(A->Restitution(), B->Restitution());
            }
        }

        for (auto const& contact : contacts)
        {
            contact->Resolve(_dt);
        }

        contacts.clear();
    }
}