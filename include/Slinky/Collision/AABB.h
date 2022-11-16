#pragma once

#include "Slinky/Math/Vector2.hpp"

using namespace Slinky::Math;

namespace Slinky::Collision
{
    struct AABB
    {
        Vector2 center;
        Vector2 hSize;

        AABB() = default;
        AABB(const Vector2& _center,
             const Vector2& _hSize);

        [[nodiscard]] bool Intersects(const AABB& _other) const;
        [[nodiscard]] bool Contains(const AABB& _other) const;
    };
}