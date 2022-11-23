#include <Slinky/Collision/Body.hpp>

namespace Slinky::Collision {

    Body::Body(const BodyCfg &_cfg)
            :
            pos{_cfg.pos},
            size{_cfg.size},
            mass{_cfg.mass},
            restitution{_cfg.restitution},
            damping{_cfg.damping},
            collider{_cfg.pos,
                     _cfg.size / 2.f}
    {
        if (mass <= 0.f)
            invMass = 0.f;
        else
            invMass = 1.f / _cfg.mass;
    }

    Math::Vector2 Body::Position() const {
        return pos;
    }
    Math::Vector2 Body::Velocity() const {
        return vel;
    }
    Math::Vector2 Body::Acceleration() const {
        return acc;
    }

    void Body::SetPosition(const Math::Vector2& _pos)
    {
        pos = _pos;
        collider.center = pos;
    }
    void Body::SetVelocity(const Math::Vector2 &_vel)
    {
        vel = _vel;
    }
    void Body::SetAcceleration(const Math::Vector2 &_acc)
    {
        acc = _acc;
    }

    Math::Vector2 Body::Size() const {
        return size;
    }
    Math::Vector2 Body::HalfSize() const
    {
        return size / 2.f;
    }

    float Body::Mass() const {
        return mass;
    }
    float Body::InvMass() const {
        return invMass;
    }
    float Body::Restitution() const {
        return restitution;
    }
    float Body::Damping() const {
        return damping;
    }
    float Body::Rotation() const
    {
        return rotation;
    }

    void Body::SetMass(float _mass)
    {
        mass = _mass;
        invMass = 1.f / _mass;
    }
    void Body::SetRestitution(float _res)
    {
        restitution = _res;
    }
    void Body::SetRotation(float _rot)
    {
        rotation = _rot;
    }

    const AABB &Body::Collider() const {
        return collider;
    }

    void Body::Integrate(float _dt)
    {
        if (invMass <= 0.f ||
            _dt < 0.f)
            return;

        pos += vel * _dt;
        collider.center = pos;

        Math::Vector2 resultingAcc = acc;
        resultingAcc += forces * invMass;
        vel += resultingAcc * _dt;

        vel *= powf(damping, _dt);

        ClearForces();
    }
    void Body::ApplyForce(const Math::Vector2& _force)
    {
        forces += _force;
    }
    void Body::ClearForces()
    {
        forces.Zero();
    }
}