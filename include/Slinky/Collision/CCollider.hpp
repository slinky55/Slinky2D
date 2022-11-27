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
        const float distance = (_A.center - _B.center).Magnitude();
        return distance < _A.radius + _B.radius;
    }

    [[nodiscard]] inline bool Contains(const CCollider& _A,
                                       const Math::Vector2& _point)
    {
        const float distance = (_A.center - _point).Magnitude();
        return distance < _A.radius;
    }

    [[nodiscard]] inline float CircleVsCircle(const CCollider& _A,
                                              const CCollider& _B)
    {
        const float distance = (_A.center - _B.center).Magnitude();
        return (_A.radius + _B.radius) - distance;
    }
}