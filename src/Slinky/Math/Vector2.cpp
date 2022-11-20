#include "Slinky/Math/Vector2.hpp"

namespace Slinky::Math
{
    Vector2::Vector2(float _x,
                     float _y)
            :
            x{_x},
            y{_y} {}

    Vector2 Vector2::operator+(const Vector2 &_rhs) const {
        return {x + _rhs.x, y + _rhs.y};
    }
    Vector2 Vector2::operator-(const Vector2 &_rhs) const {
        return {x - _rhs.x, y - _rhs.y};
    }
    Vector2 Vector2::operator*(float _rhs) const {
        return {x * _rhs, y * _rhs};
    }
    Vector2 Vector2::operator/(float _rhs) const {
        return {x / _rhs, y / _rhs};
    }

    float Vector2::operator*(const Vector2& _rhs) const
    {
        return (x * _rhs.x) + (y * _rhs.y);
    }

    Vector2 &Vector2::operator+=(const Vector2 &_rhs) {
        x += _rhs.x;
        y += _rhs.y;

        return *this;
    }
    Vector2 &Vector2::operator-=(const Vector2 &_rhs) {
        x -= _rhs.x;
        y -= _rhs.y;

        return *this;
    }
    Vector2 &Vector2::operator*=(float _rhs) {
        x *= _rhs;
        y *= _rhs;

        return *this;
    }
    Vector2 &Vector2::operator/=(float _rhs) {
        x /= _rhs;
        y /= _rhs;

        return *this;
    }

    float Vector2::Magnitude() const
    {
        return sqrtf(powf(x, 2) + powf(y, 2));
    }

    void Vector2::Normalize()
    {
        *this /= Magnitude();
    }
    Vector2 Vector2::Normal() const
    {
        return (*this / Magnitude());
    }

    void Vector2::Zero()
    {
        x = 0; y = 0;
    }
}

