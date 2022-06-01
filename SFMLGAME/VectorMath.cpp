#include "VectorMath.h"

namespace sf
{
    Vector2f Normalize(const Vector2f& vector)
    {
        float length = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
        if (length != 0)
            return Vector2(vector.x / length, vector.y / length);
        else
            return vector;
    }

    float SqrtLength(const Vector2f& vector)
    {
        return (vector.x * vector.x) + (vector.y * vector.y);
    }

    float Length(const Vector2f& vector)
    {
        return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
    }

    float Distance(Vector2f vector, Vector2f vector2)
    {
        vector -= vector2;
        return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
    }
}