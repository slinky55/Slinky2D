#pragma once

#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Collision/AABB.hpp>

namespace Slinky::Collision
{
    struct BodyCfg
    {
        Math::Vector2 pos;
        Math::Vector2 size;
        float mass;
        float restitution;
        float damping;
    };

    class Body
    {
    public:
        explicit Body(const BodyCfg& _cfg);

        [[nodiscard]] Math::Vector2 Position() const;
        [[nodiscard]] Math::Vector2 Velocity() const;
        [[nodiscard]] Math::Vector2 Acceleration() const;

        void SetPosition(const Math::Vector2& _pos);
        void SetVelocity(const Math::Vector2& _vel);
        void SetAcceleration(const Math::Vector2& _acc);

        [[nodiscard]] Math::Vector2 Size() const;
        [[nodiscard]] Math::Vector2 HalfSize() const;

        [[nodiscard]] float Mass() const;
        [[nodiscard]] float InvMass() const;
        [[nodiscard]] float Restitution() const;
        [[nodiscard]] float Damping() const;
        [[nodiscard]] float Rotation() const;

        void SetMass(float _mass);
        void SetRestitution(float _res);
        void SetRotation(float _rot);

        [[nodiscard]] const AABB& Collider() const;

        void Integrate(float _dt);

        void ApplyForce(const Math::Vector2& _force);
        void ClearForces();

    private:
        Math::Vector2 pos;
        Math::Vector2 vel {0, 0};
        Math::Vector2 acc {0, 0};

        Math::Vector2 forces;

        Math::Vector2 size;

        float mass;
        float invMass;
        float restitution;
        float damping;
        float rotation;

        AABB collider;
    };
}