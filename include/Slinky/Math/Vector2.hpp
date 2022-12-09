#pragma once

#include <cmath>

namespace Slinky::Math
{   
    struct Vector2 {
        float x{0};
        float y{0};

        constexpr Vector2() noexcept = default;

        constexpr Vector2(float _x,
                          float _y) noexcept
                :
                x{_x},
                y{_y} {}

        [[nodiscard]] constexpr Vector2 operator+(const Vector2 &_rhs) const {
            return {x + _rhs.x, y + _rhs.y};
        }
        [[nodiscard]] constexpr Vector2 operator-(const Vector2 &_rhs) const {
            return {x - _rhs.x, y - _rhs.y};
        }
        [[nodiscard]] constexpr Vector2 operator*(float _rhs) const {
            return {x * _rhs, y * _rhs};
        }
        [[nodiscard]] constexpr Vector2 operator/(float _rhs) const {
            return {x / _rhs, y / _rhs};
        }
        [[nodiscard]] constexpr Vector2 operator-() const {
            return {-x, -y};
        }

        // dot product
        [[nodiscard]] constexpr float operator*(const Vector2 &_rhs) const {
            return x * _rhs.x + y * _rhs.y;
        }

        constexpr Vector2 &operator+=(const Vector2 &_rhs) {
            x += _rhs.x;
            y += _rhs.y;
            return *this;
        }
        constexpr Vector2 &operator-=(const Vector2 &_rhs) {
            x -= _rhs.x;
            y -= _rhs.y;
            return *this;
        }
        constexpr Vector2 &operator*=(float _rhs) {
            x *= _rhs;
            y *= _rhs;
            return *this;
        }
        constexpr Vector2 &operator/=(float _rhs)
        {
            x /= _rhs;
            y /= _rhs;
            return *this;
        }
    };

    inline float Magnitude(const Vector2& _vector)
    {
        return std::sqrt(_vector.x * _vector.x + _vector.y * _vector.y);
    }
    inline float MagnitudeSq(const Vector2& _vector)
    {
        return _vector.x * _vector.x + _vector.y * _vector.y;
    }

    inline Vector2 Normal(const Vector2& _vector)
    {
        return _vector / Magnitude(_vector);
    }
    inline void Normalize(Vector2& _vector)
    {
        _vector /= Magnitude(_vector);
    }

    inline float Cross(const Vector2& _a,
                       const Vector2& _b)
    {
        return _a.x * _b.y - _a.y * _b.x;
    }
    inline Vector2 Cross(const Vector2& _a,
                         float _scalar)
    {
        return Vector2(_scalar * _a.y, -_scalar * _a.x);
    }

    constexpr Vector2 ZERO {0, 0};
}
