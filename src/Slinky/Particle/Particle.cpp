#include <Slinky/Particle/Particle.hpp>

namespace Slinky::Particle
{
    ParticleCfg::ParticleCfg(const Math::Vector2& _pos,
                             float _radius,
                             float _mass,
                             float _restitution,
                             float _damping,
                             float _lifetime)
            :
            pos{_pos},
            mass{_mass},
            restitution{_restitution},
            damping{_damping},
            radius{_radius},
            lifetime{_lifetime}
    {}

    Particle::Particle(const ParticleCfg &_cfg)
            :
            pos{_cfg.pos},
            mass{_cfg.mass},
            invMass{1.f / _cfg.mass},
            restitution{_cfg.restitution},
            damping{_cfg.damping},
            radius{_cfg.radius},
            lifetime{_cfg.lifetime}
    {
        if (_cfg.mass <= 0)
            invMass = 0.f;
    }

    Math::Vector2 Particle::Position() const
    {
        return pos;
    }
    Math::Vector2 Particle::Velocity() const
    {
        return vel;
    }
    Math::Vector2 Particle::Acceleration() const
    {
        return acc;
    }

    void Particle::SetPosition(const Math::Vector2 &_pos)
    {
        pos = _pos;
    }
    void Particle::SetVelocity(const Math::Vector2 &_vel)
    {
        vel = _vel;
    }
    void Particle::SetAcceleration(const Math::Vector2 &_acc)
    {
        acc = _acc;
    }

    float Particle::Mass() const
    {
        return mass;
    }
    float Particle::InvMass() const
    {
        return invMass;
    }
    float Particle::Restitution() const
    {
        return restitution;
    }
    float Particle::Damping() const
    {
        return damping;
    }
    float Particle::Radius() const
    {
        return radius;
    }

    float Particle::Lifetime() const
    {
        return lifetime;
    }
    void Particle::Integrate(float _dt)
    {
        if (invMass <= 0.f ||
            _dt < 0.f)
            return;

        pos += vel * _dt;
        acc += forces * invMass;
        vel += acc * _dt;

        vel *= powf(damping, _dt);

        lifetime -= _dt;
    }
    void Particle::ApplyForce(const Math::Vector2 &_force)
    {
        forces += _force;
    }
    void Particle::ClearForces()
    {
        acc.Zero();
    }
}