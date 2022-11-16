#include <gtest/gtest.h>

#include <Slinky/Collision/AABB.h>

TEST (AABBTest, Intersection)
{
    using namespace Slinky::Collision;

    AABB box1 {{2, 4}, {2, 2}};
    AABB box2 {{4, 2}, {2, 2}};

    AABB box3 {{2, 4}, {2, 2}};
    AABB box4 {{8, 2}, {2, 2}};

    EXPECT_EQ(true, box1.Intersects(box2)) << "boxes SHOULD intersect";
    EXPECT_EQ(false, box3.Intersects(box4)) << "boxes should NOT intersect";
}