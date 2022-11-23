#include <gtest/gtest.h>

#include <Slinky/Collision/AABB.hpp>

TEST (AABBTest, Intersection)
{
    using namespace Slinky::Collision;

    constexpr float PIXELS_PER_METER {32.f};

    AABB box {
        { 400 / PIXELS_PER_METER, (600 - 45) / PIXELS_PER_METER},
        {16.f / PIXELS_PER_METER, 16.f / PIXELS_PER_METER}
    };

    AABB ground {
        {400.f / PIXELS_PER_METER, (600 - 16) / PIXELS_PER_METER},
        {400 / PIXELS_PER_METER, 16 / PIXELS_PER_METER}
    };

    EXPECT_EQ(true, box.Intersects(ground));

    box.center = { 400 / PIXELS_PER_METER, (600 - 49) / PIXELS_PER_METER};
    EXPECT_EQ(false, box.Intersects(ground));
}