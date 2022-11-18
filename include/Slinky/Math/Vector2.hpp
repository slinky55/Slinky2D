#pragma once

#include <cmath>

namespace Slinky::Math
{   
    struct Vector2
    {
        float x {0};
        float y {0};

        Vector2() = default;
        Vector2(float _x,
                float _y);

        [[nodiscard]] Vector2 operator+(const Vector2& _rhs) const;
        [[nodiscard]] Vector2 operator-(const Vector2& _rhs) const;
        [[nodiscard]] Vector2 operator*(float _rhs) const;
        [[nodiscard]] Vector2 operator/(float _rhs) const;

        Vector2& operator+=(const Vector2& _rhs);
        Vector2& operator-=(const Vector2& _rhs);
        Vector2& operator*=(float _rhs);
        Vector2& operator/=(float _rhs);

        [[nodiscard]] float Magnitude() const;

        [[nodiscard]] Vector2 Normal() const;
        void Normalize();

        void Zero();
    };

}
