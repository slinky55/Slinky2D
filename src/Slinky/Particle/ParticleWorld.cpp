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
        return particles.emplace_back(new Particle(_cfg));
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
                if (A == B) return;
                std::cout << "collision!\n";

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
                     std::cout << "Collision!\n";
                }
            }
        }
    }
}