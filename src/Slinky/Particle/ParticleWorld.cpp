#include <Slinky/Particle/ParticleWorld.hpp>

namespace Slinky::Particle
{
    ParticleWorld::ParticleWorld(const Math::Vector2& _grav,
                                 uint8_t _itr)
        :
        solver{_itr},
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
        particles.erase(
                std::remove(particles.begin(), particles.end(), _particle),
                particles.end());
    }

    void ParticleWorld::Step(float _dt)
    {
        for (auto& particle : particles)
        {
            particle->ApplyForce(gravity);
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
            float distanceSq {std::powf((B->Position().x - A->Position().x), 2) +
                              std::powf((B->Position().y - A->Position().y), 2)};

            if (float rSq{std::powf(A->Radius() + B->Radius(), 2)};
                    rSq > distanceSq)
            {
                auto& contact { contacts.emplace_back(new ParticleContact) };
                contact->particles[0] = A;
                contact->particles[1] = B;
                contact->restitution = std::min(A->Restitution(), B->Restitution());
                contact->intersection = rSq - distanceSq;
                contact->normal = (B->Position() - A->Position()).Normal();
            }
        }

        for (auto& contact : contacts)
        {
            contact->Resolve(_dt);
        }

        contacts.clear();

        for (auto& particle : particles)
        {
            particle->ClearForces();
        }
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
                float distanceSq {std::powf((B->Position().x - A->Position().x), 2) +
                                  std::powf((B->Position().y - A->Position().y), 2)};

                if (float rSq{std::powf(A->Radius() + B->Radius(), 2)};
                    rSq > distanceSq)
                {
                     auto& contact { contacts.emplace_back(new ParticleContact) };
                     contact->particles[0] = A;
                     contact->particles[1] = B;
                     contact->restitution = std::min(A->Restitution(), B->Restitution());
                     contact->intersection = rSq - distanceSq;
                     contact->normal = (B->Position() - A->Position()).Normal();
                }
            }
        }
    }
}