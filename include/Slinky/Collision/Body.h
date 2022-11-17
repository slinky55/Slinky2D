
#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Collision/AABB.h>

namespace Slinky::Collision
{
    struct Body
    {
        Math::Vector2 pos;
        Math::Vector2 vel;
        Math::Vector2 acc;

        Math::Vector2 size;

        float restitution;
        float mass;
        float invMass;

        AABB collider;

    private:
        friend class PhysicsWorld;

        Body();

        Body(const Math::Vector2& _pos,
             const Math::Vector2& _size,
             float _mass,
             float restitution);
    };
}