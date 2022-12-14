#pragma once

#include <optional>
#include <limits>

#include "Slinky/Collision/Contact.hpp"

#include "Slinky/Math/Vector2.hpp"

namespace Slinky::Collision
{
    struct AABB
    {
        Math::Vector2 center;
        Math::Vector2 hSize;

        AABB() = default;
    };

    [[nodiscard]] inline std::optional<Math::Vector2> AABBvsAABB(const AABB& _A,
                                                                 const AABB& _B)
    {
        Math::Vector2 intersection {
                (_A.hSize.x + _B.hSize.x) - std::fabs(_A.center.x - _B.center.x),
                (_A.hSize.y + _B.hSize.y) - std::fabs(_A.center.y - _B.center.y)
        };

        if (intersection.x < 0.f ||
            intersection.y < 0.f)
            return std::nullopt;

        return intersection;
    }

    [[nodiscard]] inline bool Contains(const AABB& _A,
                                       const AABB& _B)
    {
        return (_A.center.x - _A.hSize.x <= _B.center.x - _B.hSize.x) &&
               (_A.center.x + _A.hSize.x >= _B.center.x + _B.hSize.x) &&
               (_A.center.y - _A.hSize.y <= _B.center.y - _B.hSize.y) &&
               (_A.center.y + _A.hSize.y >= _B.center.y + _B.hSize.y);
    }

    [[nodiscard]] inline bool Contains(const AABB& _A,
                                       const Math::Vector2& _point)
    {
        return (_A.center.x - _A.hSize.x <= _point.x) &&
               (_A.center.x + _A.hSize.x >= _point.x) &&
               (_A.center.y - _A.hSize.y <= _point.y) &&
               (_A.center.y + _A.hSize.y >= _point.y);
    }
}