#include <gtest/gtest.h>

#include <Slinky/Math/Vector2.hpp>
#include <Slinky/Collision/Algorithms.hpp>
#include <Slinky/Collision/Polygon.hpp>

TEST (GJKTest, BoxVsBox)
{
    using namespace Slinky::Collision;
    using namespace Slinky::Math;

    Polygon box1;
    box1.vertices.push_back({4, 1});
    box1.vertices.push_back({4, 3});
    box1.vertices.push_back({6, 3});
    box1.vertices.push_back({6, 1});

    Polygon box2;
    box2.vertices.push_back({5, 2});
    box2.vertices.push_back({5, 4});
    box2.vertices.push_back({7, 4});
    box2.vertices.push_back({7, 2});

    EXPECT_TRUE(GJK(box1, box2));
}
TEST (GJKTest, BoxVsTriangle)
{
    using namespace Slinky::Collision;
    using namespace Slinky::Math;

    Polygon box;
    box.vertices.push_back({3, 6.75});
    box.vertices.push_back({3, 8});
    box.vertices.push_back({4.25, 8});
    box.vertices.push_back({4.25, 6.75});

    Polygon triangle;
    triangle.vertices.push_back({4, 7});
    triangle.vertices.push_back({6, 7});
    triangle.vertices.push_back({5, 5});

    EXPECT_TRUE(GJK(box, triangle));
}
