#pragma once

#include "Slinky/Math/Vector2.hpp"

namespace Slinky::Collision
{
    struct CCollider
    {
        Math::Vector2 center;
        float radius;
    };
}