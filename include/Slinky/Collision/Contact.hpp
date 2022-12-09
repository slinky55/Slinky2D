
#include "Slinky/Collision/CCollider.hpp"

#include "Slinky/Math/Vector2.hpp"

namespace Slinky::Collision
{
    struct AABBContact
    {
        Math::Vector2 normal;
        float toi;
    };

    struct Contact
    {
        Math::Vector2 a;
        Math::Vector2 b;

        Math::Vector2 normal;

        float intersection {0.f};
    };

    inline Contact CircleVsCircle(const CCollider& _A,
                                  const CCollider& _B)
    {

    }
}