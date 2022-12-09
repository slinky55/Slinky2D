#pragma once

#include <vector>

#include "Slinky/Math/Vector2.hpp"

namespace Slinky::Collision
{
    enum class ShapeType
    {
        Circle,
        Line,
        Triangle,
        Rectangle,
        Polygon
    };

    struct Polygon
    {
        Math::Vector2 center;
        std::vector<Math::Vector2> vertices;
    };
}