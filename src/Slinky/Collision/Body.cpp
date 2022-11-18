#include <Slinky/Collision/Body.hpp>

namespace Slinky::Collision
{
    BodyCfg::BodyCfg(const Math::Vector2& _pos,
                     const Math::Vector2& _size,
                     float _mass,
                     float _restitution)
            :
            pos{_pos},
            size{_size},
            mass{_mass},
            restitution{_restitution}
    {}

    Body::Body(const BodyCfg& _cfg)
        :
        pos{_cfg.pos},
        size{_cfg.size},
        mass{_cfg.mass},
        invMass{1.f / _cfg.mass},
        restitution{_cfg.restitution},
        collider{_cfg.pos,
                 _cfg.size / 2.f}
    {}

    Math::Vector2 Body::Position() const
    {
        return pos;
    }
    Math::Vector2 Body::Velocity() const
    {
        return vel;
    }
    Math::Vector2 Body::Acceleration() const
    {
        return acc;
    }

    Math::Vector2 Body::Size() const
    {
        return size;
    }
    Math::Vector2 Body::HalfSize() const
    {
        return size / 2.f;
    }

    float Body::Mass() const
    {
        return mass;
    }
    float Body::InvMass() const
    {
        return invMass;
    }
    float Body::Restitution() const
    {
        return restitution;
    }

    const AABB& Body::Collider() const
    {
        return collider;
    }

    void Body::ApplyForce(const Math::Vector2& _force)
    {
        acc += _force * invMass;
    }

    void Body::ClearForces()
    {
        acc.Zero();
    }
}