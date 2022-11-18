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
        if ( fabsf(_other.center.x - center.x) < hSize.x + _other.hSize.x &&
             fabsf(_other.center.y - center.y) < hSize.y + _other.hSize.y)
        {
            return true;
        }
        return false;
    }

    bool AABB::Contains(const AABB &_other) const
    {
        return false;
    }
}