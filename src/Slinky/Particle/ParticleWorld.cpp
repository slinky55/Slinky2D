#include <Slinky/Particle/ParticleWorld.hpp>

namespace Slinky::Particle
{
    ParticleWorld::ParticleWorld(const Math::Vector2& _grav)
        :
        gravity{_grav}
    {}

    ParticleWorld::~ParticleWorld()
    {
        for (auto& particle : particles)
        {
            delete particle;
        }
    }

    Particle* ParticleWorld::CreateParticle(const ParticleCfg &_cfg)
    {
        return particles.emplace_back(new Particle{_cfg});
    }

    void ParticleWorld::DestroyParticle(Particle* _particle)
    {
        return;
    }

    void ParticleWorld::Step(float _dt)
    {
        for (auto& particle : particles)
        {
            // If particle has infinite mass,
            // don't apply gravity
            if (particle->Mass() == 0.f) continue;

            particle->ApplyForce(gravity * particle->Mass());
        }

        for (auto& particle : particles)
        {
            particle->Integrate(_dt);

            if (particle->Lifetime() < 0.f)
            {
                DestroyParticle(particle);
            }
        }
        Containers::ParticleQuadTree quadTree{
                {
                    {0.f, 0.f},
                    {800.f / 32.f, 600.f / 32.f}
                },
                0
        };

        for (auto& particle : particles)
        {
            quadTree.Insert(particle);
        }

        std::vector<std::pair<Particle*, Particle*>> pairs;
        quadTree.GetPairs(pairs);

        for (auto const& [A, B] : pairs)
        {
            float distanceSq {powf((B->Position().x - A->Position().x), 2) +
                              powf((B->Position().y - A->Position().y), 2)};

            if (float rSq{powf(A->Radius() + B->Radius(), 2)};
                    rSq > distanceSq)
            {
                auto& contact { contacts.emplace_back(new ParticleContact) };
                contact->particles[0] = A;
                contact->particles[1] = B;
                contact->restitution = std::min(A->Restitution(), B->Restitution());
                contact->normal = Math::Normal(A->Position() - B->Position());
                contact->intersection = (rSq - distanceSq);
            }
        }

        for (auto& contact : contacts)
        {
            contact->Resolve(_dt);
        }

        contacts.clear();
    }

    const std::vector<Particle*>& ParticleWorld::Particles() const
    {
        return particles;
    }

    void ParticleWorld::GenerateContacts()
    {
        for (auto A : particles)
        {
            for (auto B : particles) {
                if (A == B) continue;

                // If the distance is less than the sum of radii,
                // the particles are colliding
                float distanceSq {powf((B->Position().x - A->Position().x), 2) +
                                  powf((B->Position().y - A->Position().y), 2)};

                if (float rSq{powf(A->Radius() + B->Radius(), 2)};
                    rSq > distanceSq)
                {
                     auto& contact { contacts.emplace_back(new ParticleContact) };
                     contact->particles[0] = A;
                     contact->particles[1] = B;
                     contact->restitution = std::min(A->Restitution(), B->Restitution());
                     contact->intersection = rSq - distanceSq;
                     contact->normal = Math::Normal(B->Position() - A->Position());
                }
            }
        }
    }
}