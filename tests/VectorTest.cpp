#include <gtest/gtest.h>

#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Collision/Algorithms.hpp>

TEST (VectorTest, TripleProduct)
{
    using namespace Slinky::Collision;
    using namespace Slinky::Math;

    Vector2 res { TripleProduct({5, -4}, {4, -1}, {5, -4}) };
    Vector2 ex { 44, 55 };

    EXPECT_EQ(res.x, ex.x);
    EXPECT_EQ(res.y, ex.y);
}
