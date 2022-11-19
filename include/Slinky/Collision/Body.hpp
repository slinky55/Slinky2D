#pragma once

#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Collision/AABB.hpp>

namespace Slinky::Core
{
    class World;
}

namespace Slinky::Collision
{
    struct BodyCfg
    {
        Math::Vector2 pos;
        Math::Vector2 size;
        float mass;
        float restitution;
        float damping;

        BodyCfg(const Math::Vector2& _pos,
                const Math::Vector2& _size,
                float _mass,
                float _restitution,
                float _damping);
    };

    struct Body
    {
        [[nodiscard]] Math::Vector2 Position() const;
        [[nodiscard]] Math::Vector2 Velocity() const;
        [[nodiscard]] Math::Vector2 Acceleration() const;

        [[nodiscard]] Math::Vector2 Size() const;
        [[nodiscard]] Math::Vector2 HalfSize() const;

        [[nodiscard]] float Mass() const;
        [[nodiscard]] float InvMass() const;
        [[nodiscard]] float Restitution() const;
        [[nodiscard]] float Damping() const;

        [[nodiscard]] const AABB& Collider() const;

        void Integrate(float _dt);

        void ApplyForce(const Math::Vector2& _force);
        void ClearForces();

    private:
        friend class Core::World;

        explicit Body(const BodyCfg& _cfg);

        Math::Vector2 pos;
        Math::Vector2 vel {0, 0};
        Math::Vector2 acc {0, 0};

        Math::Vector2 forces;

        Math::Vector2 size;

        float mass;
        float invMass;
        float restitution;
        float damping;

        AABB collider;
    };
}