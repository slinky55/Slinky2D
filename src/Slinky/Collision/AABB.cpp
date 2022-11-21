#include "Slinky/Collision/AABB.hpp"

namespace Slinky::Collision
{
    AABB::AABB(const Vector2& _center,
               const Vector2& _hSize)
               :
               center{_center},
               hSize{_hSize}
    {}

    bool AABB::Intersects(const AABB &_other) const
    {
        return (std::fabsf(center.x - _other.center.x) < (hSize.x + _other.hSize.x)) &&
               (std::fabsf(center.y - _other.center.y) < (hSize.y + _other.hSize.y));
    }

    bool AABB::Contains(const AABB &_other) const
    {
        return false;
    }
}