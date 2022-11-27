#pragma once

#include "Slinky/Math/Vector2.hpp"
#include "Slinky/Collision/AABB.hpp"

namespace Slinky::Dynamics
{
    struct Body
    {
    public:
        Math::Vector2 position;
        float orientation {0};

        Math::Vector2 linearVelocity;
        float angularVelocity {0};

        Math::Vector2 acc;
        float angularAcc {0};

        Math::Vector2 forces;
        float torque {0};

        Math::Vector2 size;
        Math::Vector2 halfSize;

        float mass {0};
        float invMass {0};
        float invMomentOfInertia {0};

        float restitution {0};

        float linearDamping {0};
        float angularDamping {0};

        Collision::AABB collider;

        /*
         * @param _position: The position of the body
         * @param _orientation: The orientation of the body
         * @param _size: The size of the body
         * @param _mass: The mass of the body
         * @param _restitution: The restitution of the body
         * @param _damping: The damping of the body
         */
        Body(const Math::Vector2& _pos,
             float _orientation,
             const Math::Vector2& _size,
             float _mass,
             float _restitution,
             float _linearDamping,
             float _angularDamping)
             :
             position{_pos},
             orientation{_orientation},
             size{_size},
             halfSize{_size / 2.f},
             mass{_mass},
             invMass{_mass > 0 ? 1.0f / _mass : 0},
             invMomentOfInertia{1.f / ((_mass / 12.f) *
                                      ((_size.x * _size.x) + (_size.y * _size.y) ))},
             restitution{_restitution},
             linearDamping{_linearDamping},
             angularDamping{_angularDamping},
             collider{_pos, _size / 2.f}
        {}
    };

    inline void ClearForces(Body* _body)
    {
        _body->forces.Zero();
    }

    inline void  IntegrateBody(Body* _body,
                              float _dt)
    {
        if (_body->invMass <= 0.f ||
            _dt < 0.f)
            return;

        _body->position += _body->linearVelocity * _dt;
        _body->collider.center = _body->position;
        _body->orientation += _body->angularVelocity * _dt;

        _body->linearVelocity += _body->forces * (_body->invMass * _dt);
        _body->angularVelocity += _body->torque * (_body->invMomentOfInertia * _dt);

        _body->linearVelocity *= powf(_body->linearDamping, _dt);
        _body->angularVelocity *= powf(_body->angularDamping, _dt);
    }

    inline void ApplyForceToCM(Body* _body,
                               const Math::Vector2& _force)
    {
        _body->forces += _force;
    }

    inline void ApplyForceToPoint(Body* _body,
                                  const Math::Vector2& _point,
                                  const Math::Vector2& _force)
    {
        Math::Vector2 r { _point - _body->position };
        r = { -r.y, r.x };
        _body->forces += _force;
        _body->torque += r * _force;
    }
}