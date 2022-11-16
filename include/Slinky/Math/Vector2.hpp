
namespace slinky::math
{   
    struct Vector2
    {
        float x {0};
        float y {0};

        Vector2() = default;
        ~Vector2() = default;
        Vector2(float _x,
                float _y);
        Vector2(const Vector2& _other);
        Vector2& operator=(const Vector2& _rhs) = default;
    };

}
