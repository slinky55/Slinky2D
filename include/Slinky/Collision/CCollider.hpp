#pragma once

#include "Slinky/Math/Vector2.hpp"

namespace Slinky::Collision
{
    struct CCollider
    {
        Math::Vector2 center;
        float radius;
    };

    [[nodiscard]] inline bool Contains(const CCollider& _A,
                                       const CCollider& _B)
    {
        const float distance { Math::Magnitude(_A.center - _B.center) };
        return distance < _A.radius + _B.radius;
    }
    [[nodiscard]] inline bool Contains(const CCollider& _A,
                                       const Math::Vector2& _point)
    {
        const float distance { Math::Magnitude(_A.center - _point) };
        return distance < _A.radius;
    }
    [[nodiscard]] inline bool Intersects(const CCollider& _A,
                                         const CCollider& _B)
    {
        const float distanceSq { Math::MagnitudeSq(_A.center - _B.center) };
        return distanceSq < std::pow(_A.radius + _B.radius, 2);
    }
}