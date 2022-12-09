#pragma once

#include "Slinky/Math/Vector2.hpp"

namespace Slinky::Math
{
    struct Mat2
    {
        Vector2 col1;
        Vector2 col2;

        Mat2() = default;

        Mat2(const Vector2& _col1,
             const Vector2& _col2)
             :
             col1{_col1},
             col2{_col2}
        {}
    };

    inline Mat2 Rotation(float angle)
    {
        float c { std::cos(angle) };
        float s { std::sin(angle) };

        return Mat2(Vector2(c, s), Vector2(-s, c));
    }
    inline Mat2 Transpose(const Mat2& _mat)
    {
        return Mat2 {{_mat.col1.x, _mat.col2.x},
                     {_mat.col1.y, _mat.col2.y}};
    }
    inline Mat2 Invert(const Mat2& _mat)
    {
        float a { _mat.col1.x };
        float b { _mat.col2.x };
        float c { _mat.col1.y };
        float d { _mat.col2.y };

        float det { a * d - b * c };
        if (det == 0) return Mat2{};
        det = 1.0f / det;

        return Mat2 {{det * d, -det * c},
                     {-det * b, det * a}};
    }

    inline Vector2 operator*(const Mat2& _mat,
                             const Vector2& _vec)
    {
        return Vector2{_mat.col1.x * _vec.x + _mat.col2.x * _vec.y,
                       _mat.col1.y * _vec.x + _mat.col2.y * _vec.y};
    }

    inline Mat2 operator*(const Mat2& _mat1,
                          const Mat2& _mat2)
    {
        return Mat2{_mat1 * _mat2.col1,
                    _mat1 * _mat2.col2};
    }
}