#pragma once

#include <cmath>

#include <Slinky/Math/Vector2.hpp>

namespace Slinky::Particle
{
    class ParticleWorld;

    struct ParticleCfg
    {
        Math::Vector2 pos;

        float mass;
        float restitution;
        float damping;
        float radius;
        float lifetime;

        ParticleCfg(const Math::Vector2& _pos,
                    float _radius,
                    float _mass,
                    float _restitution,
                    float _damping,
                    float _lifetime);
    };

    struct Particle
    {
        [[nodiscard]] Math::Vector2 Position() const;
        [[nodiscard]] Math::Vector2 Velocity() const;
        [[nodiscard]] Math::Vector2 Acceleration() const;

        void SetPosition(const Math::Vector2& _pos);
        void SetVelocity(const Math::Vector2& _vel);
        void SetAcceleration(const Math::Vector2& _acc);

        [[nodiscard]] float Mass() const;
        [[nodiscard]] float InvMass() const;
        [[nodiscard]] float Restitution() const;
        [[nodiscard]] float Damping() const;
        [[nodiscard]] float Radius() const;

        [[nodiscard]] float Lifetime() const;

        void ApplyForce(const Math::Vector2& _force);
        void ClearForces();

        void Integrate(float _dt);

    private:
        friend class ParticleWorld;

        explicit Particle(const ParticleCfg& _cfg);

        Math::Vector2 pos;
        Math::Vector2 vel;
        Math::Vector2 acc;

        Math::Vector2 forces;

        float mass;
        float invMass;
        float restitution;
        float damping;
        float radius;

        float lifetime;
    };
}