#pragma once

#include <limits>
#include <algorithm>

#include "Slinky/Collision/Polygon.hpp"

namespace Slinky::Collision
{
    inline Math::Vector2 TripleProduct(const Math::Vector2& _a,
                                       const Math::Vector2& _b,
                                       const Math::Vector2& _c)
    {
        float z { _a.x * _b.y - _a.y * _b.x };
        return Math::Normal({-z * _c.y, z * _c.x});
    }

    inline Math::Vector2 FurthestPoint(const Polygon& _s,
                                       const Math::Vector2& _dir)
    {
        float max { -std::numeric_limits<float>::infinity() };
        Math::Vector2 result;

        for (const auto& v : _s.vertices)
        {
            float projection { v * _dir };

            if (projection > max)
            {
                max = projection;
                result = v;
            }
        }

        return result;
    }

    inline Math::Vector2 Support(const Polygon& _A,
                                 const Polygon& _B,
                                 const Math::Vector2& _d)
    {
        return FurthestPoint(_A, _d) - FurthestPoint(_B, -_d);
    }

    inline bool CheckSimplex(std::vector<Math::Vector2>& _simplex,
                             Math::Vector2& _d)
    {
        // Line
        if (_simplex.size() == 2)
        {
            Math::Vector2 A { _simplex[1]};
            Math::Vector2 B { _simplex[0] };
            Math::Vector2 AB { B - A };
            Math::Vector2 AO { -A };

            _d = TripleProduct(AB, AO, AB);
            return false;
        }
        // Triangle
        else
        {
            Math::Vector2 A { _simplex[2] };
            Math::Vector2 B { _simplex[1] };
            Math::Vector2 C { _simplex[0] };

            Math::Vector2 AB { B - A };
            Math::Vector2 AC { C - A };
            Math::Vector2 AO { -A };

            Math::Vector2 ABPerp { TripleProduct(AC, AB, AB) };
            Math::Vector2 ACPerp { TripleProduct(AB, AC, AC) };

            if (ABPerp * AO > 0)
            {
                _simplex.erase(_simplex.begin());
                _d = ABPerp;
                return false;
            }
            else if (ACPerp * AO > 0)
            {
                _simplex.erase(std::next(_simplex.begin()));
                _d = ACPerp;
                return false;
            }

            return true;
        }
    }

    inline bool GJK(const Polygon& _A,
                    const Polygon& _B)
    {
        constexpr Math::Vector2 ORIGIN { 0, 0 };

        Math::Vector2 d { Math::Normal(_B.center - _A.center) };

        std::vector<Math::Vector2> simplex;
        simplex.emplace_back(Support(_A, _B, d));

        d = Math::Normal( -simplex[0] );

        while (true)
        {
            Math::Vector2 A { Support(_A, _B, d) };

            if (A * d < 0)
            {
                return false;
            }

            simplex.emplace_back(A);

            if (CheckSimplex(simplex, d))
            {
                return true;
            }
        }
    }
}